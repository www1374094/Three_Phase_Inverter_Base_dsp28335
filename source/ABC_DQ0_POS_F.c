#include "Solar_F.h"

//*********** Structure Init Function ****//
void ABC_DQ0_POS_F_init(ABC_DQ0_POS_F *v){
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
void ABC_DQ0_POS_F_FUNC(ABC_DQ0_POS_F *v){
	v->alpha=(0.6666666667)*(v->a-0.5*(v->b+v->c));
	v->beta=(0.57735026913)*(v->b-v->c);
	v->z =0.57735026913*(v->a+v->b+v->c);
	v->d=v->alpha*v->cos+v->beta*v->sin;
	v->q=-v->alpha*v->sin+v->beta*v->cos;
}
