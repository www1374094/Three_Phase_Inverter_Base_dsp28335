#ifndef CLARKE_F_H
#define CLARKE_F_H

//*********** Structure Definition ********//
typedef struct{
	float32 a;
	float32 b;
	float32 c;
	float32 alpha;
	float32 beta;
	float32 zero;
}CLARKE_F;

//*********** Function Declarations *******//
void CLARKE_F_init(CLARKE_F *v);
void CLARKE_F_FUNC(CLARKE_F *v);

//*********** Macro Definition ***********//
#define CLARKE_F_MACRO(v) 									\
	v.alpha=((0.66666666667)*(v.a - ((0.5)*(v.b+v.c))));	\
	v.beta =((0.57735026913)*(v.b - v.c));					\
	v.zero =((0.33333333333)*(v.a + v.b + v.c));


#endif /* CLARKE_F_H_ */
