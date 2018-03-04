; TI File $Revision: /main/3 $
; Checkin $Date: January 25, 2008   16:13:52 $
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
; FILE:  div_f32.asm
;
; TITLE: Fast 32-bit floating-point division for the C28x + Floating-Point Unit.
;
; DESCRIPTION:
;
;    This function computes a 32-bit floating point division A/B.
;
; FUNCTIONS:
;
;    This funciton (FS$$DIV) will be called when 32-bit floating point division 
;    is performed.  That is:
;    
;    float32 A,B,Y;
;    ...
;    <A & B initalized>
;    ...
;    Y = A/B;  // Call to FS$$DIV
;
; ASSUMPTIONS:
; 
;
; ALGORITHM:
;
;              Ye = Estimate(1/B);
;              Ye = Ye*(2.0 - Ye*B)
;              Ye = Ye*(2.0 - Ye*B)
;              Y  = A*Ye
;
; ###########################################################################
; $TI Release: C28x FPU fastRTS Library V1.00 $
; $Release Date: August 6, 2008 $
; ###########################################################################
        .page
        .global     FS$$DIV
        .text

FS$$DIV:

        EINVF32     R2H, R1H            ; R2H = Ye = Estimate(1/B)
        CMPF32      R0H, #0.0           ; Check if A == 0
        MPYF32      R3H, R2H, R1H       ; R3H = Ye*B
        NOP
        SUBF32      R3H, #2.0, R3H      ; R3H = 2.0 - Ye*B       
        NOP        
        MPYF32      R2H, R2H, R3H       ; R2H = Ye = Ye*(2.0 - Ye*B)
        NOP
; Next line: if commented out: 0.0/0.0 = 0.0
;            if not commented: 0.0/0.0 = infinity
;       MOV32       R2H, R0H, EQ        ; If A == 0.0, Ye = 0.0
        MPYF32      R3H, R2H, R1H       ; R3H = Ye*B
        CMPF32      R1H, #0.0           ; Check if B == 0.0
        SUBF32      R3H, #2.0, R3H      ; R3H = 2.0 - Ye*B
        NEGF32      R0H, R0H, EQ        ; Fixes sign for A/0.0
        MPYF32      R2H, R2H, R3H       ; R2H = Ye = Ye*(2.0 - Ye*B)
        NOP
        MPYF32      R0H, R0H, R2H       ; R0H = Y = A*Ye = A/B
        LRETR
       	.endasmfunc
;--------------------------------------------------------------------------
;            Copyright (c) 2007-2008 Texas Instruments, Incorporated.
;                           All Rights Reserved.
;===========================================================================
;===========================================================================
; End of File.
;===========================================================================
