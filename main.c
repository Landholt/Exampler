//Acknowledgment to https://microcontrollerslab.com/introduction-tiva-tm4c123g-launchpad/

#ifndef MAIN_C
#define MAIN_C

#include "basic_led.h"
#include "interrupt.h"

int bhb;

int main(void)
{
    //init_gtimer();
    init_gpiof();
    //init_gpiof_interrupt();
    init_stimer();
    while(1) {
        //polling_color_cycle();
        //polling_switch();
    }
}

#endif
