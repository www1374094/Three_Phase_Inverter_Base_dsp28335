#include "Solar_F.h"

//*********** Structure Init Function ****//
void DQ0_ABC_F_init(DQ0_ABC_F *v)
{
	v->a=0;
	v->b=0;
	v->c=0;
	v->alpha=0;
	v->beta=0;
	v->z=0;
	v->d=0;
	v->q=0;
}

//*********** Function Definition ********//
void DQ0_ABC_F_FUNC(DQ0_ABC_F *v)
{
	v->alpha = v->d*v->cos - v->q*v->sin;
	v->beta  = v->d*v->sin + v->q*v->cos;
	v->a = v->alpha + 0.5*v->z;
	v->b = -0.5*v->alpha + 0.8660254*v->beta + 0.5*v->z;
	v->c = -0.5*v->alpha - 0.8660254*v->beta + 0.5*v->z;
}

