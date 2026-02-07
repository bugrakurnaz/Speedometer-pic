/* 
 * File:   uart.h
 * Author: bugra
 *
 * Created on 07 ?ubat 2026 Cumartesi, 12:35
 */

#ifndef UART_H
#define	UART_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include <stdint.h>

// Protocol Definitions
#define STX 0x02
#define ETX 0x03
#define PAYLOAD_SIZE 80
#define PACKET_SIZE (PAYLOAD_SIZE + 2) // 82 bytes

// Buffer accessible by main.c
extern volatile uint8_t rx_buffer[PACKET_SIZE];
extern volatile uint8_t packet_received;

// Functions
void uart_init(void);
void uart_write(char data);
void uart_write_string(const char *text);
void uart_rx_handler(void); // Call this from ISR

#ifdef	__cplusplus
}
#endif

#endif	/* UART_H */

