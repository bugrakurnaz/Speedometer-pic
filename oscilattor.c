#include "oscilattor.h"

void initialize_oscillator() {
    // Set internal oscillator to 8 MHz
    OSCCON = 0b01110010;
}
