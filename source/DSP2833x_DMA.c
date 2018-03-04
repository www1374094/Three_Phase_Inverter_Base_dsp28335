//###########################################################################
//
// FILE:	DSP2833x_DMA.c
//
// TITLE:	DSP2833x Device DMA Initialization & Support Functions.
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
// DMAInitialize - This function initializes the DMA to a known state.
//
void 
DMAInitialize(void)
{
    EALLOW;

    //
    // Perform a hard reset on DMA
    //
    DmaRegs.DMACTRL.bit.HARDRESET = 1;
    asm (" nop");       // one NOP required after HARDRESET
    
    //
    // Allow DMA to run free on emulation suspend
    //
    DmaRegs.DEBUGCTRL.bit.FREE = 1;

    EDIS;
}

//
// DMACH1AddrConfig - 
//
void 
DMACH1AddrConfig(volatile Uint16 *DMA_Dest,volatile Uint16 *DMA_Source)
{
    EALLOW;
    
    //
    // Set up SOURCE address
    //
    
    //
    // Point to beginning of source buffer
    //
    DmaRegs.CH1.SRC_BEG_ADDR_SHADOW = (Uint32)DMA_Source;
    
    DmaRegs.CH1.SRC_ADDR_SHADOW =     (Uint32)DMA_Source;

    //
    // Set up DESTINATION address
    //
    
    //
    // Point to beginning of destination buffer
    //
    DmaRegs.CH1.DST_BEG_ADDR_SHADOW = (Uint32)DMA_Dest;
    
    DmaRegs.CH1.DST_ADDR_SHADOW =     (Uint32)DMA_Dest;

    EDIS;
}

//
// DMACH1BurstConfig - 
//
void 
DMACH1BurstConfig(Uint16 bsize, int16 srcbstep, int16 desbstep)
{
	EALLOW;

    //
	// Set up BURST registers:
    //
	
    //
    // Number of words(X-1) x-ferred in a burst
    //
    DmaRegs.CH1.BURST_SIZE.all = bsize;
    
    //
    // Increment source addr between each word x-ferred
    //
	DmaRegs.CH1.SRC_BURST_STEP = srcbstep;
    
    //
    // Increment dest addr between each word x-ferred
    //
	DmaRegs.CH1.DST_BURST_STEP = desbstep;

	EDIS;
}

//
// DMACH1TransferConfig - 
//
void 
DMACH1TransferConfig(Uint16 tsize, int16 srctstep, int16 deststep)
{
	EALLOW;

    //
	// Set up TRANSFER registers:
    //
    
    //
    // Number of bursts per transfer, DMA interrupt will occur after 
    // completed transfer
    //
	DmaRegs.CH1.TRANSFER_SIZE = tsize;
	
    //
    // TRANSFER_STEP is ignored when WRAP occurs
    //
    DmaRegs.CH1.SRC_TRANSFER_STEP = srctstep;
	
    //
    // TRANSFER_STEP is ignored when WRAP occurs
    //
    DmaRegs.CH1.DST_TRANSFER_STEP = deststep;

	EDIS;
}

//
// DMACH1WrapConfig -
//
void DMACH1WrapConfig(Uint16 srcwsize, int16 srcwstep, Uint16 deswsize, int16
                 deswstep)
{
	EALLOW;

    //
    // Set up WRAP registers
    //
	DmaRegs.CH1.SRC_WRAP_SIZE = srcwsize; // Wrap source address after N bursts
    DmaRegs.CH1.SRC_WRAP_STEP = srcwstep; // Step for source wrap

    //
    // Wrap destination address after N bursts
    //
	DmaRegs.CH1.DST_WRAP_SIZE = deswsize; 
    
	DmaRegs.CH1.DST_WRAP_STEP = deswstep; // Step for destination wrap

	EDIS;
}

