#ifndef IPARK_F_H_
#define IPARK_F_H_

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
}iPARK_F;

//*********** Function Declarations *******//
void iPARK_F_init(iPARK_F *v);
void iPARK_F_FUNC(iPARK_F *v);

//*********** Macro Definition ***********//
#define iPARK_F_MACRO(v) 			\
	v.alpha = v.d*v.cos - v.q*v.sin;\
	v.beta  = v.d*v.sin + v.q*v.cos;\
	v.zero  = v.z;


#endif /* iPARK_F_H_ */
