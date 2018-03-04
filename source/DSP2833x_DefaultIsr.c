//###########################################################################
//
// FILE:	DSP2833x_DefaultIsr.c
//
// TITLE:	DSP2833x Device Default Interrupt Service Routines.
//
// This file contains shell ISR routines for the 2833x PIE vector table.
// Typically these shell ISR routines can be used to populate the entire PIE
// vector table during device debug.  In this manner if an interrupt is taken
// during firmware development, there will always be an ISR to catch it.
//
// As development progresses, these ISR routines can be eliminated and replaced
// with the user's own ISR routines for each interrupt.  Since these shell ISRs
// include infinite loops they will typically not be included as-is in the final
// production firmware.
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
#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

//
// INT13_ISR - Connected to INT13 of CPU (use MINT13 mask):
// Note CPU-Timer1 is reserved for TI use, however XINT13
// ISR can be used by the user.
//
interrupt void 
INT13_ISR(void)     // INT13 or CPU-Timer1
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// INT14_ISR - Note CPU-Timer2 is reserved for TI use.
//
interrupt void 
INT14_ISR(void)     // CPU-Timer2
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// DATALOG_ISR - Datalogging interrupt 
//
interrupt void 
DATALOG_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// RTOSINT_ISR - RTOS interrupt
//
interrupt void 
RTOSINT_ISR(void)   
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// EMUINT_ISR - Emulation interrupt
//
interrupt void 
EMUINT_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// NMI_ISR - Non-maskable interrupt
//
interrupt void 
NMI_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// ILLEGAL_ISR - Illegal operation TRAP
//
interrupt void 
ILLEGAL_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// USER1_ISR - User Defined trap 1
//
interrupt void 
USER1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// USER2_ISR - User Defined trap 2
//
interrupt void 
USER2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// USER3_ISR - User Defined trap 3
//
interrupt void 
USER3_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// USER4_ISR - User Defined trap 4
//
interrupt void 
USER4_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// USER5_ISR - User Defined trap 5
//
interrupt void 
USER5_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// USER6_ISR - User Defined trap 6
//
interrupt void 
USER6_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// USER7_ISR - User Defined trap 7
//
interrupt void 
USER7_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// USER8_ISR - User Defined trap 8
//
interrupt void 
USER8_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// USER9_ISR - User Defined trap 9
//
interrupt void 
USER9_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// USER10_ISR - User Defined trap 10
//
interrupt void 
USER10_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// USER11_ISR - User Defined trap 11
//
interrupt void 
USER11_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// USER12_ISR - User Defined trap 12
//
interrupt void 
USER12_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// PIE Group 1 - MUXed into CPU INT1
//

//
// SEQ1INT_ISR - INT1.1
//
interrupt void 
SEQ1INT_ISR(void)   //SEQ1 ADC
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this 
    // interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// SEQ2INT_ISR - INT1.2
//
interrupt void 
SEQ2INT_ISR(void)  //SEQ2 ADC
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this interrupt
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
    //

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //

    asm("	  ESTOP0");
    for(;;);
}

//
// INT1.3 - Reserved
//

//
// XINT1_ISR - INT1.4
//
interrupt void  
XINT1_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this 
    // interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// XINT2_ISR - INT1.5
//
interrupt void  
XINT2_ISR(void)
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this 
    // interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// ADCINT_ISR - INT1.6
//
interrupt void  
ADCINT_ISR(void)     // ADC
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this 
    // interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// TINT0_ISR - INT1.7
//
interrupt void  
TINT0_ISR(void)      // CPU-Timer 0
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this 
    // interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// WAKEINT_ISR - INT1.8
//
interrupt void  
WAKEINT_ISR(void)    // WD, LOW Power
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this 
    // interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

// 
// PIE Group 2 - MUXed into CPU INT2
// 

//
// EPWM1_TZINT_ISR - INT2.1
//
interrupt void 
EPWM1_TZINT_ISR(void)    // EPWM-1
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this 
    // interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// EPWM2_TZINT_ISR - INT2.2
//
interrupt void 
EPWM2_TZINT_ISR(void)    // EPWM-2
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this 
    // interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// EPWM3_TZINT_ISR - INT2.3
//
interrupt void 
EPWM3_TZINT_ISR(void)    // EPWM-3
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge 
    // this interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// EPWM4_TZINT_ISR - INT2.4
//
interrupt void 
EPWM4_TZINT_ISR(void)    // EPWM-4
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this 
    // interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// EPWM5_TZINT_ISR - INT2.5
//
interrupt void 
EPWM5_TZINT_ISR(void)    // EPWM-5
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this 
    // interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// EPWM6_TZINT_ISR - INT2.6
