#pragma once
#ifndef __DBG_H__
#define __DBG_H__

#include <stdio.h>
#include <errno.h>
#include <string.h>

#include <time.h>
#include <sys/time.h>

#ifdef __MACH__
#include <mach/mach_time.h>
#define ORWL_NANO (+1.0E-9)
#define ORWL_NANO2MICRO (+1.0E-3)
#define ORWL_NANO2MILLI (+1.0E-6)
#define ORWL_GIGA UINT64_C(1000000000)

static double orwl_timebase = 0.0;
static uint64_t orwl_timestart = 0;
struct timespec orwl_gettime(void);
char *gettime_s(void);
time_t gettime_ms(void);
time_t gettime_us(void);
time_t gettime_ns(void);
void synctime(void);

#else
clock_gettime(CLOCK_REALTIME, &ts);
#endif

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
#define RESET "\033[0m"

#ifdef NDEBUG
	#define _DEBUG(S, M, ...)
	#define _LOG_ERR(S, M, ...)
	#define _LOG_WARN(S, M, ...) 
	#define _LOG_INFO(S, M, ...) 
	#define _LOG_ACTION(S, M, ...) 
	#define _LOG_EXIT(S, M, ...) 
#else
	#define _DEBUG(S, M, ...) fprintf(stderr, KGRN "%s - [DEBUG][%s] ( %s : %s : %d ) : "RESET M  "\n", gettime_s(), S, __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
	#define _LOG_ERR(S, M, ...) fprintf(stderr, KRED"%s - [ERROR][%s] ( %s : %s : %d : errno: %s ) : "RESET M "\n", gettime_s(), S, __FILE__, __FUNCTION__, __LINE__, CLEAN_ERRNO(), ##__VA_ARGS__)
	#define _LOG_WARN(S, M, ...) fprintf(stderr, KYEL"%s - [WARN][%s] ( %s : %s : %d : errno: %s ) : "RESET M "\n", gettime_s(), S, __FILE__, __FUNCTION__, __LINE__, CLEAN_ERRNO(), ##__VA_ARGS__)
	#define _LOG_INFO(S, M, ...) fprintf(stderr, KWHT"%s - [INFO][%s] ( %s : %s : %d ) : "RESET M "\n", gettime_s(), S, __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
	#define _LOG_ACTION(S, M, ...) fprintf(stderr, KWHT"%s - [ACTION][%s] ( %s : %s : %d ) : "RESET M "\n", gettime_s(), S, __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
	#define _LOG_EXIT(S, M, ...) fprintf(stderr, KBLU"%s - [EXIT][%s] ( %s : %s : %d ) :"RESET" REASON : " M "\n", gettime_s(), S, __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#endif

#define CLEAN_ERRNO() (errno == 0 ? "None" : strerror(errno))

#define __CHECK(F, A, M, X, ...) 			if(!(A)) 		{ F (M, ##__VA_ARGS__); {X} }
#define __CHECK_RE(F, A, E, M, X, ...) 		if(A != E) 		{ F (KMAG "[ Expected : %d ] [ Real : %d ] : " RESET M, E, A, ##__VA_ARGS__); {X} }

#define _CHECK_ERR(F, A, M, ...) 			__CHECK 		(F, A, M, {errno=0; goto error;}, ##__VA_ARGS__)
#define _CHECK_ERR_RE(F, A, E, M, ...) 		__CHECK_RE 		(F, A, E, M, {errno=0; goto error;}, ##__VA_ARGS__)

#define _CHECK_WARN(F, A, M, ...) 			__CHECK 		(F, A, M, {errno=0;}, ##__VA_ARGS__)
#define _CHECK_WARN_RE(F, A, E, M, ...) 	__CHECK_RE 		(F, A, E, M, {errno=0;}, ##__VA_ARGS__)

#define _CHECK_INFO(F, A, M, ...) 			__CHECK 		(F, A, M, {}, ##__VA_ARGS__)
#define _CHECK_INFO_RE(F, A, E, M, ...) 	__CHECK_RE 		(F, A, E, M, {}, ##__VA_ARGS__)

#define _CHECK_DEBUG(F, A, M, ...) 			__CHECK 		(F, A, M, {errno=0; goto error;}, ##__VA_ARGS__)
#define _CHECK_DEBUG_RE(F, A, E, M, ...) 	__CHECK_RE 		(F, A, E, M, {errno=0; goto error;}, ##__VA_ARGS__)

