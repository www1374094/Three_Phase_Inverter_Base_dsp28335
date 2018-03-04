//###########################################################################
//
// FILE:	DSP2833x_McBSP.c
//
// TITLE:	DSP2833x Device McBSP Initialization & Support Functions.
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
// MCBSP_INIT_DELAY determines the amount of CPU cycles in the 2 sample rate
// generator (SRG) cycles required for the Mcbsp initialization routine.
// MCBSP_CLKG_DELAY determines the amount of CPU cycles in the 2 clock
// generator (CLKG) cycles required for the Mcbsp initialization routine.
// For the functions defined in Mcbsp.c, MCBSP_INIT_DELAY and MCBSP_CLKG_DELAY
// are based off of either a 150 MHz SYSCLKOUT (default) or a 100 MHz SYSCLKOUT
//

//
// CPU_FRQ_100MHZ and CPU_FRQ_150MHZ are defined in DSP2833x_Examples.h
//

//
// For 150 MHz SYSCLKOUT(default)
//
#if CPU_FRQ_150MHZ
    #define CPU_SPD              150E6

    //
    // SRG input is LSPCLK (SYSCLKOUT/4) for examples
    //
    #define MCBSP_SRG_FREQ       CPU_SPD/4                    
#endif

//
// For 100 MHz SYSCLKOUT
//
#if CPU_FRQ_100MHZ
    #define CPU_SPD              100E6
    
    //
    // SRG input is LSPCLK (SYSCLKOUT/4) for examples
    //
    #define MCBSP_SRG_FREQ       CPU_SPD/4
#endif

#define CLKGDV_VAL           1

//
// # of CPU cycles in 2 SRG cycles-init delay
//
#define MCBSP_INIT_DELAY     2*(CPU_SPD/MCBSP_SRG_FREQ)

//
// # of CPU cycles in 2 CLKG cycles-init delay
//
#define MCBSP_CLKG_DELAY     2*(CPU_SPD/(MCBSP_SRG_FREQ/(1+CLKGDV_VAL)))

//
// Function Prototypes
//
void delay_loop(void);		// Delay function used for SRG initialization
void clkg_delay_loop(void); // Delay function used for CLKG initialization

//
// InitMcbsp - This function initializes the McBSP to a known state.
//
void InitMcbsp(void)
{
    InitMcbspa();
#if DSP28_MCBSPB
    InitMcbspb();
#endif // end DSP28_MCBSPB
}

//
// InitMcbspa - This function initializes McBSPa to a known state.
//
void 
InitMcbspa(void)
{
    //
    // McBSP-A register settings
    //
    
    //
    // Reset FS generator, sample rate generator & transmitter
    //
    McbspaRegs.SPCR2.all=0x0000;
    
    McbspaRegs.SPCR1.all=0x0000;        // Reset Receiver, Right justify word
    
    //
    // Enable loopback mode for test. 
    // Comment out for normal McBSP transfer mode.
    //
    McbspaRegs.SPCR1.bit.DLB = 1;       

    McbspaRegs.MFFINT.all=0x0;          // Disable all interrupts

    //
    // Single-phase frame, 1 word/frame, No companding	(Receive)
    //
    McbspaRegs.RCR2.all=0x0;
    McbspaRegs.RCR1.all=0x0;
    
    //
    // Single-phase frame, 1 word/frame, No companding	(Transmit)
    //
    McbspaRegs.XCR2.all=0x0;
    McbspaRegs.XCR1.all=0x0;

    //
    // FSX generated internally, FSR derived from an external source
    //
    McbspaRegs.PCR.bit.FSXM = 1;
    
    //
    // CLKX generated internally, CLKR derived from an external source
    //
    McbspaRegs.PCR.bit.CLKXM = 1;

    //
    // CLKSM=1 (If SCLKME=0, i/p clock to SRG is LSPCLK)
    //
    McbspaRegs.SRGR2.bit.CLKSM = 1;
    
    McbspaRegs.SRGR2.bit.FPER = 31;     // FPER = 32 CLKG periods

    McbspaRegs.SRGR1.bit.FWID = 0;      // Frame Width = 1 CLKG period
    
    //
    // CLKG frequency = LSPCLK/(CLKGDV+1)
    //
    McbspaRegs.SRGR1.bit.CLKGDV = CLKGDV_VAL;

    delay_loop();                   // Wait at least 2 SRG clock cycles

    McbspaRegs.SPCR2.bit.GRST=1;    // Enable the sample rate generator
    clkg_delay_loop();              // Wait at least 2 CLKG cycles
    McbspaRegs.SPCR2.bit.XRST=1;    // Release TX from Reset
    McbspaRegs.SPCR1.bit.RRST=1;    // Release RX from Reset
    McbspaRegs.SPCR2.bit.FRST=1;    // Frame Sync Generator reset
}

