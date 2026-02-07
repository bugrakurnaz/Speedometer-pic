/* 
 * File:   i2c_lcd.c
 */

#include "i2c_master.h"
#include "i2c_lcd.h"

// Define Frequency for Delays
#ifndef _XTAL_FREQ
#define _XTAL_FREQ 8000000
#endif

// Internal Pin Mappings for PCF8574
#define LCD_BACKLIGHT 0x08
#define LCD_ENABLE    0x04
#define LCD_RS        0x01

// Low-level function to send nibbles via I2C Expander
void lcd_send_internal(unsigned char data, unsigned char flags) {
    unsigned char up = data & 0xF0;
    unsigned char lo = (data << 4) & 0xF0;
    
    unsigned char data_arr[4];
    
    // High Nibble + Enable High
    data_arr[0] = up | flags | LCD_BACKLIGHT | LCD_ENABLE;
    // High Nibble + Enable Low (Latch)
    data_arr[1] = up | flags | LCD_BACKLIGHT;
    
    // Low Nibble + Enable High
    data_arr[2] = lo | flags | LCD_BACKLIGHT | LCD_ENABLE;
    // Low Nibble + Enable Low (Latch)
    data_arr[3] = lo | flags | LCD_BACKLIGHT;
    
    i2c_start();
    i2c_write(LCD_ADDR);
    for(int i=0; i<4; i++) {
        i2c_write(data_arr[i]);
    }
    i2c_stop();
}

void lcd_command(unsigned char cmd) {
    // RS = 0 for Command
    lcd_send_internal(cmd, 0);
}

void lcd_write_char(char data) {
    // RS = 1 for Data
    lcd_send_internal(data, LCD_RS);
}

void lcd_write_string(const char *str) {
    while (*str) {
        lcd_write_char(*str++);
    }
}

void lcd_set_cursor(unsigned char row, unsigned char col) {
    unsigned char address[] = {0x00, 0x40, 0x14, 0x54};
    if (row > 3) row = 3;
    lcd_command(0x80 | (address[row] + col));
}

void lcd_initialize(void) {
    // Initial wait for power up
    __delay_ms(50); 
    
    // Reset sequence for 4-bit mode (Specific to HD44780)
    // We must send 0x30 three times, but purely as nibbles, not full bytes with double-clocking
    // So we manually construct the packets here to be safe
    
    i2c_start();
    i2c_write(LCD_ADDR);
    
    // 1. Send 0x30
    i2c_write(0x30 | LCD_BACKLIGHT | LCD_ENABLE);
    __delay_us(1);
    i2c_write(0x30 | LCD_BACKLIGHT);
    __delay_ms(5);
    
    // 2. Send 0x30
    i2c_write(0x30 | LCD_BACKLIGHT | LCD_ENABLE);
    __delay_us(1);
    i2c_write(0x30 | LCD_BACKLIGHT);
    __delay_us(150);
    
    // 3. Send 0x30
    i2c_write(0x30 | LCD_BACKLIGHT | LCD_ENABLE);
    __delay_us(1);
    i2c_write(0x30 | LCD_BACKLIGHT);
    __delay_us(150);
    
    // 4. Set 4-bit mode (0x20)
    i2c_write(0x20 | LCD_BACKLIGHT | LCD_ENABLE);
    __delay_us(1);
    i2c_write(0x20 | LCD_BACKLIGHT);
    
    i2c_stop();
    __delay_ms(5);

    // Now we can use the standard command function
    lcd_command(0x28); // Function Set: 4-bit, 2 lines
    lcd_command(0x08); // Display Off
    lcd_command(0x01); // Clear Display
    __delay_ms(5);
    lcd_command(0x06); // Entry Mode: Increment
    lcd_command(0x0C); // Display On, Cursor Off
}