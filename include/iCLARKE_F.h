#ifndef ICLARKE_F_H_
#define ICLARKE_F_H_

//*********** Structure Definition ********//
typedef struct{
	float32 a;
	float32 b;
	float32 c;
	float32 alpha;
	float32 beta;
	float32 zero;
}iCLARKE_F;

//*********** Function Declarations *******//
void iCLARKE_F_init(iCLARKE_F *v);
void iCLARKE_F_FUNC(iCLARKE_F *v);

//*********** Macro Definition ***********//
#define iCLARKE_F_MACRO(v)								\
	v.a = v.alpha + 0.5*v.zero;							\
	v.b = -0.5*v.alpha + 0.8660254*v.beta + 0.5*v.zero;	\
	v.c = -0.5*v.alpha - 0.8660254*v.beta + 0.5*v.zero;


#endif /* ICLARKE_F_H_ */
