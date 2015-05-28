#include <stdio.h>
#include <unistd.h>
#include "stdlib.h"
#include "string.h"
#include "icp.h"
#include "topics.h"
#include "mqtt.h"
#include "dbg.h"

volatile MQTTAsync 			*p_client;

/**
 * Print out the packet content.
 * @param p_packet Pointer to the packet.
 */
uint8_t print_packet( icp_packet_t *p_packet ) {
	int i = 0;

	if (p_packet == NULL) {
		SENTINEL("Packet is NULL");
	}
	
	printf("Packet content:\n");
	printf("   destination[%02X]:\t%s\n", p_packet->destination, mac_addrs[p_packet->destination]);
	printf("        source[%02X]:\t%s\n", p_packet->source, mac_addrs[p_packet->source]);
	printf("            received:\t%hu\n", p_packet->receive_timestamp);
	printf("  data_len[%02X %02X]:\t%d\n", p_packet->data_length >> 8, (uint8_t)(p_packet->data_length & 0x00FF), p_packet->data_length);
	printf("               data:\t");
	for (i=0; i < p_packet->data_length+1; i++) {
		putchar( i ? ' ': '[' );
		printf("%02X", p_packet->data[i]);
	}
	printf("] \"");
	for (i=0; i < p_packet->data_length+1; i++) {
		putchar( p_packet->data[i] );
	}
	puts("\"");

	return 0;

error:
	return -1;
	
}

uint8_t icp_bytes_out_cb( const uint8_t* output_byte_array, buf_index_t array_len ) {
	int i = 0;
	MQTTAsync_message pubmsg = MQTTAsync_message_initializer;
	sent = FALSE;
	
	ICP_CHECK_MEM(output_byte_array);
	ICP_CHECK_WARN(array_len != 0, "array_len, 0")


	ICP_LOG_INFO("Outputting %d bytes", array_len);
	ICP_DEBUG_({
		printf("[ ");
		for (i=0; i < array_len; i++) {
			printf("%02X ", output_byte_array[i]);
		}
		puts("]");
	});
	pubmsg.payload = (char*)output_byte_array;
	pubmsg.payloadlen = array_len;
	pubmsg.qos = QOS;
	pubmsg.retained = 0;

	ICP_CHECK_MEM(p_client);
	sendmsg(*p_client, topic_names[TOPIC_PRIM_RS485], &pubmsg);

	while(!sent);

	icp_notify_bytes_out_finished();

	ICP_DEBUG("Returning: %d", array_len);
	return array_len;

error:
	return 0;
}

uint8_t icp_packet_received_cb( icp_packet_t *new_packet ) {
	ICP_CHECK_MEM(new_packet);
	print_packet( new_packet );
	return 0;
error:
	return -1;
}

uint8_t icp_error_cb( icp_error_t error, uint8_t* packet_data, buf_index_t packet_length ) {
	char error_names[][50] = {"ICP_SUCCESS", "ICP_BUSY", "ICP_INVALID_PARAMETERS", "ICP_TOO_SHORT_PACKET", "ICP_TOO_SHORT_PAYLOAD", "ICP_ESCAPE_ERROR", "ICP_FAWLTY_CHECKSUM", "ICP_WRONG_RECIPIENT", "ICP_QUEUE_FULL", "ICP_GOT_NACK", "ICP_PACKET_RECEIVED_OUT_OF_ORDER", "ICP_PACKET_COULD_NOT_BE_DELIVERED", "ICP_QUEUE_LOCKED"};
	
	ICP_CHECK_MEM(packet_data);
	ICP_CHECK_WARN(packet_length != 0, "packet_length, 0");

	if (error >= NUM_OF_ERROR_CODES){
		ICP_LOG_ERR("Unknown error : %d", error);
	}
	else{
		ICP_LOG_ERR("%s", error_names[error]);
	}
	return 0;

error:
	return -1;
}

icp_time_t icp_get_time_cb( void ) {
	return 1;
}

