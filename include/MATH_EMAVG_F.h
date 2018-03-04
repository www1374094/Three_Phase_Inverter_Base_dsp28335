#ifndef MATH_EMAVG_F_H_
#define MATH_EMAVG_F_H_

//*********** Structure Definition ********//

// Performs exponential moving average calculation.  This macro requires the use of the
// MATH_EMAVG_F structure.  The structure should be initialized with the MATH_EMAVG_F_INIT
// macro.

typedef struct {
	float32 In;
	float32 Out;
	float32 Multiplier;
} MATH_EMAVG_F;

//*********** Function Declarations *******//
void MATH_EMAVG_F_init(MATH_EMAVG_F *v);
void MATH_EMAVG_F_FUNC(MATH_EMAVG_F *v);

//*********** Macro Definition ***********//
#define MATH_EMAVG_F_MACRO(v)						\
	v.Out = ((v.In - v.Out)*v.Multiplier) + v.Out;	\


#endif /* MATH_EMAVG_F_H_ */
