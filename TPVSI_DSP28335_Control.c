/*
 * TPVSI_DSP28335_Control.c
 *
 *  Created on: 2018年3月4日
 *      Author: chen318
 */
#include "TPVSI_DSP28335_Control.h"


void CON_Sample(Sample_Stru *p)
{
	static Uint16 zero[SAMPLE_NUM];
	Uint8 i = 0;
	for(;i<SAMPLE_NUM;i++)
	{
		p->data[i] = p->k[i]*(DMA_Buf[i] - zero[i]);
	}
}
//这个函数之后删除掉
void ABC_DQ0_POS_Init(ABC_DQ0_POS_F *abc_dq0_pos1)
{
	ABC_DQ0_POS_F_init(abc_dq0_pos1);
}

void CON_ABC_DQ0_CAL(float32 a,float32 b,float32 c,float32 theta,ABC_DQ0_POS_F *abc_dq0_pos1)
{
	abc_dq0_pos1->a = a;
	abc_dq0_pos1->b = b;
	abc_dq0_pos1->c = c;
	abc_dq0_pos1->sin = sin(theta);
	abc_dq0_pos1->cos = cos(theta);
	ABC_DQ0_POS_F_FUNC(abc_dq0_pos1);
}

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

void CON_PID_Init(PID_Stru *p,float Ts,float kp,float ki)
{
	CON_PID_Deinit(p);
	p->Ts = Ts;
	p->kp = kp;
	p->ki = ki;
}

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




