/**
 * @file icp.h
 * The library containing core ICP functionality.
 */
#pragma once
#ifndef ICP_H
#define ICP_H

#include "icp_config.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifndef FALSE
#define FALSE       (0)
#endif

#ifndef TRUE
#define TRUE        (!FALSE)
#endif
 
typedef uint8_t bool_t;

//! "Not applicable"/"Not available".
// #define ICP_NA_VALUE -10

// Length of the packet head in bytes.
#define ICP_PACKET_HEAD_LENGTH 4
// Length of the packet tail in bytes.
#define ICP_PACKET_TAIL_LENGTH 2

//! Minimal possible length of a non-escaped packet (with sync bytes included). Zero-length payload.
#define ICP_MIN_PACKET_LENGTH (ICP_PACKET_HEAD_LENGTH + ICP_PACKET_TAIL_LENGTH + 1)

// Maximum length of the data inside a packet in bytes.
#define ICP_MAX_PAYLOAD_LENGTH (BUFFER_LEN/2 - ICP_PACKET_HEAD_LENGTH - ICP_PACKET_TAIL_LENGTH)
#define ICP_MIN_PAYLOAD_LENGTH 1

/**
 * Maximal total length of the packet in bytes. MAX_PAYLOAD_LENGTH is
 * defined by the user.
 */
#define ICP_MAX_PACKET_LENGTH (ICP_MAX_PAYLOAD_LENGTH + ICP_MIN_PACKET_LENGTH)

typedef uint16_t 	buf_index_t;
typedef uint16_t 	checksum_t;
typedef uint16_t 	icp_time_t; // system time in ms

typedef void 		*icp_callback_t;
#define ICP_callback_initializer NULL

/**
 * TODO
 */
typedef enum role_et{
	NO_ROLE = 0,
	TX,
	RX,
	LISTEN_IN,
	NUM_OF_ROLES
}role_t; 

/**
 * ICP's packet structure. Used for both input and output.
 */
typedef struct icp_packet_ts {
	uint8_t 	destination; ///< Target device number or broadcast.
	uint8_t 	source; ///< Target device number.
	buf_index_t data_length; ///< Length of the data. Must be MAX_DATA_LENGTH or less.
	uint8_t 	*data; ///< Data to be sent.
	checksum_t 	checksum;
	icp_time_t 	receive_timestamp;
	icp_time_t 	receive2_timestamp;
} icp_packet_t;

#define ICP_packet_initializer { 0, 0, 0, NULL, 0 }

// Each packet field's offset from the packet's first byte.
typedef enum packet_field_offset_te {
	DESTINATION_OFFSET,
	SOURCE_OFFSET,
	PAYLOAD_LEN_OFFSET,
	PAYLOAD_LEN_OFFSET_2,
	PAYLOAD_OFFSET,
} packet_field_offset_t;

typedef enum icp_error_te {
	ICP_SUCCESS = 0,
	ICP_BUSY,
	ICP_INVALID_PARAMETERS,
	// Return values for more in-depth debugging or monitoring
	ICP_TOO_SHORT_PACKET,	///< An impossibly short packet?
	ICP_TOO_SHORT_PAYLOAD,	///< Payload shorter than described in the header?
	ICP_FAWLTY_CHECKSUM,	///< A faulty checksum?
	ICP_WRONG_RECIPIENT,	///< No local endpoint matches the packet destination
	ICP_UNKNOWN_DESTINATION,	 ///< Received a packet with a destination that is not in our routing table.
	ICP_PACKET_COULD_NOT_BE_DELIVERED, ///< ICP did not succeed in sending this packet through any link.
	NUM_OF_ERROR_CODES
} icp_error_t;

/**
 * Configuration object containing all user-configurable parameters of ICP.
 */
