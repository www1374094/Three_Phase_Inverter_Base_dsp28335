#include "Solar_F.h"

//*********** Structure Init Function ****//
void MATH_EMAVG_F_init(MATH_EMAVG_F *v){
	v->In = 0;
	v->Out = 0;
	v->Multiplier = 0;
}

//*********** Function Definition ********//
void MATH_EMAVG_F_FUNC(MATH_EMAVG_F *v){
	v->Out = ((v->In - v->Out)*v->Multiplier) + v->Out;
}

