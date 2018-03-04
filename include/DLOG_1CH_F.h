#ifndef DLOG_1CH_F_H
#define DLOG_1CH_F_H

//*********** Structure Definition ********//
typedef struct{
	float32 *input_ptr;
	float32 *output_ptr;
	float32 prev_value;
	float32 trig_value;
	int16 status;
	int16 pre_scalar;
	int16 skip_count;
	int16 size;
	int16 count;
}DLOG_1CH_F;

//*********** Function Declarations *******//
void DLOG_1CH_F_init(DLOG_1CH_F *v);
void DLOG_1CH_F_FUNC(DLOG_1CH_F *v);

//*********** Macro Definition ***********//
#define DLOG_1CH_F_MACRO(v)										\
switch(v.status)												\
{																\
case 1: /* wait for trigger*/									\
	if(*v.input_ptr>v.trig_value && v.prev_value<v.trig_value)	\
	{															\
		/* rising edge detected start logging data*/			\
		v.status=2;												\
	}															\
	break;														\
case 2:															\
	v.skip_count++;												\
	if(v.skip_count==v.pre_scalar)								\
	{															\
		v.skip_count=0;											\
		v.output_ptr[v.count]=*v.input_ptr;						\
		v.count++;												\
		if(v.count==v.size)										\
		{														\
			v.count=0;											\
			v.status=1;											\
		}														\
	}															\
	break;														\
}																\
v.prev_value=*v.input_ptr;										\


#endif /* DLOG_1CH_F_H_ */