uint8_t icp_notify_packet_ack_cb( void ) {
	// MQTTAsync_message pubmsg = MQTTAsync_message_initializer;
	// char str[64] = "ACTIVE by ";
	// strcat (str, mac_addrs[local_mac_addr]);
	// uint8_t timeout = 0;
	// sent = FALSE;

	// pubmsg.payload = (char*)str;
	// pubmsg.payloadlen = strlen(str);
	// pubmsg.qos = QOS;
	// pubmsg.retained = 0;

	// sendmsg(*p_client, topic_names[TOPIC_PRIM_ACCESS_OUT], &pubmsg);

	// while (g_access == INACTIVE && timeout < 10){
	// 	sleep(1);
	// 	timeout++; // TODO should this be part of ICP ??
	// }

	LOG_INFO("I got ACK. My last packet has been transmitted");

	return ICP_SUCCESS;
}

uint8_t icp_set_access_sig_cb( void ) {
	MQTTAsync_message pubmsg = MQTTAsync_message_initializer;
	char str[64] = "ACTIVE by ";
	strcat (str, mac_addrs[local_mac_addr]);
	uint8_t timeout = 0;
	sent = FALSE;

	pubmsg.payload = (char*)str;
	pubmsg.payloadlen = strlen(str);
	pubmsg.qos = QOS;
	pubmsg.retained = 0;

	sendmsg(*p_client, topic_names[TOPIC_PRIM_ACCESS_OUT], &pubmsg);

	while (g_access == INACTIVE && timeout < 10){
		sleep(1);
		timeout++; // TODO should this be part of ICP ??
	}

	return line_is_mine ? ICP_SUCCESS : ICP_BUSY;
}

uint8_t icp_clear_access_sig_cb( void ) {
	MQTTAsync_message pubmsg = MQTTAsync_message_initializer;
	char str[64] = "INACTIVE  by ";
	strcat (str, mac_addrs[local_mac_addr]);
	sent = FALSE;

	pubmsg.payload = (char*)str;
	pubmsg.payloadlen = strlen(str);
	pubmsg.qos = QOS;
	pubmsg.retained = 0;

	sendmsg(*p_client, topic_names[TOPIC_PRIM_ACCESS_OUT], &pubmsg);

	while (g_access == ACTIVE);

	return ICP_SUCCESS;
}

uint8_t icp_get_access_sig_cb( void ) {
	return g_access;
}

uint8_t icp_listen_for_ack_cb( bool_t enable ) {
	listen_for_ack = enable;
	return ICP_SUCCESS;
}

uint8_t icp_set_shudup_sig_cb( void ) {
	return ICP_SUCCESS;
}

uint8_t icp_clear_shudup_sig_cb( void ) {
	return ICP_SUCCESS;
}

uint8_t icp_get_shudup_sig_cb( void ) {
	return INACTIVE;
}

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

	int 			rc = ICP_SUCCESS;
	char 			s_topic[128];
	icp_config_t 	conf;

	printf("\n\n\n\n\n\n");

	// MQTT setup, connection and subscribe's
	p_client = &client;
	CHECK_MEM(p_client);
	MQTTAsync_create(&client, ADDRESS, mac_addrs[local_mac_addr], MQTTCLIENT_PERSISTENCE_NONE, NULL);
	MQTTAsync_setCallbacks(client, NULL, connlost, msgarrvd, NULL);
	
	conn_opts.keepAliveInterval = 20;
	conn_opts.cleansession = 1;
	conn_opts.onSuccess = onConnect;
	conn_opts.onFailure = onConnectFailure;
	conn_opts.context = client;
	if ((rc = MQTTAsync_connect(client, &conn_opts)) != MQTTASYNC_SUCCESS){
		MQTT_DEBUG("Failed to start connect, return code %d", rc);
		exit(-1);	
	}
	while	(!connected);

	subscribe(client, topic_names[TOPIC_TEST]);
	subscribe(client, topic_names[TOPIC_PRIM_ACCESS]);
	subscribe(client, topic_names[TOPIC_PRIM_GPINTL]);
	subscribe(client, topic_names[TOPIC_PRIM_SHUDUP]);
	subscribe(client, topic_names[TOPIC_PRIM_RS485]);
	subscribe(client, topic_names[TOPIC_SEC_ACCESS]);
	subscribe(client, topic_names[TOPIC_SEC_GPINTL]);
	subscribe(client, topic_names[TOPIC_SEC_SHUDUP]);
	subscribe(client, topic_names[TOPIC_SEC_RS485]);
	subscribe(client, topic_names[TOPIC_SIMULATOR_BASE]);
	strcpy(s_topic, topic_names[TOPIC_SIMULATOR_BASE]);
	strcat(s_topic, mac_addrs[local_mac_addr]);
	subscribe(client, s_topic);
	while	(!(subscribed==11));
	sim_topic = s_topic;

	if (finished)
		goto exit;
	
	mqtt_enable_debug_output(FALSE);
	icp_enable_debug_output(TRUE);
	sys_enable_debug_output(TRUE);

