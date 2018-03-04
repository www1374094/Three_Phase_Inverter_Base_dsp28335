; TI File $Revision: /main/2 $
; Checkin $Date: July 10, 2008   16:53:20 $
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
; FILE:  cos_f32.asm
;
; TITLE: Fast cos function for the C28x + Floating-Point Unit.
;
; DESCRIPTION:
;
;    This function computes a 32-bit floating point cos given a
;    radian input.  This function uses the FPU math tables to
;    compute the cos.
;
; FUNCTIONS:
;
;    float32 cos (float32 radian)
;
; ASSUMPTIONS:
;
;     * FPUsinTable and FPUcosTable are linked into the project.
;
; ALGORITHM:
;
;       The cos value is calculated as follows:
;
;       1) The offset into a 512 word sin/cos table is calculated:
;          k = 0x1FF & (int(Radian*512/(2*pi)))
;
;
;       2) The fractional component between table samples is
;          calculated:
;          x = fract(Radian*512/2*pi) * (2*pi)/512
;
;       3) The output sine value is calculated as follows:
;
;          cos(Radian) = C(k) + x*(-S(k) + x*(-0.5*C(k) + 0.166667*x*S(k)))
;
;          sin(Radian) = S(k) + x*(C(k) + x*(-0.5*S(k) - 0.166667*x*C(k)))
;
;          where  S(k) = Sin table value at offset "k"
;                 C(k) = Cos table value at offset "k"
; ###########################################################################
; $TI Release: C28x FPU fastRTS Library V1.00 $
; $Release Date: August 6, 2008 $
; ###########################################################################

       .page
       .global _cos
       .ref    _FPUsinTable
       .ref    _FPUcosTable
       .text
_cos:                                ; R0H = Radian (on entry)
        MOVIZ     R1H,#0x42A2        ; R1H = 512/(2*pi) = 512/6.28318531 = 81.4873309
        MOVXI     R1H,#0xF983
        MPYF32    R0H, R0H, R1H      ; R0H = Radian * 512/(2*pi)
        MOVIZ     R2H,#0x3C49        ; R2H = (2*pi)/512 = 6.28318531/512
        MOVXI     R2H,#0x0FDB        ;     = 0x3C490FDB or 0.012271846644531
        F32TOI32  R1H, R0H           ; R1H = int(Radian * 512/(2*pi))
        MOVL      XAR6,#_FPUsinTable
        MOVL      XAR7,#_FPUcosTable
        MOV32     ACC, R1H           ; ACC = int(Radian *512/(2*pi))
        AND       @AL,#0x1FF
        LSL       AL,#1
        MOVZ      AR0,@AL            ; AR0 = Index into "sin/cos" table = k
        FRACF32   R0H, R0H           ; R0H = fract(Radian*512/(2*pi))
        MOVIZ     R3H,#0x3E2A        ; R3H = 0.166667 (0x3E2AAAAB)
        MOVXI     R3H,#0xAAAB
        MPYF32    R2H, R0H, R2H      ; R2H = x = fract(Radian*512/(2*pi)) * (2*pi)/512
     || MOV32     R1H,*+XAR6[AR0]    ; R1H = S(k)
        MPYF32    R3H, R3H, R1H      ; R3H = .166*C(k)
     || MOV32     R0H,*+XAR7[AR0]    ; R0H = C(k)
        MPYF32    R0H, -0.5, R0H     ; R0H = -.5*C(k)
        MPYF32    R3H, R2H, R3H      ; R1H = x*0.166667*S(k)
        NOP
        ADDF32    R0H, R0H, R3H      ; R0H = -.5*C(k) + 0.166667*x*S(k)
        NOP
        MPYF32    R3H, R2H, R0H      ; R3H = x*(-.5*C(k) + 0.166667*x*S(k))
     || MOV32     R1H, *+XAR6[AR0]   ; R1H = S(k)
        NOP
        SUBF32    R3H, R3H, R1H      ; R3H = -S(k) + x*(-.5*C(k) + 0.166667*x*S(k))
        NOP
        MPYF32    R3H, R2H, R3H      ; R3H = x*(-S(k) + x*(-.5*C(k) + 0.166667*x*S(k)))
     || MOV32     R0H, *+XAR7[AR0]   ; R0H = C(k)
        NOP
        ADDF32    R0H, R0H, R3H      ; R0H = cos(Radian) = C(k) + x*(-S(k) + x*(-.5*C(k) + 0.166667*x*S(k)))
        LRETR
           .endasmfunc
;--------------------------------------------------------------------------
;            Copyright (c) 2007-2008 Texas Instruments, Incorporated.
;                           All Rights Reserved.
;===========================================================================
;===========================================================================
; End of File.
;===========================================================================
