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



