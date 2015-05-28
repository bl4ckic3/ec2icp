#include <stdio.h>
#include "stdlib.h"
#include "string.h"
#include "icp.h"
#include "icp_config.h"
#include "topics.h"
#include "mqtt.h"
#include "dbg.h"

volatile MQTTAsync 			*p_client;
char						*sim_topic;
char						*sim_dbg_topic;

struct timespec orwl_gettime(void)  {
  // be more careful in a multithreaded environement
  if (!orwl_timestart) {
    mach_timebase_info_data_t tb = { 0 };
    mach_timebase_info(&tb);
    orwl_timebase = tb.numer;
    orwl_timebase /= tb.denom;
    orwl_timestart = mach_absolute_time();
  }
  struct timespec t;
  double diff = (mach_absolute_time() - orwl_timestart) * orwl_timebase;
  t.tv_sec = diff * ORWL_NANO;
  t.tv_nsec = diff - (t.tv_sec * ORWL_GIGA);
  return t;
}

static char result[64];

char *gettime_s(void) {
  struct timespec t = orwl_gettime();
  sprintf(result, "%lu.%09lu sec", t.tv_sec, t.tv_nsec);
  sprintf(result, "");
  return result;
}

icp_time_t local_time_ms;
int32_t local_time_ns;

icp_time_t gettime(void) {
  struct timespec t = orwl_gettime();
  local_time_ns = (t.tv_sec / ORWL_GIGA) + t.tv_nsec;
  local_time_ms = (icp_time_t) (local_time_ns * ORWL_NANO2MILLI);
  return local_time_ms;
}

void synctime(void) {
	LOG_INFO("Reseting time");
	orwl_timebase = 0.0;
	orwl_timestart = 0;
	mach_timebase_info_data_t tb = { 0 };
    mach_timebase_info(&tb);
    orwl_timebase = tb.numer;
    orwl_timebase /= tb.denom;
    orwl_timestart = mach_absolute_time();
	LOG_INFO("Time reset!");
    return;
}

#ifdef SYSDEBUG
bool_t g_sys_enable_debug_output = TRUE;
bool_t g_sys_enable_err_output= TRUE;
bool_t g_sys_enable_warn_output= TRUE;
bool_t g_sys_enable_info_output= TRUE;
uint8_t sys_enable_debug_output( uint8_t enabled ) {
    LOG_INFO("Setting g_sys_enable_debug_output to %d", enabled);
    g_sys_enable_debug_output = enabled;
    return 0;
}
uint8_t sys_enable_err_output( uint8_t enabled ) {
    LOG_INFO("Setting g_sys_enable_err_output to %d", enabled);
    g_sys_enable_err_output = enabled;
    return 0;
}
uint8_t sys_enable_warn_output( uint8_t enabled ) {
    LOG_INFO("Setting g_sys_enable_warn_output to %d", enabled);
    g_sys_enable_warn_output = enabled;
    return 0;
}
uint8_t sys_enable_all_output( uint8_t enabled ) {
    sys_enable_debug_output( enabled );
    sys_enable_err_output( enabled );
    sys_enable_warn_output( enabled );
    sys_enable_info_output( enabled );
    return 0;
}
uint8_t sys_enable_info_output( uint8_t enabled ) {
    LOG_INFO("Setting g_sys_enable_info_output to %d", enabled);
    g_sys_enable_info_output = enabled;
    return 0;
}
#else
uint8_t sys_enable_debug_output( uint8_t enabled ) { return 0;}
uint8_t sys_enable_err_output( uint8_t enabled ) { return 0;}
uint8_t sys_enable_warn_output( uint8_t enabled ) { return 0;}
uint8_t sys_enable_info_output( uint8_t enabled ) { return 0;}
uint8_t sys_enable_all_output( uint8_t enabled ) { return 0;}
#endif



