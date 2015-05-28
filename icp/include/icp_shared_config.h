/** 
 * @file icp_config.h
 * ICP's shared configuration header file.
 */
#pragma once
#ifndef ICP_SHARED_CONFIG_H
#define ICP_SHARED_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/** 
 * TODO
 */
typedef enum mac_addr_et{
	BROADCAST,
	NODE_PC,
	NODE_CAM,
	NODE_EPS,
	NODE_CDHS,
	NODE_TEST,
	NODE_BUS,
	NUM_OF_NODES,
	INVALID_MAC_ADDR
} mac_addr_t;
/** 
 * TODO
 */
static char mac_addrs[NUM_OF_NODES][32] = { 
	"BROADCAST",
	"PC",
	"CAM",
	"EPS",
	"CDHS",
	"TEST",
	"BUS"
};

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ICP_SHARED_CONFIG_H
