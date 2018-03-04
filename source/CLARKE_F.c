#include "Solar_F.h"

//*********** Structure Init Function ****//
void CLARKE_F_init(CLARKE_F *v){
	v->a=0;
	v->b=0;
	v->c=0;
	v->alpha=0;
	v->beta=0;
}

//*********** Function Definition ********//
void CLARKE_F_FUNC(CLARKE_F *v){
	v->alpha=((0.66666666667)*(v->a-((0.5)*(v->b+v->c))));
	v->beta =((0.57735026913)*(v->b-v->c));
	v->zero =((0.33333333333)*(v->a+v->b+v->c));
}
