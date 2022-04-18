#ifndef DRIVER_H
#define DRIVER_H

#include <stdint.h>
#include "tm4c123gh6pm.h" // copyright Texas Instruments

enum led_colors {RED=2, BLUE=4, PURPLE=6, GREEN=8, YELLOW=0xA, CYAN=0xC, WHITE=0xE};

int i;
delay() {
    for (i = 0; i < 500000; i++) {}
}

void init_gpiof() {
    SYSCTL_RCGCGPIO_R |= 1<<5;
// Commit control
    GPIO_PORTF_LOCK_R = 0x4C4F434B;
    GPIO_PORTF_CR_R |= 1; //Lock is reapplied by the write to the CR
// Pad Control
    GPIO_PORTF_PUR_R |= 0b10001;
    GPIO_PORTF_DEN_R |= 0x1F;
// Data Control
    GPIO_PORTF_DIR_R |= 0b01110;
    GPIO_PORTF_DATA_R &= 0b10001; //clear bits [3:1]
}

#endif
/*

********************************
IMPORTANT SYSTEM CONTROL REGISTERS
********************************

SYSCTL_RCGCGPIO_R GPIO Run mode clock gating control

********************************

********************************
********************************
********************************

********************************
IMPORTANT GPIO REGISTERS
********************************

For advanced peripheral bus, format GPIO_PORTF_AFSEL_R
for advanced high-performance bus, format GPIO_PORTF_AHB_AFSEL_R

===========
PAD CONTROL
===========
GPIO_PORTF_DR2R_R 2mA drive
DR4R
DR8R
SLR Slew rate for 8mA drive
PUR pull-up resistor
PDR pull-down
ODR open drain
DEN digital enable
AMSEL analog mode

===========
MODE CONTROL
===========
AFSEL alternate function
ADCCTL ADC control
DMACTL μDMA

===========
COMMIT CONTROL
===========
LOCK
CR commit register

===========
DATA CONTROL
===========
DATA
DIR data direction

===========
PORT CONTROL
===========
PCTL

===========
INTERRUPT CONTROL
===========
IS interrupt sense
IBE both edges
IEV interrupt event
IM interrupt mask
RIS raw interrupt status
MIS masked interrupt status
ICR interrupt clear

===========
IDENTIFICATION REGISTERS
===========
GPIOPeriphIDn, n = [0:7]
GPIOPCellIDn, n = [0:3]

*/

