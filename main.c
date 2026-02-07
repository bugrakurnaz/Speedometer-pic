/*
 * File:   main.c
 * Author: Muammer Bugra Kurnaz
 */

// ================= CONFIGURATION =================
#pragma config OSC = INTIO67   // Internal oscillator
#pragma config WDT = OFF       // Watchdog OFF
#pragma config LVP = OFF       // Low-voltage programming OFF
#pragma config PBADEN = OFF    // PORTB digital on reset
#pragma config MCLRE = ON      // MCLR enabled

#include <xc.h>
#include <string.h>
#include "led.h"
#include "oscilattor.h"
#include "i2c_master.h"
#include "i2c_lcd.h"
#include "uart.h"

#define _XTAL_FREQ 8000000     // 8 MHz internal oscillator

char display_line_buf[21]; 

// ================= INTERRUPT SERVICE ROUTINE =================
void __interrupt() ISR(void) {
    // Check if UART Receive Interrupt triggered
    if (PIR1bits.RCIF) {
        uart_rx_handler(); // Handle the byte in uart.c
    }
}

void update_lcd_line(uint8_t row, volatile uint8_t *source) {
    // Copy 20 bytes from volatile UART buffer to local buffer
    // casting volatile away is safe here as we are in main loop and own the flag
    memcpy(display_line_buf, (void*)source, 20);
    display_line_buf[20] = '\0'; // Null terminate
    
    lcd_set_cursor(row, 0);
    lcd_write_string(display_line_buf);
}

void main(void) {
    initialize_oscillator();
    initialize_green_led();
    initialize_blue_led();
    i2c_initialize();
    lcd_initialize();
    uart_init();
    
    INTCONbits.PEIE = 1; // Enable Peripheral Interrupts (for UART)
    INTCONbits.GIE = 1;  // Enable Global Interrupts
    
    lcd_set_cursor(0, 0);
    lcd_write_string("Waiting for Data...");
    lcd_set_cursor(1, 0);
    lcd_write_string("Baud: 115200");
    
    turn_green_led_on();
    while(1)
    {
        if (packet_received) {
            // Buffer Map:
            // 0: STX
            // 1-20: Line 1
            // 21-40: Line 2
            // 41-60: Line 3
            // 61-80: Line 4
            // 81: ETX
            
            update_lcd_line(0, &rx_buffer[1]);
            update_lcd_line(1, &rx_buffer[21]);
            update_lcd_line(2, &rx_buffer[41]);
            update_lcd_line(3, &rx_buffer[61]);
            
            packet_received = 0; // Reset flag to wait for next packet
            toggle_blue_led();
        }
    }
}
