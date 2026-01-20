#include "F28x_Project.h"
#include "initialisation_header.h"

int main(void)
{
    init_sysclk();
    perip_clocks();

    while(1)
    {}
}