//
// DMACH1ModeConfig - 
//
void 
DMACH1ModeConfig(Uint16 persel, Uint16 perinte, Uint16 oneshot, Uint16 cont, 
                 Uint16 synce, Uint16 syncsel, Uint16 ovrinte, Uint16 datasize,
                 Uint16 chintmode, Uint16 chinte)
{
    EALLOW;

    //
    // Set up MODE Register:
    //
    
    //
    // Passed DMA channel as peripheral interrupt source
    //
    DmaRegs.CH1.MODE.bit.PERINTSEL = persel;
    
    DmaRegs.CH1.MODE.bit.PERINTE = perinte;  // Peripheral interrupt enable
    DmaRegs.CH1.MODE.bit.ONESHOT = oneshot;  // Oneshot enable
    DmaRegs.CH1.MODE.bit.CONTINUOUS = cont;  // Continous enable
    DmaRegs.CH1.MODE.bit.SYNCE = synce;      // Peripheral sync enable/disable
    DmaRegs.CH1.MODE.bit.SYNCSEL = syncsel;  // Sync effects source or destination
    DmaRegs.CH1.MODE.bit.OVRINTE = ovrinte;  // Enable/disable the overflow interrupt
    DmaRegs.CH1.MODE.bit.DATASIZE = datasize; // 16/32-bit data size transfers
    
    //
    // Generate interrupt to CPU at beginning/end of transfer
    //
    DmaRegs.CH1.MODE.bit.CHINTMODE = chintmode;
    
    //
    // Channel Interrupt to CPU enable
    //
    DmaRegs.CH1.MODE.bit.CHINTE = chinte;

    //
    // Clear any spurious flags:
    //
    DmaRegs.CH1.CONTROL.bit.PERINTCLR = 1;// Clear any spurious interrupt flags
    DmaRegs.CH1.CONTROL.bit.SYNCCLR = 1;  // Clear any spurious sync flags
    DmaRegs.CH1.CONTROL.bit.ERRCLR = 1;  // Clear any spurious sync error flags

    //
    // Initialize PIE vector for CPU interrupt:
    //
    PieCtrlRegs.PIEIER7.bit.INTx1 = 1;   // Enable DMA CH1 interrupt in PIE

    EDIS;
}

//
// StartDMACH1 - This function starts DMA Channel 1.
//
void 
StartDMACH1(void)
{
    EALLOW;
    DmaRegs.CH1.CONTROL.bit.RUN = 1;
    EDIS;
}

//
// DMACH2AddrConfig - 
//
void 
DMACH2AddrConfig(volatile Uint16 *DMA_Dest,volatile Uint16 *DMA_Source)
{
    EALLOW;

    //
    // Set up SOURCE address:
    //
    
    //
    // Point to beginning of source buffer
    //
    DmaRegs.CH2.SRC_BEG_ADDR_SHADOW = (Uint32)DMA_Source;
    DmaRegs.CH2.SRC_ADDR_SHADOW =     (Uint32)DMA_Source;

    //
    // Set up DESTINATION address:
    //
    
    //
    // Point to beginning of destination buffer
    //
    DmaRegs.CH2.DST_BEG_ADDR_SHADOW = (Uint32)DMA_Dest;
    DmaRegs.CH2.DST_ADDR_SHADOW =     (Uint32)DMA_Dest;

    EDIS;
}

//
// DMACH2BurstConfig -
//
void
DMACH2BurstConfig(Uint16 bsize, int16 srcbstep, int16 desbstep)
{
	EALLOW;

    //
	// Set up BURST registers:
    //
	
    //
    // Number of words(X-1) x-ferred in a burst
    //
    DmaRegs.CH2.BURST_SIZE.all = bsize;
    
	//
    // Increment source addr between each word x-ferred
    //
    DmaRegs.CH2.SRC_BURST_STEP = srcbstep;
    
    //
	// Increment dest addr between each word x-ferred
    //
    DmaRegs.CH2.DST_BURST_STEP = desbstep;

	EDIS;
}

//
// DMACH2TransferConfig - 
//
void 
DMACH2TransferConfig(Uint16 tsize, int16 srctstep, int16 deststep)
{
	EALLOW;
    
    //
    // Set up TRANSFER registers:
    //
	
    //
    // Number of bursts per transfer, DMA interrupt will occur 
    // after completed transfer
    //
    DmaRegs.CH2.TRANSFER_SIZE = tsize;
	
    //
    // TRANSFER_STEP is ignored when WRAP occurs
    //
    DmaRegs.CH2.SRC_TRANSFER_STEP = srctstep;
    
    //
    // TRANSFER_STEP is ignored when WRAP occurs
    //
	DmaRegs.CH2.DST_TRANSFER_STEP = deststep;

	EDIS;
}

