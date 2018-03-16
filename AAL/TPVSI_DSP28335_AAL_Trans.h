/*
 * TPVSI_DSP28335_AAL_Trans.h
 *
 *  Created on: 2018Äê3ÔÂ12ÈÕ
 *      Author: Chuck
 */

#ifndef AAL_TPVSI_DSP28335_AAL_TRANS_H_
#define AAL_TPVSI_DSP28335_AAL_TRANS_H_
#include "TPVSI_DSP28335_HAL.h"
#include "TPVSI_DSP28335_Structure_Define.h"




extern ThreePhase_Data_Structure Inverter_Voltage_Data;
extern ThreePhase_Data_Structure Inverter_Current_Data;
extern ThreePhase_Data_Structure Control_Data;
extern ThreePhase_Data_Structure Inverter_CapVoltage_Data;
extern ThreePhase_Data_Structure Inverter_CapCurrent_Data;
extern ThreePhase_Data_Structure Target_Data;

#pragma CODE_SECTION(AAL_Trans_Park,"ramfuncs");
#pragma CODE_SECTION(AAL_Trans_Clark,"ramfuncs");
#pragma CODE_SECTION(AAL_Trans_iPark,"ramfuncs");
#pragma CODE_SECTION(AAL_Trans_iClark,"ramfuncs");
#pragma CODE_SECTION(AAL_Trans_SetDQ0Value,"ramfuncs");
#pragma CODE_SECTION(AAL_Trans_ABCDQ0,"ramfuncs");
#pragma CODE_SECTION(AAL_Trans_DQ0ABC,"ramfuncs");
#pragma CODE_SECTION(AAL_Trans_Update,"ramfuncs");

void AAL_Trans_Update(Sample_Structure *p);
void AAL_Trans_Init(void);
void AAL_Trans_StruInit(ThreePhase_Data_Structure *p);
void AAL_Trans_Park(ThreePhase_Data_Structure *p,float angle);
void AAL_Trans_iPark(ThreePhase_Data_Structure *p,float angle);
void AAL_Trans_Clark(ThreePhase_Data_Structure *p);
void AAL_Trans_iClark(ThreePhase_Data_Structure *p);
void AAL_Trans_ABCDQ0(ThreePhase_Data_Structure *p,float angle);
void AAL_Trans_DQ0ABC(ThreePhase_Data_Structure *p,float angle);
void AAL_Trans_SetDQ0Value(ThreePhase_Data_Structure *p,float d,float q,float zero);

#endif /* AAL_TPVSI_DSP28335_AAL_TRANS_H_ */
