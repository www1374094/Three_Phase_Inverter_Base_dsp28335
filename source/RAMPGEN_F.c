#include "Solar_F.h"

//*********** Structure Init Function ****//
void RAMPGEN_F_init(RAMPGEN_F *v)
{
	v->Freq=0;
	v->StepAngleMax=0;
	v->Angle=0;
	v->Out=0;
}

//*********** Function Definition ********//
void RAMPGEN_F_FUNC(RAMPGEN_F *v)
{
/* Compute the angle rate */
	v->Angle += (v->StepAngleMax*v->Freq);
/* Saturate the angle rate within (0,1) */
	if (v->Angle>(1.0))
		v->Angle -= (1.0);
	v->Out=v->Angle;
}
