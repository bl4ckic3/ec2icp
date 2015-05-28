
#include <stdint.h>
#include <stdio.h>
#include "string.h"
#include <stdlib.h>
#include "icp.h"
#include "dbg.h"

#include <unistd.h>
#include "mqtt.h"

bool_t icp_update_in_progress 	= FALSE;
uint8_t destination; // TODO find a suitable place for this

#define timeout_exceeded( start_time, current_time, timeout ) \
	( (icp_time_t)(start_time <= current_time ? \
		current_time - start_time : \
		g_conf->timer_custom_overflow - start_time + current_time + 1 ) \
	>= timeout )

/**
 * ICP public API
 */

uint8_t icp_init_conf_struct( icp_config_t *p_conf ) {
	ICP_DEBUG_(ICP_CHECK_MEM(p_conf));

	p_conf->bytes_out_cb 				= NULL;
	p_conf->packet_received_cb 			= NULL;
	p_conf->get_time_cb 				= NULL;
	p_conf->notify_packet_ack_cb 		= NULL;
	p_conf->set_access_sig_cb 			= NULL;
	p_conf->clear_access_sig_cb 		= NULL;
	p_conf->get_access_sig_cb 			= NULL;
	p_conf->set_shudup_sig_cb 			= NULL;
	p_conf->clear_shudup_sig_cb 		= NULL;
	p_conf->get_shudup_sig_cb 			= NULL;
	p_conf->error_cb 					= NULL;
	p_conf->notify_wrong_recipient_cb 	= NULL;

	p_conf->transmition_timeout 		= 10000;
	p_conf->ack_timeout 				= 5;

	// p_conf->timer_custom_overflow 	= UINT16_MAX;

	p_conf->waiting_for_ack				= FALSE;
	p_conf->destination_received		= FALSE;
	p_conf->listen_to_all				= FALSE;
	p_conf->received_in_this_frame		= 0;
	p_conf->role						= NO_ROLE;

	return ICP_SUCCESS;

error:
	return ICP_INVALID_PARAMETERS;
}

uint8_t icp_init( const icp_config_t *p_conf ) {
	// These must be set.
	ICP_CHECK_ERR(p_conf						!= NULL, "ICP conf struct not valid");
	ICP_CHECK_ERR(p_conf->bytes_out_cb 			!= NULL, "bytes_out_cb is not registered");
	ICP_CHECK_ERR(p_conf->packet_received_cb 	!= NULL, "packet_received_cb is not registered");
	ICP_CHECK_ERR(p_conf->get_time_cb 			!= NULL, "get_time_cb is not registered");
	ICP_CHECK_ERR(p_conf->notify_packet_ack_cb	!= NULL, "notify_packet_ack_cb is not registered");
	ICP_CHECK_ERR(p_conf->set_access_sig_cb 	!= NULL, "set_access_sig_cb is not registered");
	ICP_CHECK_ERR(p_conf->clear_access_sig_cb	!= NULL, "clear_access_sig_cb is not registered");
	ICP_CHECK_ERR(p_conf->get_access_sig_cb 	!= NULL, "get_access_sig_cb is not registered");
	ICP_CHECK_ERR(p_conf->set_shudup_sig_cb 	!= NULL, "set_shudup_sig_cb is not registered");
	ICP_CHECK_ERR(p_conf->clear_shudup_sig_cb	!= NULL, "clear_shudup_sig_cb is not registered");
	ICP_CHECK_ERR(p_conf->get_shudup_sig_cb 	!= NULL, "get_shudup_sig_cb is not registered");
	// TODO check if something is missing from here

	g_conf = (icp_config_t*) p_conf;

	g_conf->rx_buffer = (uint8_t*) icp_malloc( BUFFER_LEN * sizeof(uint8_t) );
	ICP_CHECK_ERR(g_conf->rx_buffer != NULL, "could not allocate memory for ICP rx buffer");
	icp_memset(g_conf->rx_buffer, 0xFF, BUFFER_LEN * sizeof(uint8_t));
	g_conf->rx_buf_pos = 0;
	g_conf->rx_buf_size = (buf_index_t) BUFFER_LEN;

	g_conf->tx_buffer = (uint8_t*) icp_malloc( BUFFER_LEN * sizeof(uint8_t) );
	ICP_CHECK_ERR(g_conf->tx_buffer != NULL, "could not allocate memory for ICP tx buffer");
	g_conf->tx_buf_start = 0;
	g_conf->tx_buf_end = 0;
	g_conf->tx_buf_size = (buf_index_t) BUFFER_LEN;

	icp_update_in_progress = FALSE;

	return ICP_SUCCESS;
error:
	if (g_conf) {
		icp_free(g_conf);
	}
	return ICP_INVALID_PARAMETERS;
}