typedef struct icp_config_ts {
	icp_callback_t bytes_out_cb;
	icp_callback_t packet_received_cb;
	icp_callback_t get_time_cb;	
	icp_callback_t notify_packet_ack_cb; 

	icp_callback_t set_access_sig_cb;
	icp_callback_t clear_access_sig_cb;
	icp_callback_t get_access_sig_cb;

	icp_callback_t set_shudup_sig_cb;
	icp_callback_t clear_shudup_sig_cb;
	icp_callback_t get_shudup_sig_cb;

	icp_callback_t error_cb; // Optional. Defaults to NULL.
	icp_callback_t notify_wrong_recipient_cb; // Optional. Defaults to NULL.	

	icp_time_t transmition_timeout; ///< Timeout for sending a packet. Defaults to TODO (slowest transmition time X2)
	icp_time_t ack_timeout; ///< Timeout for waiting for ACK.

	// //! If the GET_TIME callback does not wrap around after UINT16_MAX (the default value), update this value.
	// //! Set this to the highest possible value before wrap-around occurs.
	// icp_time_t timer_custom_overflow;

	uint8_t *rx_buffer; ///< Receive buffer.
	buf_index_t rx_buf_size; ///< Size of the receive buffer.
	buf_index_t rx_buf_pos; ///< Position at which the next received byte will be stored.

	uint8_t *tx_buffer; ///< Transmit buffer.
	buf_index_t tx_buf_size; ///< Size of the transmit buffer.
	buf_index_t tx_buf_start; ///< Position of the first byte in the transmit buffer waiting to be sent.
	buf_index_t tx_buf_end; ///< Position of the last byte in the transmit buffer waiting to be sent.
	
	bool_t			destination_received;
	uint8_t			received_in_this_frame;
	bool_t			waiting_for_ack;
	bool_t			listen_to_all;
	role_t 			role;	

} icp_config_t;

//! ICP's central configuration.
icp_config_t *g_conf;

/**
 * @addtogroup Platform specific callbacks
 * @{
 */
/**
 * Callback function used by ICP to output individual bytes
 * 
 * @param output_byte_array Array of bytes to be passed to the link.
 * @param array_len Number of bytes to be passed to the link.
 *
 * @return The number of bytes that were successfully processed (e.g. put into a UART buffer).
 */
typedef uint8_t (*icp_bytes_out_cb_t)( const uint8_t* output_byte_array, buf_index_t array_len );

#define ICP_BYTES_OUT( byte_array, array_len ) \
	((icp_bytes_out_cb_t) g_conf->bytes_out_cb)( byte_array, array_len )
	
/**
 * Callback function used by ICP to notify the user of new received packets.
 * 
 * @param new_packet Pointer to the received packet. The pointer will not be valid
 *		after returning from this callback.
 */
typedef uint8_t (*icp_packet_received_cb_t)( icp_packet_t *new_packet );

#define ICP_PACKET_RECEIVED( packet ) \
	( g_conf->packet_received_cb != NULL ? \
		((icp_packet_received_cb_t) g_conf->packet_received_cb)( packet ) : \
		0 )

/**
 * Callback function used by ICP to get current time to implement timeouts.
 * Must return time in the same units that are used in timeout configuration.
 */
typedef icp_time_t (*icp_get_time_cb_t)( void );

/**
 * @return Current time in the same units that the link timeouts are defined in.
 */
 // TODO
#define ICP_GET_TIME() ((icp_get_time_cb_t) g_conf->get_time_cb)( )

/**
 * Callback function used by ICP to report errors to the user.
 * 
 * @param error The code of the error that occurred.
 * @param packet_data Content of the erroneous packet. NULL, if not applicable.
 * @param packet_length Length of the erroneous packet.
 */
typedef uint8_t (*icp_error_cb_t)( icp_error_t error, uint8_t* packet_data, buf_index_t packet_length );

// Error callback is disabled, if error_cb == NULL.
#define ICP_ERROR( error, packet_data, packet_length ) \
	( g_conf->error_cb != NULL ? \
		((icp_error_cb_t) g_conf->error_cb)( error, packet_data, packet_length ) : \
		0 )

/**
 * Callback function used by ICP to set ACCESS signal to HIGH.
 * 
 * @retval ICP_SUCCESS Signal line was successfully set.
 * @retval ICP_BUSY Could not set signal.
 */
typedef uint8_t (*icp_set_access_sig_cb_t)( void );

