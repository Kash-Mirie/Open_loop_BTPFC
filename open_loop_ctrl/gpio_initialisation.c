#include "F28x_Project.h"

// Function to initialize GPIOs for EPWM1A/1B, GPIO16, and ADC pins
void gpio_init(void)
{
    EALLOW;

    /*********************** EPWM1A (GPIO0) and EPWM1B (GPIO1) ************************/

    GpioCtrlRegs.GPAGMUX1.bit.GPIO0 = 0;     // GMUX for GPIO0 -> Primary function
    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;      // MUX for GPIO0 -> EPWM1A

    GpioCtrlRegs.GPAGMUX1.bit.GPIO1 = 0;
    GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;      // MUX for GPIO1 -> EPWM1B

    /****************************** GPIO16 as Output **********************************/
    GpioCtrlRegs.GPAGMUX2.bit.GPIO16 = 0;    // GMUX for GPIO16 -> GPIO
    GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 0;     // MUX for GPIO16 -> GPIO
    GpioCtrlRegs.GPADIR.bit.GPIO16 = 1;      // Direction = Output

    /************************* ADC Pins Note (Pin 28, 30) *****************************/
    // No explicit GPIO config required here if using internal ADC channels.
    // Just comment to document the use.

    // ADCINA0 (Pin 30, GPIO24), ADCINA1 (Pin 28, GPIO25)  A0-A1 .. Used in True Differential mode

    /********************************** DAC pins *****************************************/



    EDIS;
}