#define _CHECK_EXIT(F, A, M, ...) 			__CHECK 		(F, A, M, {errno=0; goto end;}, ##__VA_ARGS__)
#define _CHECK_EXIT_RE(F, A, E, M, ...) 	__CHECK_RE 		(F, A, E, M, {errno=0; goto end;}, ##__VA_ARGS__)


#ifdef SYSDEBUG
	//! Use "extern uint8_t icp_allow_DEBUG_output; icp_allow_DEBUG_output = TRUE/FALSE;" to turn debugging on/off at run-time.
	extern uint8_t g_sys_enable_debug_output;
	extern uint8_t g_sys_enable_err_output;
	extern uint8_t g_sys_enable_warn_output;
	extern uint8_t g_sys_enable_info_output;
	#define DEBUG(M, ...) if (g_sys_enable_debug_output) {_DEBUG("SYS", M, ##__VA_ARGS__);}
	#define LOG_ERR(M, ...) if (g_sys_enable_err_output) {_LOG_ERR("SYS", M, ##__VA_ARGS__);}
	#define LOG_WARN(M, ...) if (g_sys_enable_warn_output) {_LOG_WARN("SYS", M, ##__VA_ARGS__);}
	#define LOG_INFO(M, ...) if (g_sys_enable_info_output) {_LOG_INFO("SYS", M, ##__VA_ARGS__);}
	#define LOG_ACTION(x, M, ...) if (g_sys_enable_info_output) {_LOG_ACTION("SYS", M, ##__VA_ARGS__); x;}
	#define LOG_EXIT(M, ...) if (g_sys_enable_info_output) {_LOG_EXIT("SYS", M, ##__VA_ARGS__);}
#else
	//! \note Allow for the DBG macros to be customized (custom output channels).
	#define DEBUG(M, ...) 
	#define LOG_ERR(M, ...) 
	#define LOG_WARN(M, ...) 
	#define LOG_INFO(M, ...) 
	#define LOG_ACTION(x, M, ...) 
	#define LOG_EXIT(M, ...) 
#endif

#define CHECK_ERR(A, M, ...) 				_CHECK_ERR 		(LOG_ERR, A, M, ##__VA_ARGS__)
#define CHECK_WARN(A, M, ...) 				_CHECK_WARN 	(LOG_WARN, A, M, ##__VA_ARGS__)
#define CHECK_INFO(A, M, ...) 				_CHECK_INFO 	(LOG_INFO, A, M, ##__VA_ARGS__)
#define CHECK_DEBUG(A, M, ...) 				_CHECK_DEBUG 	(DEBUG, A, M, ##__VA_ARGS__)
#define CHECK_EXIT(A, M, ...) 				_CHECK_EXIT 	(LOG_EXIT, A, M, ##__VA_ARGS__)
#define CHECK_ERR_RE(A, E, M, ...) 			_CHECK_ERR_RE	(LOG_ERR, A, E, M, ##__VA_ARGS__)
#define CHECK_WARN_RE(A, E, M, ...) 		_CHECK_WARN_RE	(LOG_WARN, A, E, M, ##__VA_ARGS__)
#define CHECK_INFO_RE(A, E, M, ...) 		_CHECK_INFO_RE	(LOG_INFO, A, E, M, ##__VA_ARGS__)
#define CHECK_DEBUG_RE(A, E, M, ...) 		_CHECK_DEBUG_RE	(DEBUG, A, E, M, ##__VA_ARGS__)
#define CHECK_EXIT_RE(A, E, M, ...) 		_CHECK_EXIT_RE	(LOG_EXIT, A, E, M, ##__VA_ARGS__)

#define SENTINEL(M, ...)  { LOG_ERR(M, ##__VA_ARGS__); errno=0; goto error; }
#define CHECK_MEM(A) CHECK_ERR((A), "Out of memory.")

uint8_t sys_enable_debug_output( uint8_t enabled );
uint8_t sys_enable_err_output( uint8_t enabled );
uint8_t sys_enable_warn_output( uint8_t enabled );
uint8_t sys_enable_info_output( uint8_t enabled );
uint8_t sys_enable_all_output( uint8_t enabled );


