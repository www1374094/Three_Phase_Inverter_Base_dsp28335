#include "Solar_F.h"

//*********** Structure Init Function ****//
void DLOG_1CH_F_init(DLOG_1CH_F *v)
{
	v->input_ptr = 0;
	v->output_ptr = 0;
	v->prev_value = 0;
	v->trig_value = 0;
	v->status = 0;
	v->pre_scalar = 0;
	v->skip_count = 0;
	v->size = 0;
	v->count = 0;
}

//*********** Function Definition ********//
void DLOG_1CH_F_FUNC(DLOG_1CH_F *v)
{
	switch(v->status)
	{
	case 1: /* wait for trigger*/
		if(*v->input_ptr>v->trig_value && v->prev_value<v->trig_value)
		{
			/* rising edge detected start logging data*/
			v->status=2;
		}
		break;
	case 2:
		v->skip_count++;
		if(v->skip_count==v->pre_scalar)
		{
			v->skip_count=0;
			v->output_ptr[v->count]=*v->input_ptr;
			v->count++;
			if(v->count==v->size)
			{
				v->count=0;
				v->status=1;
			}
		}
		break;
	}
	v->prev_value=*v->input_ptr;
}

