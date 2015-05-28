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
// #define icp_malloc my_malloc
#endif
#ifndef icp_free
#define icp_free free
// #define icp_free my_free
#endif

#ifndef icp_memmove
#define icp_memmove memmove
// #define icp_memmove my_memmove
#endif

#ifndef icp_memset
#define icp_memset memset
// #define icp_memset my_memset
#endif

#ifndef icp_crc16
#define icp_crc16 crc16
// #define icp_memset my_memset
#endif


void *my_malloc(uint8_t len);
void my_free(uint8_t *ptr) ;
void my_memmove(uint8_t *ptr);
void my_memset(uint8_t *ptr) ;
uint16_t crc16(const uint8_t *p, int len);


#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ICP_CONFIG_H
