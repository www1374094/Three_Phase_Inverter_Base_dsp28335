#ifndef ABC_DQ0_POS_F_H
#define ABC_DQ0_POS_F_H

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
}ABC_DQ0_POS_F;

//*********** Function Declarations *******//
void ABC_DQ0_POS_F_init(ABC_DQ0_POS_F *v);
void ABC_DQ0_POS_F_FUNC(ABC_DQ0_POS_F *v);

//*********** Macro Definition ************//
#define ABC_DQ0_POS_F_MACRO(v) 						\
	v.alpha=(0.6666666667)*(v.a - 0.5*(v.b + v.c));	\
	v.beta=(0.57735026913)*(v.b - v.c);				\
	v.z =0.57735026913*(v.a + v.b + v.c);			\
	v.d=v.alpha*v.cos + v.beta*v.sin;				\
	v.q=-v.alpha*v.sin + v.beta*v.cos;


#endif /* ABC_DQ0_POS_F_H_ */
