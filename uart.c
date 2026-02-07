/* 
 * File:   uart.c
 * Device: PIC18F4520
 */

#include "uart.h"

// Buffer memory
volatile uint8_t rx_buffer[PACKET_SIZE];
volatile uint8_t packet_received = 0;
volatile uint16_t rx_idx = 0;

void uart_init(void) {
    // Configure Pins
    TRISCbits.TRISC6 = 0; // TX as Output
    TRISCbits.TRISC7 = 1; // RX as Input

    // Baud Rate Configuration for 115200 @ 8MHz
    // Formula: Fosc / (4 * (SPBRG + 1)) -> BRGH=1, BRG16=1
    // 8000000 / (4 * (16 + 1)) = 117647 (~2.1% error, acceptable)
    TXSTAbits.BRGH = 1;   // High Speed
    BAUDCONbits.BRG16 = 1; // 16-bit Baud Rate Generator
    SPBRG = 16;
    SPBRGH = 0;

    // Enable Serial Port
    TXSTAbits.SYNC = 0;   // Asynchronous mode
    RCSTAbits.SPEN = 1;   // Enable Serial Port (Configures RX/TX pins)
    
    // Enable Transmitter
    TXSTAbits.TXEN = 1;

    // Enable Receiver
    RCSTAbits.CREN = 1;

    // Enable Interrupts for Reception
    PIE1bits.RCIE = 1;    // Enable RX Interrupt
    IPR1bits.RCIP = 1;    // High Priority (optional on basic setup)
    
    // Note: Global interrupts (GIE/PEIE) are enabled in main()
}

void uart_write(char data) {
    while (!TXSTAbits.TRMT); // Wait for Transmit Shift Register to be empty
    TXREG = data;
}

void uart_write_string(const char *text) {
    while (*text) {
        uart_write(*text++);
    }
}

// This function processes one byte at a time inside the ISR
void uart_rx_handler(void) {
    uint8_t rx_byte_tmp = RCREG; // Read the byte immediately to clear RCIF

    // Protocol State Machine (Matches your STM32 logic)
    
    // 1. Waiting for Start of Packet
    if (rx_idx == 0) {
        if (rx_byte_tmp == STX) {
            rx_buffer[rx_idx++] = rx_byte_tmp;
        }
    }
    // 2. Receiving Payload
    else if (rx_idx < (PACKET_SIZE - 1)) {
        rx_buffer[rx_idx++] = rx_byte_tmp;
    }
    // 3. Waiting for End of Packet
    else if (rx_idx == (PACKET_SIZE - 1)) {
        if (rx_byte_tmp == ETX) {
            rx_buffer[rx_idx] = rx_byte_tmp;
            packet_received = 1; // Flag complete packet for main loop
        }
        // Reset to look for next packet regardless of success
        rx_idx = 0;
    }
}