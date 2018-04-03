/*
 * TPVSI_DSP28335_HAL.h
 *
 *  Created on: 2018Äê3ÔÂ10ÈÕ
 *      Author: wangchu
 */

#ifndef HAL_TPVSI_DSP28335_HAL_H_
#define HAL_TPVSI_DSP28335_HAL_H_
#include "TPVSI_DSP28335_BSP.h"
#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include "TPVSI_DSP28335_BSP.h"
#include "Solar_F.h"
#include "TPVSI_DSP28335_AAL_Trans.h"
#include "TPVSI_DSP28335_Structure_Define.h"
#include "TPVSI_DSP28335_AAL_Math.h"



#define _GRAPH_DISPLAY_ 0



extern Sample_Structure p_sam;
extern Sin_Structure _p_sin1;
extern EPWM_Structure _p_epwm1;
extern EPWM_Structure _p_epwm2;
extern EPWM_Structure _p_epwm3;

#if DEBUG_DAC_OUTPUT
extern EPWM_Structure _p_epwm4;
extern EPWM_Structure _p_epwm5;
extern EPWM_Structure _p_epwm6;
#endif

void HAL_EPWM_Structure_Init(void);
void HAL_PWM_DutyValue_Cal(EPWM_Structure *ep,float duty,float duty_max,float duty_min);
void HAL_Init(void);
void HAL_Sample_Init(Sample_Structure *p);
void HAL_Sample(Sample_Structure *p);
void HAL_DutySet(ThreePhase_Data_Structure *p,EPWM_Structure *epa,EPWM_Structure *epb,EPWM_Structure *epc);
float HAL_GetSampleResult(Uint8 index);
void HAL_EPWM_DISABLE(void);
void HAL_Relay_On(void);
void HAL_PUSH_BUFFER(float x);
#endif /* HAL_TPVSI_DSP28335_HAL_H_ */