#ifdef ICPDEBUG
	//! Use "extern uint8_t icp_allow_DEBUG_output; icp_allow_DEBUG_output = TRUE/FALSE;" to turn debugging on/off at run-time.
	extern uint8_t g_icp_enable_debug_output;
	extern uint8_t g_icp_enable_err_output;
	extern uint8_t g_icp_enable_warn_output;
	extern uint8_t g_icp_enable_info_output;
	#define ICP_DEBUG(M, ...) if (g_icp_enable_debug_output) {_DEBUG("ICP", M, ##__VA_ARGS__);}
	#define ICP_DEBUG_( x ) if (g_icp_enable_debug_output) {x}
	#define ICP_LOG_ERR(M, ...) if (g_icp_enable_err_output) {_LOG_ERR("ICP", M, ##__VA_ARGS__);}
	#define ICP_LOG_WARN(M, ...) if (g_icp_enable_warn_output) {_LOG_WARN("ICP", M, ##__VA_ARGS__);}
	#define ICP_LOG_INFO(M, ...) if (g_icp_enable_info_output) {_LOG_INFO("ICP", M, ##__VA_ARGS__);}
	#define ICP_LOG_ACTION(x, M, ...) if (g_icp_enable_info_output) {_LOG_ACTION("ICP", M, ##__VA_ARGS__); x;}
	#define ICP_LOG_EXIT(M, ...) if (g_icp_enable_info_output) {_LOG_EXIT("ICP", M, ##__VA_ARGS__);}
#else
	//! \note Allow for the DBG macros to be customized (custom output channels).
	#define ICP_DEBUG(M, ...)
	#define ICP_DEBUG_( x )
	#define ICP_LOG_ERR(M, ...)
	#define ICP_LOG_WARN(M, ...)
	#define ICP_LOG_INFO(M, ...)
	#define ICP_LOG_ACTION(x, M, ...)
	#define ICP_LOG_EXIT(M, ...)
#endif

#define ICP_CHECK_ERR(A, M, ...) 			_CHECK_ERR 		(ICP_LOG_ERR, A, M, ##__VA_ARGS__) 
#define ICP_CHECK_WARN(A, M, ...) 			_CHECK_WARN 	(ICP_LOG_WARN, A, M, ##__VA_ARGS__) 
#define ICP_CHECK_INFO(A, M, ...) 			_CHECK_INFO 	(ICP_LOG_INFO, A, M, ##__VA_ARGS__) 
#define ICP_CHECK_EXIT(A, M, ...) 			_CHECK_EXIT 	(ICP_LOG_EXIT, A, M, ##__VA_ARGS__) 
#define ICP_CHECK_DEBUG(A, M, ...) 			_CHECK_DEBUG 	(ICP_DEBUG, A, M, ##__VA_ARGS__) 
#define ICP_CHECK_ERR_RE(A, E, M, ...) 		_CHECK_ERR_RE	(ICP_LOG_ERR, A, E, M, ##__VA_ARGS__) 
#define ICP_CHECK_WARN_RE(A, E, M, ...) 	_CHECK_WARN_RE 	(ICP_LOG_WARN, A, E, M, ##__VA_ARGS__)
#define ICP_CHECK_INFO_RE(A, E, M, ...) 	_CHECK_INFO_RE 	(ICP_LOG_INFO, A, E, M, ##__VA_ARGS__)
#define ICP_CHECK_EXIT_RE(A, E, M, ...) 	_CHECK_EXIT_RE 	(ICP_LOG_EXIT, A, E, M, ##__VA_ARGS__)
#define ICP_CHECK_DEBUG_RE(A, E, M, ...) 	_CHECK_DEBUG_RE	(ICP_DEBUG, A, E, M, ##__VA_ARGS__)

#define ICP_SENTINEL(M, ...)  { ICP_LOG_ERR(M, ##__VA_ARGS__); errno=0; goto error; }
#define ICP_CHECK_MEM(A) ICP_CHECK_ERR((A), "Out of memory.")

uint8_t icp_enable_debug_output( uint8_t enabled );
uint8_t icp_enable_err_output( uint8_t enabled );
uint8_t icp_enable_warn_output( uint8_t enabled );
uint8_t icp_enable_info_output( uint8_t enabled );
uint8_t icp_enable_all_output( uint8_t enabled );


