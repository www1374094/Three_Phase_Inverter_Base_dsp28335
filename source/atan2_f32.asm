; TI File $Revision: /main/1 $
; Checkin $Date: January 24, 2008   14:46:38 $
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
; FILE:  atan2_f32.asm
;
; TITLE: Fast atan2 function for the C28x + Floating-Point Unit.
;
; DESCRIPTION:
;
;    This function computes a 32-bit floating point atan2 given a
;    Y, X input.  This function uses the FPU math tables to
;    compute the atan2 resulting angle.
;
; FUNCTIONS:
;
;    float32 atan2 (float32 Y, float32 X)
;
; ASSUMPTIONS:
;
;     * FPUatan2Table and FPUatan2Table are linked into the project.
;
; ALGORITHM:
;             The algorithm steps to calculate the "atan2" of the given
;             input X and Y is as follows:
;
;             Step(1):   if( abs(X) >= abs(Y) )
;                            Numerator   = abs(Y)
;                            Denominator = abs(X)
;                        else
;                            Numerator   = abs(X)
;                            Denominator = abs(Y)
;
;             Step(2):   Ratio = Numerator/Denominator
;
;                        Note: Ratio range = 0.0 to 1.0
;
;             Step(3):   Use the upper 6-bits of the "Ratio" value as an
;                        index into the table to obtain the coefficients
;                        for a second order equation:
;
;                        _FPUatan2Table:
;                             CoeffA0[0]
;                             CoeffA1[0]
;                             CoeffA2[0]
;                                .
;                                .
;                             CoeffA0[63]
;                             CoeffA1[63]
;                             CoeffA2[63]
;
;             Step(4):   Calculate the angle using the folowing equation:
;
;                        arctan(Ratio) = A0 + A1*Ratio + A2*Ratio*Ratio
;                        arctan(Ratio) = A0 + Ratio(A1 + A2*Ratio)
;
;             Step(5):   The final angle is determined as follows:
;
;                        if( X >= 0 and Y >= 0 and abs(X) >= abs(Y) )
;                            Angle = arctan(abs(Y)/abs(X))
;                        if( X >= 0 and Y >= 0 and abs(X) <  abs(Y) )
;                            Angle = PI/2 - arctan(abs(X)/abs(Y))
;                        if( X < 0  and Y >= 0 and abs(X) <  abs(Y) )
;                            Angle = PI/2 + arctan(abs(X)/abs(Y))
;                        if( X < 0  and Y >= 0 and abs(X) >= abs(Y) )
;                            Angle = PI - arctan(abs(Y)/abs(X))
;                        if( Y < 0 )
;                            Angle = -Angle
;===========================================================================
; ###########################################################################
; $TI Release: C28x FPU fastRTS Library V1.00 $
; $Release Date: August 6, 2008 $
; ###########################################################################

       .page
       .global _atan2
       .ref _FPUatan2HalfPITable
       .ref _FPUatan2Table
       .text
_atan2:

       MOV32    *SP++,R4H            ; Save on entry register
                                     ; R0H = Y on entry
                                     ; R1H = X on entry
; Perform Step (1):
       ABSF32    R3H, R0H            ; (1) R3H = abs(Y)
       ABSF32    R4H, R1H            ; (1) R4H = abs(X)
       MINF32    R3H, R4H            ; (1) R3H = Numerator = min(abs(Y),abs(X))
    || MOV32     R4H, R3H            ; (1) R4H = Denominator = max(abs(Y),abs(X))
