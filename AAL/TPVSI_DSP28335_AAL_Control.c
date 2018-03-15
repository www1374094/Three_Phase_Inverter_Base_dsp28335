/*
 * TPVSI_DSP28335_AAL_Control.c
 *
 *  Created on: 2018年3月12日
 *      Author: Chuck
 */

#include "TPVSI_DSP28335_AAL_Control.h"

ThirdOrder_Controller_Structure PR_Controller;


/*
 * FunName:AAL_Control_PID_DeInit
 * Description:将PID结构体初始化为缺省值
 * Input:PID结构体指针p
 * Output:None
 * Others:None
 * */
void AAL_Control_PID_DeInit(PID_Structure *p)
{
	p->Ts = 0;
	p->err = 0;
	p->err_last = 0;
	p->ki = 0;
	p->kp = 0;
	p->output = 0;
	p->output_last = 0;
}

/*
 * FunName:AAL_Control_PID_Init
 * Description:将PID结构体按照给定参数初始化
 * Input:PID结构体指针p,采样时间Ts,比例系数kp,积分系数ki
 * Output:None
 * Others:None
 * */
void AAL_Control_PID_Init(PID_Structure *p,float Ts,float kp,float ki)
{
	AAL_Control_PID_DeInit(p);
	p->Ts = Ts;
	p->kp = kp;
	p->ki = ki;
}


/*
 * FunName:AAL_Control_PID
 * Description:电压闭环pid函数
 * Input:PID结构体指针p,误差输入err
 * Output:None
 * Others:None
 * */
void AAL_Control_PID(PID_Structure *p,float err)
{
	//更新数据
	p->err_last = p->err;
	p->err = err;
	p->output_last = p->output;
	//计算PID，欧拉近似
	p->output = p->output_last + p->kp*(p->err - p->err_last) + p->ki*p->Ts*p->err;
	if(p->output>1)
		p->output = 0.99;
	else if(p->output<-1)
		p->output = -0.99;
}

void AAL_Control_ThirdOrderController(ThirdOrder_Controller_Structure *p)
{
	//PR控制器
	p->y = 2*(p->y1) - 0.9745*(p->y2) + 0.673*(p->x) - 0.04*(p->x2);
}
