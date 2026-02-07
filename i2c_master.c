/* 
 * File:   i2c_master.c
 * Device: PIC18F4520
 */

#include "i2c_master.h"

void i2c_initialize(void) {
    // Configure TRISC for I2C Communication (RC3=SCL, RC4=SDA)
    TRISCbits.TRISC3 = 1;
    TRISCbits.TRISC4 = 1;
    
    // Disable Slew Rate Control (Standard Speed 100kHz)
    SSPSTATbits.SMP = 1; 
    
    // Enable SMBus inputs? No, default levels.
    SSPSTATbits.CKE = 0;
    
    // Enable Master Synchronous Serial Port
    SSPCON1bits.SSPEN = 1;
    
    // Configure as I2C Master Mode
    SSPCON1bits.SSPM = 0b1000;
    
    // Set Baud Rate to 100khz @ 8MHz Oscillator
    // Formula: Fclock = Fosc / (4 * (SSPADD + 1))
    // 100,000 = 8,000,000 / (4 * (19 + 1))
    SSPADD = 0x13; // Decimal 19
    
    SSPCON2 = 0;
}

void i2c_wait(void) {
    // Wait for MSSP module to be idle (Start, Stop, Ack, RCEN not in progress)
    while ((SSPCON2 & 0x1F) || (SSPSTATbits.R_W));
}

void i2c_start(void) {
    i2c_wait();
    SSPCON2bits.SEN = 1; // Initiate Start condition
    while (SSPCON2bits.SEN); // Wait for hardware to clear the bit
}

void i2c_repeated_start(void) {
    i2c_wait();
    SSPCON2bits.RSEN = 1; // Initiate Repeated Start
    while (SSPCON2bits.RSEN);
}

void i2c_stop(void) {
    i2c_wait();
    SSPCON2bits.PEN = 1; // Initiate Stop condition
    while (SSPCON2bits.PEN);
}

void i2c_write(unsigned char data) {
    i2c_wait();
    SSPBUF = data; // Load data into buffer
    while (SSPSTATbits.BF); // Wait until buffer is full/data shifted out
    i2c_wait(); // Wait for the bus to be idle again (ACK cycle complete)
}