uint8_t icp_deinit( void ) {
	ICP_DEBUG("Done");
	return ICP_SUCCESS;
}

uint8_t icp_bytes_in( const uint8_t *byte_array, buf_index_t num_bytes ) {
	//! \note icp_byte_in is called from an interrupt. Printing must not be called
	//! from any interrupts.

	// TODO remove role from conf, tee uus struct
	if (g_conf->role == RX && !g_conf->destination_received){

		g_conf->destination_received = TRUE;

		ICP_LOG_INFO("Checking if this frame is meant for me.");
		if (byte_array[0] != local_mac_addr){

			g_conf->role = (g_conf->listen_to_all ? LISTEN_IN : NO_ROLE);
			
			ICP_LOG_INFO("ASSUME ROLE: %s", (g_conf->listen_to_all ? "LISTEN_IN" : "NO_ROLE"));
			if(g_conf->role == NO_ROLE){	
				ICP_LOG_INFO("Flushing RX buffer");
				icp_flush_rx_buffer();
				ICP_LOG_INFO("Notify host machine that this frame is not for us.");
				ICP_NOTIFY_WRONG_RECIPIENT();
			} else if (g_conf->role == RX) {
				ICP_LOG_INFO("Frame is meant for me.");
			} else if (g_conf->role == LISTEN_IN) {
				ICP_LOG_INFO("Frame is not meant for me, but I am listening nevertheless");
			}
		}
	}

	ICP_CHECK_EXIT(g_conf->role == RX || g_conf->role == LISTEN_IN ,"Frame not meant for me");
	ICP_CHECK_EXIT(g_conf->rx_buf_pos < g_conf->rx_buf_size, "RX buffer OVF. Pos %d, size %d", g_conf->rx_buf_pos, g_conf->rx_buf_size);// TODO add meaningful returncode
	ICP_CHECK_EXIT(g_conf->rx_buf_pos + num_bytes < g_conf->rx_buf_size, "RX buffer OVF.");// TODO add meaningful returncode
	
	if (num_bytes != 1) {
		icp_memmove( g_conf->rx_buffer + g_conf->rx_buf_pos, byte_array, num_bytes );
		g_conf->rx_buf_pos += num_bytes;
	} else {
		g_conf->rx_buffer[g_conf->rx_buf_pos++] = *byte_array;
	}
	ICP_LOG_INFO("Put %d bytes to RX buffer.", num_bytes);

	// ICP_DEBUG_({
	// 	uint8_t i = 0;
	// 	printf("[ ");
	// 	for (; i < num_bytes; i++)
	// 		printf("%02X ", byte_array[i]);
	// 	puts("]");
	// });

	ICP_DEBUG("Returning");
	return ICP_SUCCESS;
end:
	return ICP_BUSY;
}

