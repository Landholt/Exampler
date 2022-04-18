#ifndef BASIC_LED_H
#define BASIC_LED_H

#include "driver.h"
#define SW1 (~GPIO_PORTF_DATA_R & 0x10)>>4
#define SW2 (~GPIO_PORTF_DATA_R & 0x01)
#define LED_CLEAR GPIO_PORTF_DATA_R &= 0b10001

enum led_colors color;

polling_color_cycle() {
    for (color = RED; color <= WHITE; color+=2) {
        GPIO_PORTF_DATA_R |= color;
        delay();
        GPIO_PORTF_DATA_R &= ~color;
          delay();
    }
    return;
}

polling_switch() {
    LED_CLEAR;
    GPIO_PORTF_DATA_R |= SW1<<2 | SW2 <<1;
}

#endif
