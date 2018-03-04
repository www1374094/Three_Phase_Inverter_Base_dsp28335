#ifndef DQ0_ABC_F_H
#define DQ0_ABC_F_H

//*********** Structure Definition ********//
typedef struct{
	float32 a;
	float32 b;
	float32 c;
	float32 alpha;
	float32 beta;
	float32 sin;
	float32 cos;
	float32 d;
	float32 q;
	float32 z;
}DQ0_ABC_F;

//*********** Function Declarations *******//
void DQ0_ABC_F_init(DQ0_ABC_F *v);
void DQ0_ABC_F_FUNC(DQ0_ABC_F *v);

//*********** Macro Definition ***********//
#define DQ0_ABC_F_MACRO(v) 							\
	v.alpha = v.d*v.cos - v.q*v.sin;				\
	v.beta  = v.d*v.sin + v.q*v.cos;				\
	v.a = v.alpha + 0.5*v.z;						\
	v.b = -0.5*v.alpha + 0.8660254*v.beta + 0.5*v.z;\
	v.c = -0.5*v.alpha - 0.8660254*v.beta + 0.5*v.z;


#endif /* DQ0_ABC_F_H_ */
