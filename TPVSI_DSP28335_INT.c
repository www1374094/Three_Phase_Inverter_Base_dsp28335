/*
 * TPVSI_DSP28335_INT.c
 *
 *  Created on: 2018年1月12日
 *      Author: Chuck Wang
 */
#include "TPVSI_DSP28335_INT.h"
#include "TPVSI_DSP28335_HAL.h"

//#include "TPVSI_DSP28335_Control.h"

#pragma CODE_SECTION(epwm1_isr,"ramfuncs");

__interrupt void epwm1_isr(void)
{
	/*TODO:中断变量定义*/
	static float Angle = 0;
	/*TODO:这里编写中断函数*/
	GpioDataRegs.GPBSET.bit.GPIO60 = 1;
	HAL_Sample(&p_sam);
	AAL_Trans_Update(&p_sam);
	Angle += 0.0251327;
	if(Angle>6.2831853)
		Angle = 0;
	AAL_Trans_SetDQ0Value(&Control_Data,0.9,0,0);
	AAL_Trans_DQ0ABC(&Control_Data,Angle);
	HAL_DutySet(&Control_Data,&_p_epwm1,&_p_epwm2,&_p_epwm3);
#if DEBUG_DAC_OUTPUT
	HAL_PWM_DutyValue_Cal(&_p_epwm4,0.02*(Inverter_CapVoltage_Data.abc_data[index_a]),0.9,-0.9);
	HAL_PWM_DutyValue_Cal(&_p_epwm5,10*Inverter_CapCurrent_Data.abc_data[index_a],0.9,-0.9);
	EPwm4Regs.CMPA.half.CMPA = _p_epwm4.cmpa_value;
	EPwm5Regs.CMPA.half.CMPA = _p_epwm5.cmpa_value;
#endif
	AAL_Trans_ABCDQ0(&Inverter_Voltage_Data,Angle);
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



