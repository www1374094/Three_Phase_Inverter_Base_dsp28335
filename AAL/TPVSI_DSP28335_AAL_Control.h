/*
 * TPVSI_DSP28335_AAL_Control.h
 *
 *  Created on: 2018年3月12日
 *      Author: Chuck
 */

#ifndef AAL_TPVSI_DSP28335_AAL_CONTROL_H_
#define AAL_TPVSI_DSP28335_AAL_CONTROL_H_
#include "TPVSI_DSP28335_HAL.h"
#include "TPVSI_DSP28335_Structure_Define.h"


//PID控制器函数声明
void AAL_Control_PID_DeInit(PID_Structure *p);
void AAL_Control_PID_Init(PID_Structure *p,float Ts,float kp,float ki);
void AAL_Control_PID(PID_Structure *p,float err);

//准谐振控制器函数声明

#endif /* AAL_TPVSI_DSP28335_AAL_CONTROL_H_ */
