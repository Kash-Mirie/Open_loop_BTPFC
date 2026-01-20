#include "F28x_Project.h"
#include "structs.h"

void pi_current_init(pi_controller *pi)
{
    pi-> Kp    = 10;
    pi-> Ki    = 0.001;
    pi-> error = 0;
    pi-> duty  = 0.1;
}

void update_pi_controller(pi_controller *pi ,float v_in , float i_L ,float  v_out , float i_ref )
{
    pi->error = i_ref - i_L;
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