reset:
	// ICP setup
	icp_init_conf_struct( &conf );
	conf.bytes_out_cb 		= icp_bytes_out_cb;
	conf.packet_received_cb = icp_packet_received_cb;
	conf.error_cb 			= icp_error_cb;
	conf.get_time_cb 		= icp_get_time_cb;
	conf.notify_packet_ack_cb 		= icp_notify_packet_ack_cb;

	conf.set_access_sig_cb 	= icp_set_access_sig_cb;
	conf.clear_access_sig_cb = icp_clear_access_sig_cb;
	conf.get_access_sig_cb 	= icp_get_access_sig_cb;

	conf.set_shudup_sig_cb 	= icp_set_shudup_sig_cb;
	conf.clear_shudup_sig_cb = icp_clear_shudup_sig_cb;
	conf.get_shudup_sig_cb 	= icp_get_shudup_sig_cb;
	conf.get_time_cb 	= gettime;

	CHECK_ERR_RE(icp_init( &conf ), ICP_SUCCESS, "Could not initialize ICP");

	DEBUG("Running...");

	// icp_packet_t packet = ICP_packet_initializer;
	// CHECK_ERR_RE(print_packet(NULL), -1, "failed with p_packet=NULL");
	// CHECK_ERR_RE(print_packet(&packet), 0, "failed with valid args");

	// char str[64];
 	// 	CHECK_ERR_RE(icp_bytes_out_cb( (const uint8_t *)NULL, 10, NULL), 0, "failed with output_byte_array=NULL");
 	// 	CHECK_ERR_RE(icp_bytes_out_cb( (const uint8_t *)str, 0, NULL), 0, "failed with array_len=0");

 	// 	strcpy(str, "Hello");
 	// 	CHECK_ERR_RE(icp_bytes_out_cb( (const uint8_t *)str, 10, NULL), 10, "failed");

 	// 	strcpy(str, "Hello");
 	// 	CHECK_ERR_RE(icp_bytes_out_cb( (const uint8_t *)str, strlen(str), NULL), (int)strlen(str), "failed with valid args");
   
	// CHECK_ERR_RE(icp_packet_received_cb(NULL, NULL), -1, "failed with p_packet=NULL");
	// CHECK_ERR_RE(icp_packet_received_cb(&packet, NULL), 0, "failed with valid args");

	// CHECK_ERR_RE(icp_error_cb(ICP_SUCCESS, packet.data, packet.data_length, NULL), -1, "failed with invalid packet");
	// packet.data = (uint8_t *)&str;
	// CHECK_ERR_RE(icp_error_cb(ICP_WRONG_RECIPIENT, packet.data, packet.data_length, NULL), 0, "failed with valid args");

	// while(TRUE);

	while (TRUE) {

		if (bytes_in){
			bytes_in = FALSE;
			DEBUG("bytes_in was TRUE with %d bytes ", payload_in_len)
			icp_bytes_in( (const uint8_t *)payload_in, payload_in_len );
		}

		if (update_now){
			icp_update();
			update_now = FALSE;
		}

		if (reset_flag){
			LOG_INFO("Reseting system...");
			reset_flag = FALSE;
			goto reset;
		}
		sleep(1);

	}

	disc_opts.onSuccess = onDisconnect;
	if ((rc = MQTTAsync_disconnect(client, &disc_opts)) != MQTTASYNC_SUCCESS){
		MQTT_DEBUG("Failed to start disconnect, return code %d", rc);
		exit(-1);	
	}
 	while	(!connected);

error:

exit:
	MQTTAsync_destroy(&client);
 	return rc;
}
