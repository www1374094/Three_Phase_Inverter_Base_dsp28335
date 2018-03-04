#include "Solar_F.h"

//*********** Structure Init Function ****//
void SPLL_3ph_SRF_F_init(int Grid_freq, float32 DELTA_T, SPLL_3ph_SRF_F *spll_obj)
{
	spll_obj->v_q[0]=(float32)(0.0);
	spll_obj->v_q[1]=(float32)(0.0);

	spll_obj->ylf[0]=(float32)(0.0);
	spll_obj->ylf[1]=(float32)(0.0);

	spll_obj->fo=(float32)(0.0);
	spll_obj->fn=(float32)(Grid_freq);

	spll_obj->theta[0]=(float32)(0.0);
	spll_obj->theta[1]=(float32)(0.0);

	// loop filter coefficients for 20kHz
	spll_obj->lpf_coeff.B0_lf=(float32)(166.9743);
	spll_obj->lpf_coeff.B1_lf=(float32)(-166.266);
	spll_obj->lpf_coeff.A1_lf=(float32)(-1.0);

	spll_obj->delta_T=(float32)DELTA_T;
}

//*********** Function Definition ********//
void SPLL_3ph_SRF_F_FUNC(SPLL_3ph_SRF_F *spll_obj)
{
	//update v_q[0] before calling the routine
	//---------------------------------//
	// Loop Filter                     //
	//---------------------------------//
	spll_obj->ylf[0]=spll_obj->ylf[1] + (spll_obj->lpf_coeff.B0_lf*spll_obj->v_q[0]) + (spll_obj->lpf_coeff.B1_lf*spll_obj->v_q[1]);
	spll_obj->ylf[1]=spll_obj->ylf[0];
	spll_obj->v_q[1]=spll_obj->v_q[0];

	spll_obj->ylf[0]=(spll_obj->ylf[0]>(float32)(200.0))?(float32)(200.0):spll_obj->ylf[0];
	//---------------------------------//
	// VCO                             //
	//---------------------------------//
	spll_obj->fo=spll_obj->fn + spll_obj->ylf[0];

	spll_obj->theta[0]=spll_obj->theta[1] + ((spll_obj->fo*spll_obj->delta_T)*(float32)(2*3.1415926));
	if(spll_obj->theta[0] > (float32)(2*3.1415926))
		spll_obj->theta[0]=spll_obj->theta[0] - (float32)(2*3.1415926);

	spll_obj->theta[1]=spll_obj->theta[0];
}

