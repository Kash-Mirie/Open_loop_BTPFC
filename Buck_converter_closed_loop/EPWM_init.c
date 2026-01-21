#include "F28x_Project.h"

// ======================= PWM Timing Macros ========================
#define EPWM1_CLK_HZ     100000000UL   // EPWM clock: 100 MHz
#define EPWM1_FREQ_HZ    50000UL       // Desired PWM frequency: 50 kHz
#define TBPRD_50KHZ      ((EPWM1_CLK_HZ / 2*EPWM1_FREQ_HZ))
#define Q15(x) ((uint16_t)((x) * 32768.0f))


// ======================= EPWM1 Pin Mapping ========================
/*
 * EPWM1A --> Pin 40: Main duty output + SOC0 trigger
 * EPWM1B --> Pin 39: Active-high complementary with dead-band
 */

void epwm1_init(void)
{
    EALLOW;

    // ================== Time-Base Control ==============================
    EPwm1Regs.TBPRD = TBPRD_50KHZ;               // Set period for 50 kHz
    EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;   // Up-down count mode
    EPwm1Regs.TBCTL.bit.PRDLD   = TB_SHADOW;     // Load TBPRD from shadow when tbctr == 0;
    EPwm1Regs.TBCTL2.bit.PRDLDSYNC = 0;          // Load on CTR = 0

    // ================== Compare Control ===============================
    EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;  // Use shadow register for CMPA
    EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;  // Use shadow register for CMPB
    EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;// Load CMPA on TBCTR=0
    EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;// Load CMPB on TBCTR=0

    //=================== Action Qualifier Control (AQCTL) ==============//
      EPwm1Regs.AQCTL.bit.SHDWAQAMODE = 1;   // Enable shadow mode for AQ-A
      EPwm1Regs.AQCTL.bit.SHDWAQBMODE = 1;   // Enable shadow mode for AQ-B
      EPwm1Regs.AQCTL.bit.LDAQAMODE   = 0;   // Load AQ-A on TBCTR = 0
      EPwm1Regs.AQCTL.bit.LDAQBMODE   = 0;   // Load AQ-B on TBCTR = 0

    //=================== CMPA Qualifier =================================

    uint16_t duty_q15 = Q15(0.5);  // More readable

    EPwm1Regs.CMPA.bit.CMPA = (TBPRD_50KHZ * duty_q15) >> 15;

    //=================== Action Qualifier Events ======================//

       EPwm1Regs.AQCTLA.bit.ZRO = AQ_NO_ACTION;     // Set PWM high at TBCTR = 0
       EPwm1Regs.AQCTLA.bit.PRD = AQ_NO_ACTION;   // No action by CMPA on up-count
       EPwm1Regs.AQCTLA.bit.CAU = AQ_SET ;
       EPwm1Regs.AQCTLA.bit.CAD = AQ_CLEAR;

       // =================== Generating SOC Triggers from the EPWM1A Module.

       EPwm1Regs.ETSEL.bit.SOCAEN = 1;        // Enable the SOCA
       EPwm1Regs.ETSEL.bit.SOCASEL = 0b001;   // Interrupt when CTR == 0 ;

       EPwm1Regs.ETPS.bit.SOCBPRD = 0;     // No SOCB pulse will be generated.
       EPwm1Regs.ETPS.bit.SOCAPRD = 1;     // Generate on First event.
    EDIS;
}

void db_epwm1_init(void)
{
    EALLOW;

    EPwm1Regs.DBCTL.bit.IN_MODE   = 0;     // EPWMxA used for both RED and FED
    EPwm1Regs.DBCTL.bit.DEDB_MODE = 0;     // RED goes to EPWMxA, FED to EPWMxB
    EPwm1Regs.DBCTL.bit.POLSEL    = 2;     // Active High Complementary: EPWMxB = ~EPWMxA
    EPwm1Regs.DBCTL.bit.OUT_MODE  = 3;     // Dead-band fully enabled (both RED and FED paths)
    EPwm1Regs.DBCTL.bit.OUTSWAP   = 0;     // No swap

    // Add these two lines!
    EPwm1Regs.DBRED.bit.DBRED     = 50;    // Rising edge delay (50 TBCLKs)
    EPwm1Regs.DBFED.bit.DBFED     = 50;    // Falling edge delay (50 TBCLKs)
    EDIS;
}


void epwm2_init()
{
    EALLOW;


    EDIS;
}

void db_epwm2_init()
{
    EALLOW;


    EDIS;
}

