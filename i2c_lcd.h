/* 
 * File:   i2c_lcd.h
 * Author: bugra
 *
 * Created on 07 ?ubat 2026 Cumartesi, 12:29
 */

#ifndef I2C_LCD_H
#define	I2C_LCD_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>

// I2C Address (0x27 shifted left 1 bit = 0x4E)
// Check your specific module; some are 0x3F << 1 = 0x7E
#define LCD_ADDR 0x4E 

void lcd_initialize(void);
void lcd_command(unsigned char cmd);
void lcd_write_char(char data);
void lcd_write_string(const char *str);
void lcd_set_cursor(unsigned char row, unsigned char col);


#ifdef	__cplusplus
}
#endif

#endif	/* I2C_LCD_H */