//
interrupt void 
EPWM6_TZINT_ISR(void)   // EPWM-6
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this 
    // interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// INT2.7 - Reserved
//

//
// INT2.8 - Reserved
//

//
// PIE Group 3 - MUXed into CPU INT3
//

//
// EPWM1_INT_ISR - INT 3.1
//
interrupt void 
EPWM1_INT_ISR(void)     // EPWM-1
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this 
    // interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// EPWM2_INT_ISR - INT3.2
//
interrupt void 
EPWM2_INT_ISR(void)     // EPWM-2
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this 
    // interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// EPWM3_INT_ISR - INT3.3
//
interrupt void 
EPWM3_INT_ISR(void)    // EPWM-3
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this 
    // interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// EPWM4_INT_ISR - INT3.4
//
interrupt void 
EPWM4_INT_ISR(void)    // EPWM-4
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this 
    // interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// EPWM5_INT_ISR - INT3.5
//
interrupt void 
EPWM5_INT_ISR(void)    // EPWM-5
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this 
    // interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// EPWM6_INT_ISR - INT3.6
//
interrupt void 
EPWM6_INT_ISR(void)    // EPWM-6
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this 
    // interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// INT3.7 - Reserved
//

//
// INT3.8 - Reserved
//

//
// PIE Group 4 - MUXed into CPU INT4
//

//
// ECAP1_INT_ISR - INT 4.1
//
interrupt void 
ECAP1_INT_ISR(void)    // ECAP-1
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this 
    // interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// ECAP2_INT_ISR - INT4.2
//
interrupt void 
ECAP2_INT_ISR(void)    // ECAP-2
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this 
    // interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// ECAP3_INT_ISR - INT4.3
//
interrupt void 
ECAP3_INT_ISR(void)    // ECAP-3
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this 
    // interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// ECAP4_INT_ISR - INT4.4
//
interrupt void 
ECAP4_INT_ISR(void)     // ECAP-4
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this 
    // interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// ECAP5_INT_ISR - INT4.5
//
interrupt void 
ECAP5_INT_ISR(void)     // ECAP-5
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this 
    // interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// ECAP6_INT_ISR - INT4.6
//
interrupt void 
ECAP6_INT_ISR(void)     // ECAP-6
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this 
    // interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// INT4.7 - Reserved
//

//
// INT4.8 - Reserved
//

//
// PIE Group 5 - MUXed into CPU INT5
//

//
// EQEP1_INT_ISR - INT 5.1
//
interrupt void 
EQEP1_INT_ISR(void)    // EQEP-1
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this 
    // interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP5;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// EQEP2_INT_ISR - INT5.2
//
interrupt void 
EQEP2_INT_ISR(void)    // EQEP-2
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this 
    // interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP5;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// INT5.3 - Reserved
//

//
// INT5.4 - Reserved
//

//
// INT5.5 - Reserved
//

//
// INT5.6 - Reserved
//

//
// INT5.7 - Reserved
//

//
// INT5.8 - Reserved
//

//
// PIE Group 6 - MUXed into CPU INT6
//

//
// SPIRXINTA_ISR - INT6.1
//
interrupt void 
SPIRXINTA_ISR(void)    // SPI-A
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this 
    // interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// SPITXINTA_ISR - INT6.2
//
interrupt void 
SPITXINTA_ISR(void)     // SPI-A
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this 
    // interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// MRINTB_ISR - INT6.3
//
interrupt void 
MRINTB_ISR(void)     // McBSP-B
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this 
    // interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// MXINTB_ISR - INT6.4
//
interrupt void 
MXINTB_ISR(void)     // McBSP-B
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this 
    // interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// MRINTA_ISR - INT6.5
//
interrupt void 
MRINTA_ISR(void)     // McBSP-A
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this 
    // interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// MXINTA_ISR - INT6.6
//
interrupt void 
MXINTA_ISR(void)     // McBSP-A
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this 
    // interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// INT6.7 - Reserved
//

//
// INT6.8 - Reserved
//

//
// PIE Group 7 - MUXed into CPU INT7
//

//
// DINTCH1_ISR - INT7.1
//
interrupt void 
DINTCH1_ISR(void)     // DMA
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this 
    // interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// DINTCH2_ISR - INT7.2
//
interrupt void 
DINTCH2_ISR(void)     // DMA
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this 
    // interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// DINTCH3_ISR - INT7.3
//
interrupt void 
DINTCH3_ISR(void)     // DMA
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this 
    // interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// DINTCH4_ISR - INT7.4
//
interrupt void 
DINTCH4_ISR(void)     // DMA
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this 
    // interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// DINTCH5_ISR - INT7.5
//
interrupt void 
DINTCH5_ISR(void)     // DMA
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this 
    // interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// DINTCH6_ISR - INT7.6
