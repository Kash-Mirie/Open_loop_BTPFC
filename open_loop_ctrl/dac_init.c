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
