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
#include "Solar_F.h"

typedef struct{
	float data;//数据
	float k;//ADC转换的比例系数
}Sample_Stru;


#endif /* TPVSI_DSP28335_CONTROL_H_ */
