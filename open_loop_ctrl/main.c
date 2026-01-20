#include <initialisation_header.h>
#include "F28x_Project.h"
#include "structs.h"

#define DELAY_NOP(count)  __asm(" RPT #" #count " || NOP")     // Define the Delay

int main(void)

{

    // Clocks EPWM1 . ADCA . ADCB

       init_sysclk();
       perip_clocks();

    // GPIO initialisation

       gpio_init();

   // EPWM initialisation

       epwm1_init();
       db_epwm1_init();

   // ADC Initialisation

       adcA_init();
       adcB_init();

       pi_current_init(pi_current_ptr);

    // DAC initialisation

       dacA_init();         // Initialise the DAC A
       dacB_init();         // Initialise the DAC B

   EALLOW;
       CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0x01;       // Start the TBCTr Clock
   EDIS;

   while(1)
   {}

}
