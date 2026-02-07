# A Speedometer implementation with PIC18F4520 for ETS

This project communicates with ETS2 Telemetry Server + Custom Middleware (REST->Serial). Here are the links to those projects.

https://github.com/bugrakurnaz/Speedometer-Telemetry-Serial-Server

https://github.com/Funbit/ets2-telemetry-server

It uses UART to communicate with middleware, which in turn communicates with ETS2 Telemetry Server through REST. It also uses an I2C to communicate with 20x4 I2C LED. 

## Requirements

* A PIC18F4520 DPIP version. (40 pins)
* PICKIT 3
* A lot of jumpers (I used around 25)
* 10k OHM resistor (or resistors that can provide this ohmage, I used 3 3.3k OHM resistors in seriies)
* (Optional) 1 Green, 1 Blue led for status with 2x 220 OHM Resistors. (330 OHM resistors are also fine)
* MPLAB X IDE v6.00

## Connection Layout

PIC18F4520 is put on a breadboard.

### PICKIT Connections

PICKIT3 Pin 1 (MCLR) -> Pin 1 of PIC18 (MCLR)
PICKIT3 Pin 2 (VDD) -> Positive rail of breadboard
PICKIT3 Pin 3 (VSS) -> Negative (GND) rail of breadboard
PICKIT3 Pin 4 (PGD) -> 40th pin of PIC18 (PGD)
PICKIT3 Pin 5 (PGC) -> 39th pin of PIC18 (PGC)

Provided 5V voltage through PICKIT3.

### Positive Rail Connections
From the positive rail, we connect:

11th pin of PIC (Vdd)
32th pin of PIC (Vdd)
VCC of I2C LCD

### Positive Rail <-> MCLR 
Between positive rail and MCLR line, use 10K ohm resistor. I used 3x 3.3K Ohm resistors in series.

### Ground rail
From the negative (GND) rail, we connect:
12th pin of PIC (Vss)
31th pin of PIC (Vss)
GND pin of I2C LCD
GND pin of UART
One end of blue LED (optional)
One end of green led (optional)

### I2C Connections

18th pin of PIC (SCL) -> I2C SCL
23rd pin of PIC (SDA) -> I2C SDA

### Uart connections

UART TXD -> 26th pin of PIC (RX)
UART RXD -> 25th pin of PIC (TX)
UART GND -> Ground rail

### (Optional) Status LEDS

33th pin of PIC (RB0) -> 220 OHM -> Green Led -> GND
34th pin of PIC (RB1) -> 220 OHM -> Blue Led -> GND



