/*
 * TPVSI_DSP28335_Structure_Define.h
 *
 *  Created on: 2018年3月12日
 *      Author: wangchu
 */

#ifndef TPVSI_DSP28335_STRUCTURE_DEFINE_H_
#define TPVSI_DSP28335_STRUCTURE_DEFINE_H_


/*与电路板ADC通道对应的数据的含义*/
typedef enum{
	VoltageA = 0,
	VoltageB,
	VoltageC,
	CurrentA,
	CurrentB,
	CurrentC,
	VoltageDC,
	CurrentDC,
	CapVoltageA,
	CapVoltageB,
	CapVoltageC,
	InvCurrentA,
	InvCurrentB,
	InvCurrentC,
	SAMPLE_NUM,//这个枚举变量必须放在所有变量的最后，用以标识采样数据的个数
}Sample_Index;


/*
 * StructureName:EPWM_Structure
 * Description:EPWM模块的抽象结构体。
 * Elements:
 * 	cmp_max->比较寄存器允许的最大值
 * 	cmp_min->比较寄存器允许的最小值
 * 	fre->EPWM模块的工作频率
 * 	bias->给比较寄存器赋值时的偏移量
 * 	cmpa_value->比较寄存器a的值
 * 	cmpb_value->比较寄存器b的值
 * */
typedef struct{
	Uint16 cmp_max;
	Uint16 cmp_min;
	Uint16 fre;
	Uint16 bias;
	Uint16 cmpa_value;
	Uint16 cmpb_value;
} EPWM_Structure;

/*
 * StructureName:Sample_Structure
 * Description:采样模块的抽象结构体。
 * Elements:
 * 	data->采样数据；
 * 	k->采样值到实际数据的转换系数，例如ADC采样得到的值为x(0<=x<=4095)，则实际数据为k*x
 * */
typedef struct{
	float data[SAMPLE_NUM];//数据
	float k[SAMPLE_NUM];//ADC转换的比例系数
} Sample_Structure;


/*
 * StructureName:Sin_Structure
 * Description:Sine函数值结构体。
 * Elements:
 * 	Angle->当前角度
 * 	sin_value->当前角度的正弦值
 * */
typedef struct{
  float Angle;
  float sin_value;
} Sin_Structure;

/*
 * StructureName:ThreePhase_Data_Structure
 * Description:储存三相数据的结构体，将三相的数据分别以abc、dq0、αβ0三个坐标轴中的量进行储存，各数据的索引值参考枚举变量定义
 * Elements:
 * 	abc_data->abc轴数据；
 *	angle->角度数据;
 *	dq0_data->dq0坐标轴数据;
 *	alphabeta0_data->αβ0坐标轴数据
 *	clarke_p->与Solar库的clark变换的接口结构体，不应被外部访问
 *	park_p->与Solar库的park变换的接口结构体，不应被外部访问
 *	iclarke_p->与Solar库的iclark变换的接口结构体，不应被外部访问
 *	ipark_p->与Solar库的ipark变换的接口结构体，不应被外部访问
 * */
typedef struct{
	float abc_data[3];
	float angle;
	float dq0_data[3];
	float alphabeta0_data[3];
	CLARKE_F clarke_p;
	PARK_F park_p;
	iCLARKE_F iclarke_p;
	iPARK_F ipark_p;
}ThreePhase_Data_Structure;


/*
 * StructureName:PID_Structure
 * Description:PID控制器结构体.
 * Elements:
 * 	kp->比例系数
 * 	ki->积分系数
 * 	Ts->采样时间
 * 	output->输出变量
 * 	err->误差变量
 * 	err_last->上一次控制时的误差变量
 * 	output_last->上一次控制时的输出变量
 * */
typedef struct{
	float kp;
	float ki;
	float Ts;
	float output;
	float err;
	float err_last;
	float output_last;
}PID_Structure;

/*
 * StructureName:PID_Structure
 * Description:PID控制器结构体.
 * Elements:
 * 	y2->y(n-2)
 * 	y1->y(n-1)
 * 	y->y(n)
 * 	x2->x(n-2)
 * 	x1->x(n-1)
 * 	x->x(n)
 * */
typedef struct{
	float x[4];
	float y[4];
}ThirdOrder_Controller_Structure;


/*三相数据结构体索引枚举定义*/
/*0->a,1->b,2->c*/
typedef enum{
	index_a = 0,
	index_b,
	index_c,
}abc_Index;

/*0->0,1->d,2->q*/
typedef enum{
	index_d = 1,
	index_q,
}dq0_index;

/*0->0,1->α,2->β*/
typedef enum{
	index_alpha = 1,
	index_beta,
}alphabeta0_index;


#endif /* TPVSI_DSP28335_STRUCTURE_DEFINE_H_ */
