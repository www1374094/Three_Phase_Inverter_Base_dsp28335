#include "Solar_F.h"

//*********** Structure Init Function ****//
void PARK_F_init(PARK_F *v)
{
	v->alpha=0;
	v->beta=0;
	v->zero=0;
	v->d=0;
	v->q=0;
	v->z=0;
}

//*********** Function Definition ********//
void PARK_F_FUNC(PARK_F *v)
{
	v->d= v->alpha*v->cos + v->beta*v->sin;
	v->q=-v->alpha*v->sin + v->beta*v->cos;
	v->z=v->zero;
}
