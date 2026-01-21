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


// DAC Functions

void update_dac_vals(uint16_t adcA_16bit, uint16_t adcB_16bit);

#endif /* STRUCTS_H_ */
