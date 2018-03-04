#include "Solar_F.h"

void NOTCH_FLTR_F_VARS_init(NOTCH_VARS_F *v)
{
	v->In=0;
	v->In1=0;
	v->In2=0;
	v->Out=0;
	v->Out1=0;
	v->Out2=0;
}

void NOTCH_FLTR_F_run(NOTCH_VARS_F *v,NOTCH_COEFF_F *w)
{
	v->Out=(w->A1_notch*v->Out1) \
			+(w->A2_notch*v->Out2)\
			+(w->B0_notch*v->In)\
			+(w->B1_notch*v->In1)\
			+(w->B2_notch*v->In2);

	v->Out2=v->Out1;
	v->Out1=v->Out;
	v->In2=v->In1;
	v->In1=v->In;
}

void NOTCH_FLTR_F_COEFF_Update(float32 delta_T, float32 wn,float32 c2, float32 c1, NOTCH_COEFF_F *notch_obj)
{
	// Note c2<<c1 for the notch to work
	float32 x,y,z;
	x=(float32)(2.0*c2*wn*delta_T);
	y=(float32)(2.0*c1*wn*delta_T);
	z=(float32)(wn*delta_T*wn*delta_T);

	notch_obj->A1_notch=-(y-2);
	notch_obj->A2_notch=-(z-y+1);
	notch_obj->B0_notch=(1.0);
	notch_obj->B1_notch=(x-2);
	notch_obj->B2_notch=(z-x+1);
}