//
// DMACH2WrapConfig - 
//
void 
DMACH2WrapConfig(Uint16 srcwsize, int16 srcwstep, Uint16 deswsize, 
                 int16 deswstep)
{
	EALLOW;

    //
	// Set up WRAP registers:
    //
    
    //
    // Wrap source address after N bursts
    //
	DmaRegs.CH2.SRC_WRAP_SIZE = srcwsize;
    
    //
    // Step for source wrap
    //
    DmaRegs.CH2.SRC_WRAP_STEP = srcwstep;

    //
    // Wrap destination address after N bursts
    //    
	DmaRegs.CH2.DST_WRAP_SIZE = deswsize;
    
    //
    // Step for destination wrap
    //
	DmaRegs.CH2.DST_WRAP_STEP = deswstep;

	EDIS;
}

//
// DMACH2ModeConfig - 
//
void 
DMACH2ModeConfig(Uint16 persel, Uint16 perinte, Uint16 oneshot, Uint16 cont, 
                 Uint16 synce, Uint16 syncsel, Uint16 ovrinte, Uint16 datasize,
                 Uint16 chintmode, Uint16 chinte)
{
    EALLOW;

    //
    // Set up MODE Register
    //
    
    //
    // Passed DMA channel as peripheral interrupt source
    //
    DmaRegs.CH2.MODE.bit.PERINTSEL = persel;	    
    
    //
    // Peripheral interrupt enable
    //
    DmaRegs.CH2.MODE.bit.PERINTE = perinte;
    
    //
    // Oneshot enable
    //
    DmaRegs.CH2.MODE.bit.ONESHOT = oneshot;
    
    //
    // Continous enable
    //
    DmaRegs.CH2.MODE.bit.CONTINUOUS = cont;
    
    //
    // Peripheral sync enable/disable
    //
    DmaRegs.CH2.MODE.bit.SYNCE = synce;
    
    //
    // Sync effects source or destination
    //
    DmaRegs.CH2.MODE.bit.SYNCSEL = syncsel;
    
    //
    // Enable/disable the overflow interrupt
    //
    DmaRegs.CH2.MODE.bit.OVRINTE = ovrinte;
    
    //
    // 16-bit/32-bit data size transfers
    //
    DmaRegs.CH2.MODE.bit.DATASIZE = datasize;
    
    //
    // Generate interrupt to CPU at beginning/end of transfer
    //
    DmaRegs.CH2.MODE.bit.CHINTMODE = chintmode;
    
    //
    // Channel Interrupt to CPU enable
    //
    DmaRegs.CH2.MODE.bit.CHINTE = chinte;

    //
    // Clear any spurious flags:
    //
    
    //
    // Clear any spurious interrupt flags
    //
    DmaRegs.CH2.CONTROL.bit.PERINTCLR = 1;
    
    //
    // Clear any spurious sync flags
    //
    DmaRegs.CH2.CONTROL.bit.SYNCCLR = 1;
    
    //
    // Clear any spurious sync error flags
    //
    DmaRegs.CH2.CONTROL.bit.ERRCLR = 1;

    //
    // Initialize PIE vector for CPU interrupt
    //
    PieCtrlRegs.PIEIER7.bit.INTx2 = 1;      // Enable DMA CH2 interrupt in PIE

    EDIS;
}

//
// StartDMACH2 - This function starts DMA Channel 2.
//
void 
StartDMACH2(void)
{
    EALLOW;
    DmaRegs.CH2.CONTROL.bit.RUN = 1;
    EDIS;
}

//
// DMACH3AddrConfig - 
//
void 
DMACH3AddrConfig(volatile Uint16 *DMA_Dest,volatile Uint16 *DMA_Source)
{
    EALLOW;

    //
    // Set up SOURCE address:
    //
    
    //
    // Point to beginning of source buffer
    //
    DmaRegs.CH3.SRC_BEG_ADDR_SHADOW = (Uint32)DMA_Source;
    DmaRegs.CH3.SRC_ADDR_SHADOW =     (Uint32)DMA_Source;

    //
    // Set up DESTINATION address:
    //
    
    //
    // Point to beginning of destination buffer
    //
    DmaRegs.CH3.DST_BEG_ADDR_SHADOW = (Uint32)DMA_Dest;
    
    DmaRegs.CH3.DST_ADDR_SHADOW =     (Uint32)DMA_Dest;

    EDIS;
}

