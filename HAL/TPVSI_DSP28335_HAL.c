/*
 * TPVSI_DSP28335_HAL.c
 *
 *  Created on: 2018年3月10日
 *      Author: wangchu
 */
#include "TPVSI_DSP28335_HAL.h"
#include "C28x_FPU_FastRTS.h"
EPWM_Structure _p_epwm1;
EPWM_Structure _p_epwm2;
EPWM_Structure _p_epwm3;
Sin_Structure _p_sin1;
Sample_Structure p_sam;

#pragma CODE_SECTION(HAL_Sample,"ramfuncs");

void HAL_Init(void)
{
	HAL_EPWM_Structure_Init();
	HAL_Sample_Init(&p_sam);
	BSP_GPIO_Init();
	BSP_ADC_Init();
	BSP_ePWM_Init();
	BSP_DMA_Init();

}
void HAL_EPWM_Structure_Init(void)
{
	_p_epwm1.fre = 50000;
	_p_epwm1.bias = 1500;
	_p_epwm1.cmp_max = 3000;
	_p_epwm1.cmp_min = 0;
	_p_epwm1.cmpa_value = 1500;
	_p_epwm1.cmpb_value = 1500;
	_p_epwm2.fre = 50000;
	_p_epwm2.bias = 1500;
	_p_epwm2.cmp_max = 3000;
	_p_epwm2.cmp_min = 0;
	_p_epwm2.cmpa_value = 1500;
	_p_epwm2.cmpb_value = 1500;
	_p_epwm3.fre = 50000;
	_p_epwm3.bias = 1500;
	_p_epwm3.cmp_max = 3000;
	_p_epwm3.cmp_min = 0;
	_p_epwm3.cmpa_value = 1500;
	_p_epwm3.cmpb_value = 1500;
}


void HAL_PWM_DutyValue_Cal(EPWM_Structure *ep,float duty,float duty_max,float duty_min)
{
	Uint16 temp;
	if(duty>duty_max) duty = duty_max;
	else if(duty<duty_min) duty = duty_min;
	temp = (Uint16)(duty*((ep->cmp_max) - (ep->cmp_min))/2.0 + (ep->bias));
	if(temp>(ep->cmp_max)) temp = ep->cmp_max;
	else if (temp<(ep->cmp_min)) temp = ep->cmp_min;
	ep->cmpa_value = temp;
}

/*
 * FunName:HAL_Sample_Init
 * Description:初始化采样结构体，系数k数组代表了采样数据到真实数据转换的系数，这个数组的初始化应随采样数据的多少而定
 * Input:采样结构体指针p
 * Output:None
 * */
void HAL_Sample_Init(Sample_Structure *p)
{
	Uint8 i;
	/*TODO:在这里定义采样的系数*/
	p->k[0] = 0.0362;
	p->k[1] = 0.0362;
	p->k[2] = 0.0362;
	p->k[3] = 0.014066;
	p->k[4] = 0.014066;
	p->k[5] = 0.014066;
	/*下面初始化数据数组*/
	for(i=0;i<SAMPLE_NUM;i++)
	{
		p->data[i] = 0;
	}
}

#pragma CODE_SECTION(HAL_Sample,"ramfuncs");
#pragma CODE_SECTION(HAL_DutySet,"ramfuncs");
/*
 * FunName:HAL_Sample
 * Description:对采样数据进行处理，源数据来自DMA缓冲区数组DMA_Buf，
 * 			   DMA_Buf是一个全局变量，定义在TPVSI_DSP28335_BSP.c中
 * Input:采样结构体指针p
 * Output:None
 * Others:None
 * */
void HAL_Sample(Sample_Structure *p)
{
	static int zero[SAMPLE_NUM];
	Uint8 i = 0;
	/*TODO：在这里定义采样零点偏移量*/
	zero[0] = 1430;
	zero[1] = 1483;
	zero[2] = 1430;
	zero[3] = 1566;
	zero[4] = 1567;
	zero[5] = 1567;
	/*下面计算各采样数据*/
	for(;i<SAMPLE_NUM;i++)
	{
		p->data[i] = p->k[i]*(float)((int)DMA_Buf[i] - zero[i]);
	}
}



/*
 * FunName:HAL_DutySet
 * Description:输出由控制变量结构体指定的占空比
 * Input:控制变量结构体指针p，EPWM模块结构体指针epa,epb,epc
 * Output:None
 * Others:None
 * */
void HAL_DutySet(ThreePhase_Data_Structure *p,EPWM_Structure *epa,EPWM_Structure *epb,EPWM_Structure *epc)
{
	HAL_PWM_DutyValue_Cal(epa,p->abc_data[index_a],0.9,-0.9);
	HAL_PWM_DutyValue_Cal(epb,p->abc_data[index_b],0.9,-0.9);
	HAL_PWM_DutyValue_Cal(epc,p->abc_data[index_c],0.9,-0.9);
	EPwm1Regs.CMPA.half.CMPA = epa->cmpa_value;
	EPwm2Regs.CMPA.half.CMPA = epb->cmpa_value;
	EPwm3Regs.CMPA.half.CMPA = epc->cmpa_value;
}

/*
 * FunName:HAL_GetSampleResult
 * Description:获取采样值
 * Input:采样索引index.
 * Output:None
 * Others:None
 * */
float HAL_GetSampleResult(Uint8 index)
{
	if(index >= SAMPLE_NUM) return 0;
	return (p_sam.data[index]);
}
