/* 
 * File:   i2c_master.h
 * Author: bugra
 *
 * Created on 07 ?ubat 2026 Cumartesi, 12:06
 */

#ifndef I2C_MASTER_H
#define	I2C_MASTER_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>

void i2c_initialize();

void i2c_wait();

void i2c_start();
    
void i2c_repeated_start();
    
void i2c_stop();
    
void i2c_write(unsigned char data);
    
#ifdef	__cplusplus
}
#endif

#endif	/* I2C_MASTER_H */

