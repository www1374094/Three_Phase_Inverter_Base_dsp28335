/*
 * TPVSI_DSP28335_INT.c
 *
 *  Created on: 2018年1月12日
 *      Author: Chuck Wang
 */
#include "TPVSI_DSP28335_INT.h"
#include "TPVSI_DSP28335_SPWM.h"




__interrupt void epwm1_isr(void)
{
	/*TODO:这里编写中断函数*/
	SPWM_Sin_Cal(&_p_sin1);
	SPWM_DutyValue_Cal(&_p_epwm1,0.9*(_p_sin1.sin_value),0.9,-0.9);
	EPwm1Regs.CMPA.half.CMPA = _p_epwm1.cmpa_value;
	EPwm2Regs.CMPA.half.CMPA = _p_epwm1.cmpa_value;
	EPwm3Regs.CMPA.half.CMPA = _p_epwm1.cmpa_value;
	//下面两行代码其实没用，先不管
	EPwm1Regs.CMPB = _p_epwm1.cmpa_value;
	_p_epwm1.cmpb_value = _p_epwm1.cmpa_value;
	/*下面是清除中断标志位，不要修改*/
	/* Begin*/
	EPwm1Regs.ETCLR.bit.INT = 1;
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
	/*End*/
}



