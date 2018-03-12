/*
 * TPVSI_DSP28335_INT.c
 *
 *  Created on: 2018年1月12日
 *      Author: Chuck Wang
 */
#include "TPVSI_DSP28335_INT.h"
#include "TPVSI_DSP28335_HAL.h"
#include "TPVSI_DSP28335_Control.h"

#pragma CODE_SECTION(epwm1_isr,"ramfuncs");

__interrupt void epwm1_isr(void)
{
	/*TODO:这里编写中断函数*/
	GpioDataRegs.GPBSET.bit.GPIO60 = 1;
	_p_sin1.Angle += 0.0251327;
	if(_p_sin1.Angle>6.2831853)
		_p_sin1.Angle = 0;
	CON_DQ0_ABC_CAL(0.9,0,0,_p_sin1.Angle,&p_dq0_abc);
	CON_VOL_CL_ABC_REG(&p_dq0_abc,&_p_epwm1,&_p_epwm2,&_p_epwm3);
	EPwm1Regs.CMPA.half.CMPA = _p_epwm1.cmpa_value;
	EPwm2Regs.CMPA.half.CMPA = _p_epwm2.cmpa_value;
	EPwm3Regs.CMPA.half.CMPA = _p_epwm3.cmpa_value;
	HAL_Sample(&p_vol_sam);
	CON_ABC_DQ0_CAL(p_vol_sam.data[CurrentA],p_vol_sam.data[CurrentB],p_vol_sam.data[CurrentC],_p_sin1.Angle,&p_vol_dq0);
#if _GRAPH_DISPLAY_
	CON_PUSH_BUFFER(p_vol_sam.data[1]);
#endif
	GpioDataRegs.GPBCLEAR.bit.GPIO60 = 1;
	/*下面是清除中断标志位，不要修改*/
	/* Begin*/
	EPwm1Regs.ETCLR.bit.INT = 1;
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
	/*End*/
}



