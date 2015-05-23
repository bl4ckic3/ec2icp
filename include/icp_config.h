/** 
 * @file icp_config.h
 * ICP's platform specific configuration header file.
 */
#pragma once
#ifndef ICP_CONFIG_H
#define ICP_CONFIG_H

#include <stdlib.h>
#include <string.h>
#include "icp_shared_config.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus


/** 
 * TODO
 */
#ifdef N_PC
static mac_addr_t 	local_mac_addr 	= NODE_PC;
#elif N_CAM
static mac_addr_t 	local_mac_addr 	= NODE_CAM;
#elif N_EPS
static mac_addr_t 	local_mac_addr 	= NODE_EPS;
#elif N_CDHS
static mac_addr_t 	local_mac_addr 	= NODE_CDHS;
#elif N_TEST
static mac_addr_t 	local_mac_addr 	= NODE_TEST;
#elif N_BUS
static mac_addr_t 	local_mac_addr 	= NODE_BUS;
#endif



//! Length of the buffer used for constructing a packet and handing it over directly to the user.
#define BUFFER_LEN ((64*1024)-1) // TODO buffer OVF handling


/** 
 * ICP's memory handling functionality.
 */
#ifndef icp_malloc
#define icp_malloc malloc
// #define icp_malloc myfun
#endif
#ifndef icp_free
#define icp_free free
#endif

#ifndef icp_memmove
#define icp_memmove memmove
#endif

#ifndef icp_memset
#define icp_memset memset
#endif

/*
int buff[MAX_BUFFER_LEN] = {0xFF};
int *p_first_free = buff;

void *myfun(int len) {

	int *ptr = p_first_free;
	p_first_free += len;


	return ptr;
}
*/

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ICP_CONFIG_H