//
// DMACH3BurstConfig - 
//
void 
DMACH3BurstConfig(Uint16 bsize, int16 srcbstep, int16 desbstep)
{
	EALLOW;

    //
	// Set up BURST registers:
    //
    
    //
    // Number of words(X-1) x-ferred in a burst
    //
	DmaRegs.CH3.BURST_SIZE.all = bsize;
    
    //
    // Increment source addr between each word x-ferred
    //
	DmaRegs.CH3.SRC_BURST_STEP = srcbstep;
    
    //
    // Increment dest addr between each word x-ferred
    //
	DmaRegs.CH3.DST_BURST_STEP = desbstep;

	EDIS;
}

//
// DMACH3TransferConfig - 
//
void 
DMACH3TransferConfig(Uint16 tsize, int16 srctstep, int16 deststep)
{
	EALLOW;

    //
    // Set up TRANSFER registers:
    //
    
    //
    // Number of bursts per transfer, DMA interrupt will occur after
    // completed transfer
    //
	DmaRegs.CH3.TRANSFER_SIZE = tsize;
    
    //
    // TRANSFER_STEP is ignored when WRAP occurs
    //
	DmaRegs.CH3.SRC_TRANSFER_STEP = srctstep;
    
    //
    // TRANSFER_STEP is ignored when WRAP occurs
    //
	DmaRegs.CH3.DST_TRANSFER_STEP = deststep;

	EDIS;
}

//
// DMACH3WrapConfig - 
//
void 
DMACH3WrapConfig(Uint16 srcwsize, int16 srcwstep, Uint16 deswsize, 
                 int16 deswstep)
{
	EALLOW;
    
    //
    // Set up WRAP registers:
    //
	DmaRegs.CH3.SRC_WRAP_SIZE = srcwsize; // Wrap source address after N bursts
    DmaRegs.CH3.SRC_WRAP_STEP = srcwstep; // Step for source wrap

    //
    // Wrap destination address after N bursts
    //
	DmaRegs.CH3.DST_WRAP_SIZE = deswsize;
    
    //
    // Step for destination wrap
    //
	DmaRegs.CH3.DST_WRAP_STEP = deswstep;

	EDIS;
}

//
// DMACH3ModeConfig - 
//
void 
DMACH3ModeConfig(Uint16 persel, Uint16 perinte, Uint16 oneshot, Uint16 cont, 
                 Uint16 synce, Uint16 syncsel, Uint16 ovrinte, Uint16 datasize,
                 Uint16 chintmode, Uint16 chinte)
{
	EALLOW;

    //
	// Set up MODE Register:
    //
    
    //
    // Passed DMA channel as peripheral interrupt source
    //
	DmaRegs.CH3.MODE.bit.PERINTSEL = persel;
    
    //
    // Peripheral interrupt enable
    //
	DmaRegs.CH3.MODE.bit.PERINTE = perinte;
    
	DmaRegs.CH3.MODE.bit.ONESHOT = oneshot;     // Oneshot enable
	DmaRegs.CH3.MODE.bit.CONTINUOUS = cont;   	// Continous enable
	DmaRegs.CH3.MODE.bit.SYNCE = synce;     // Peripheral sync enable/disable
	
    //
    // Sync effects source or destination
    //
    DmaRegs.CH3.MODE.bit.SYNCSEL = syncsel;
    
    //
    // Enable/disable the overflow interrupt
    //
	DmaRegs.CH3.MODE.bit.OVRINTE = ovrinte;
    
    //
    // 16-bit/32-bit data size transfers
    //
	DmaRegs.CH3.MODE.bit.DATASIZE = datasize;
    
    //
    // Generate interrupt to CPU at beginning/end of transfer
    //
	DmaRegs.CH3.MODE.bit.CHINTMODE = chintmode;
    
    //
    // Channel Interrupt to CPU enable
    //
	DmaRegs.CH3.MODE.bit.CHINTE = chinte;

    //
	// Clear any spurious flags:
    //
    
    //
    // Clear any spurious interrupt flags
    //
	DmaRegs.CH3.CONTROL.bit.PERINTCLR = 1;
    
	DmaRegs.CH3.CONTROL.bit.SYNCCLR = 1;   	// Clear any spurious sync flags
	
    //
    // Clear any spurious sync error flags
    //
    DmaRegs.CH3.CONTROL.bit.ERRCLR = 1;

    //
	// Initialize PIE vector for CPU interrupt:
    //
	PieCtrlRegs.PIEIER7.bit.INTx3 = 1;     // Enable DMA CH3 interrupt in PIE

	EDIS;
}

