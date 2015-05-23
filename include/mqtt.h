#include "MQTTAsync.h"
#include "icp.h"

// #define ADDRESS     "tcp://test.mosquitto.org:1883"
#define ADDRESS     "tcp://localhost:1883"
#define QOS         1
#define TIMEOUT     10000L

typedef enum signal_state_et{
	LOW = 0,
	HIGH,
	NUM_OF_SIG_STATES
}signal_state_t;

extern signal_state_t g_access;
extern signal_state_t g_shudup;
extern signal_state_t g_gpintl;

extern char		*sim_topic;
extern char		*sim_dbg_topic;
extern char		payload[64];
extern uint8_t	payload_in[ICP_MAX_PACKET_LENGTH];
extern uint16_t	payload_len;
extern uint16_t	payload_in_len;

extern bool_t 	connected;
extern bool_t 	finished;
extern bool_t 	sent;
extern bool_t 	update_now;
extern bool_t 	reset_flag;
extern bool_t 	line_is_mine;
extern bool_t 	bytes_in;
extern bool_t 	listen_for_ack;
extern uint8_t 	subscribed;

void onSend(void* context, MQTTAsync_successData* response);

int sendmsg(void *context, char *topicName, MQTTAsync_message *message);

void onSubscribe(void* context, MQTTAsync_successData* response);

void onSubscribeFailure(void* context, MQTTAsync_failureData* response);

void subscribe(void* context, char* topic);

void onConnect(void* context, MQTTAsync_successData* response);

void onConnectFailure(void* context, MQTTAsync_failureData* response);

void onDisconnect(void* context, MQTTAsync_successData* response);

void connlost(void *context, char *cause);

int msgarrvd(void *context, char *topicName, int topicLen, MQTTAsync_message *message);

