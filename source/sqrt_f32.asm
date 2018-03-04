; TI File $Revision: /main/1 $
; Checkin $Date: January 24, 2008   14:47:08 $
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
; FILE:  sqrt_f32.asm
;
; TITLE: Fast 32-bit floating-point sqrt for the C28x + Floating-Point Unit.
;
; DESCRIPTION:
;
;    This function computes a 32-bit floating point sqrt..
;
; FUNCTIONS:
;
;    float32 sqrt(float32 X)
;
; ASSUMPTIONS:
; 
;
; ALGORITHM:
;
;              Ye = Estimate(1/sqrt(X));
;              Ye = Ye*(1.5 - Ye*Ye*X*0.5)
;              Ye = Ye*(1.5 - Ye*Ye*X*0.5)
;              Y  = sqrt(X) = X*Ye
;
; ###########################################################################
; $TI Release: C28x FPU fastRTS Library V1.00 $
; $Release Date: August 6, 2008 $
; ###########################################################################


        .page
        .global     _sqrt
        .text

_sqrt:
                                        ; R0H = X on entry
        EISQRTF32   R1H, R0H            ; R1H = Ye = Estimate(1/sqrt(X))
        MPYF32      R2H, R0H, #0.5      ; R2H = X*0.5
        MPYF32      R3H, R1H, R1H       ; R3H = Ye*Ye
        NOP
        MPYF32      R3H, R3H, R2H       ; R3H = Ye*Ye*X*0.5
        NOP
        SUBF32      R3H, #1.5, R3H      ; R3H = 1.5 - Ye*Ye*X*0.5
        NOP
        MPYF32      R1H, R1H, R3H       ; R2H = Ye = Ye*(1.5 - Ye*Ye*X*0.5)
        NOP
        MPYF32      R3H, R1H, R2H       ; R3H = Ye*X*0.5
        NOP
        MPYF32      R3H, R1H, R3H       ; R3H = Ye*Ye*X*0.5
        NOP
        SUBF32      R3H, #1.5, R3H      ; R3H = 1.5 - Ye*Ye*X*0.5
        CMPF32      R0H, #0.0           ; Check if X == 0
        MPYF32      R1H, R1H, R3H       ; R2H = Ye = Ye*(1.5 - Ye*Ye*X*0.5)
        NOP
        MOV32       R1H, R0H, EQ        ; If X is zero, change the Ye estimate to 0
        MPYF32      R0H, R0H, R1H       ; R0H = Y = X*Ye = sqrt(X)
        LRETR
        .endasmfunc
;--------------------------------------------------------------------------
;            Copyright (c) 2007-2008 Texas Instruments, Incorporated.
;                           All Rights Reserved.
;===========================================================================
;===========================================================================
; End of File.
;===========================================================================
