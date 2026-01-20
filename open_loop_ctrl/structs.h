#include "F28x_Project.h"

#ifndef STRUCTS_H_
#define STRUCTS_H_

typedef struct
{
    float Kp;
    float Ki;
    float error;
    float duty;

}pi_controller;

typedef struct
{
    float a0;
    float a1;
    float b0;
    float b1;
}sogi_pll;

void pi_current_init(pi_controller *pi);
void update_pi_controller(pi_controller *pi ,float v_in , float i_L ,float  v_out, float i_ref);


// DAC Functions

void update_dac_vals(uint16_t adcA_16bit, uint16_t adcB_16bit);


/* Extern declarations ONLY */

// Current PI Controller

extern pi_controller pi_current;
extern pi_controller *pi_current_ptr;

// Voltage PI Controller

extern pi_controller pi_voltage;
extern pi_controller *pi_voltage_ptr;

//SOGI instance functions

extern sogi_pll sogi_const;
extern sogi_pll *sogi_pll_ptr;

#endif /* STRUCTS_H_ */
