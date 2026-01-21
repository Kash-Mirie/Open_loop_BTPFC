#ifndef INITIALISATION_HEADER_H_
#define INITIALISATION_HEADER_H_

#include "F28x_Project.h"


// ================== DELAY UTILITIES ===========================

static inline void delay_cycles(unsigned int cycles)
{
    while (cycles--) __asm(" NOP");
}

// ============================= CLOCK CONFIGURATIONS =====================================================

void init_sysclk();       // 200 MHz clock
void perip_clocks();       // Clock signals for ADC , DAC and PWM modules
void gpio_init();         // GPIO initialisation function

// ============================= EPWM modules =============================================================

void epwm1_init();
void db_epwm1_init();

void epwm2_init();        // Both epwm's are down . Using the full bridge as buck converter.

// ============================= ADC modules ==============================================================

void adcA_init();
void adcB_init();

__interrupt void adc_ISR(void);

// ============================= DAC modules ==============================================================

void dacA_init();
void dacB_init();


#endif /* INITIALISATION_HEADER_H_ */
