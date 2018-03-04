//###########################################################################
//
// FILE:    DSP2833x_CpuTimers.c
//
// TITLE:   CPU 32-bit Timers Initialization & Support Functions.
//
// NOTES:   CpuTimer2 is reserved for use with DSP BIOS and
//          other realtime operating systems.
//
//          Do not use these this timer in your application if you ever plan
//          on integrating DSP-BIOS or another realtime OS.
//
//###########################################################################
// $TI Release: F2833x/F2823x Header Files and Peripheral Examples V142 $
// $Release Date: November  1, 2016 $
// $Copyright: Copyright (C) 2007-2016 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

//
// Included Files
//
#include "DSP2833x_Device.h"     // Headerfile Include File
#include "DSP2833x_Examples.h"   // Examples Include File

//
// Defines
//
struct CPUTIMER_VARS CpuTimer0;

//
// When using DSP BIOS & other RTOS, comment out CPU Timer 2 code.
//
struct CPUTIMER_VARS CpuTimer1;
struct CPUTIMER_VARS CpuTimer2;

//
// InitCpuTimers - This function initializes all three CPU timers to a known 
// state.
//
void 
InitCpuTimers(void)
{
    //
    // CPU Timer 0 - Initialize address pointers to respective timer registers
    //
    CpuTimer0.RegsAddr = &CpuTimer0Regs;
    
    //
    // Initialize timer period to maximum
    //
    CpuTimer0Regs.PRD.all  = 0xFFFFFFFF;
    
    //
    // Initialize pre-scale counter to divide by 1 (SYSCLKOUT)
    //
    CpuTimer0Regs.TPR.all  = 0;
    CpuTimer0Regs.TPRH.all = 0;
    
    //
    // Make sure timer is stopped
    //
    CpuTimer0Regs.TCR.bit.TSS = 1;
    
    //
    // Reload all counter register with period value
    //
    CpuTimer0Regs.TCR.bit.TRB = 1;
    
    //
    // Reset interrupt counters
    //
    CpuTimer0.InterruptCount = 0;

    //
    // CpuTimer2 is reserved for DSP BIOS & other RTOS
    // Do not use this timer if you ever plan on integrating
    // DSP-BIOS or another realtime OS.
    //

    //
    // Initialize address pointers to respective timer registers
    //
    CpuTimer1.RegsAddr = &CpuTimer1Regs;
    CpuTimer2.RegsAddr = &CpuTimer2Regs;
    
    //
    // Initialize timer period to maximum
    //
    CpuTimer1Regs.PRD.all  = 0xFFFFFFFF;
    CpuTimer2Regs.PRD.all  = 0xFFFFFFFF;
    
    //
    // Make sure timers are stopped
    //
    CpuTimer1Regs.TCR.bit.TSS = 1;
    CpuTimer2Regs.TCR.bit.TSS = 1;
    
    //
    // Reload all counter register with period value
    //
    CpuTimer1Regs.TCR.bit.TRB = 1;
    CpuTimer2Regs.TCR.bit.TRB = 1;
    
    //
    // Reset interrupt counters
    //
    CpuTimer1.InterruptCount = 0;
    CpuTimer2.InterruptCount = 0;
}

//
// ConfigCpuTimer - This function initializes the selected timer to the period 
// specified by the "Freq" and "Period" parameters. The "Freq" is entered as 
// "MHz" and the period in "uSeconds". The timer is held in the stopped state
// after configuration.
//
void 
ConfigCpuTimer(struct CPUTIMER_VARS *Timer, float Freq, float Period)
{
    Uint32  temp;

    //
    // Initialize timer period
    //
    Timer->CPUFreqInMHz = Freq;
    Timer->PeriodInUSec = Period;
    temp = (long) (Freq * Period);
    Timer->RegsAddr->PRD.all = temp;

    //
    // Set pre-scale counter to divide by 1 (SYSCLKOUT)
    //
    Timer->RegsAddr->TPR.all  = 0;
    Timer->RegsAddr->TPRH.all  = 0;

    //
    // Initialize timer control register
    //
    
    //
    // 1 = Stop timer, 0 = Start/Restart Timer
    //
    Timer->RegsAddr->TCR.bit.TSS = 1;
    
    Timer->RegsAddr->TCR.bit.TRB = 1;    // 1 = reload timer
    Timer->RegsAddr->TCR.bit.SOFT = 1;
    Timer->RegsAddr->TCR.bit.FREE = 1;   // Timer Free Run
    
    //
    // 0 = Disable/ 1 = Enable Timer Interrupt
    //
    Timer->RegsAddr->TCR.bit.TIE = 1;    

    //
    // Reset interrupt counter
    //
    Timer->InterruptCount = 0;
}

//
// End of File
//

