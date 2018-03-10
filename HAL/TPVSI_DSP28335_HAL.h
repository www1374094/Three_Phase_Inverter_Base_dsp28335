/*
 * TPVSI_DSP28335_HAL.h
 *
 *  Created on: 2018年3月10日
 *      Author: wangchu
 */

#ifndef HAL_TPVSI_DSP28335_HAL_H_
#define HAL_TPVSI_DSP28335_HAL_H_
#include "TPVSI_DSP28335_BSP.h"


/*
 * StructureName:EPWM_structure
 * Description:EPWM模块的抽象结构体。
 * Elements:
 * 	cmp_max->比较寄存器允许的最大值
 * 	cmp_min->比较寄存器允许的最小值
 * 	fre->EPWM模块的工作频率
 * 	bias->给比较寄存器赋值时的偏移量
 * 	cmpa_value->比较寄存器a的值
 * 	cmpb_value->比较寄存器b的值
 * */
typedef struct{
	Uint16 cmp_max;
	Uint16 cmp_min;
	Uint16 fre;
	Uint16 bias;
	Uint16 cmpa_value;
	Uint16 cmpb_value;
} EPWM_structure;

/*
 * StructureName:Sin_structure
 * Description:Sine函数值结构体。
 * Elements:
 * 	Angle->当前角度
 * 	sin_value->当前角度的正弦值
 * */
typedef struct{
  float Angle;
  float sin_value;
} Sin_structure;

extern Sin_structure _p_sin1;
extern EPWM_structure _p_epwm1;
extern EPWM_structure _p_epwm2;
extern EPWM_structure _p_epwm3;
void HAL_EPWM_Structure_Init(void);
void HAL_PWM_DutyValue_Cal(EPWM_structure *ep,float duty,float duty_max,float duty_min);
void HAL_Init(void);
#endif /* HAL_TPVSI_DSP28335_HAL_H_ */
