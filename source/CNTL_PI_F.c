#include "Solar_F.h"

//*********** Structure Init Function ****//
void CNTL_PI_F_init(CNTL_PI_F *k){
	/* Initialize variables */
	k->Ref = 0;
	k->Fbk = 0;
	k->Out = 0;
	k->Kp = 0;
	k->Ki = 0;
	k->Umax = (1.0);
	k->Umin = (0.0);
	k->up = 0;
	k->ui = 0;
	k->v1 = 0;
	k->i1 = 0;
	k->w1 = 0;
}

//*********** Function Definition ********//
void CNTL_PI_F_FUNC(CNTL_PI_F *v){
	/* proportional term */
	v->up = ((v->Ref - v->Fbk)*v->Kp);

	/* integral term */
	v->ui = (v->Out == v->v1)?((v->Ki* v->up)+ v->i1) : v->i1;
	v->i1 = v->ui;

	/* control output */
	v->v1 = (v->up + v->ui);
	v->Out = (v->v1 > v->Umax)?(v->Umax) : v->v1;
	v->Out = (v->Out < v->Umin)?(v->Umin) : v->Out;
}