; Perform Step (2) and (3):
       EINVF32   R2H, R4H            ; (2) R2H = Ye = Estimate(1/Numerator)
       TESTTF    LEQ                 ; (5) Set TF if abs(X) >= abs(Y)
       MPYF32    R0H, R2H, R4H       ; (2) R0H = Ye*B
    || MOV32     *SP++, R0H          ; Store Y (*-SP[2] = Y)
       MPYF32    R1H, R2H, R3H       ; (3) R1H = 16-bit accurate estimate
    || MOV32    *SP++,R1H            ; Store X (*-SP[4] = Y, *-SP[2] = X)
       SUBF32    R0H, #2.0, R0H      ; (2) R0H = 2.0 - Ye*B
       MPYF32    R1H, R1H, 64.0      ; (3) 64 = Elements In Table
       MPYF32    R2H, R2H, R0H       ; (2) R2H = Ye = Ye*(2.0 - Ye*B)  (first estimate)
       F32TOUI16 R1H, R1H            ; (3) R1H = int(64*ratio) (16-bit accurate)
       MPYF32    R0H, R2H, R4H       ; (2) R0H = Ye*B
       MOVL      XAR7, #_FPUatan2Table+4   ; (3) Point to A2
       SUBF32    R0H, #2.0, R0H      ; (2) R0H = 2.0 - Ye*B
       MOVL      XAR6, #_FPUatan2Table+2   ; Point to A1
       MOV32     ACC, R1H            ; (3) ACC = int(64*Ratio)
       MPY       P, @AL, #6          ; (3) P = 6 * int(64*Ratio)
       MOVZ      AR0, @PL            ; (3) AR0 = _FPUatan2Table index
       MPYF32    R2H, R2H, R0H       ; (2) R2H = Ye = Ye*(2.0 - Ye*B)
       MOVL      XAR5, #_FPUatan2Table     ; Point to A0
       MPYF32    R0H, R3H, R2H       ; (2) R0H = Ratio = A*Ye = A/B
; Perform Step (4):
; arctan(Ratio) = A0 + Ratio(A1 + A2*Ratio)
       MOV32     R1H, *+XAR7[AR0]    ; (4) R1H = A2
       MPYF32    R3H, R1H, R0H       ; (4) R3H = A2*Ratio
    || MOV32     R1H, *+XAR6[AR0]    ; (4) R1H = A1
       MOVL      XAR7, #_FPUatan2HalfPITable ; (5) *XAR7[2] == pi/2
       ADDF32    R3H, R1H, R3H       ; (4) R3H = A1 + A2*Ratio
    || MOV32     R4H, *+XAR5[AR0]    ; (4) R4H = A0
       MOV32     R1H, *+XAR7[2], UNC ; (5) R1H = pi/2 (no flag change)
       MPYF32    R3H, R0H, R3H       ; (4) R3H = Ratio*(A1 + A2*Ratio)
       NOP
       ADDF32    R0H, R4H, R3H       ; (4) R0H = arctan(Ratio) = A0 + Ratio(A1 + A2*Ratio)
    || MOV32     R2H, *--SP          ; (5) R2H = X (set/clear NF,ZF for use below)
; Perform Step (5):
       NEGF32    R3H, R1H, UNC       ; (5) R3H = -pi/2 (no flag change)
       MOV32     R0H, R2H, EQ        ; (5) if (X == 0), R0H = 0
       NEGF32    R0H, R0H, GEQ       ; (5) if (X >= 0) R0H flip sign of atan(Ratio)
       NEGF32    R0H, R0H, TF        ; (5) if (abs(X) >= abs(Y)) flip sign of atan(Ratio)
       NEGF32    R3H, R3H, LT        ; (5) if (X < 0) R3H = pi/2
       ADDF32    R3H, R3H, R1H       ; (5) R3H = R3H + pi/2
                                     ;     if (X < 0) R3H = pi
                                     ;     if (X > 0) R3H = 0
   ||  MOV32     R2H, *--SP          ; (5) R2H = Y (set/clear NF,ZF)
       MOV32     R4H, *--SP, UNC     ; Restore save on entry register (no flag change)
       MOV32     R3H, R1H, NTF       ; (5) if(abs(X) < abs(Y) R3H = pi/2
       ADDF32    R0H, R0H, R3H       ; R0H = Angle
       NOP
       NEGF32    R0H, R0H, LT        ; if (Y < 0) Angle = -Angle
       LRETR
       .endasmfunc

;--------------------------------------------------------------------------
;            Copyright (c) 2007-2008 Texas Instruments, Incorporated.
;                           All Rights Reserved.
;===========================================================================
;===========================================================================
; End of File.
;===========================================================================
