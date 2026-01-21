#include "F28x_Project.h"
#include "initialisation_header.h"

int main(void)
{

    //Sys clock + Peripheral clocks (EPWM , ADC , DAC )

    init_sysclk();
    perip_clocks();

    gpio_init();


    //EPWM Initialisation

    epwm1_init();
    db_epwm1_init();

    epwm2_init();

    // ADC Initialisation

    adcA_init();                            // Current sensor
    adcB_init();                            // Voltage Sensor

    //DAC initialisation

    dacA_init();
    dacB_init();


    while(1)
    {}
}