//
// StartDMACH3 - This function starts DMA Channel 3.
//
void 
StartDMACH3(void)
{
    EALLOW;
    DmaRegs.CH3.CONTROL.bit.RUN = 1;
    EDIS;
}

//
// DMACH4AddrConfig - 
//
void 
DMACH4AddrConfig(volatile Uint16 *DMA_Dest,volatile Uint16 *DMA_Source)
{
    EALLOW;

    //
    // Set up SOURCE address:
    //
    
    //
    // Point to beginning of source buffer
    //
    DmaRegs.CH4.SRC_BEG_ADDR_SHADOW = (Uint32)DMA_Source;
    
    DmaRegs.CH4.SRC_ADDR_SHADOW =     (Uint32)DMA_Source;

    //
    // Set up DESTINATION address:
    //
    
    //
    // Point to beginning of destination buffer
    //
    DmaRegs.CH4.DST_BEG_ADDR_SHADOW = (Uint32)DMA_Dest;
    
    DmaRegs.CH4.DST_ADDR_SHADOW =     (Uint32)DMA_Dest;

    EDIS;
}

//
// DMACH4BurstConfig - 
//
void 
DMACH4BurstConfig(Uint16 bsize, int16 srcbstep, int16 desbstep)
{
	EALLOW;

    //
	// Set up BURST registers:
    //
    
    //
    // Number of words(X-1) x-ferred in a burst
    //
	DmaRegs.CH4.BURST_SIZE.all = bsize;
    
    //
    // Increment source addr between each word x-ferred
    //
	DmaRegs.CH4.SRC_BURST_STEP = srcbstep;
    
    //
    // Increment dest addr between each word x-ferred
    //
	DmaRegs.CH4.DST_BURST_STEP = desbstep;

	EDIS;
}

//
// DMACH4TransferConfig - 
//
void 
DMACH4TransferConfig(Uint16 tsize, int16 srctstep, int16 deststep)
{
	EALLOW;
    
    //
	// Set up TRANSFER registers:
    //
	
    //
    // Number of bursts per transfer, DMA interrupt will occur after completed
    // transfer
    //
    DmaRegs.CH4.TRANSFER_SIZE = tsize;
    
    //
    // TRANSFER_STEP is ignored when WRAP occurs
    //
	DmaRegs.CH4.SRC_TRANSFER_STEP = srctstep;
    
    //
    // TRANSFER_STEP is ignored when WRAP occurs
    //
	DmaRegs.CH4.DST_TRANSFER_STEP = deststep;

	EDIS;
}

//
// DMACH4WrapConfig - 
//
void 
DMACH4WrapConfig(Uint16 srcwsize, int16 srcwstep, Uint16 deswsize, 
                 int16 deswstep)
{
	EALLOW;
    
    //
	// Set up WRAP registers:
    //
	DmaRegs.CH4.SRC_WRAP_SIZE = srcwsize;// Wrap source address after N bursts
    DmaRegs.CH4.SRC_WRAP_STEP = srcwstep;// Step for source wrap

	//
    // Wrap destination address after N bursts
    //
    DmaRegs.CH4.DST_WRAP_SIZE = deswsize;
    
	DmaRegs.CH4.DST_WRAP_STEP = deswstep;   // Step for destination wrap

	EDIS;
}