#define ICP_SET_ACCESS_SIG( void ) \
	( g_conf->set_access_sig_cb != NULL ? \
		((icp_set_access_sig_cb_t) g_conf->set_access_sig_cb)( void ) : \
		0 )

/**
 * Callback function used by ICP to clear ACCESS signal to LOW.
 * 
 * @retval ICP_SUCCESS Signal line was successfully cleared.
 * @retval ICP_BUSY Could not clear signal.
 */
typedef uint8_t (*icp_clear_access_sig_cb_t)( void );

#define ICP_CLEAR_ACCESS_SIG( void ) \
	( g_conf->clear_access_sig_cb != NULL ? \
		((icp_clear_access_sig_cb_t) g_conf->clear_access_sig_cb)( void ) : \
		0 )

/**
 * Callback function used by ICP to get ACCESS signal.
 * 
 * @retval 0 Signal line is LOW.
 * @retval 1 Signal line is HIGH.
 */
// TODO CB vs field in struct mainida töös, miks, turvalisem
typedef uint8_t (*icp_get_access_sig_cb_t)( void );

#define ICP_GET_ACCESS_SIG( void ) \
	( g_conf->get_access_sig_cb != NULL ? \
		((icp_get_access_sig_cb_t) g_conf->get_access_sig_cb)( void ) : \
		0 )

/**
 * Callback function used by ICP to set SHUDUP signal to HIGH.
 * 
 * @retval ICP_SUCCESS Signal line was successfully set.
 * @retval ICP_BUSY Could not set signal.
 */
typedef uint8_t (*icp_set_shudup_sig_cb_t)( void );

#define ICP_SET_SHUDUP_SIG( void ) \
	( g_conf->set_shudup_sig_cb != NULL ? \
		((icp_set_shudup_sig_cb_t) g_conf->set_shudup_sig_cb)( void ) : \
		0 )

/**
 * Callback function used by ICP to clear SHUDUP signal to LOW.
 * 
 * @retval ICP_SUCCESS Signal line was successfully cleared.
 * @retval ICP_BUSY Could not clear signal.
 */
typedef uint8_t (*icp_clear_shudup_sig_cb_t)( void );

#define ICP_CLEAR_SHUDUP_SIG( void ) \
	( g_conf->clear_shudup_sig_cb != NULL ? \
		((icp_clear_shudup_sig_cb_t) g_conf->clear_shudup_sig_cb)( void ) : \
		0 )

/**
 * Callback function used by ICP to get SHUDUP signal.
 * 
 * @retval 0 Signal line is LOW.
 * @retval 1 Signal line is HIGH.
 */
typedef uint8_t (*icp_get_shudup_sig_cb_t)( void );

#define ICP_GET_SHUDUP_SIG( void ) \
	( g_conf->get_shudup_sig_cb != NULL ? \
		((icp_get_shudup_sig_cb_t) g_conf->get_shudup_sig_cb)( void ) : \
		0 )

/**
 * Callback function used by ICP to notify the user that current frame is not meant for this system. 
 *
 * All further bytes in interrupts can be disabled (until transmittion end).
 *
 * @Note Optional
 *
 * @Warning This function is called from icp_bytes_in interrupt. Make it short.
 */
typedef uint8_t (*icp_notify_wrong_recipient_cb_t)( void );

#define ICP_NOTIFY_WRONG_RECIPIENT( void ) \
	( g_conf->notify_wrong_recipient_cb != NULL ? \
		((icp_notify_wrong_recipient_cb_t) g_conf->notify_wrong_recipient_cb)( void ) : \
		0 )

/**
 * Callback function used by ICP to notify the user that ACK for last frame has been received.
 */
typedef uint8_t (*icp_notify_packet_ack_cb_t)( void );

#define ICP_NOTIFY_PACKET_ACK( void ) \
	( g_conf->notify_packet_ack_cb != NULL ? \
		((icp_notify_packet_ack_cb_t) g_conf->notify_packet_ack_cb)( void ) : \
		0 )

/**
 * @}
 */

/**
 * @addtogroup ICP public API
 * @{
 */
/**
 * Set some nice default values in a icp_config_t structure.
 * @param conf ICP configuration file to initialize.
 */
uint8_t icp_init_conf_struct( icp_config_t *conf );

