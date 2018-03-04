; TI File $Revision: /main/1 $
; Checkin $Date: January 24, 2008   14:47:01 $
; ========================================================================
;  This software is licensed for use with Texas Instruments C28x
;  family DSCs.  This license was provided to you prior to installing
;  the software.  You may review this license by consulting a copy of
;  the agreement in the doc directory of this library.
; ------------------------------------------------------------------------
;          Copyright (C) 2007-2008 Texas Instruments, Incorporated.
;                          All Rights Reserved.
; ========================================================================
;
; FILE:  isqrt_f32.asm
;
; TITLE: Fast 32-bit floating-point 1.0/sqrt(X) for the C28x + Floating-Point Unit.
;
; DESCRIPTION:
;
;    This function computes a 32-bit floating point (1.0)/sqrt(X)
;    Note: This function is not part of the normal RTS library.
;
; FUNCTIONS:
;
;    float32 isqrt(float32 X)
;
; ASSUMPTIONS:
; 
;
; ALGORITHM:
;
;              Ye = Estimate(1/sqrt(X));
;              Ye = Ye*(1.5 - Ye*Ye*X*0.5)
;              Y  = Ye*(1.5 - Ye*Ye*X*0.5)
;
; ###########################################################################
; $TI Release: C28x FPU fastRTS Library V1.00 $
; $Release Date: August 6, 2008 $
; ###########################################################################

        .page
        .global     _isqrt
        .text
_isqrt:
        EISQRTF32   R1H,R0H             ; R1H = Ye = Estimate(1/sqrt(X))        
        MPYF32      R2H,R0H,#0.5        ; R2H = X*0.5
        MPYF32      R3H,R1H,R1H         ; R3H = Ye*Ye
        NOP
        MPYF32      R3H,R3H,R2H         ; R3H = Ye*Ye*X*0.5
        NOP
        SUBF32      R3H,#1.5,R3H        ; R3H = 1.5 - Ye*Ye*X*0.5
        NOP
        MPYF32      R1H,R1H,R3H         ; R2H = Ye = Ye*(1.5 - Ye*Ye*X*0.5)
        NOP

        MPYF32      R3H,R1H,R2H         ; R3H = Ye*X*0.5
        NOP
        MPYF32      R3H,R1H,R3H         ; R3H = Ye*Ye*X*0.5
        NOP
        SUBF32      R3H,#1.5,R3H        ; R3H = 1.5 - Ye*Ye*X*0.5
        NOP
        MPYF32      R0H,R1H,R3H         ; R0H = Ye = Ye*(1.5 - Ye*Ye*X*0.5)
        LRETR
        .endasmfunc
;--------------------------------------------------------------------------
;            Copyright (c) 2007-2008 Texas Instruments, Incorporated.
;                           All Rights Reserved.
;===========================================================================
;===========================================================================
; End of File.
;===========================================================================
