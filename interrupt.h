#ifndef INTERRUPT_H
#define INTERRUPT_H

/*
 With credit to https://microcontrollerslab.com/gpio-interrupts-tm4c123-tiva-launchpad-edge-level-triggered/
*/

#include "driver.h"

void init_gpiof_interrupt() {
    init_gpiof();
//Interrupt Control
    GPIO_PORTF_IS_R &= 0b01110;
    GPIO_PORTF_IBE_R &= 0b01110;
    GPIO_PORTF_IEV_R &= 0b01110;
    GPIO_PORTF_ICR_R |= 0b10001;
    GPIO_PORTF_IM_R |= 0b10001;
//NVIC interrupt enable and priority
    NVIC_EN0_R |= (1<<30);
    NVIC_PRI7_R = 0b011<<21;
}

/* SW1 is connected to PF4 pin, SW2 is connected to PF0. */
/* Both of them trigger PORTF falling edge interrupt */
void f_handler(void) {
    if (GPIO_PORTF_MIS_R & 0x10) { /* check if interrupt causes by PF4/SW1*/
        GPIO_PORTF_ICR_R |= 0x10; /* clear the interrupt flag */
        GPIO_PORTF_DATA_R = (GPIO_PORTF_DATA_R & 0b10001) | 1<<3;

    }
    else if (GPIO_PORTF_MIS_R & 0x01) { /* check if interrupt causes by PF4/SW1*/
        GPIO_PORTF_ICR_R |= 0x01; /* clear the interrupt flag */
        GPIO_PORTF_DATA_R = (GPIO_PORTF_DATA_R & 0b10001) | 1<<2;
    }
}

//GPIO Timer driver
void init_gtimer() {
    SYSCTL_RCGCTIMER_R |= 0b10; // Enable and provide clock to timer module 1
    //SYSCTL_RCC_R used to set System Divisor, among other things
    TIMER1_CTL_R = 0; // clear timer controls
    TIMER1_CFG_R = 4; // select lower width of timer (i.e. 16-bit for 16/32-bit timer or 32 for 32/64-bit timer)
    TIMER1_TAMR_R = 2; // Set timer 1-A mode to periodic (also, with bit 4 not being set, the count direction will be down)
    TIMER1_TAPR_R = 250 - 1; // timer 1-A prescale
    TIMER1_TAILR_R = 64000 - 1; // Starting value for counting down (would be upper bound for counting up if count direction was up)
    TIMER1_ICR_R = 0x1; // Clear the timer 1-A time-out raw and masked interrupt status
    TIMER1_CTL_R |= 1; // Timer 1-A "is enabled and begins counting or the capture logic is enabled based on the GPTMCFG register." (Datasheet p. 740)
    TIMER1_IMR_R |= 1; // Enable timer 1-A time-out mode interrupt

    NVIC_EN0_R |= (1<<21); // Enable interrupt for 16/32-Bit Timer 1A
}

void timer1a_handler(void) {
    if (TIMER1_MIS_R & 1) {
        GPIO_PORTF_DATA_R ^= 1<<1; //(GPIO_PORTF_DATA_R & 0b10001) ^ 1<<1;
        TIMER1_ICR_R = 0x1;
    }
}

//System timer/SysTick driver
void init_stimer() {
    SYSCTL_RCC_R ^= 1;
    SYSCTL_RCC_R |= 0b10101000000; // Enable main oscillator crystal value of 16 MHz
    SYSCTL_RCC_R &= 0b001111<<4; // Clear bits 5:4 of the register, thereby using the main oscillator instead of the precision osc.
    NVIC_ST_CTRL_R = 0b111; // Enable counter and interrupt, and use system clock instead of precision oscillator
    NVIC_ST_RELOAD_R = 16000000 - 1;

    //NVIC_ST_CURRENT_R = 0;

    //NVIC_EN0_R |= (1<<15); // Enable SysTick exception
   // NVIC_PRI3_R |= 0b011<<29;
}

void stimer_handler(void) {
    GPIO_PORTF_DATA_R ^= 0b111<<1;
}

#endif