uint8_t icp_send_data( mac_addr_t destination_mac, const uint8_t *data, buf_index_t data_length ) {
	icp_packet_t packet = ICP_packet_initializer;
	packet.destination 	= destination_mac;
	packet.data_length 	= data_length;
	packet.data 		= (uint8_t *)data;
	return icp_send_packet(&packet);
}
uint8_t icp_send_packet( const icp_packet_t *p_packet ) {
	uint8_t 			rc 		= ICP_INVALID_PARAMETERS;
	uint8_t 			i 		= 0;
	buf_index_t 		buf_i 	= 0;
	buf_index_t			data_len;

	///***  DEBUG.  ***///

	ICP_DEBUG_({
		ICP_DEBUG("dest: %s; data[%d]: ", mac_addrs[p_packet->destination], p_packet->data_length);
		for (i=0; i < p_packet->data_length; i++) {
			putchar( i ? ' ': '[' );
			printf("%2x", p_packet->data[i]);
		}
		printf("] \"");
		for (i=0; i < p_packet->data_length; i++) {
			putchar( p_packet->data[i] );
		}
		puts("\" );");
	}); // ICP_DEBUG_

	ICP_LOG_INFO("Got packet to send from host.");

	///***  Validate input.  ***///

	// Validate packet and data existance
	ICP_CHECK_ERR(p_packet != NULL, "Packet validation failed: Packet is corrupt.");
	ICP_LOG_INFO("Packet validation successful.");
	ICP_CHECK_ERR(!(p_packet->data == NULL && p_packet->data_length != 0), "Packet validation failed: Packet data is corrupt.");
	ICP_LOG_INFO("Packet data validation successful.");

	// Validate data length
	ICP_CHECK_ERR(p_packet->data_length <= ICP_MAX_PAYLOAD_LENGTH, 
					"Packet validation failed: Length of data (%d) too long.", p_packet->data_length);
	ICP_CHECK_ERR(p_packet->data_length > ICP_MIN_PAYLOAD_LENGTH, 
					"Packet validation failed: Length of data (%d) too short.", p_packet->data_length);
	ICP_LOG_INFO("Packet data length validation successful.");
	data_len  = p_packet->data_length - 1;

	// Validate destination
	ICP_CHECK_ERR(p_packet->destination < NUM_OF_NODES && p_packet->destination >= 0, 
					"Packet validation failed: Packet destination (%d) incorrect.", p_packet->destination);
	ICP_LOG_INFO("Packet destination validation successful.");
	

	
	///***  Translate packet to bytes  ***///

	g_conf->tx_buf_start = 0;
	g_conf->tx_buf_end = 0;

	g_conf->tx_buffer[buf_i++] = p_packet->destination;
	g_conf->tx_buffer[buf_i++] = local_mac_addr;
	g_conf->tx_buffer[buf_i++] = data_len >> 8;
	g_conf->tx_buffer[buf_i++] = (uint8_t)(data_len & 0x00FF);

	if (p_packet->data_length) {
		icp_memmove( g_conf->tx_buffer + buf_i, p_packet->data, p_packet->data_length );
		buf_i += p_packet->data_length;
	}

	///***  Compute the checksum and add it directly to the buffer.  ***///
	
	// TODO
	// Compute the checksum and add it directly to the buffer.
	// fletcher16(&g_conf->tx_buffer[buf_i],
	// 	&g_conf->tx_buffer[buf_i+1],
	// 	g_conf->tx_buffer,
	// 	buf_i);
	// buf_i += 2;
	g_conf->tx_buffer[buf_i++] = 0x55;
	g_conf->tx_buffer[buf_i++] = 0x55;
	ICP_LOG_INFO("Calculated and added checksum to the packet.");

	g_conf->tx_buf_end += buf_i-1;
	ICP_LOG_INFO("Parsed packet and put %d bytes to TX buffer.", buf_i);

	// if (send_immediately) {
	// 	process_tx_queue( GET_TIME() );
	// }
	
	ICP_DEBUG("Returning");
	return ICP_SUCCESS;
error:
	return rc;
}

