/*
 * TPVSI_DSP28335_HAL.h
 *
 *  Created on: 2018年3月10日
 *      Author: wangchu
 */

#ifndef HAL_TPVSI_DSP28335_HAL_H_
#define HAL_TPVSI_DSP28335_HAL_H_
#include "TPVSI_DSP28335_BSP.h"
#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include "TPVSI_DSP28335_BSP.h"
#include "Solar_F.h"

/*与电路板ADC通道对应的数据的含义*/
typedef enum{
	VoltageA = 0,
	VoltageB,
	VoltageC,
	CurrentA,
	CurrentB,
	CurrentC,
	SAMPLE_NUM,//这个枚举变量必须放在所有变量的最后，用以标识采样数据的个数
}Sample_Index;


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
 * StructureName:Sample_structure
 * Description:采样模块的抽象结构体。
 * Elements:
 * 	data->采样数据；
 * 	k->采样值到实际数据的转换系数，例如ADC采样得到的值为x(0<=x<=4095)，则实际数据为k*x
 * */
typedef struct{
	float data[SAMPLE_NUM];//数据
	float k[SAMPLE_NUM];//ADC转换的比例系数
}Sample_structure;


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


extern Sample_structure p_vol_sam;
extern Sin_structure _p_sin1;
extern EPWM_structure _p_epwm1;
extern EPWM_structure _p_epwm2;
extern EPWM_structure _p_epwm3;

void HAL_EPWM_Structure_Init(void);
void HAL_PWM_DutyValue_Cal(EPWM_structure *ep,float duty,float duty_max,float duty_min);
void HAL_Init(void);
void HAL_Sample_Init(Sample_structure *p);
void HAL_Sample(Sample_structure *p);
#endif /* HAL_TPVSI_DSP28335_HAL_H_ */