//
// InitMcbspb - This function initializes McBSPb to a known state.
//
#if (DSP28_MCBSPB)
void 
InitMcbspb(void)
{
    //
    // McBSP-B register settings
    //
    
    //
    // Reset FS generator, sample rate generator & transmitter
    //
    McbspbRegs.SPCR2.all=0x0000;		
    
    McbspbRegs.SPCR1.all=0x0000;		// Reset Receiver, Right justify word
    
    //
    // Enable loopback mode for test. 
    // Comment out for normal McBSP transfer mode.
    //
    McbspbRegs.SPCR1.bit.DLB = 1;

    McbspbRegs.MFFINT.all=0x0;			// Disable all interrupts

    //
    // Single-phase frame, 1 word/frame, No companding	(Receive)
    //
    McbspbRegs.RCR2.all=0x0;
    McbspbRegs.RCR1.all=0x0;

    //
    // Single-phase frame, 1 word/frame, No companding	(Transmit)
    //
    McbspbRegs.XCR2.all=0x0;
    McbspbRegs.XCR1.all=0x0;

    //
    // CLKSM=1 (If SCLKME=0, i/p clock to SRG is LSPCLK)
    //
    McbspbRegs.SRGR2.bit.CLKSM = 1;
    McbspbRegs.SRGR2.bit.FPER = 31;		// FPER = 32 CLKG periods

    McbspbRegs.SRGR1.bit.FWID = 0;      // Frame Width = 1 CLKG period
    
    //
    // CLKG frequency = LSPCLK/(CLKGDV+1)
    //
    McbspbRegs.SRGR1.bit.CLKGDV = CLKGDV_VAL;

    //
    // FSX generated internally, FSR derived from an external source
    //
    McbspbRegs.PCR.bit.FSXM = 1;
    
    //
    // CLKX generated internally, CLKR derived from an external source
    //
    McbspbRegs.PCR.bit.CLKXM = 1;
    
    delay_loop();                   // Wait at least 2 SRG clock cycles
    McbspbRegs.SPCR2.bit.GRST=1;    // Enable the sample rate generator
    clkg_delay_loop();              // Wait at least 2 CLKG cycles
    McbspbRegs.SPCR2.bit.XRST=1;    // Release TX from Reset
    McbspbRegs.SPCR1.bit.RRST=1;    // Release RX from Reset
    McbspbRegs.SPCR2.bit.FRST=1;    // Frame Sync Generator reset
}
#endif // end DSP28_MCBSPB

//
// InitMcbspa8bit - McBSP-A 8-bit Length
//
void 
InitMcbspa8bit(void)
{
    McbspaRegs.RCR1.bit.RWDLEN1=0;     // 8-bit word
    McbspaRegs.XCR1.bit.XWDLEN1=0;     // 8-bit word
}

//
// InitMcbspa12bit - McBSP-A 12 bit Length
//
void 
InitMcbspa12bit(void)
{
    McbspaRegs.RCR1.bit.RWDLEN1=1;     // 12-bit word
    McbspaRegs.XCR1.bit.XWDLEN1=1;     // 12-bit word
}