uint8_t icp_notify_bytes_out_finished( ) {
	//! \note icp_notify_bytes_out_finished might be called from an interrupt. Printing must not be called
	//! from any interrupts.
	uint8_t rc = FALSE; // Assume fail

	if (g_conf->tx_buffer[0] == BROADCAST){
		ICP_CHECK_ERR( ICP_CLEAR_ACCESS_SIG() == ICP_SUCCESS, "Could not clear bus for transmitting. ICP bus is jammed. Can't send data!" );
		ICP_LOG_INFO( "ICP bus released. ASSUME ROLE: NO_ROLE");
		g_conf->role = NO_ROLE;
	} else {
		ICP_LOG_INFO( "Host system finsihed sending current frame. Waiting for ack...");
		g_conf->waiting_for_ack = TRUE;
	}
	
	ICP_DEBUG("Returning");
error:
	return rc;
}

uint8_t icp_notify_acces_inactive( ) {
	//! \note icp_notify_acces_inactive might be called from an interrupt. Printing must not be called
	//! from any interrupts.
	uint8_t rc = FALSE; // Assume fail
	ICP_CHECK_ERR(rc = ICP_GET_ACCESS_SIG() == INACTIVE,"Access is not INACTIVE");
	
	if (g_conf->waiting_for_ack && g_conf->role == TX){
		ICP_LOG_INFO( "ACK received. ASSUME ROLE: NO_ROLE");
		g_conf->role = NO_ROLE;
		g_conf->waiting_for_ack = FALSE;
		ICP_NOTIFY_PACKET_ACK();
	} else if (g_conf->role == RX || g_conf->role == LISTEN_IN){ // TODO: WHAT IF BROADCAST
		ICP_LOG_INFO( "Transmition canceled. ASSUME ROLE: NO_ROLE"); // TODO: WHAT IF CURRENT SYSTEM DRIVES ACCESS INACTIVE
		g_conf->role = NO_ROLE;
		icp_flush_rx_buffer();
	} else if (g_conf->role == NO_ROLE){
		ICP_LOG_INFO( "Got notice that bus is clear.");
	} else if (g_conf->role == TX){
		ICP_LOG_INFO( "Got notice that bus is clear.");
	}
		
	ICP_DEBUG("Returning");
error:
	return rc;
}

uint8_t icp_notify_acces_active( ) {
	//! \note icp_notify_acces_active might be called from an interrupt. Printing must not be called
	//! from any interrupts.
	uint8_t rc = FALSE; // Assume fail
	ICP_CHECK_ERR(rc = ICP_GET_ACCESS_SIG() == ACTIVE,"Access is not ACTIVE");
	
	ICP_LOG_INFO( "Someone is starting to transmit. ASSUME ROLE: RX");
	g_conf->role = RX;
	g_conf->received_in_this_frame = 0;
	g_conf->destination_received = FALSE;

	ICP_DEBUG("Returning");
error:
	return rc;
}

uint8_t icp_set_listen_to_all( bool_t enable ) {
	ICP_LOG_INFO( "Set listen_to_all to %s", (enable ? "TRUE":"FALSE"));
	g_conf->listen_to_all = enable;
	ICP_DEBUG("Returning");
	return TRUE;
}

uint8_t ack_timeout_cnt = 0;

uint8_t icp_update( void ) {

	ICP_CHECK_EXIT(icp_update_in_progress == FALSE, "ICP update in progress.");
	icp_update_in_progress = TRUE;
	
	ICP_LOG_INFO("Process bytes in RX buffer");
	icp_process_rx_buffer();

	ICP_CHECK_EXIT(g_conf->role == NO_ROLE,"I have a role. Frame transmition in progress.");
	ICP_LOG_INFO("Trasmit bytes in TX buffer");
	icp_process_tx_buffer();
	
	icp_update_in_progress = FALSE;

	ICP_DEBUG("Returning");
	return ICP_SUCCESS;

end:
	if ( g_conf->waiting_for_ack ) {
		// timeout_exceeded(...); TODO
		if ( g_conf->ack_timeout <= ack_timeout_cnt++) {
			icp_ack_timeout();
		}
	}

	icp_update_in_progress = FALSE;
	return ICP_BUSY;
}