//
// DMACH4ModeConfig - 
//
void 
DMACH4ModeConfig(Uint16 persel, Uint16 perinte, Uint16 oneshot, Uint16 cont, 
                 Uint16 synce, Uint16 syncsel, Uint16 ovrinte, Uint16 datasize,
                 Uint16 chintmode, Uint16 chinte)
{
    EALLOW;

    //
	// Set up MODE Register:
    //
    
    //
    // Passed DMA channel as peripheral interrupt source
    //
	DmaRegs.CH4.MODE.bit.PERINTSEL = persel;
    
    //
    // Peripheral interrupt enable
    //
	DmaRegs.CH4.MODE.bit.PERINTE = perinte;
    
	DmaRegs.CH4.MODE.bit.ONESHOT = oneshot;     // Oneshot enable
	DmaRegs.CH4.MODE.bit.CONTINUOUS = cont;   	// Continous enable
	DmaRegs.CH4.MODE.bit.SYNCE = synce;     // Peripheral sync enable/disable
	
    //
    // Sync effects source or destination
    //
    DmaRegs.CH4.MODE.bit.SYNCSEL = syncsel;
    
    //
    // Enable/disable the overflow interrupt
    //
	DmaRegs.CH4.MODE.bit.OVRINTE = ovrinte;
    
    //
    // 16-bit/32-bit data size transfers
    //
	DmaRegs.CH4.MODE.bit.DATASIZE = datasize;
    
    //
    // Generate interrupt to CPU at beginning/end of transfer
    //
	DmaRegs.CH4.MODE.bit.CHINTMODE = chintmode;
    
    //
    // Channel Interrupt to CPU enable
    //
	DmaRegs.CH4.MODE.bit.CHINTE = chinte;

    //
	// Clear any spurious flags:
    //
    
    //
    // Clear any spurious interrupt flags
    //
	DmaRegs.CH4.CONTROL.bit.PERINTCLR = 1;
    
	DmaRegs.CH4.CONTROL.bit.SYNCCLR = 1;   	// Clear any spurious sync flags
	
    //
    // Clear any spurious sync error flags
    //
    DmaRegs.CH4.CONTROL.bit.ERRCLR = 1;

    //
	// Initialize PIE vector for CPU interrupt:
    //
	PieCtrlRegs.PIEIER7.bit.INTx4 = 1;     // Enable DMA CH4 interrupt in PIE

	EDIS;
}

//
// StartDMACH4 - This function starts DMA Channel 4.
//
void 
StartDMACH4(void)
{
    EALLOW;
    DmaRegs.CH4.CONTROL.bit.RUN = 1;
    EDIS;
}

//
// DMACH5AddrConfig - 
//
void 
DMACH5AddrConfig(volatile Uint16 *DMA_Dest,volatile Uint16 *DMA_Source)
{
	EALLOW;

    //
	// Set up SOURCE address:
    //
	
    //
    // Point to beginning of source buffer
    //
    DmaRegs.CH5.SRC_BEG_ADDR_SHADOW = (Uint32)DMA_Source;
    
	DmaRegs.CH5.SRC_ADDR_SHADOW =     (Uint32)DMA_Source;

    //
	// Set up DESTINATION address:
    //
    
    //
    // Point to beginning of destination buffer
    //
	DmaRegs.CH5.DST_BEG_ADDR_SHADOW = (Uint32)DMA_Dest;
    
	DmaRegs.CH5.DST_ADDR_SHADOW =     (Uint32)DMA_Dest;

    EDIS;
}

//
// DMACH5BurstConfig - 
//
void 
DMACH5BurstConfig(Uint16 bsize, int16 srcbstep, int16 desbstep)
{
	EALLOW;

    //
	// Set up BURST registers:
    //
    
    //
    // Number of words(X-1) x-ferred in a burst
    //
	DmaRegs.CH5.BURST_SIZE.all = bsize;
    
    //
    // Increment source addr between each word x-ferred
    //
	DmaRegs.CH5.SRC_BURST_STEP = srcbstep;
    
    //
    // Increment dest addr between each word x-ferred
    //
	DmaRegs.CH5.DST_BURST_STEP = desbstep;

	EDIS;
}

//
// DMACH5TransferConfig - 
//
void 
DMACH5TransferConfig(Uint16 tsize, int16 srctstep, int16 deststep)
{
	EALLOW;
    
    //
	// Set up TRANSFER registers:
    //
	
    //
    // Number of bursts per transfer, DMA interrupt will occur after completed
    // transfer
    //
    DmaRegs.CH5.TRANSFER_SIZE = tsize;
    
    //
    // TRANSFER_STEP is ignored when WRAP occurs
    //
	DmaRegs.CH5.SRC_TRANSFER_STEP = srctstep;
    
    //
    // TRANSFER_STEP is ignored when WRAP occurs
    //
	DmaRegs.CH5.DST_TRANSFER_STEP = deststep;

	EDIS;
}

