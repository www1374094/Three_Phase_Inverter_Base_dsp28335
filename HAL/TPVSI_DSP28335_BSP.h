/*
 * TPVSI_DSP28335_BSP.h
 *
 *  Created on: 2018年1月10日
 *      Author: Chuck Wang
 */

#ifndef TPVSI_DSP28335_BSP_H_
#define TPVSI_DSP28335_BSP_H_

#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include "DSP2833x_DMA.h"
#include "DSP2833x_EPwm.h"

void BSP_ADC_Init(void);
void BSP_ePWM_Init(void);
void BSP_GPIO_Init(void);
void BSP_SCI_Init(void);
void BSP_eCAN_Init(void);
void BSP_DMA_Init(void);
void BSP_Driver_Rst(void);

#define INTERNAL_REFERENCE 1
#define EXTERNAL_REFERENCE 0
//定义下面的宏为1可以打开DAC输出功能，用以在调试的时候观察波形
#define DEBUG_DAC_OUTPUT 1

extern Uint16 DMA_Buf[14];
#endif /* TPVSI_DSP28335_BSP_H_ */