/**
 * ICP internal API
 */


uint8_t icp_ack_timeout( void ) {
	ICP_LOG_WARN("TIMEOUT when waiting for ACK!");
	ack_timeout_cnt = 0;
	g_conf->waiting_for_ack = FALSE;
	ICP_LOG_INFO("ASSUME ROLE: NO_ROLE");
	g_conf->role = NO_ROLE;
	ICP_CLEAR_ACCESS_SIG();
	return ICP_SUCCESS;
}

bool_t icp_process_tx_buffer( void ) {
	ICP_CHECK_EXIT(g_conf->tx_buf_start <= g_conf->tx_buf_end-1, "No bytes to transmit.");
	
	if (g_conf->role != TX){
		// Wait for line to be free
		ICP_CHECK_EXIT( ICP_GET_ACCESS_SIG() == INACTIVE, "ICP bus is busy. Can't send data!" );
		ICP_CHECK_EXIT( ICP_SET_ACCESS_SIG() == ICP_SUCCESS, "Could not reserve bus for transmitting. ICP bus is busy. Can't send data!" );
		ICP_LOG_INFO( "ICP bus reserved for transmitting. ASSUME ROLE: TX");
		g_conf->role = TX;
	}

	ICP_LOG_INFO("%d bytes in TX buffer to transmit", g_conf->tx_buf_end - g_conf->tx_buf_start + 1);
	g_conf->tx_buf_start += ICP_BYTES_OUT( &g_conf->tx_buffer[g_conf->tx_buf_start],
	                                     g_conf->tx_buf_end - g_conf->tx_buf_start + 1);
	
end:
	ICP_DEBUG("Returning");
	return (g_conf->tx_buf_start > g_conf->tx_buf_end);
}

// TODO
uint8_t icp_flush_tx_buffer( void ) {
	ICP_DEBUG("Returning");
	return ICP_SUCCESS;
}

uint8_t icp_process_rx_buffer( void ) {
	// Buffer position must be copied for thread safety.
	buf_index_t buffer_position = g_conf->rx_buf_pos;
	buf_index_t i 		= 0; 

	icp_packet_t 	packet 			= ICP_packet_initializer;
	uint8_t 		*packet_data;

	ICP_CHECK_EXIT(buffer_position != 0, "No bytes in RX buffer.");
	ICP_LOG_INFO("%d bytes in RX buffer to process", buffer_position);

	// ICP_DEBUG_({
	// 	printf("[ ");
	// 	for (i=0; i < buffer_position; i++) {
	// 		printf("%02X ", g_conf->rx_buffer[i]);
	// 	}
	// 	printf("]\n");
	// });
	
	// TODO: Check if running out of buffer space!!
	i = 0;
	// Look for valid destination byte and get the packet start pointer
	ICP_CHECK_EXIT(g_conf->rx_buffer[i] < NUM_OF_NODES, "Did not find valid destination MAC @ %d : %d", i, g_conf->rx_buffer[i]);
	ICP_LOG_INFO("Found valid destination MAC @ %d", i);
	packet.destination 	= g_conf->rx_buffer[i++];

	// Look for valid source byte
	ICP_CHECK_EXIT(g_conf->rx_buffer[i] < NUM_OF_NODES, "Did not find valid source MAC @ %d : %d", i, g_conf->rx_buffer[i]);
	ICP_LOG_INFO("Found valid source MAC @ %d", i);
	packet.source 		= g_conf->rx_buffer[i++];

	// Look for valid data length bytes
	ICP_CHECK_EXIT((((g_conf->rx_buffer[i]<<8)|(g_conf->rx_buffer[i+1])) <= ICP_MAX_PAYLOAD_LENGTH) &&
					(((g_conf->rx_buffer[i]<<8)|(g_conf->rx_buffer[i+1])) >= ICP_MIN_PAYLOAD_LENGTH), 
					"Did not find valid data length bytes @ %d", i);
	ICP_LOG_INFO("Found valid data length bytes @ %d : %d", i, (g_conf->rx_buffer[i]<<8)|(g_conf->rx_buffer[i+1]));
	packet.data_length 	= (g_conf->rx_buffer[i]<<8)|(g_conf->rx_buffer[i+1]);
	i += 2;

	packet_data = (uint8_t*) icp_malloc( packet.data_length * sizeof(uint8_t) );

	icp_memmove( packet_data, g_conf->rx_buffer + i , packet.data_length+1 );
	i += packet.data_length;

	packet.data 		= packet_data;
	packet.checksum 	= (g_conf->rx_buffer[i]<<8)|(g_conf->rx_buffer[i+1]);
	packet.receive_timestamp = ICP_GET_TIME();

	// TODO Check if chekcsum is OK
	
	ICP_LOG_INFO("Found a complete packet.");

	if (g_conf->role == RX || g_conf->role == LISTEN_IN ){
		if (g_conf->role == RX) {
			ICP_LOG_INFO("Send ACK.");
			ICP_CLEAR_ACCESS_SIG();
		}
		ICP_LOG_INFO("ASSUME ROLE: NO_ROLE");
		g_conf->role = NO_ROLE;
	}

	icp_flush_rx_buffer();

	ICP_LOG_INFO("Give packet to host machine.");
	ICP_PACKET_RECEIVED( &packet );

end:

	ICP_DEBUG("Returning");
	return ICP_SUCCESS; // TODO Give meaningful return
}

