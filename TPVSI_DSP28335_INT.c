/*
 * TPVSI_DSP28335_INT.c
 *
 *  Created on: 2018年1月12日
 *      Author: Chuck Wang
 */
#include "TPVSI_DSP28335_INT.h"
#include "TPVSI_DSP28335_HAL.h"
#include "TPVSI_DSP28335_AAL_PLL.h"
#include "TPVSI_DSP28335_AAL_Control.h"
#include<math.h>

//#include "TPVSI_DSP28335_Control.h"

#pragma CODE_SECTION(epwm1_isr,"ramfuncs");

__interrupt void epwm1_isr(void)
{
	/*TODO:中断变量定义*/
	static float Angle = 0;
	static float Angle_pll = 0;
	static Uint32 count = 0;
	/*TODO:这里编写中断函数*/
	GpioDataRegs.GPBSET.bit.GPIO60 = 1;
	HAL_Sample(&p_sam);
	AAL_Trans_Update(&p_sam);
	Angle += 0.01256635;
	if(Angle>6.2831853)
		Angle = 0;
	if(count<250000)
	{
		count++;
	}
	Angle_pll = AAL_PLL_GetPhase();
	AAL_Trans_ABCDQ0(&Inverter_Voltage_Data,Angle_pll);
	AAL_PLL_Cal(&Inverter_Voltage_Data);
//	AAL_Trans_SetDQ0Value(&Control_Data,0.9,0,0);
	if(count<250000)
	{
		AAL_Trans_SetDQ0Value(&Target_Data,0.1,0,0);
	}
	else
	{
		AAL_Trans_SetDQ0Value(&Target_Data,0.7,0,0);
	}
/*	AAL_Trans_DQ0ABC(&Control_Data,Angle);
	AAL_Trans_ABCDQ0(&Inverter_Voltage_Data,Angle);*/
//	AAL_Trans_SetDQ0Value(&Target_Data,0.7,0,0);
	AAL_Trans_DQ0ABC(&Target_Data,Angle_pll);

	//---------------------
/*	Target_Data.abc_data[index_a]+= 0.05;
	Target_Data.abc_data[index_b]+= 0.05;
	Target_Data.abc_data[index_c]-= 0.1;*/

	AAL_Control_CurrentLoop(&Inverter_Current_Data,&Inverter_CapCurrent_Data,
			&Control_Data,&Target_Data);
	HAL_DutySet(&Control_Data,&_p_epwm1,&_p_epwm2,&_p_epwm3);
#if DEBUG_DAC_OUTPUT
	HAL_PWM_DutyValue_Cal(&_p_epwm4,0.5*Inverter_Current_Data.abc_data[index_a],0.99,-0.99);
	HAL_PWM_DutyValue_Cal(&_p_epwm5,0.05*Inverter_Voltage_Data.abc_data[index_a],0.9,-0.9);
	if(count<250000)
	{
		HAL_PWM_DutyValue_Cal(&_p_epwm6,-0.89,0.9,-0.9);
	}
	else
	{
		HAL_PWM_DutyValue_Cal(&_p_epwm6,0.89,0.9,-0.9);
	}
	EPwm4Regs.CMPA.half.CMPA = _p_epwm4.cmpa_value;
	EPwm5Regs.CMPA.half.CMPA = _p_epwm5.cmpa_value;
	EPwm6Regs.CMPA.half.CMPA = _p_epwm6.cmpa_value;
#endif
	//AAL_Trans_ABCDQ0(&Inverter_Current_Data,Angle);
#if _GRAPH_DISPLAY_
	HAL_PUSH_BUFFER(Inverter_Voltage_Data.abc_data[0]);
#endif
	GpioDataRegs.GPBCLEAR.bit.GPIO60 = 1;
	/*下面是清除中断标志位，不要修改*/
	/* Begin*/
	EPwm1Regs.ETCLR.bit.INT = 1;
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
	/*End*/
}



