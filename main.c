/*
 * Title:3 Phase VSI Base Program
 * Author:Chuck Wang
 * Description:提供了三相逆变器需要的基本程序,主要包括:
 * A、板级硬件初始化程序，包含板级硬件初始化函数，定义在TPVSI_DSP28335_BSP.c中
 * B、中断程序，包含了所有需要的中断函数，定义在TPVSI_DSP28335_BSP.c中
 * main.c
 */


#include "DSP28x_Project.h"


/*全局变量定义*/
int main(void)
{
	memcpy((Uint16 *)&RamfuncsRunStart,(Uint16 *)&RamfuncsLoadStart, (unsigned long)&RamfuncsLoadSize);
	InitSysCtrl();
	DINT;
	/*下面不要修改*/
	/*Begin*/
	//中断设置
	InitPieCtrl();
	//清除所有中断标志位
	IER = 0x0000;
	IFR = 0x0000;
	InitPieVectTable();
	/*End*/
	/*TODO:这里指定中断函数*/
	EALLOW;
	PieVectTable.EPWM1_INT = &epwm1_isr;
	EDIS;
	/*TODO:这里初始化硬件抽象层和算法抽象层*/
//	HAL_EPWM_DISABLE();
	HAL_Init();
	AAL_Trans_Init();
	AAL_PLL_Init();
	AAL_Control_ThirdOrderControllerInit();
	HAL_Relay_On();
	/*TODO:这里配置中断源*/
	IER |= M_INT3;
	PieCtrlRegs.PIEIER3.bit.INTx1 = 1;
	/*下面开启中断，不要修改*/
	/*Begin*/
	EINT;
	ERTM;
	/*End*/
	for(;;)
	{

	}
	return 0;
}