uint8_t icp_flush_rx_buffer() {

	icp_memset(g_conf->rx_buffer, 0xFF, BUFFER_LEN * sizeof(uint8_t));
	g_conf->rx_buf_pos = 0;

	ICP_LOG_INFO("Flushed RX buffer");

	ICP_DEBUG("Returning");
	return TRUE;
}

/**
 * Functions, flags and macros for easy debugging and stuff
 */

#ifdef ICPDEBUG
bool_t g_icp_enable_debug_output = TRUE;
bool_t g_icp_enable_err_output= TRUE;
bool_t g_icp_enable_warn_output= TRUE;
bool_t g_icp_enable_info_output= TRUE;
uint8_t icp_enable_debug_output( uint8_t enabled ) {
    LOG_INFO("Setting g_icp_enable_debug_output to %d", enabled);
    g_icp_enable_debug_output = enabled;
    return 0;
}
uint8_t icp_enable_err_output( uint8_t enabled ) {
    LOG_INFO("Setting g_icp_enable_err_output to %d", enabled);
    g_icp_enable_err_output = enabled;
    return 0;
}
uint8_t icp_enable_warn_output( uint8_t enabled ) {
    LOG_INFO("Setting g_icp_enable_warn_output to %d", enabled);
    g_icp_enable_warn_output = enabled;
    return 0;
}
uint8_t icp_enable_info_output( uint8_t enabled ) {
    LOG_INFO("Setting g_icp_enable_info_output to %d", enabled);
    g_icp_enable_info_output = enabled;
    return 0;
}
uint8_t icp_enable_all_output( uint8_t enabled ) {
    icp_enable_debug_output( enabled );
    icp_enable_err_output( enabled );
    icp_enable_warn_output( enabled );
    icp_enable_info_output( enabled );
    return 0;
}
#else
uint8_t icp_enable_debug_output( uint8_t enabled ) { return 0;}
uint8_t icp_enable_err_output( uint8_t enabled ) { return 0;}
uint8_t icp_enable_warn_output( uint8_t enabled ) { return 0;}
uint8_t icp_enable_info_output( uint8_t enabled ) { return 0;}
uint8_t icp_enable_all_output( uint8_t enabled ) { return 0;}
#endif
