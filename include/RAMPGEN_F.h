#ifndef RAMPGEN_F_H
#define RAMPGEN_F_H

//*********** Structure Definition ********//
typedef struct {
	float32  Freq; 		// Input: Ramp frequency (pu)
	float32  StepAngleMax;// Parameter: Maximum step angle (pu)
	float32  Angle;		// Variable: Step angle (pu)
	float32  Out;  	 	// Output: Ramp signal (pu)
} RAMPGEN_F;

//*********** Function Declarations *******//
void RAMPGEN_F_init(RAMPGEN_F *v);
void RAMPGEN_F_FUNC(RAMPGEN_F *v);

//*********** Macro Definition ***********//
#define RAMPGEN_F_MACRO(v)							\
/* Compute the angle rate */						\
	v.Angle += (v.StepAngleMax*v.Freq);				\
/* Saturate the angle rate within (0,1) */			\
	if (v.Angle>(1.0))								\
		v.Angle -= (1.0);							\
	v.Out=v.Angle;


#endif /* RAMPGEN_F_H_ */
