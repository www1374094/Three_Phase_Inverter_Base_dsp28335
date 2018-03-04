#include "Solar_F.h"

//*********** Structure Init Function ****//
void iPARK_F_init(iPARK_F *v)
{
	v->alpha=0;
	v->beta=0;
	v->zero=0;
	v->d=0;
	v->q=0;
	v->z=0;
}

//*********** Function Definition ********//
void iPARK_F_FUNC(iPARK_F *v)
{
	v->alpha = v->d*v->cos - v->q*v->sin;
	v->beta  = v->d*v->sin + v->q*v->cos;
	v->zero  = v->z;
}

