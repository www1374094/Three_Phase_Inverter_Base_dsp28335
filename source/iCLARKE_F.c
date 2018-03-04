#include "Solar_F.h"

//*********** Structure Init Function ****//
void iCLARKE_F_init(iCLARKE_F *v)
{
	v->a=0;
	v->b=0;
	v->c=0;
	v->alpha=0;
	v->beta=0;
}

//*********** Function Definition ********//
void iCLARKE_F_FUNC(iCLARKE_F *v)
{
	v->a = v->alpha + 0.5*v->zero;
	v->b = -0.5*v->alpha + 0.8660254*v->beta + 0.5*v->zero;
	v->c = -0.5*v->alpha - 0.8660254*v->beta + 0.5*v->zero;
}