//
interrupt void 
DINTCH6_ISR(void)     // DMA
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this 
    // interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// INT7.7 - Reserved
//

//
// INT7.8 - Reserved
//

//
// PIE Group 8 - MUXed into CPU INT8
//

//
// I2CINT1A_ISR - INT8.1
//
interrupt void 
I2CINT1A_ISR(void)     // I2C-A
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this 
    // interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// I2CINT2A_ISR - INT8.2
//
interrupt void 
I2CINT2A_ISR(void)     // I2C-A
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this 
    // interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// INT8.3 - Reserved
//

//
// INT8.4 - Reserved
//

//
// SCIRXINTC_ISR - INT8.5
//
interrupt void 
SCIRXINTC_ISR(void)     // SCI-C
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this 
    // interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// SCITXINTC_ISR - INT8.6
//
interrupt void 
SCITXINTC_ISR(void)     // SCI-C
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this 
    // interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// INT8.7 - Reserved
//

//
// INT8.8 - Reserved
//

//
// PIE Group 9 - MUXed into CPU INT9
//

//
// SCIRXINTA_ISR - INT9.1
//
interrupt void 
SCIRXINTA_ISR(void)     // SCI-A
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this 
    // interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// SCITXINTA_ISR - INT9.2
//
interrupt void 
SCITXINTA_ISR(void)     // SCI-A
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this 
    // interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// SCIRXINTB_ISR - INT9.3
//
interrupt void 
SCIRXINTB_ISR(void)     // SCI-B
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this 
    // interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// SCITXINTB_ISR - INT9.4
//
interrupt void 
SCITXINTB_ISR(void)     // SCI-B
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this 
    // interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// ECAN0INTA_ISR - INT9.5
//
interrupt void 
ECAN0INTA_ISR(void)  // eCAN-A
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this 
    // interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// ECAN1INTA_ISR - INT9.6
//
interrupt void 
ECAN1INTA_ISR(void)  // eCAN-A
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this 
    // interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// ECAN0INTB_ISR - INT9.7
//
interrupt void 
ECAN0INTB_ISR(void)  // eCAN-B
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this 
    // interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// ECAN1INTB_ISR - INT9.8
//
interrupt void 
ECAN1INTB_ISR(void)  // eCAN-B
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this 
    // interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// PIE Group 10 - MUXed into CPU INT10
//

//
// INT10.1 - Reserved
//

//
// INT10.2 - Reserved
//

//
// INT10.3 - Reserved
//

//
// INT10.4 - Reserved
//

//
// INT10.5 - Reserved
//

//
// INT10.6 - Reserved
//

//
// INT10.7 - Reserved
//

//
// INT10.8 - Reserved
//

//
// PIE Group 11 - MUXed into CPU INT11
//

//
// INT11.1 - Reserved
//

//
// INT11.2 - Reserved
//

//
// INT11.3 - Reserved
//

//
// INT11.4 - Reserved
//

//
// INT11.5 - Reserved
//

//
// INT11.6 - Reserved
//

//
// INT11.7 - Reserved
//

//
// INT11.8 - Reserved
//

//
// PIE Group 12 - MUXed into CPU INT12
//

//
// XINT3_ISR - INT12.1
//
interrupt void 
XINT3_ISR(void)  // External Interrupt
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this 
    // interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// XINT4_ISR - INT12.2
//
interrupt void 
XINT4_ISR(void)  // External Interrupt
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this 
    // interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// XINT5_ISR - INT12.3
//
interrupt void 
XINT5_ISR(void)  // External Interrupt
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this 
    // interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// XINT6_ISR - INT12.4
//
interrupt void 
XINT6_ISR(void)  // External Interrupt
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this 
    // interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// XINT7_ISR - INT12.5
//
interrupt void 
XINT7_ISR(void)  // External Interrupt
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this 
    // interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// INT12.6 - Reserved
//

//
// LVF_ISR - INT12.7
//
interrupt void 
LVF_ISR(void)  // Latched overflow
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this 
    // interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// LUF_ISR - INT12.8
//
interrupt void 
LUF_ISR(void)  // Latched underflow
{
    //
    // Insert ISR Code here
    //

    //
    // To receive more interrupts from this PIE group, acknowledge this 
    // interrupt
    //
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    asm ("      ESTOP0");
    for(;;);
}

//
// Catch All Default ISRs:
//

//
// PIE_RESERVED - Reserved space.  For test.
//
interrupt void 
PIE_RESERVED(void)
{
    asm ("      ESTOP0");
    for(;;);
}

//
// rsvd_ISR - For test
//
interrupt void 
rsvd_ISR(void)
{
    asm ("      ESTOP0");
    for(;;);
}

//
// End of file
//