#ifdef MQTTDEBUG
	extern uint8_t g_mqtt_enable_debug_output;
	extern uint8_t g_mqtt_enable_err_output;
	extern uint8_t g_mqtt_enable_warn_output;
	extern uint8_t g_mqtt_enable_info_output;
	#define MQTT_DEBUG(M, ...)  if (g_mqtt_enable_debug_output) {_DEBUG("MQTT", M, ##__VA_ARGS__);}
	#define MQTT_DEBUG_( x ) if (g_mqtt_enable_debug_output) {x}
	#define MQTT_LOG_ERR(M, ...) if (g_mqtt_enable_err_output) {_LOG_ERR("MQTT", M, ##__VA_ARGS__);}
	#define MQTT_LOG_WARN(M, ...) if (g_mqtt_enable_warn_output) {_LOG_WARN("MQTT", M, ##__VA_ARGS__);}
	#define MQTT_LOG_INFO(M, ...) if (g_mqtt_enable_info_output) {_LOG_INFO("MQTT", M, ##__VA_ARGS__);}
	#define MQTT_LOG_ACTION(x, M, ...) if (g_mqtt_enable_info_output) {_LOG_ACTION("MQTT", M, ##__VA_ARGS__); x;}
	#define MQTT_LOG_EXIT(M, ...) if (g_mqtt_enable_info_output) {_LOG_EXIT("MQTT", M, ##__VA_ARGS__);}
#else
	//! \note Allow for the DBG macros to be customized (custom output channels).
	#define MQTT_DEBUG(M, ...)
	#define MQTT_DEBUG_( x )
	#define MQTT_LOG_ERR(M, ...)
	#define MQTT_LOG_WARN(M, ...)
	#define MQTT_LOG_INFO(M, ...)
	#define MQTT_LOG_ACTION(x, M, ...)
	#define MQTT_LOG_EXIT(M, ...)
#endif

#define MQTT_CHECK_ERR(A, M, ...) 			_CHECK_ERR 		(MQTT_LOG_ERR, A, M, ##__VA_ARGS__)
#define MQTT_CHECK_WARN(A, M, ...) 			_CHECK_WARN 	(MQTT_LOG_WARN, A, M, ##__VA_ARGS__)
#define MQTT_CHECK_INFO(A, M, ...) 			_CHECK_INFO 	(MQTT_LOG_INFO, A, M, ##__VA_ARGS__)
#define MQTT_CHECK_EXIT(A, M, ...) 			_CHECK_EXIT 	(MQTT_LOG_EXIT, A, M, ##__VA_ARGS__)
#define MQTT_CHECK_DEBUG(A, M, ...) 		_CHECK_DEBUG 	(MQTT_debug, A, M, ##__VA_ARGS__)
#define MQTT_CHECK_ERR_RE(A, E, M, ...) 	_CHECK_ERR_RE	(MQTT_LOG_ERR, A, E, M, ##__VA_ARGS__)
#define MQTT_CHECK_WARN_RE(A, E, M, ...) 	_CHECK_WARN_RE	(MQTT_LOG_WARN, A, E, M, ##__VA_ARGS__)
#define MQTT_CHECK_INFO_RE(A, E, M, ...) 	_CHECK_INFO_RE	(MQTT_LOG_INFO, A, E, M, ##__VA_ARGS__)
#define MQTT_CHECK_EXIT_RE(A, E, M, ...) 	_CHECK_EXIT_RE	(MQTT_LOG_EXIT, A, E, M, ##__VA_ARGS__)
#define MQTT_CHECK_DEBUG_RE(A, E, M, ...) 	_CHECK_DEBUG_RE	(MQTT_debug, A, E, M, ##__VA_ARGS__)

#define MQTT_SENTINEL(M, ...)  { MQTT_LOG_ERR(M, ##__VA_ARGS__); errno=0; goto error; }
#define MQTT_CHECK_MEM(A) MQTT_CHECK_ERR((A), "Out of memory.")

uint8_t mqtt_enable_debug_output( uint8_t enabled );
uint8_t mqtt_enable_err_output( uint8_t enabled );
uint8_t mqtt_enable_warn_output( uint8_t enabled );
uint8_t mqtt_enable_info_output( uint8_t enabled );
uint8_t mqtt_enable_all_output( uint8_t enabled );

#endif // 
