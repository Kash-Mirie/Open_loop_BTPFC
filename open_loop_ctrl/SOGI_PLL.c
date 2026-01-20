#include "F28x_Project.h"
#include "structs.h"

sogi_pll sogi_const;
sogi_pll *sogi_pll_ptr = &sogi_const;


void sogi_init(sogi_pll *sogi)
{
    sogi->a0 = 0;
    sogi->a1 = 0;
    sogi->b0 = 0;
    sogi->b1 = 0;
}