//
// InitMcbspa16bit - McBSP-A 16 bit Length
//
void 
InitMcbspa16bit(void)
{
    McbspaRegs.RCR1.bit.RWDLEN1=2;      // 16-bit word
    McbspaRegs.XCR1.bit.XWDLEN1=2;      // 16-bit word
}

//
// InitMcbspa20bit - McBSP-A 20 bit Length
//
void 
InitMcbspa20bit(void)
{
    McbspaRegs.RCR1.bit.RWDLEN1=3;     // 20-bit word
    McbspaRegs.XCR1.bit.XWDLEN1=3;     // 20-bit word
}

//
// InitMcbspa24bit - McBSP-A 24 bit Length
//
void 
InitMcbspa24bit(void)
{
    McbspaRegs.RCR1.bit.RWDLEN1=4;     // 24-bit word
    McbspaRegs.XCR1.bit.XWDLEN1=4;     // 24-bit word
}

//
// InitMcbspa32bit - McBSP-A 32 bit Length
//
void 
InitMcbspa32bit(void)
{
    McbspaRegs.RCR1.bit.RWDLEN1=5;     // 32-bit word
    McbspaRegs.XCR1.bit.XWDLEN1=5;     // 32-bit word
}

//
// McBSP-B Data Lengths
//
#if (DSP28_MCBSPB)
//
// InitMcbspb8bit - McBSP-B 8-bit Length
//
void 
InitMcbspb8bit(void)
{
    McbspbRegs.RCR1.bit.RWDLEN1=0;     // 8-bit word
    McbspbRegs.XCR1.bit.XWDLEN1=0;     // 8-bit word
}

//
// InitMcbspb12bit - McBSP-B 12 bit Length
//
void 
InitMcbspb12bit(void)
{
    McbspbRegs.RCR1.bit.RWDLEN1=1;     // 12-bit word
    McbspbRegs.XCR1.bit.XWDLEN1=1;     // 12-bit word
}

//
// InitMcbspb16bit - McBSP-B 16 bit Length
//
void 
InitMcbspb16bit(void)
{
    McbspbRegs.RCR1.bit.RWDLEN1=2;     // 16-bit word
    McbspbRegs.XCR1.bit.XWDLEN1=2;     // 16-bit word
}

//
// InitMcbspb20bit - McBSP-B 20 bit Length
//
void 
InitMcbspb20bit(void)
{
    McbspbRegs.RCR1.bit.RWDLEN1=3;     // 20-bit word
    McbspbRegs.XCR1.bit.XWDLEN1=3;     // 20-bit word
}

//
// InitMcbspb24bit - McBSP-B 24 bit Length
//
void 
InitMcbspb24bit(void)
{
    McbspbRegs.RCR1.bit.RWDLEN1=4;     // 24-bit word
    McbspbRegs.XCR1.bit.XWDLEN1=4;     // 24-bit word
}

//
// InitMcbspb32bit - McBSP-B 32 bit Length
//
void 
InitMcbspb32bit(void)
{
    McbspbRegs.RCR1.bit.RWDLEN1=5;     // 32-bit word
    McbspbRegs.XCR1.bit.XWDLEN1=5;     // 32-bit word
}

#endif //end DSP28_MCBSPB

//
// InitMcbspGpio - 
//
void 
InitMcbspGpio(void)
{
    InitMcbspaGpio();
#if DSP28_MCBSPB
    InitMcbspbGpio();
#endif               // end DSP28_MCBSPB
}

