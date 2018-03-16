/*
 * TPVSI_DSP28335_AAL_PLL.h
 *
 *  Created on: 2018Äê3ÔÂ16ÈÕ
 *      Author: Chuck
 */

#ifndef AAL_TPVSI_DSP28335_AAL_PLL_H_
#define AAL_TPVSI_DSP28335_AAL_PLL_H_
#include "TPVSI_DSP28335_HAL.h"
#include "TPVSI_DSP28335_AAL_Trans.h"
#include "TPVSI_DSP28335_Structure_Define.h"

#pragma CODE_SECTION(AAL_PLL_Cal,"ramfuncs");
void AAL_PLL_Init(void);
void AAL_PLL_Cal(ThreePhase_Data_Structure *p);
float AAL_PLL_GetPhase(void);




#endif /* AAL_TPVSI_DSP28335_AAL_PLL_H_ */
