/*
 * TPVSI_DSP28335_AAL_Trans.c
 *
 *  Created on: 2018年3月12日
 *      Author: Chuck
 */
#include "TPVSI_DSP28335_AAL_Trans.h"
#include<math.h>
/*全局变量定义*/
ThreePhase_Data_Structure Inverter_Voltage_Data;
ThreePhase_Data_Structure Inverter_Current_Data;
ThreePhase_Data_Structure Control_Data;
ThreePhase_Data_Structure Inverter_CapVoltage_Data;
ThreePhase_Data_Structure Inverter_CapCurrent_Data;
ThreePhase_Data_Structure Target_Data;

/*
 * FunName:AAL_Trans_Update
 * Description:从HAL层中的采样结构体中读取数据到算法层
 * Input:采样结构体指针p
 * Output:None
 * Others:None
 * */
void AAL_Trans_Update(Sample_Structure *p)
{
	static float vcap_last[3] = {0,0,0};
	int i = 0;
	Inverter_Voltage_Data.abc_data[index_a] = p->data[VoltageA];
	Inverter_Voltage_Data.abc_data[index_b] = p->data[VoltageB];
	Inverter_Voltage_Data.abc_data[index_c] = p->data[VoltageC];
	Inverter_Current_Data.abc_data[index_a] = p->data[CurrentA];
	Inverter_Current_Data.abc_data[index_b] = p->data[CurrentB];
	Inverter_Current_Data.abc_data[index_c] = p->data[CurrentC];
	Inverter_CapVoltage_Data.abc_data[index_a] = p->data[CapVoltageA];
	Inverter_CapVoltage_Data.abc_data[index_b] = p->data[CapVoltageB];
	Inverter_CapVoltage_Data.abc_data[index_c] = p->data[CapVoltageC];
	//利用差分法计算滤波电容的电流，单位为A
	for(i = 0;i<3;i++)
	{
		Inverter_CapCurrent_Data.abc_data[i] =
				0.055*(Inverter_CapVoltage_Data.abc_data[i] - vcap_last[i]);
		vcap_last[i] = Inverter_CapVoltage_Data.abc_data[i];
	}
}

/*
 * FunName:AAL_Trans_Init
 * Description:初始化算法抽象层中坐标变换所需要的结构体
 * Input:None
 * Output:None
 * Others:None
 * */
void AAL_Trans_Init(void)
{
	AAL_Trans_StruInit(&Inverter_Voltage_Data);
	AAL_Trans_StruInit(&Inverter_Current_Data);
	AAL_Trans_StruInit(&Control_Data);
	AAL_Trans_StruInit(&Inverter_CapVoltage_Data);
	AAL_Trans_StruInit(&Inverter_CapCurrent_Data);
	AAL_Trans_StruInit(&Target_Data);
}

/*
 * FunName:AAL_Trans_StruInit
 * Description:将算法抽象层中坐标变换所需要的结构体重置为默认值
 * Input:三相数据结构体指针p
 * Output:None
 * Others:None
 * */
void AAL_Trans_StruInit(ThreePhase_Data_Structure *p)
{
	Uint8 i;
	for(i = 0;i<3;i++)
	{
		p->abc_data[i] = 0;
		p->alphabeta0_data[i] = 0;
		p->dq0_data[i] = 0;
	}
	p->angle = 0;
	CLARKE_F_init(&p->clarke_p);
	PARK_F_init(&p->park_p);
}

/*
 * FunName:AAL_Trans_Park
 * Description:Park变换
 * Input:三相数据结构体指针p
 * Output:None
 * Others:None
 * */
