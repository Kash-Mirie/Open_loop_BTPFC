#include "F28x_Project.h"
#include "structs.h"

void dacA_init()
{
    EALLOW;
         DacaRegs.DACCTL.bit.LOADMODE = 0;
         DacaRegs.DACCTL.bit.DACREFSEL = 0;
         DacaRegs.DACVALS.bit.DACVALS = 0x0;    // Initial value inside the DAC register
         DacaRegs.DACOUTEN.bit.DACOUTEN = 1;
    EDIS;
}



void dacB_init()
{
    EALLOW;
        DacbRegs.DACCTL.bit.LOADMODE   = 0;
        DacbRegs.DACCTL.bit.DACREFSEL  = 0;
        DacaRegs.DACVALS.bit.DACVALS   = 0x0;
        DacbRegs.DACOUTEN.bit.DACOUTEN = 1;
    EDIS;
}

void update_dac_vals(uint16_t adcA_16bit, uint16_t adcB_16bit)

{
    uint16_t dacA, dacB;

    dacA = adcA_16bit >> 4;
    dacB = adcB_16bit >> 4;

    if (dacA > 4095) dacA = 4095;
    if (dacB > 4095) dacB = 4095;

    EALLOW;
    DacaRegs.DACVALS.all = dacA;
    DacbRegs.DACVALS.all = dacB;
    EDIS;
}
