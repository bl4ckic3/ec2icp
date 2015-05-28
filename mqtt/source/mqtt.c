#include "stdlib.h"
#include "string.h"
#include "icp.h"
#include "topics.h"
#include "mqtt.h"
#include "dbg.h"

volatile MQTTAsync_token 	deliveredtoken;

signal_state_t g_access = INACTIVE;
signal_state_t g_shudup = INACTIVE;
signal_state_t g_gpintl = INACTIVE;

char		*sim_topic;
char		*sim_dbg_topic;
char		payload[64];
uint8_t		payload_in[ICP_MAX_PACKET_LENGTH];
uint16_t	payload_len;
uint16_t	payload_in_len;

uint8_t 	subscribed 		= 0;

bool_t 		connected 		= FALSE;
bool_t 		finished 		= FALSE;
bool_t 		sent 			= FALSE;
bool_t 		line_is_mine	= FALSE;
bool_t 		update_now		= FALSE;
bool_t 		reset_flag		= FALSE;
bool_t 		bytes_in		= FALSE;
bool_t 		listen_for_ack	= FALSE;

typedef uint8_t (*pt_cb_t)( int user_data );

typedef struct node_ts{
    char cmd[64];                  
    void *fn;
    int user_data;
} node_t;   


uint8_t all_enable_debug_output( uint8_t enabled ) {
    sys_enable_debug_output( enabled );
    icp_enable_debug_output( enabled );
    mqtt_enable_debug_output( enabled );
    return 0;
}
uint8_t all_enable_err_output( uint8_t enabled ) {
    sys_enable_err_output( enabled );
    icp_enable_err_output( enabled );
    mqtt_enable_err_output( enabled );
    return 0;
}
uint8_t all_enable_warn_output( uint8_t enabled ) {
    sys_enable_warn_output( enabled );
    icp_enable_warn_output( enabled );
    mqtt_enable_warn_output( enabled );
    return 0;
}
uint8_t all_enable_all_output( uint8_t enabled ) {
    sys_enable_all_output( enabled );
    icp_enable_all_output( enabled );
    mqtt_enable_all_output( enabled );
    return 0;
}
uint8_t all_enable_info_output( uint8_t enabled ) {
    sys_enable_info_output( enabled );
    icp_enable_info_output( enabled );
    mqtt_enable_info_output( enabled );
    return 0;
}    
 
 
node_t lookup_table[]={
{ "set icp debug true", icp_enable_debug_output, TRUE},
{ "set icp debug false", icp_enable_debug_output, FALSE},
{ "set icp err true", icp_enable_err_output, TRUE},
{ "set icp err false", icp_enable_err_output, FALSE},
{ "set icp warn true", icp_enable_warn_output, TRUE},
{ "set icp warn false", icp_enable_warn_output, FALSE},
{ "set icp info true", icp_enable_info_output, TRUE},
{ "set icp info false", icp_enable_info_output, FALSE},
{ "set icp all true", icp_enable_all_output, TRUE},
{ "set icp all false", icp_enable_all_output, FALSE},
{ "set mqtt debug true", mqtt_enable_debug_output, TRUE},
{ "set mqtt debug false", mqtt_enable_debug_output, FALSE},
{ "set mqtt err true", mqtt_enable_err_output, TRUE},
{ "set mqtt err false", mqtt_enable_err_output, FALSE},
{ "set mqtt warn true", mqtt_enable_warn_output, TRUE},
{ "set mqtt warn false", mqtt_enable_warn_output, FALSE},
{ "set mqtt info true", mqtt_enable_info_output, TRUE},
{ "set mqtt info false", mqtt_enable_info_output, FALSE},
{ "set mqtt all true", mqtt_enable_all_output, TRUE},
{ "set mqtt all false", mqtt_enable_all_output, FALSE},
{ "set sys debug true", sys_enable_debug_output, TRUE},
{ "set sys debug false", sys_enable_debug_output, FALSE},
{ "set sys err true", sys_enable_err_output, TRUE},
{ "set sys err false", sys_enable_err_output, FALSE},
{ "set sys warn true", sys_enable_warn_output, TRUE},
{ "set sys warn false", sys_enable_warn_output, FALSE},
{ "set sys info true", sys_enable_info_output, TRUE},
{ "set sys info false", sys_enable_info_output, FALSE},
{ "set sys all true", sys_enable_all_output, TRUE},
{ "set sys all false", sys_enable_all_output, FALSE},
{ "set all debug true", all_enable_debug_output, TRUE},
{ "set all debug false", all_enable_debug_output, FALSE},
{ "set all err true", all_enable_err_output, TRUE},
{ "set all err false", all_enable_err_output, FALSE},
{ "set all warn true", all_enable_warn_output, TRUE},
{ "set all warn false", all_enable_warn_output, FALSE},
{ "set all info true", all_enable_info_output, TRUE},
{ "set all info false", all_enable_info_output, FALSE},
{ "set all all true", all_enable_all_output, TRUE},
{ "set all all false", all_enable_all_output, FALSE},
};

