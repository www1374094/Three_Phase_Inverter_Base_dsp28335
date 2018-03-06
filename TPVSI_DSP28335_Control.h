/*
 * TPVSI_DSP28335_Control.h
 *
 *  Created on: 2018年3月4日
 *      Author: chen318
 */

#ifndef TPVSI_DSP28335_CONTROL_H_
#define TPVSI_DSP28335_CONTROL_H_

#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include "TPVSI_DSP28335_BSP.h"
#include "TPVSI_DSP28335_SPWM.h"
#include "Solar_F.h"

/*调试功能宏定义*/
#define _GRAPH_DISPLAY_ 0//设置为1以使用GRAPH观察数据

#define SAMPLE_NUM 3
typedef struct{
	float data[SAMPLE_NUM];//数据
	float k[SAMPLE_NUM];//ADC转换的比例系数
}Sample_Stru;

typedef struct{
	float kp;
	float ki;
	float Ts;
	float output;
	float err;
	float err_last;
	float output_last;
}PID_Stru;


extern ABC_DQ0_POS_F p_vol_dq0;
extern Sample_Stru p_vol_sam;
extern DQ0_ABC_F p_dq0_abc;

void CON_Sample_Init(Sample_Stru *p);
void CON_Sample(Sample_Stru *p);
void CON_ABC_DQ0_CAL(float32 a,float32 b,float32 c,float32 theta,ABC_DQ0_POS_F *abc_dq0_pos1);
void CON_PID_DeInit(PID_Stru *p);
void CON_PID_Init(PID_Stru *p,float Ts,float kp,float ki);
void CON_VOL_CL_PID(PID_Stru *dpid,PID_Stru *qpid,ABC_DQ0_POS_F *abc_dq0_pos1);
void CON_DQ0_ABC_CAL(float d,float q,float z,float theta,DQ0_ABC_F *p);
void CON_VOL_CL_ABC_REG(DQ0_ABC_F *p,EPWM_structure *epa,EPWM_structure *epb,EPWM_structure *epc);
#if _GRAPH_DISPLAY_
void CON_PUSH_BUFFER(float x);
#endif

#endif /* TPVSI_DSP28335_CONTROL_H_ */
