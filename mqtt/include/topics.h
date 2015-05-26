

#ifndef TOPICS_H
#define TOPICS_H

typedef enum topic_id_et{
	TOPIC_TEST,
	TOPIC_PRIM_ACCESS,
	TOPIC_PRIM_ACCESS_OUT,
	TOPIC_PRIM_SHUDUP,
	TOPIC_PRIM_SHUDUP_OUT,
	TOPIC_PRIM_GPINTL,
	TOPIC_PRIM_GPINTL_OUT,
	TOPIC_PRIM_RS485,
	TOPIC_SEC_ACCESS,
	TOPIC_SEC_ACCESS_OUT,
	TOPIC_SEC_SHUDUP,
	TOPIC_SEC_SHUDUP_OUT,
	TOPIC_SEC_GPINTL,
	TOPIC_SEC_GPINTL_OUT,
	TOPIC_SEC_RS485,
	TOPIC_SIMULATOR_BASE,
	TOPIC_SIMULATOR_DBG_BASE,
	NUM_OF_TOPICS
} topic_id_t;

static char topic_names[NUM_OF_TOPICS][64] = { 
	"ec2/test",
	"ec2/icp/bus/primary/access",
	"ec2/icp/bus_out/primary/access",
	"ec2/icp/bus/primary/shudup",
	"ec2/icp/bus_out/primary/shudup",
	"ec2/icp/bus/primary/gpintl",
	"ec2/icp/bus_out/primary/gpintl",
	"ec2/icp/bus/primary/rs485",
	"ec2/icp/bus/secondary/access",
	"ec2/icp/bus_out/secondary/access",
	"ec2/icp/bus/secondary/shudup",
	"ec2/icp/bus_out/secondary/shudup",
	"ec2/icp/bus/secondary/gpintl",
	"ec2/icp/bus_out/secondary/gpintl",
	"ec2/icp/bus/secondary/rs485",
	"ec2/sim/cmd/",
	"ec2/sim/dbg/"
};

#endif