//
// DMACH5WrapConfig - 
//
void 
DMACH5WrapConfig(Uint16 srcwsize, int16 srcwstep, Uint16 deswsize, 
                 int16 deswstep)
{
	EALLOW;
    
    //
	// Set up WRAP registers:
    //
	DmaRegs.CH5.SRC_WRAP_SIZE = srcwsize;// Wrap source address after N bursts
    DmaRegs.CH5.SRC_WRAP_STEP = srcwstep;// Step for source wrap

	//
    // Wrap destination address after N bursts
    //
    DmaRegs.CH5.DST_WRAP_SIZE = deswsize;
    
	DmaRegs.CH5.DST_WRAP_STEP = deswstep;   // Step for destination wrap

	EDIS;
}

//
// DMACH5ModeConfig - 
//
void 
DMACH5ModeConfig(Uint16 persel, Uint16 perinte, Uint16 oneshot, Uint16 cont, 
                 Uint16 synce, Uint16 syncsel, Uint16 ovrinte, Uint16 datasize,
                 Uint16 chintmode, Uint16 chinte)
{
	EALLOW;

    //
	// Set up MODE Register:
    //
    
    //
    // Passed DMA channel as peripheral interrupt source
    //
	DmaRegs.CH5.MODE.bit.PERINTSEL = persel;
    
    //
    // Peripheral interrupt enable
    //
	DmaRegs.CH5.MODE.bit.PERINTE = perinte;
    
	DmaRegs.CH5.MODE.bit.ONESHOT = oneshot;     // Oneshot enable
	DmaRegs.CH5.MODE.bit.CONTINUOUS = cont;   	// Continous enable
	DmaRegs.CH5.MODE.bit.SYNCE = synce;     // Peripheral sync enable/disable
	
    //
    // Sync effects source or destination
    //
    DmaRegs.CH5.MODE.bit.SYNCSEL = syncsel;
    
    //
    // Enable/disable the overflow interrupt
    //
	DmaRegs.CH5.MODE.bit.OVRINTE = ovrinte;
    
    //
    // 16-bit/32-bit data size transfers
    //
	DmaRegs.CH5.MODE.bit.DATASIZE = datasize;
    
    //
    // Generate interrupt to CPU at beginning/end of transfer
    //
	DmaRegs.CH5.MODE.bit.CHINTMODE = chintmode;
    
    //
    // Channel Interrupt to CPU enable
    //
	DmaRegs.CH5.MODE.bit.CHINTE = chinte;

    //
	// Clear any spurious flags:
    //
    
    //
    // Clear any spurious interrupt flags
    //
	DmaRegs.CH5.CONTROL.bit.PERINTCLR = 1;
    
	DmaRegs.CH5.CONTROL.bit.SYNCCLR = 1;   	// Clear any spurious sync flags
	
    //
    // Clear any spurious sync error flags
    //
    DmaRegs.CH5.CONTROL.bit.ERRCLR = 1;

    //
	// Initialize PIE vector for CPU interrupt:
    //
	PieCtrlRegs.PIEIER7.bit.INTx5 = 1;     // Enable DMA CH5 interrupt in PIE

	EDIS;
}

//
// StartDMACH5 - This function starts DMA Channel 5.
//
void 
StartDMACH5(void)
{
	EALLOW;
	DmaRegs.CH5.CONTROL.bit.RUN = 1;
	EDIS;
}

//
// DMACH6AddrConfig - 
//
void 
DMACH6AddrConfig(volatile Uint16 *DMA_Dest,volatile Uint16 *DMA_Source)
{
	EALLOW;

    //
	// Set up SOURCE address:
    //
    
	//
    // Point to beginning of source buffer
    //
    DmaRegs.CH6.SRC_BEG_ADDR_SHADOW = (Uint32)DMA_Source;
    
	DmaRegs.CH6.SRC_ADDR_SHADOW =     (Uint32)DMA_Source;

    //
	// Set up DESTINATION address:
    //
	
    //
    // Point to beginning of destination buffer
    //
    DmaRegs.CH6.DST_BEG_ADDR_SHADOW = (Uint32)DMA_Dest;
    
	DmaRegs.CH6.DST_ADDR_SHADOW =     (Uint32)DMA_Dest;

	EDIS;
}

//
// DMACH6BurstConfig - 
//
void 
DMACH6BurstConfig(Uint16 bsize, int16 srcbstep, int16 desbstep)
{
	EALLOW;

    //
	// Set up BURST registers:
    //
    
    //
    // Number of words(X-1) x-ferred in a burst
    //
	DmaRegs.CH6.BURST_SIZE.all = bsize;
    
    //
    // Increment source addr between each word x-ferred
    //
	DmaRegs.CH6.SRC_BURST_STEP = srcbstep;
    
    //
    // Increment dest addr between each word x-ferred
    //
	DmaRegs.CH6.DST_BURST_STEP = desbstep;

	EDIS;
}

