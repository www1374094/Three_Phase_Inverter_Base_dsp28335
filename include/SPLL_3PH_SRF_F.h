#ifndef SPLL_3ph_SRF_F_H_
#define SPLL_3ph_SRF_F_H_

//*********** Structure Definition ********//
typedef struct{
	float32	B1_lf;
	float32	B0_lf;
	float32	A1_lf;
}SPLL_3ph_SRF_F_LPF_COEFF;

typedef struct{
	float32 v_q[2];
	float32 ylf[2];
	float32 fo; // output frequency of PLL
	float32 fn; //nominal frequency
	float32 theta[2];
	float32 delta_T;
	SPLL_3ph_SRF_F_LPF_COEFF lpf_coeff;
}SPLL_3ph_SRF_F;

//*********** Function Declarations *******//
void SPLL_3ph_SRF_F_init(int Grid_freq, float32 DELTA_T, SPLL_3ph_SRF_F *spll);
void SPLL_3ph_SRF_F_FUNC(SPLL_3ph_SRF_F *spll_obj);

//*********** Macro Definition ***********//
#define SPLL_3ph_SRF_F_MACRO(spll_obj)																							\
	/*update v_q[0] before calling the routine*/																				\
	/* Loop Filter*/                     																						\
	spll_obj.ylf[0]=spll_obj.ylf[1] + (spll_obj.lpf_coeff.B0_lf*spll_obj.v_q[0]) + (spll_obj.lpf_coeff.B1_lf*spll_obj.v_q[1]);	\
	spll_obj.ylf[1]=spll_obj.ylf[0];																							\
	spll_obj.v_q[1]=spll_obj.v_q[0];																							\
	spll_obj.ylf[0]=(spll_obj.ylf[0]>(float32)(200.0))?(float32)(200.0):spll_obj.ylf[0];											\
	/* VCO                             */																						\
	spll_obj.fo=spll_obj.fn + spll_obj.ylf[0];																					\
	spll_obj.theta[0]=spll_obj.theta[1] + ((spll_obj.fo*spll_obj.delta_T)*(float32)(2*3.1415926));								\
	if(spll_obj.theta[0] > (float32)(2*3.1415926))																				\
		spll_obj.theta[0]=spll_obj.theta[0] - (float32)(2*3.1415926);																\
	spll_obj.theta[1]=spll_obj.theta[0];																						\


#endif /* SPLL_3ph_SRF_F_H_ */
