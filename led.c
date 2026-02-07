#include "led.h"

uint8_t green_led_state = 0;
uint8_t blue_led_state = 0;

void turn_green_led_on() {
    LATBbits.LATB0 = 1;
    green_led_state = 1;
}

void turn_green_led_off() {
    LATBbits.LATB0 = 0;
    green_led_state = 0;
}

void toggle_green_led(){
    green_led_state ^= 1u;
    LATBbits.LATB0 = green_led_state;
}

void initialize_green_led() {
    // Make RB0 an output
    TRISBbits.TRISB0 = 0;

    turn_green_led_off();
}

void turn_blue_led_on() {
    LATBbits.LATB1 = 1;
    blue_led_state = 1;
}

void turn_blue_led_off() {
    LATBbits.LATB1 = 0;
    blue_led_state = 0;
}

void toggle_blue_led() {
    blue_led_state ^= 1u;
    LATBbits.LATB1 = blue_led_state;
}

void initialize_blue_led() {
    // Make RB1 an output
    TRISBbits.TRISB1 = 0;

    turn_blue_led_off();
}