void Interpreter(char *string , int str_len){
    node_t *pt;
    const int table_length = sizeof(lookup_table)/sizeof(*lookup_table);
    int row;
 	DEBUG("%s %d", string, str_len);
    for(row=0; row < table_length; row++){
 
        pt = &lookup_table[row];
        if(strncmp(string, (const char *)pt->cmd, str_len) == 0){
            ((pt_cb_t) pt->fn)( pt->user_data );
            return;
        }
    }
    MQTT_LOG_ERR("Could not find a suitable function.");
	return;
}

void onSend(void* context, MQTTAsync_successData* response){
	// MQTT_LOG_INFO("Message with token value %d delivery confirmed.", response->token);
	sent = TRUE;
}

int sendmsg(void *context, char *topicName, MQTTAsync_message *message){
    MQTTAsync 					client 	= (MQTTAsync)context;
	MQTTAsync_responseOptions 	opts 	= MQTTAsync_responseOptions_initializer;
	int 						rc;
	sent 			= FALSE;
    opts.onSuccess 	= onSend;
	opts.context 	= client;
	deliveredtoken 	= 0;

	if ((rc = MQTTAsync_sendMessage(client, topicName, message, &opts)) != MQTTASYNC_SUCCESS){
		MQTT_LOG_ERR("Failed to start sendMessage, return code %d.", rc);
 		exit(-1);	
	}
    return 1;
}

void onSubscribe(void* context, MQTTAsync_successData* response){
	// MQTT_LOG_INFO("Subscribe succeeded.");
	subscribed += 1;
}

void onSubscribeFailure(void* context, MQTTAsync_failureData* response){
	MQTT_LOG_INFO("Subscribe failed, rc %d.", response ? response->code : 0);
	finished = TRUE;
}

void subscribe(void* context, char* topic){
	MQTTAsync 					client 	= (MQTTAsync)context;
	MQTTAsync_responseOptions 	opts 	= MQTTAsync_responseOptions_initializer;
 	int 						rc;

	MQTT_LOG_INFO("Subscribing to topic %s for client %s using QoS%d.", topic, mac_addrs[local_mac_addr], QOS);

	opts.onSuccess 	= onSubscribe;
	opts.onFailure 	= onSubscribeFailure;
	opts.context 	= client;
	deliveredtoken 	= 0;

	if ((rc = MQTTAsync_subscribe(client, topic, QOS, &opts)) != MQTTASYNC_SUCCESS){
		MQTT_LOG_ERR("Failed to start subscribe, return code %d.", rc);
		exit(-1);	
	}
}

void onConnect(void* context, MQTTAsync_successData* response){
	MQTT_LOG_INFO("Successful connection.");
	connected = TRUE;
}

void onConnectFailure(void* context, MQTTAsync_failureData* response){
	MQTT_LOG_ERR("Connect failed, rc %d.", response ? response->code : 0);
	finished = TRUE;
}

void onDisconnect(void* context, MQTTAsync_successData* response){
	MQTT_LOG_INFO("Successful disconnection.");
	connected = FALSE;
}

void connlost(void *context, char *cause){
	MQTTAsync 					client 		= (MQTTAsync)context;
	MQTTAsync_connectOptions 	conn_opts 	= MQTTAsync_connectOptions_initializer;
	int 						rc;

	connected = FALSE;

	MQTT_LOG_INFO("Connection lost; cause: %s.", cause);
	MQTT_LOG_INFO("Reconnecting.");

	conn_opts.keepAliveInterval = 20;
	conn_opts.cleansession 		= 1;

	if ((rc = MQTTAsync_connect(client, &conn_opts)) != MQTTASYNC_SUCCESS){
		MQTT_LOG_ERR("Failed to start connect, return code %d.", rc);
	    finished = TRUE;
	}

	connected = TRUE;
}