int main( int argc, const char* argv[] ){
	MQTTAsync 					client;
	MQTTAsync_connectOptions 	conn_opts = MQTTAsync_connectOptions_initializer;
	MQTTAsync_disconnectOptions disc_opts = MQTTAsync_disconnectOptions_initializer;
	MQTTAsync_message 			pubmsg 	  = MQTTAsync_message_initializer;

	int 			rc = ICP_SUCCESS;
	char 			str[128];
	char 			topic[128];
	char 			ch = 'a';
	char 			cmd[128] = "";
	char 			sub_cmd[8][8];
	char 			*pch;
	int 			i;

	mac_addr_t 		receiver;

	printf("\n\n\n\n\n");

	// MQTT setup, connection and subscribe's
	MQTTAsync_create(&client, ADDRESS, mac_addrs[local_mac_addr], MQTTCLIENT_PERSISTENCE_NONE, NULL);
	MQTTAsync_setCallbacks(client, NULL, connlost, msgarrvd, NULL);
	
	p_client = &client;
	CHECK_MEM(p_client);
	mqtt_enable_debug_output(TRUE);

	conn_opts.keepAliveInterval = 20;
	conn_opts.cleansession = 1;
	conn_opts.onSuccess = onConnect;
	conn_opts.onFailure = onConnectFailure;
	conn_opts.context = client;
	if ((rc = MQTTAsync_connect(client, &conn_opts)) != MQTTASYNC_SUCCESS){
		MQTT_DEBUG("Failed to start connect, return code %d\n", rc);
		exit(-1);	
	}
	while	(!connected);

	// CHECK_ERR(print_packet(NULL) == -1, "failed with p_packet=NULL");
	// CHECK_ERR(print_packet(&packet) == 0, "failed with valid args");

 // 	CHECK_ERR(icp_bytes_out_cb( (const uint8_t *)NULL, 10, NULL) == 0, "failed with output_byte_array=NULL");
 // 	CHECK_ERR(icp_bytes_out_cb( (const uint8_t *)str, 0, NULL) == 0, "failed with array_len=0");

 // 	strcpy(str, "Hello");
 // 	CHECK_ERR(icp_bytes_out_cb( (const uint8_t *)str, 10, NULL) == 0, "failed with array_len:10!=strlen(output_byte_array):%s", str);

 // 	strcpy(str, "Hello");
 // 	CHECK_ERR(icp_bytes_out_cb( (const uint8_t *)str, strlen(str), NULL) == strlen(str), "failed with valid args");
   
	// CHECK_ERR(icp_packet_received_cb(NULL, NULL) == -1, "failed with p_packet=NULL");
	// CHECK_ERR(icp_packet_received_cb(&packet, NULL) == 0, "failed with valid args");

	// CHECK_ERR(icp_error_cb(ICP_SUCCESS, packet.data, packet.data_length, NULL) == -1, "failed with invalid packet");
	// packet.data = (uint8_t *)&str;
	// CHECK_ERR(icp_error_cb(ICP_SUCCESS, packet.data, packet.data_length, NULL) == 0, "failed with valid args");

	// while(TRUE);

	if (finished)
		goto exit;

if (FALSE) {
	LOG_INFO("Sending clean...");
	sent = FALSE;
	strcpy(str, "clean");
	strcpy(topic, topic_names[TOPIC_SIMULATOR_BASE]);
	pubmsg.payload = (char*)str;
	pubmsg.payloadlen = strlen(str);
	pubmsg.qos = QOS;
	pubmsg.retained = 0;
	sendmsg(client, topic, &pubmsg);
	while (!sent)
		;

	LOG_INFO("Sending 'eps' to pc...");
	sent = FALSE;
	strcpy(str, "eps");
	strcpy(topic, topic_names[TOPIC_SIMULATOR_BASE]);
	strcat(topic, mac_addrs[NODE_PC]);
	pubmsg.payload = (char*)str;
	pubmsg.payloadlen = strlen(str);
	pubmsg.qos = QOS;
	pubmsg.retained = 0;
	sendmsg(client, topic, &pubmsg);
	while (!sent)
		;

	LOG_INFO("Sending 'cdhs' to cam...");
	sent = FALSE;
	strcpy(str, "cdhs");
	strcpy(topic, topic_names[TOPIC_SIMULATOR_BASE]);
	strcat(topic, mac_addrs[NODE_CAM]);
	pubmsg.payload = (char*)str;
	pubmsg.payloadlen = strlen(str);
	pubmsg.qos = QOS;
	pubmsg.retained = 0;
	sendmsg(client, topic, &pubmsg);
	while (!sent)
		;

	LOG_INFO("Sending 'pc' to cdhs...");
	sent = FALSE;
	strcpy(str, "pc");
	strcpy(topic, topic_names[TOPIC_SIMULATOR_BASE]);
	strcat(topic, mac_addrs[NODE_CDHS]);
	pubmsg.payload = (char*)str;
	pubmsg.payloadlen = strlen(str);
	pubmsg.qos = QOS;
	pubmsg.retained = 0;
	sendmsg(client, topic, &pubmsg);
	while (!sent)
		;

	LOG_INFO("Sending 'cdhs' to eps...");
	sent = FALSE;
	strcpy(str, "cdhs");
	strcpy(topic, topic_names[TOPIC_SIMULATOR_BASE]);
	strcat(topic, mac_addrs[NODE_EPS]);
	pubmsg.payload = (char*)str;
	pubmsg.payloadlen = strlen(str);
	pubmsg.qos = QOS;
	pubmsg.retained = 0;
	sendmsg(client, topic, &pubmsg);
	while (!sent)
		;

	LOG_INFO("Sending update...");
	sent = FALSE;
	strcpy(str, "update");
	strcpy(topic, topic_names[TOPIC_SIMULATOR_BASE]);
	pubmsg.payload = (char*)str;
	pubmsg.payloadlen = strlen(str);
	pubmsg.qos = QOS;
	pubmsg.retained = 0;
	sendmsg(client, topic, &pubmsg);
	while (!sent)
		;
}

	LOG_INFO("Running...");

	while (TRUE) {
		ch = getchar();

		if (strncmp(&ch, "\n", 1) != 0) {
			strcat(cmd, &ch);
		} else {
			LOG_INFO("Got cmd: %s", cmd);

		  	pch = strtok (cmd," ");
		  	i = 0;
		  	while (pch != NULL)
		  	{
		    	strcpy(sub_cmd[i++], pch);
		    	DEBUG("sub_cmd[%d] = %s - %s", i-1, sub_cmd[i-1], (strncmp(sub_cmd[i-1], "set", 3) == 0 ? "TRUE" : "FALSE"));
		    	pch = strtok (NULL, " ");
		  	}

			receiver = INVALID_MAC_ADDR;
			if ( strncmp(sub_cmd[0], "cam", 3) == 0 ) {
				receiver = NODE_CAM;
			} else if ( strncmp(sub_cmd[0], "cdhs", 4) == 0 ) {
				receiver = NODE_CDHS;
			} else if ( strncmp(sub_cmd[0], "pc", 2) == 0 ) {
				receiver = NODE_PC;
			} else if ( strncmp(sub_cmd[0], "eps", 3) == 0 ) {
				receiver = NODE_EPS;
			} else if ( strncmp(sub_cmd[0], "test", 4) == 0 ) {
				receiver = NODE_TEST;
			} else if ( strncmp(sub_cmd[0], "bus", 3) == 0 ) {
				receiver = NODE_BUS;
			} else if ( strncmp(sub_cmd[0], "all", 4) == 0 ) {
				receiver = BROADCAST;
			} 

			strcpy(topic, topic_names[TOPIC_SIMULATOR_BASE]);

			if (receiver != INVALID_MAC_ADDR && receiver != BROADCAST) {
				strcat(topic, mac_addrs[receiver]);
			}

			if (strncmp(sub_cmd[0], "q", 1) == 0) {
				LOG_INFO("Quiting...");
				break;
			} else if (strlen(cmd) == 0) {
				LOG_INFO("Empty cmd...");
				goto end;
			}else if (strncmp(sub_cmd[0], "clean", 5) == 0 ||
				strncmp(sub_cmd[0], "update", 6) == 0 ||
				strncmp(sub_cmd[0], "reset", 5) == 0 ||
				strncmp(sub_cmd[0], "stopupdate", 10) == 0 ||
				strncmp(sub_cmd[0], "sync", 4) == 0 ||
				strncmp(sub_cmd[0], "time", 4) == 0) {
				LOG_INFO("Sending '%s' to all.", sub_cmd[0]);
				sent = FALSE;
				strcpy(str, sub_cmd[0]);
				if (strncmp(sub_cmd[0], "sync", 4) == 0) {
					synctime();
				}
			} else if (strncmp(sub_cmd[1], "clean", 5) == 0 ||
				strncmp(sub_cmd[1], "update", 6) == 0||
				strncmp(sub_cmd[1], "stopupdate", 10) == 0 ||
				strncmp(sub_cmd[1], "reset", 5) == 0 ||
				strncmp(sub_cmd[1], "time", 4) == 0) {
				CHECK_EXIT(receiver != NUM_OF_NODES, "Invalid receiver.");
				LOG_INFO("Sending '%s' to %s.", sub_cmd[1], mac_addrs[receiver]);
				strcpy(str, sub_cmd[1]);
			}else if (strncmp(sub_cmd[1], "ping", 4) == 0 ) {
				CHECK_EXIT(receiver != NUM_OF_NODES, "Invalid receiver.");

				if ( strncmp(sub_cmd[2], "cdhs", 4) == 0 ||
					 strncmp(sub_cmd[2], "cam", 3)  == 0 ||
					 strncmp(sub_cmd[2], "pc", 2)   == 0 ||
					 strncmp(sub_cmd[2], "eps", 3)  == 0 ||
					 strncmp(sub_cmd[2], "bus", 3)  == 0 ) {
					LOG_INFO("Sending '%s' to %s...", sub_cmd[2], mac_addrs[receiver]);
				} else {
					LOG_INFO("Failed to cmd to send.")
					goto fail;
				}

				strcpy(str, sub_cmd[2]);
			}else if (strncmp(sub_cmd[1], "set", 3) == 0 ) {
				CHECK_EXIT(receiver != INVALID_MAC_ADDR, "Invalid receiver.");

				if ( (strncmp(sub_cmd[2], "icp", 3) == 0 ||
					 strncmp(sub_cmd[2], "mqtt", 4)  == 0 ||
					 strncmp(sub_cmd[2], "sys", 3)   == 0 ||
					 strncmp(sub_cmd[2], "all", 3)   == 0) &&
					(strncmp(sub_cmd[3], "debug", 5) == 0 ||
					 strncmp(sub_cmd[3], "err", 3)  == 0 ||
					 strncmp(sub_cmd[3], "warn", 4)   == 0 ||
					 strncmp(sub_cmd[3], "info", 4)   == 0 ||
					 strncmp(sub_cmd[3], "all", 3)   == 0) &&
					(strncmp(sub_cmd[4], "true", 4) == 0 ||
					 strncmp(sub_cmd[4], "false", 5)  == 0)) {
					LOG_INFO("Sending '%s %s %s %s' to %s...", sub_cmd[1], sub_cmd[2], sub_cmd[3], sub_cmd[4], mac_addrs[receiver]);
					strcpy(str, sub_cmd[1]);
					strcat(str, " ");
					strcat(str, sub_cmd[2]);
					strcat(str, " ");
					strcat(str, sub_cmd[3]);
					strcat(str, " ");
					strcat(str, sub_cmd[4]);
				} else /*if ( (strncmp(sub_cmd[2], "icp", 3) == 0 ||
					 strncmp(sub_cmd[2], "mqtt", 4)  == 0 ||
					 strncmp(sub_cmd[2], "sys", 3)   == 0) &&
					(strncmp(sub_cmd[3], "debug", 5) == 0 ||
					 strncmp(sub_cmd[3], "err", 3)  == 0 ||
					 strncmp(sub_cmd[3], "warn", 4)   == 0 ||
					 strncmp(sub_cmd[3], "info", 4)   == 0) &&
					(strncmp(sub_cmd[4], "true", 4) == 0 ||
					 strncmp(sub_cmd[4], "false", 5)  == 0)) {
					LOG_INFO("Sending '%s %s %s %s' to %s...", sub_cmd[1], sub_cmd[2], sub_cmd[3], sub_cmd[4], mac_addrs[receiver]);
				 */{
					LOG_WARN("Failed to send cmd.")
					LOG_INFO("command example: [eps|pc|...|all] set [icp|sys|mqtt|all] [debug|err|warn|info|all] [true|false]");
					goto fail;
				}

			} else {
				goto fail;
			}
			sent = FALSE;
			pubmsg.payload = (char*)str;
			pubmsg.payloadlen = strlen(str);
			pubmsg.qos = QOS;
			pubmsg.retained = 0;
			LOG_INFO("Sending '%s' to '%s'", str, topic);
			sendmsg(client, topic, &pubmsg);
			while (!sent)
				;
		fail:
		end:
			LOG_INFO("Clearing cmd buffer.");
			strcpy(cmd, "");
			for(i=0;i<8;i++)
		  	{
		    	strcpy(sub_cmd[i], "");
		  	}
		}
	}

	disc_opts.onSuccess = onDisconnect;
	if ((rc = MQTTAsync_disconnect(client, &disc_opts)) != MQTTASYNC_SUCCESS){
		MQTT_LOG_ERR("Failed to start disconnect, return code %d\n", rc);
		exit(-1);	
	}
 	while	(!connected);

error:

exit:
	MQTTAsync_destroy(&client);
 	return rc;
}
