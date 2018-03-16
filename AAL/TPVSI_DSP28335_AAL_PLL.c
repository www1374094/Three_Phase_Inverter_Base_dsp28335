/*
 * TPVSI_DSP28335_AAL_PLL.c
 *
 *  Created on: 2018年3月16日
 *      Author: Chuck
 */
#include "TPVSI_DSP28335_AAL_PLL.h"


#define GRID_FREQ 50//电网频率
#define ISR_FREQUENCY 25000//中断频率
#define NORMALIZE_COE 0.025//将采样值归一化的系数

//PLL结构体定义
SPLL_3ph_SRF_F spll1;

/*
 * FunName:AAL_PLL_Init
 * Description:PLL结构体初始化函数,采用宏定义方式控制输入变量
 * Input:None
 * Output:None
 * Others:None
 * */
void AAL_PLL_Init(void)
{
	SPLL_3ph_SRF_F_init(GRID_FREQ,((float)(1.0/ISR_FREQUENCY)),&spll1);
}


/*
 * FunName:AAL_PLL_Cal
 * Description:PLL计算
 * Input:三相数据结构体指针 p
 * Output:None
 * Others:None
 * */
void AAL_PLL_Cal(ThreePhase_Data_Structure *p)
{
	spll1.v_q[0] = (p->dq0_data[index_q])*NORMALIZE_COE;
	SPLL_3ph_SRF_F_MACRO(spll1);
}

/*
 * FunName:AAL_PLL_GetPhase
 * Description:获取PLL当前输出的角度值
 * Input:None
 * Output:None
 * Others:None
 * */
float AAL_PLL_GetPhase(void)
{
	return (spll1.theta[0]);
}



