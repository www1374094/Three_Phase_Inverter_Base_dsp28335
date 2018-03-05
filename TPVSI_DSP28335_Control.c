/*
 * TPVSI_DSP28335_Control.c
 *
 *  Created on: 2018Äê3ÔÂ4ÈÕ
 *      Author: chen318
 */
#include "TPVSI_DSP28335_Control.h"


void CON_Sample(Sample_Stru *sam,Uint16 ADCRes)
{
	sam->data = sam->k*ADCRes;
}

void ABC_DQ0_POS_Init(ABC_DQ0_POS_F *abc_dq0_pos1)
{
	ABC_DQ0_POS_F_init(abc_dq0_pos1);
}

void ABC_DQ0_CAL(float32 a,float32 b,float32 c,float32 theta,ABC_DQ0_POS_F *abc_dq0_pos1)
{
	abc_dq0_pos1->a = a;
	abc_dq0_pos1->b = b;
	abc_dq0_pos1->c = c;
	abc_dq0_pos1->sin = sin(theta);
	abc_dq0_pos1->cos = cos(theta);
	ABC_DQ0_POS_F_FUNC(abc_dq0_pos1);
	//A
}