int msgarrvd(void *context, char *topicName, int topicLen, MQTTAsync_message *message){

	int 		i;
	char* 		payloadptr;

    MQTT_DEBUG_({
    	MQTT_DEBUG("Message arrived\n\t\t     topic: %s\n\t\t   message: ", topicName);
	    
	    payloadptr = message->payload;
	    printf("[ ");
		for (i=0; i < message->payloadlen; i++) {
			printf("%02X ", (int) *payloadptr++);
		}
		printf("]\n");
	    
	    payloadptr = message->payload;
    	for(i=0; i<message->payloadlen; i++){
	        putchar(*payloadptr++);
	    }
	    putchar('\n');
	});

	int topic;

	for ( topic = 0; topic < NUM_OF_TOPICS; topic++ ){
		if (strcmp(topicName, topic_names[topic]) == 0){
			break;
		}
	}
#ifdef N_BUS
	switch (topic){
		case TOPIC_TEST:
			break;
		case TOPIC_PRIM_ACCESS_OUT:
			if (strncmp(message->payload, "ACTIVE", 6) == 0 && g_access != ACTIVE){ 
				g_access = ACTIVE;

				strcpy(payload, message->payload);
				payload_len = message->payloadlen;

				line_is_mine = TOPIC_PRIM_ACCESS;
				update_now = TRUE;
			} else if (strncmp(message->payload, "INACTIVE", 8) == 0){
				g_access = INACTIVE;

				strcpy((char *)payload, (char *)message->payload);
				payload_len = (message->payloadlen);

				line_is_mine = TOPIC_PRIM_ACCESS;
				update_now = TRUE;
			}
			break;
		case TOPIC_PRIM_GPINTL_OUT:
			if (strncmp(message->payload, "ACTIVE", 6) == 0 && g_gpintl != ACTIVE){ 
				g_gpintl = ACTIVE;

				strcpy((char *)payload, (char *)message->payload);
				payload_len = message->payloadlen;

				line_is_mine = TOPIC_PRIM_GPINTL;
				update_now = TRUE;
			} else if (strncmp(message->payload, "INACTIVE", 8) == 0){
				g_gpintl = INACTIVE;

				strcpy((char *)payload, (char *)message->payload);
				payload_len = message->payloadlen;

				line_is_mine = TOPIC_PRIM_GPINTL;
				update_now = TRUE;
			}
			break;
		case TOPIC_PRIM_SHUDUP_OUT:
			if (strncmp(message->payload, "ACTIVE", 6) == 0 && g_shudup != ACTIVE){ 
				g_shudup = ACTIVE;

				strcpy((char *)payload, (char *)message->payload);
				payload_len = message->payloadlen;

				line_is_mine = TOPIC_PRIM_SHUDUP;
				update_now = TRUE;
			} else if (strncmp(message->payload, "INACTIVE", 8) == 0){
				g_shudup = INACTIVE;

				strcpy((char *)payload, (char *)message->payload);
				payload_len = message->payloadlen;

				line_is_mine = TOPIC_PRIM_SHUDUP;
				update_now = TRUE;
			}
			break;
		default:
			if (strncmp(message->payload, "reset", 5) == 0){
				LOG_INFO("Reseting signal states to INACTIVE.");
				g_access = INACTIVE;
				g_shudup = INACTIVE;
				g_gpintl = INACTIVE;
				// strcpy((char *)payload, (char *)message->payload);
				// payload_len = (message->payloadlen);

				// line_is_mine = TOPIC_PRIM_ACCESS;
				// update_now = TRUE;
				break;
			} 
			if (strncmp(message->payload, "set", 3) == 0){
				Interpreter(message->payload, message->payloadlen);
				break;
			} 
			if (strncmp(message->payload, "time", 4) == 0){
				LOG_INFO("<-- My time.");
				break;
			}
			if (strncmp(message->payload, "sync", 4) == 0){
				synctime();
				break;
			}
			if (strncmp(message->payload, "clean", 5) == 0){
				printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
				break;
			}
			MQTT_DEBUG("unknown topic\n");
			break;
	}
#else
	char str[64];
	mac_addr_t destination;
	switch (topic){
		case TOPIC_TEST:
			break;
		case TOPIC_PRIM_ACCESS:
			if (strncmp(message->payload, "ACTIVE", 6) == 0 && !line_is_mine){
				strcpy(str, "ACTIVE by ");
				strcat(str, mac_addrs[local_mac_addr]);

				g_access = ACTIVE;
				
				if (strncmp(message->payload, str, strlen(str)) == 0){
					line_is_mine = TRUE;
				} else {
					icp_notify_acces_active();
				}

			} else if (strncmp(message->payload, "INACTIVE", 8) == 0){
				g_access = INACTIVE;
				icp_notify_acces_inactive();
				line_is_mine = FALSE;
			}
			break;
		case TOPIC_PRIM_GPINTL:
			break;
		case TOPIC_PRIM_SHUDUP:
			if (strncmp(message->payload, "ACTIVE", 6) == 0){
				g_shudup = ACTIVE;
			} else if (strncmp(message->payload, "INACTIVE", 8) == 0){
				g_shudup = INACTIVE;
			}
			break;
		case TOPIC_PRIM_RS485:
		case TOPIC_SEC_RS485:

			// strcpy((char *)payload_in, (char *)message->payload);
			payload_in_len = message->payloadlen;

		    payloadptr = message->payload;

			for (i=0; i < message->payloadlen; i++) {
				payload_in[i] = *payloadptr++;
			}

			bytes_in = TRUE;
			// icp_bytes_in(message->payload, message->payloadlen );
			break;
		default:
			if (strncmp(message->payload, "time", 4) == 0){
				LOG_INFO("<-- My time.");
				break;
			}
			if (strncmp(message->payload, "update", 6) == 0){
				update_now = TRUE;
				break;
			}
			if (strncmp(message->payload, "sync", 4) == 0){
				synctime();
				break;
			}
			if (strncmp(message->payload, "reset", 5) == 0){
				reset_flag = TRUE;
				g_access = INACTIVE;
				g_shudup = INACTIVE;
				line_is_mine = FALSE;
				bytes_in = FALSE;
				break;
			} 
			if (strncmp(message->payload, "stopupdate", 10) == 0){
				update_now = FALSE;
				break;
			} 
			if (strncmp(message->payload, "set", 3) == 0){
				Interpreter(message->payload, message->payloadlen);
				break;
			} 
			if (strncmp(message->payload, "clean", 5) == 0){
				printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
				break;
			} else{
				strcpy(str, "PING to ");

				if (strncmp(message->payload, "pc", 2) == 0){
					destination 	= NODE_PC;
				} else if (strncmp(message->payload, "eps", 3) == 0){
					destination 	= NODE_EPS;
				} else if (strncmp(message->payload, "cam", 3) == 0){
					destination 	= NODE_CAM;
				} else if (strncmp(message->payload, "cdhs", 4) == 0){
					destination 	= NODE_CDHS;
				} else {
					destination 	= BROADCAST;
				}
				strcat(str, mac_addrs[destination]);
				strcat(str, " from ");
				strcat(str, mac_addrs[local_mac_addr]);

				icp_send_data(destination, (const uint8_t *) str, strlen(str));
			}
			break;
	}
#endif

    MQTTAsync_freeMessage(&message);
    MQTTAsync_free(topicName);
    MQTT_DEBUG("Returning...");
    return 1;
}

