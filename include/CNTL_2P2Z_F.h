#ifndef CNTL_2P2Z_F_H_
#define CNTL_2P2Z_F_H_

//*********** Structure Definition ********//

// Second order control law using an IIR filter structure with programmable output saturation.
// This macro uses CNTL_2P2Z_F structures to store coefficients & internal values.
// The structures should be initialized with the supplied CNTL_2P2Z_F_INIT macro.
// Within the structure the Max & Min parameters are the output bounds where as the IMin parameter
// is used for saturating the lower bound while keeping an internal history.  The IMin parameter
// should not be lower than -0.9.

typedef struct {
	// Coefficients
	float32 Coeff_B2;
	float32 Coeff_B1;
	float32 Coeff_B0;
	float32 Coeff_A2;
	float32 Coeff_A1;

	// Output saturation limits
	float32 Max;
	float32 IMin;
	float32 Min;
} CNTL_2P2Z_F_COEFFS;

typedef struct {
	float32 Out1;
	float32 Out2;
	// Internal values
	float32 Errn;
	float32 Errn1;
	float32 Errn2;
	// Inputs
	float32 Ref;
	float32 Fdbk;
	// Output values
	float32 Out;
} CNTL_2P2Z_F_VARS;

//*********** Function Declarations *******//
void CNTL_2P2Z_F_COEFFS_init(CNTL_2P2Z_F_COEFFS *v);
void CNTL_2P2Z_F_VARS_init(CNTL_2P2Z_F_VARS *k);
void CNTL_2P2Z_F_FUNC(CNTL_2P2Z_F_COEFFS *v, CNTL_2P2Z_F_VARS *k);
void CNTL_2P2Z_F_ASM(CNTL_2P2Z_F_COEFFS *v, CNTL_2P2Z_F_VARS *k);

//*********** Macro Definition ***********//
#define CNTL_2P2Z_F_MACRO(v, k)																\
	/* Calculate error */																	\
	k.Errn = k.Ref - k.Fdbk;																\
	k.Out = (v.Coeff_A2*k.Out2) + (v.Coeff_A1 *k.Out1) + (v.Coeff_B2 *k.Errn2)				\
					+ (v.Coeff_B1 * k.Errn1) + (v.Coeff_B0 * k.Errn);						\
	/* Update error values */																\
	k.Errn2 = k.Errn1;																		\
	k.Errn1 = k.Errn;																		\
	/* Determine new output */																\
	k.Out = (k.Out < v.Max) ? k.Out : v.Max;												\
	k.Out = (k.Out > v.IMin) ? k.Out : v.IMin;												\
	/* Store outputs */																		\
	k.Out2 = k.Out1;																		\
	k.Out1 = k.Out;																			\
	/* Saturated output */																	\
	k.Out = ((k.Out > v.Min) ? k.Out : v.Min);


#endif /* CNTL_2P2Z_F_H_ */
