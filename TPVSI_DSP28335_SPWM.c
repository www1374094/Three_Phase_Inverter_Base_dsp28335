/*
 * TPVSI_DSP28335_SPWM.c
 *
 *  Created on: 2018年1月13日
 *      Author: Chuck Wang
 */
#include "TPVSI_DSP28335_SPWM.h"


//全局变量定义
Sin_structure _p_sin1;
EPWM_structure _p_epwm1;
static float angle_step = _CONST_2PI/_CONST_SPWM_TABLE_SIZE;

void SPWM_Sin_Cal(Sin_structure *p)
{
	_p_sin1.Angle += (angle_step);
	if(_p_sin1.Angle>_CONST_2PI)
		_p_sin1.Angle = 0;
	_p_sin1.sin_value = sin(_p_sin1.Angle);
}

void SPWM_DutyValue_Cal(EPWM_structure *ep,float duty,float duty_max,float duty_min)
{
	Uint16 temp;
	if(duty>duty_max) duty = duty_max;
	else if(duty<duty_min) duty = duty_min;
	temp = (Uint16)(duty*((ep->cmp_max) - (ep->cmp_min))/2.0 + (ep->bias));
	if(temp>(ep->cmp_max)) temp = ep->cmp_max;
	else if (temp<(ep->cmp_min)) temp = ep->cmp_min;
	ep->cmpa_value = temp;
}


void EPWM_Structure_Init(void)
{
	_p_epwm1.fre = 50000;
	_p_epwm1.bias = 1500;
	_p_epwm1.cmp_max = 3000;
	_p_epwm1.cmp_min = 0;
	_p_epwm1.cmpa_value = 1500;
	_p_epwm1.cmpb_value = 1500;
}


