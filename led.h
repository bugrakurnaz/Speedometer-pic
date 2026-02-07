/* 
 * File:   led.h
 * Author: bugra
 *
 * Created on 06 ?ubat 2026 Cuma, 19:56
 */

#ifndef LED_H
#define	LED_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
    
extern uint8_t green_led_state;
extern uint8_t blue_led_state;
    
void initialize_green_led();
void turn_green_led_on();
void turn_green_led_off();
void toggle_green_led();

void initialize_blue_led();
void turn_blue_led_on();
void turn_blue_led_off();
void toggle_blue_led();

#ifdef	__cplusplus
}
#endif

#endif	/* LED_H */

