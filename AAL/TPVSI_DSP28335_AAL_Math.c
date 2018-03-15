/*
 * TPVSI_DSP28335_AAL_Math.c
 *
 *  Created on: 2018年3月15日
 *      Author: Chuck
 */
#include "TPVSI_DSP28335_AAL_Math.h"


/*
 * FunName:AAL_FirstOrder_Diff
 * Description:一阶差分函数
 * Input:当前数据值
 * Output:后向一阶差分值
 * Others:None
 * */
float AAL_FirstOrder_Diff(float data)
{
	static float diff_last_data;
	float temp;
	temp = data - diff_last_data;
	diff_last_data = data;
	return temp;
}