//
// DMACH6TransferConfig - 
//
void 
DMACH6TransferConfig(Uint16 tsize, int16 srctstep, int16 deststep)
{
	EALLOW;
    
    //
	// Set up TRANSFER registers:
    //
	
    //
    // Number of bursts per transfer, DMA interrupt will occur after completed
    // transfer
    //
    DmaRegs.CH6.TRANSFER_SIZE = tsize;
    
    //
    // TRANSFER_STEP is ignored when WRAP occurs
    //
	DmaRegs.CH6.SRC_TRANSFER_STEP = srctstep;
    
    //
    // TRANSFER_STEP is ignored when WRAP occurs
    //
	DmaRegs.CH6.DST_TRANSFER_STEP = deststep;

	EDIS;
}

//
// DMACH6WrapConfig - 
//
void 
DMACH6WrapConfig(Uint16 srcwsize, int16 srcwstep, Uint16 deswsize, 
                 int16 deswstep)
{
	EALLOW;
    
    //
	// Set up WRAP registers:
    //
	DmaRegs.CH6.SRC_WRAP_SIZE = srcwsize;// Wrap source address after N bursts
    DmaRegs.CH6.SRC_WRAP_STEP = srcwstep;// Step for source wrap

	//
    // Wrap destination address after N bursts
    //
    DmaRegs.CH6.DST_WRAP_SIZE = deswsize;
    
	DmaRegs.CH6.DST_WRAP_STEP = deswstep;   // Step for destination wrap

	EDIS;
}

//
// DMACH6ModeConfig - 
//
void 
DMACH6ModeConfig(Uint16 persel, Uint16 perinte, Uint16 oneshot, Uint16 cont, 
                 Uint16 synce, Uint16 syncsel, Uint16 ovrinte, Uint16 datasize,
                 Uint16 chintmode, Uint16 chinte)
{
	EALLOW;

    //
	// Set up MODE Register:
    //
    
    //
    // Passed DMA channel as peripheral interrupt source
    //
	DmaRegs.CH6.MODE.bit.PERINTSEL = persel;
    
    //
    // Peripheral interrupt enable
    //
	DmaRegs.CH6.MODE.bit.PERINTE = perinte;
    
	DmaRegs.CH6.MODE.bit.ONESHOT = oneshot;     // Oneshot enable
	DmaRegs.CH6.MODE.bit.CONTINUOUS = cont;   	// Continous enable
	DmaRegs.CH6.MODE.bit.SYNCE = synce;     // Peripheral sync enable/disable
	
    //
    // Sync effects source or destination
    //
    DmaRegs.CH6.MODE.bit.SYNCSEL = syncsel;
    
    //
    // Enable/disable the overflow interrupt
    //
	DmaRegs.CH6.MODE.bit.OVRINTE = ovrinte;
    
    //
    // 16-bit/32-bit data size transfers
    //
	DmaRegs.CH6.MODE.bit.DATASIZE = datasize;
    
    //
    // Generate interrupt to CPU at beginning/end of transfer
    //
	DmaRegs.CH6.MODE.bit.CHINTMODE = chintmode;
    
    //
    // Channel Interrupt to CPU enable
    //
	DmaRegs.CH6.MODE.bit.CHINTE = chinte;

    //
	// Clear any spurious flags:
    //
    
    //
    // Clear any spurious interrupt flags
    //
	DmaRegs.CH6.CONTROL.bit.PERINTCLR = 1;
    
	DmaRegs.CH6.CONTROL.bit.SYNCCLR = 1;   	// Clear any spurious sync flags
	
    //
    // Clear any spurious sync error flags
    //
    DmaRegs.CH6.CONTROL.bit.ERRCLR = 1;

    //
	// Initialize PIE vector for CPU interrupt:
    //
	PieCtrlRegs.PIEIER7.bit.INTx6 = 1;     // Enable DMA CH6 interrupt in PIE

	EDIS;
}

//
// StartDMACH6 - This function starts DMA Channel 6.
//
void 
StartDMACH6(void)
{
    EALLOW;
    DmaRegs.CH6.CONTROL.bit.RUN = 1;
    EDIS;
}

//
// End of File
//