#ifdef MQTTDEBUG
bool_t g_mqtt_enable_debug_output = TRUE;
bool_t g_mqtt_enable_err_output= TRUE;
bool_t g_mqtt_enable_warn_output= TRUE;
bool_t g_mqtt_enable_info_output= TRUE;
uint8_t mqtt_enable_debug_output( uint8_t enabled ) {
    LOG_INFO("Setting g_mqtt_enable_debug_output to %d", enabled);
    g_mqtt_enable_debug_output = enabled;
    return 0;
}
uint8_t mqtt_enable_err_output( uint8_t enabled ) {
    LOG_INFO("Setting g_mqtt_enable_err_output to %d", enabled);
    g_mqtt_enable_err_output = enabled;
    return 0;
}
uint8_t mqtt_enable_warn_output( uint8_t enabled ) {
    LOG_INFO("Setting g_mqtt_enable_warn_output to %d", enabled);
    g_mqtt_enable_warn_output = enabled;
    return 0;
}
uint8_t mqtt_enable_info_output( uint8_t enabled ) {
    LOG_INFO("Setting g_mqtt_enable_info_output to %d", enabled);
    g_mqtt_enable_info_output = enabled;
    return 0;
}
uint8_t mqtt_enable_all_output( uint8_t enabled ) {
    mqtt_enable_debug_output( enabled );
    mqtt_enable_err_output( enabled );
    mqtt_enable_warn_output( enabled );
    mqtt_enable_info_output( enabled );
    return 0;
}
#else
uint8_t mqtt_enable_debug_output( uint8_t enabled ) { return 0;}
uint8_t mqtt_enable_err_output( uint8_t enabled ) { return 0;}
uint8_t mqtt_enable_warn_output( uint8_t enabled ) { return 0;}
uint8_t mqtt_enable_info_output( uint8_t enabled ) { return 0;}
uint8_t mqtt_enable_all_output( uint8_t enabled ) { return 0;}
#endif