/**
 * Sets up and configures ICP. Call icp_init_conf_struct() on the config struct first.
 * 
 * @param[in] conf ICP's configuration. Its contents will not be copied, so
 *                 this structure must not be deleted after initialization.
 *
 * @retval ICP_INVALID_PARAMETERS, if either \c conf or its members are \c NULL.
 * @retval ICP_SUCCESS Everything went as expected.
 */
uint8_t icp_init( const icp_config_t *conf );

/**
 * Destroys ICP.
 */
uint8_t icp_deinit( void );

/**
 * Hands over an array of received bytes to ICP.
 *
 * @param link The link's number these bytes were received from.
 * @param byte Array of received bytes.
 * @param num_bytes Number of bytes in the byte_array.
 */
uint8_t icp_bytes_in( const uint8_t *byte_array, buf_index_t num_bytes );

/**
 * Sends data from this system to another. Formats data to a packet according to the ICP's specification.
 * 
 * @param[in] destination_mac Destination address where to send the data.
 * @param[in] *data Pointer to the data array to be sent.
 * @param[in] data_length Data length.
 * 
 * @retval ICP_SUCCESS Data was sent (does not necessarily mean that the
 *		packet was actually successfully delivered).
 * @retval ICP_BUSY All All possible links are busy right now, try again later.
 * @retval ICP_INVALID_PARAMETERS One or more of the parameters is invalid.
 */
uint8_t icp_send_data( mac_addr_t destination_mac, const uint8_t *data, buf_index_t data_length );

/**
 * Sends a packet from this system to another. Formats a packet according to the ICP's specification as a byte array and puts it to TX buffer.
 * 
 * @param[in] packet Packet to be sent.
 * 
 * @retval ICP_SUCCESS Packet was sent (does not necessarily mean that the
 *		packet was actually successfully delivered).
 * @retval ICP_BUSY All All possible links are busy right now, try again later.
 * @retval ICP_INVALID_PARAMETERS One or more of the parameters is invalid.
 */
uint8_t icp_send_packet( const icp_packet_t *packet );

/**
 * Function to notify ICP that transmition of the last frame has finished.
 */
uint8_t icp_notify_bytes_out_finished( void );

/**
 * Function to notify ICP that ACCESS line has been set to LOW.
 */
uint8_t icp_notify_acces_low(); 

/**
 * Function to notify ICP that ACCESS line has been set to HIGH.
 */
uint8_t icp_notify_acces_high(); 

/**
 * Function to notify ICP that SHUDUP line has been set to LOW.
 */
uint8_t icp_notify_shudup_low(); 

/**
 * Function to notify ICP that SHUDUP line has been set to HIGH.
 */
uint8_t icp_notify_shudup_high(); 

/**
 * Enable or disable the option to listen in to every frame on the bus.
 * 
 * @param[in] enable Value to be set. True (1) or False (0).
 */
uint8_t icp_set_listen_to_all( bool_t enable ); 

/**
 * Function to initiate ICP update. 
 *
 * ICP update processes the RX and TX buffer and acts accordingly.
 */
uint8_t icp_update( void );

/**
 * @}
 */
/**
 * @addtogroup ICP internal API
 * @{
 */

/**
 * TODO
 */
uint8_t icp_ack_timeout( void );

/**
 * If the transmit buffer is not empty, try to send all its contents via ICP_BYTES_OUT.
 * @return Whether any bytes remain in the transmit buffer.
 */
bool_t icp_process_tx_buffer( void );

/**
 * TODO
 */
uint8_t icp_flush_tx_buffer( void );

/**
 * Looks for any packets in a the received bytes' buffer. Correct
 * packets will be handed over to ICP via icp_handle_received_packet().
 * After that the processed bytes which can't contain any new packets will be
 * purged from the buffer.
 * @return The number of correct packets found in the buffer.
 */
uint8_t icp_process_rx_buffer();

/**
 * TODO
 */
uint8_t icp_flush_rx_buffer(); 

/**
 * TODO
 */
// uint8_t icp_pop_n_bytes_from_rx_buffer( uint8_t num_of_bytes ); 



#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ICP_H