//
// InitMcbspaGpio - This function initializes GPIO pins to function as McBSP-A
//
void 
InitMcbspaGpio(void)
{
    EALLOW;

    //
    // Configure McBSP-A pins using GPIO regs
    // This specifies which of the possible GPIO pins will be McBSP functional
    // pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAMUX2.bit.GPIO20 = 2;	// GPIO20 is MDXA pin
    GpioCtrlRegs.GPAMUX2.bit.GPIO21 = 2;	// GPIO21 is MDRA pin
    GpioCtrlRegs.GPAMUX2.bit.GPIO22 = 2;	// GPIO22 is MCLKXA pin
    GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 2;		// GPIO7 is MCLKRA pin
    //GpioCtrlRegs.GPBMUX2.bit.GPIO58 = 1;	// GPIO58 is MCLKRA pin
    GpioCtrlRegs.GPAMUX2.bit.GPIO23 = 2;	// GPIO23 is MFSXA pin
    GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 2;		// GPIO5 is MFSRA pin
    //GpioCtrlRegs.GPBMUX2.bit.GPIO59 = 1;	// GPIO59 is MFSRA pin

    //
    // Enable internal pull-up for the selected pins
    // Pull-ups can be enabled or disabled by the user.
    // This will enable the pullups for the specified pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO20 = 0;   // Enable pull-up on GPIO20 (MDXA)
    GpioCtrlRegs.GPAPUD.bit.GPIO21 = 0;   // Enable pull-up on GPIO21 (MDRA)
    GpioCtrlRegs.GPAPUD.bit.GPIO22 = 0;   // Enable pull-up on GPIO22 (MCLKXA)
    GpioCtrlRegs.GPAPUD.bit.GPIO7 = 0;    // Enable pull-up on GPIO7 (MCLKRA)
    //GpioCtrlRegs.GPBPUD.bit.GPIO58 = 0;  // Enable pull-up on GPIO58 (MCLKRA)
    GpioCtrlRegs.GPAPUD.bit.GPIO23 = 0;   // Enable pull-up on GPIO23 (MFSXA)
    GpioCtrlRegs.GPAPUD.bit.GPIO5 = 0;    // Enable pull-up on GPIO5 (MFSRA) 
    //GpioCtrlRegs.GPBPUD.bit.GPIO59 = 0;  // Enable pull-up on GPIO59 (MFSRA) 

    //
    // Set qualification for selected input pins to asynch only
    // This will select asynch (no qualification) for the selected pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAQSEL2.bit.GPIO21 = 3;   // Asynch input GPIO21 (MDRA)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO22 = 3;   // Asynch input GPIO22 (MCLKXA)
    GpioCtrlRegs.GPAQSEL1.bit.GPIO7 = 3;    // Asynch input GPIO7 (MCLKRA)
    //GpioCtrlRegs.GPBQSEL2.bit.GPIO58 = 3; // Asynch input GPIO58(MCLKRA)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO23 = 3;   // Asynch input GPIO23 (MFSXA)
    GpioCtrlRegs.GPAQSEL1.bit.GPIO5 = 3;    // Asynch input GPIO5 (MFSRA)
    //GpioCtrlRegs.GPBQSEL2.bit.GPIO59 = 3; // Asynch input GPIO59 (MFSRA)

    EDIS;
}