void AAL_Trans_Park(ThreePhase_Data_Structure *p,float angle)
{
	p->park_p.alpha = p->alphabeta0_data[index_alpha];
	p->park_p.beta = p->alphabeta0_data[index_beta];
	p->park_p.zero = p->alphabeta0_data[0];
	p->park_p.sin = sin(angle);
	p->park_p.cos = cos(angle);
	PARK_F_MACRO(p->park_p);
	p->dq0_data[index_d] = p->park_p.d;
	p->dq0_data[index_q] = p->park_p.q;
	p->dq0_data[0] = p->park_p.zero;
}

/*
 * FunName:AAL_Trans_Park
 * Description:反Park变换
 * Input:三相数据结构体指针p
 * Output:None
 * Others:None
 * */
void AAL_Trans_iPark(ThreePhase_Data_Structure *p,float angle)
{
	p->ipark_p.d = p->dq0_data[index_d];
	p->ipark_p.q = p->dq0_data[index_q];
	p->ipark_p.z = p->dq0_data[0];
	p->ipark_p.sin = sin(angle);
	p->ipark_p.cos = cos(angle);
	iPARK_F_MACRO(p->ipark_p);
	p->alphabeta0_data[index_alpha] = p->ipark_p.alpha;
	p->alphabeta0_data[index_beta] = p->ipark_p.beta;
	p->alphabeta0_data[0] = p->ipark_p.zero;
}

/*
 * FunName:AAL_Trans_Clark
 * Description:Clark变换
 * Input:三相数据结构体指针p
 * Output:None
 * Others:None
 * */
void AAL_Trans_Clark(ThreePhase_Data_Structure *p)
{
	p->clarke_p.a = p->abc_data[index_a];
	p->clarke_p.b = p->abc_data[index_b];
	p->clarke_p.c = p->abc_data[index_c];
	CLARKE_F_MACRO(p->clarke_p);
	p->alphabeta0_data[index_alpha] = p->clarke_p.alpha;
	p->alphabeta0_data[index_beta] = p->clarke_p.beta;
	p->alphabeta0_data[0] = p->clarke_p.zero;
}

/*
 * FunName:AAL_Trans_Clark
 * Description:反Clark变换
 * Input:三相数据结构体指针p
 * Output:None
 * Others:None
 * */
void AAL_Trans_iClark(ThreePhase_Data_Structure *p)
{
	p->iclarke_p.alpha = p->alphabeta0_data[index_alpha];
	p->iclarke_p.zero = p->alphabeta0_data[0];
	p->iclarke_p.beta = p->alphabeta0_data[index_beta];
	iCLARKE_F_MACRO(p->iclarke_p);
	p->abc_data[index_a] = p->iclarke_p.a;
	p->abc_data[index_b] = p->iclarke_p.b;
	p->abc_data[index_c] = p->iclarke_p.c;
}

/*
 * FunName:AAL_Trans_ABCDQ0
 * Description:ABC->DQ0坐标变换
 * Input:三相数据结构体指针p，坐标系变换角度angle
 * Output:None
 * Others:None
 * */
void AAL_Trans_ABCDQ0(ThreePhase_Data_Structure *p,float angle)
{
	AAL_Trans_Clark(p);
	AAL_Trans_Park(p,angle);
}

/*
 * FunName:AAL_Trans_DQ0ABC
 * Description:DQ0->ABC坐标变换
 * Input:三相数据结构体指针p，坐标系变换角度angle
 * Output:None
 * Others:None
 * */
void AAL_Trans_DQ0ABC(ThreePhase_Data_Structure *p,float angle)
{
	AAL_Trans_iPark(p,angle);
	AAL_Trans_iClark(p);
}

/*
 * FunName:AAL_Trans_SetDQ0Value
 * Description:设置DQ0坐标系中的坐标值
 * Input:三相数据结构体指针p，坐标值d,q,zero
 * Output:None
 * Others:None
 * */
void AAL_Trans_SetDQ0Value(ThreePhase_Data_Structure *p,float d,float q,float zero)
{
	p->dq0_data[index_d] = d;
	p->dq0_data[index_q] = q;
	p->dq0_data[0] = zero;
}

