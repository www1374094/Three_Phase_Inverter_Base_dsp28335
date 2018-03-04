#include "Solar_F.h"

//*********** Structure Init Function ****//
void PID_GRANDO_F_init(PID_GRANDO_F_CONTROLLER *v)
{
	v->term.Ref=0;
	v->term.Fbk=0;
	v->term.Out=0;
	v->term.c1=0;
	v->term.c2=0;

	v->param.Kr = (1.0);
	v->param.Kp = (1.0);
	v->param.Ki = (0.0);
	v->param.Kd = (0.0);
	v->param.Km = (1.0);
	v->param.Umax = (1.0);
	v->param.Umin = (-1.0);

	v->data.up = (0.0);
	v->data.ui = (0.0);
	v->data.ud = (0.0);
	v->data.v1 = (0.0);
	v->data.i1 = (0.0);
	v->data.d1 = (0.0);
	v->data.d2 = (0.0);
	v->data.w1 = (1.0);
}

//*********** Function Definition ********//
void PID_GRANDO_F_FUNC(PID_GRANDO_F_CONTROLLER *v)
{
	/* proportional term */
	v->data.up = (v->param.Kr* v->term.Ref) - v->term.Fbk;

	/* integral term */
	v->data.ui = (v->param.Ki* (v->data.w1* (v->term.Ref - v->term.Fbk))) + v->data.i1;
	v->data.i1 = v->data.ui;

	/* derivative term */
	v->data.d2 = (v->param.Kd* (v->term.c1* ((v->term.Ref* v->param.Km) - v->term.Fbk))) - v->data.d2;
	v->data.ud = v->data.d2 + v->data.d1;
	v->data.d1 = (v->data.ud* v->term.c2);

	/* control output */
	v->data.v1 = (v->param.Kp* (v->data.up + v->data.ui + v->data.ud));
	v->term.Out= __fmax((__fmin(v->param.Umax,v->data.v1)),v->param.Umin);
	v->data.w1 = (v->term.Out == v->data.v1) ? (1.0) : (0.0);
}

