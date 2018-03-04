#ifndef PARK_F_H
#define PARK_F_H

//*********** Structure Definition ********//
typedef struct{
	float32 alpha;
	float32 beta;
	float32 zero;
	float32 sin;
	float32 cos;
	float32 d;
	float32 q;
	float32 z;
}PARK_F;

//*********** Function Declarations *******//
void PARK_F_init(PARK_F *v);
void PARK_F_FUNC(PARK_F *v);

//*********** Macro Definition ***********//
#define PARK_F_MACRO(v) 				\
	v.d= v.alpha*v.cos + v.beta*v.sin;	\
	v.q=-v.alpha*v.sin + v.beta*v.cos;	\
	v.z=v.zero;


#endif /* PARK_F_H_ */
