/*
 * TPVSI_DSP28335_Control.c
 *
 *  Created on: 2018年3月4日
 *      Author: chen318
 */
#include "TPVSI_DSP28335_Control.h"

/*全局变量定义*/
ABC_DQ0_POS_F p_vol_dq0;
DQ0_ABC_F p_dq0_abc;



#pragma CODE_SECTION(CON_ABC_DQ0_CAL,"ramfuncs");
//#pragma CODE_SECTION(CON_DQ0_ABC_CAL,"ramfuncs");
//#pragma CODE_SECTION(CON_VOL_CL_ABC_REG,"ramfuncs");


#if _GRAPH_DISPLAY_
float display_buffer[512];
/*
 * FunName:CON_PUSH_BUFFER
 * Description:将采样数据存入显示缓冲区中
 * Input:数据x
 * Output:None
 * */
void CON_PUSH_BUFFER(float x)
{
	Uint8 i;
	for(i=1;i<512;i++)
	{
		display_buffer[i] = display_buffer[i-1];
	}
	display_buffer[0] = x;
}
#endif



/*
 * FunName:CON_ABC_DQ0_CAL
 * Description:abc->dq0的转换，TI ControlSuite。
 * Input:a,b,c三轴分量,坐标轴夹角theta,abc_dq0结构体指针abc_dq0_pos
 * Output:None
 * Others:None
 * */
void CON_ABC_DQ0_CAL(float32 a,float32 b,float32 c,float32 theta,ABC_DQ0_POS_F *abc_dq0_pos1)
{
	abc_dq0_pos1->a = a;
	abc_dq0_pos1->b = b;
	abc_dq0_pos1->c = c;
	abc_dq0_pos1->sin = sin(theta);
	abc_dq0_pos1->cos = cos(theta);
	ABC_DQ0_POS_F_MACRO((*abc_dq0_pos1));
}



/*
 * FunName:CON_PID_DeInit
 * Description:将PID结构体初始化为缺省值
 * Input:PID结构体指针p
 * Output:None
 * Others:None
 * */
void CON_PID_DeInit(PID_Stru *p)
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
 * FunName:CON_PID_Init
 * Description:将PID结构体按照给定参数初始化
 * Input:PID结构体指针p,采样时间Ts,比例系数kp,积分系数ki
 * Output:None
 * Others:None
 * */
void CON_PID_Init(PID_Stru *p,float Ts,float kp,float ki)
{
	CON_PID_DeInit(p);
	p->Ts = Ts;
	p->kp = kp;
	p->ki = ki;
}


/*
 * FunName:CON_VOL_CL_PID
 * Description:电压闭环pid函数
 * Input:PID结构体指针p
 * Output:None
 * Others:None
 * */
void CON_VOL_CL_PID(PID_Stru *dpid,PID_Stru *qpid,ABC_DQ0_POS_F *abc_dq0_pos1)
{
	//目标值设定
	float d_target = 0;
	float q_target = 0;
	//更新数据
	dpid->err_last = dpid->err;
	qpid->err_last = qpid->err;
	dpid->err = d_target - abc_dq0_pos1->d;
	qpid->err = q_target - abc_dq0_pos1->q;
	dpid->output_last = dpid->output;
	qpid->output_last = qpid->output;
	dpid->output = dpid->output_last + dpid->kp*(dpid->err - dpid->err_last) + dpid->ki*dpid->Ts*dpid->err;
	qpid->output = qpid->output_last + qpid->kp*(qpid->err - qpid->err_last) + qpid->ki*qpid->Ts*qpid->err;
	if(dpid->output>1)
		dpid->output = 1;
		else if(dpid->output<0)
			dpid->output = 0;
	if(qpid->output>1)
			qpid->output = 1;
		else if(qpid->output<0)
			qpid->output = 0;
}


/*
 * FunName:CON_DQ0_ABC_CAL
 * Description:dq0->abc的转换，TI ControlSuite。
 * Input:a,b,c三轴分量,坐标轴夹角theta,abc_dq0结构体指针abc_dq0_pos
 * Output:None
 * Others:None
 * */
void CON_DQ0_ABC_CAL(float d,float q,float z,float theta,DQ0_ABC_F *p)
{
	p->d = d;
	p->q = q;
	p->z = z;
	p->sin = sin(theta);
	p->cos = cos(theta);
	DQ0_ABC_F_MACRO((*p));
}

/*
 * FunName:CON_VOL_CL_DQ0_ABC
 * Description:将ABC坐标下的占空比数值转化为寄存器值
 * Input:dq0->abc结构体指针p,三相EPWM结构体指针epa,epb,epc
 * Output:None
 * Others:None
 * */
void CON_VOL_CL_ABC_REG(DQ0_ABC_F *p,EPWM_Structure *epa,EPWM_Structure *epb,EPWM_Structure *epc)
{
	HAL_PWM_DutyValue_Cal(epa,p->a,0.9,-0.9);
	HAL_PWM_DutyValue_Cal(epb,p->b,0.9,-0.9);
	HAL_PWM_DutyValue_Cal(epc,p->c,0.9,-0.9);
}






