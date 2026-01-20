#include <initialisation_header.h>
#include "F28x_Project.h"
#include "structs.h"


#define ADC_TO_VOLT  (200.0f / 65535.0f)
#define ADC_TO_AMPS  (20.0f/65535.0f)
/*
 *
 * Vin ======== ADCA2_IN
 *
 */


volatile uint16_t v_out = 0;
volatile uint16_t i_fb = 0;   //
volatile uint16_t v_in =0;    // ADCIN0 - ADCIN1

volatile float v_in_volts;
volatile float v_out_volts;
volatile float i_fb_amps;

volatile float i_fb_ref = 20;

pi_controller pi_current;
pi_controller *pi_current_ptr = &pi_current;

// PI_Current control initialisation


void adcA_init()
{
    EALLOW;

    AdcaRegs.ADCCTL1.bit.ADCPWDNZ = 1;
    __asm (" RPT #2000 || NOP");  // Wait after power-up

    AdcaRegs.ADCCTL2.bit.SIGNALMODE = 1;    // Differential-mode
    AdcaRegs.ADCCTL2.bit.RESOLUTION = 1;    // 16-bit
    AdcaRegs.ADCCTL2.bit.PRESCALE   = 0b0110; // ADCCLK = SYSCLK/4

    // SOC0 - Vin (A0-A1)
    AdcaRegs.ADCSOC0CTL.bit.CHSEL    = 0;      // ADCIN0 - ADCIN1
    AdcaRegs.ADCSOC0CTL.bit.ACQPS    = 20;
    AdcaRegs.ADCSOC0CTL.bit.TRIGSEL  = 5;

    // SOC1 - I_L(A4-A5)

    AdcaRegs.ADCSOC1CTL.bit.CHSEL = 0x4;     // ADCIN4-ADCIN5
    AdcaRegs.ADCSOC1CTL.bit.ACQPS = 20;
    AdcaRegs.ADCSOC1CTL.bit.TRIGSEL = 5;     // Triggered on EPWM 1A

    // Interrupt Config
    AdcaRegs.ADCINTSEL1N2.bit.INT1E    = 1;  // Enable ADCINT1
    AdcaRegs.ADCINTSEL1N2.bit.INT1SEL  = 1;  // EOC1 triggers ADCINT1
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1  = 1;  // Clear flag

    // PIE & ISR config
    DINT;

    IER |= 1;  // CPU interrupt group 1
    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;
    PieCtrlRegs.PIEIER1.bit.INTx1 = 1;
    PieVectTable.ADCA1_INT = &adc_ISR;

    EINT;
    EDIS;


    // Do ADC A2---A3
}




void adcB_init()
{

    EALLOW;

    AdcbRegs.ADCCTL1.bit.ADCPWDNZ = 1;
    __asm(" RPT #2000 || NOP");

    AdcbRegs.ADCCTL2.bit.SIGNALMODE =1;         // Differential
    AdcbRegs.ADCCTL2.bit.RESOLUTION =1;         // 16-bit resolution
    AdcbRegs.ADCCTL2.bit.PRESCALE = 0b0110;

    // Selection SOC0 for ADC B to give out the interrupt

    AdcbRegs.ADCSOC0CTL.bit.CHSEL = 0x2;     // Selection ADCB2 - ADCB3 (v_out)
    AdcbRegs.ADCSOC0CTL.bit.ACQPS = 20;
    AdcbRegs.ADCSOC0CTL.bit.TRIGSEL = 5;  // Trigger select

    // ======================================================================EOC Selection ==============================================================

    // No interrupt selected here as we don't need it.


    EDIS;

}


__interrupt void adc_ISR(void)
{
    v_in  = AdcaResultRegs.ADCRESULT0 ;
    i_fb  = AdcaResultRegs.ADCRESULT1 ;
    v_out = AdcbResultRegs.ADCRESULT0 ;

    v_in_volts  = v_in * ADC_TO_VOLT;
    i_fb_amps   = i_fb * ADC_TO_AMPS;
    v_out_volts = v_out * ADC_TO_VOLT;

    update_pi_controller(pi_current_ptr, v_in_volts, i_fb_amps, v_in_volts,i_fb_ref);

    update_dac_vals(v_out, v_in);                    // This function taken 16-bit inputs


    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;           // Clear ADC interrupt flag
    PieCtrlRegs.PIEACK.bit.ACK1 = 1;                 // Acknowledge PIE group 1

}
