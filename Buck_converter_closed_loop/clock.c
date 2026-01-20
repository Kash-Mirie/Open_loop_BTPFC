/*
 * clock.c
 *
 *  Created on: 16-May-2025
 *      Author: Haseeb Mir
 *      LAB : SPEL LAB
 */

#include "F28x_Project.h"


#define PLL_MULT_200MHZ      0x14   // PLL Multiplier = 20 for 10MHz crystal → 200MHz
#define PLL_DIV_BYPASS       0x0
#define PLL_DIV_FINAL        0x0    // Final setting: no division
#define PLL_DIV_INTERMEDIATE 0x1    // Used during lock
#define PLL_LOCK_RETRIES     5      // Number of times to retry locking PLL

#define EPWM_CLKDIV_1   0  // /1
#define EPWM_HSPCLKDIV_1 0 // /1
#define EPWM_SYSCLK_DIV2 1 // System clock divider = /2

void init_sysclk(void)
{
    int i;
    EALLOW;

    /************** Step 1: Select External Oscillator as Clock Source **************/
    ClkCfgRegs.CLKSRCCTL1.bit.OSCCLKSRCSEL = 1;    // 1 = External crystal (XTAL)

    /************** Step 2: Bypass the PLL before reconfiguration *******************/
    ClkCfgRegs.SYSPLLCTL1.bit.PLLCLKEN = 0;        // Disable PLL output during config

    /************** Step 3: Set PLL Multiplier and Divider **************************/
    ClkCfgRegs.SYSCLKDIVSEL.bit.PLLSYSCLKDIV = PLL_DIV_BYPASS;  // Temporarily bypass

    /************** Step 4: Lock PLL ***********************************************/
    for (i = 0; i < PLL_LOCK_RETRIES; i++)
    {
        ClkCfgRegs.SYSPLLMULT.all = PLL_MULT_200MHZ;         // Set multiplier

        __asm(" RPT #69 || NOP");                              // Executes 70 NOPs

        ClkCfgRegs.SYSCLKDIVSEL.bit.PLLSYSCLKDIV = PLL_DIV_INTERMEDIATE;  // Set divider
        DevCfgRegs.SYSDBGCTL.bit.BIT_0 = 1;                  // Allow PLL to lock

        while (ClkCfgRegs.SYSPLLSTS.bit.LOCKS != 1);         // Wait for PLL to lock
    }

    /************** Step 5: Switch to PLL Clock ************************************/
    __asm(" RPT #69 || NOP");                           // Executes 70 NOPs

    ClkCfgRegs.SYSPLLCTL1.bit.PLLCLKEN = 1;     // Enable PLL as system clock source

    DevCfgRegs.SYSDBGCTL.bit.BIT_0 = 0;         // Exit PLL lock monitor mode

    __asm(" RPT #69 || NOP");                               // Executes 70 NOPs

    ClkCfgRegs.SYSCLKDIVSEL.bit.PLLSYSCLKDIV = PLL_DIV_FINAL; // Final divider = /1

    EDIS;
}

void perip_clocks(void)
{
    EALLOW;
    /************************ EPWM1 Clock Setup ************************/
        DevCfgRegs.CPUSEL0.bit.EPWM1 = 0;                          // Assign EPWM1 to CPU1
        ClkCfgRegs.PERCLKDIVSEL.bit.EPWMCLKDIV = EPWM_SYSCLK_DIV2; // EPWM Clock = 200MHz / 2 = 100 MHz
        CpuSysRegs.PCLKCR2.bit.EPWM1 = 1;                          // Enable clock to EPWM1 module

        EPwm1Regs.TBCTL.bit.CLKDIV = EPWM_CLKDIV_1;                // TBCLK = EPWMCLK/1
        EPwm1Regs.TBCTL.bit.HSPCLKDIV = EPWM_HSPCLKDIV_1;          // High-speed time-base clock divider = 1

    /*********************** EPWM2 Clock Setup ************************/
        DevCfgRegs.CPUSEL0.bit.EPWM2 = 0;                          //Assign EPWM1 to CPU1
        ClkCfgRegs.PERCLKDIVSEL.bit.EPWMCLKDIV = EPWM_SYSCLK_DIV2; //EPWM Clock = 200 MHz / 2 = 100 MHz
        CpuSysRegs.PCLKCR2.bit.EPWM2 = 1;                          // Enable clock to EPWM Module

        EPwm2Regs.TBCTL.bit.CLKDIV = EPWM_CLKDIV_1;                // TBCLK = EPWMCLK/1
        EPwm2Regs.TBCTL.bit.HSPCLKDIV = EPWM_HSPCLKDIV_1;          // High speed time base clock divider = 1

    /************************ ADC Clock Setup *************************/
        CpuSysRegs.PCLKCR13.bit.ADC_A = 1;                         // Enable ADC-A module clock
        CpuSysRegs.PCLKCR13.bit.ADC_B = 1;                         // Enable ADC-B module clock

    /*********************** DAC Clock Setup **************************/
        CpuSysRegs.PCLKCR16.bit.DAC_A =1;
        CpuSysRegs.PCLKCR16.bit.DAC_B = 1;


    EDIS;

}