//
// InitMcbspbGpio - This function initializes GPIO pins to function as McBSP-B
//
#if DSP28_MCBSPB
void 
InitMcbspbGpio(void)
{
    EALLOW;
    
    //
    // Configure McBSP-A pins using GPIO regs
    // This specifies which of the possible GPIO pins will be McBSP functional
    // pins.
    // Comment out other unwanted lines.
    //GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 3;	    // GPIO12 is MDXB pin
    GpioCtrlRegs.GPAMUX2.bit.GPIO24 = 3;	    // GPIO24 is MDXB pin
    //GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 3;	    // GPIO13 is MDRB pin
    GpioCtrlRegs.GPAMUX2.bit.GPIO25 = 3;	    // GPIO25 is MDRB pin
    //GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 3;	    // GPIO14 is MCLKXB pin
    GpioCtrlRegs.GPAMUX2.bit.GPIO26 = 3;	    // GPIO26 is MCLKXB pin
    GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 3;		    // GPIO3 is MCLKRB pin
    //GpioCtrlRegs.GPBMUX2.bit.GPIO60 = 1;	    // GPIO60 is MCLKRB pin
    //GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 3;	    // GPIO15 is MFSXB pin
    GpioCtrlRegs.GPAMUX2.bit.GPIO27 = 3;	    // GPIO27 is MFSXB pin
    GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 3;		    // GPIO1 is MFSRB pin
    //GpioCtrlRegs.GPBMUX2.bit.GPIO61 = 1;	    // GPIO61 is MFSRB pin

    //
    // Enable internal pull-up for the selected pins
    // Pull-ups can be enabled or disabled by the user.
    // This will enable the pullups for the specified pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO24 = 0;	    //Enable pull-up on GPIO24 (MDXB)
    //GpioCtrlRegs.GPAPUD.bit.GPIO12 = 0;	//Enable pull-up on GPIO12 (MDXB)
    GpioCtrlRegs.GPAPUD.bit.GPIO25 = 0;	    //Enable pull-up on GPIO25 (MDRB)
    //GpioCtrlRegs.GPAPUD.bit.GPIO13 = 0;	//Enable pull-up on GPIO13 (MDRB)
    GpioCtrlRegs.GPAPUD.bit.GPIO26 = 0;	    //Enable pull-up on GPIO26 (MCLKXB)
    //GpioCtrlRegs.GPAPUD.bit.GPIO14 = 0;	//Enable pull-up on GPIO14 (MCLKXB)
    GpioCtrlRegs.GPAPUD.bit.GPIO3 = 0;		//Enable pull-up on GPIO3 (MCLKRB)
    //GpioCtrlRegs.GPBPUD.bit.GPIO60 = 0;	//Enable pull-up on GPIO60 (MCLKRB)
    GpioCtrlRegs.GPAPUD.bit.GPIO27 = 0;	    //Enable pull-up on GPIO27 (MFSXB)
    //GpioCtrlRegs.GPAPUD.bit.GPIO15 = 0;	//Enable pull-up on GPIO15 (MFSXB)
    GpioCtrlRegs.GPAPUD.bit.GPIO1 = 0;		//Enable pull-up on GPIO1 (MFSRB) 
    //GpioCtrlRegs.GPBPUD.bit.GPIO61 = 0;	//Enable pull-up on GPIO61 (MFSRB)

    //
    // Set qualification for selected input pins to asynch only
    // This will select asynch (no qualification) for the selected pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAQSEL2.bit.GPIO25 = 3;   // Asynch input GPIO25 (MDRB)
    //GpioCtrlRegs.GPAQSEL1.bit.GPIO13 = 3; // Asynch input GPIO13 (MDRB)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO26 = 3;   // Asynch input GPIO26(MCLKXB)
    //GpioCtrlRegs.GPAQSEL1.bit.GPIO14 = 3; // Asynch input GPIO14 (MCLKXB)
    GpioCtrlRegs.GPAQSEL1.bit.GPIO3 = 3;    // Asynch input GPIO3 (MCLKRB)
    //GpioCtrlRegs.GPBQSEL2.bit.GPIO60 = 3; // Asynch input GPIO60 (MCLKRB)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO27 = 3;   // Asynch input GPIO27 (MFSXB)
    //GpioCtrlRegs.GPAQSEL1.bit.GPIO15 = 3; // Asynch input GPIO15 (MFSXB)
    GpioCtrlRegs.GPAQSEL1.bit.GPIO1 = 3;    // Asynch input GPIO1 (MFSRB)
    //GpioCtrlRegs.GPBQSEL2.bit.GPIO61 = 3; // Asynch input GPIO61 (MFSRB)

    EDIS;
}
#endif // end DSP28_MCBSPB

//
// delay_loop - 
//
void 
delay_loop(void)
{
    long      i;
    
    //
    // delay in McBsp init. must be at least 2 SRG cycles
    //
    for (i = 0; i < MCBSP_INIT_DELAY; i++)
    {
        
    }
}

//
// clkg_delay_loop - 
//
void 
clkg_delay_loop(void)
{
    long      i;
    
    //
    // delay in McBsp init. must be at least 2 SRG cycles
    //
    for (i = 0; i < MCBSP_CLKG_DELAY; i++)
    {
     
    } 
}

//
// End of File
//

