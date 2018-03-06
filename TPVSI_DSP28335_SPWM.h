/*
 * TPVSI_DSP28335_SPWM.h
 *
 *  Created on: 2018Äê1ÔÂ13ÈÕ
 *      Author: Chuck Wang
 */

#ifndef TPVSI_DSP28335_SPWM_H_
#define TPVSI_DSP28335_SPWM_H_

#include <math.h>
#include "C28x_FPU_FastRTS.h"

#define _CONST_2PI 6.2831853
#define _CONST_SPWM_TABLE_SIZE 500

typedef struct{
  float Angle;
  float sin_value;
} Sin_structure;

typedef struct{
	Uint16 cmp_max;
	Uint16 cmp_min;
	Uint16 fre;
	Uint16 bias;
	Uint16 cmpa_value;
	Uint16 cmpb_value;
} EPWM_structure;

extern Sin_structure _p_sin1;
extern Sin_structure _p_sin2;
extern Sin_structure _p_sin3;
extern EPWM_structure _p_epwm1;
extern EPWM_structure _p_epwm2;
extern EPWM_structure _p_epwm3;
void SPWM_Sin_Cal(Sin_structure *p);
void SPWM_DutyValue_Cal(EPWM_structure *ep,float duty,float duty_max,float duty_min);
void EPWM_Structure_Init(void);

#endif /* TPVSI_DSP28335_SPWM_H_ */
