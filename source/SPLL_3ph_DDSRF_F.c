#include "Solar_F.h"

//*********** Structure Init Function ****//
void SPLL_3ph_DDSRF_F_init(int Grid_freq, float32 DELTA_T, float32 k1, float32 k2, SPLL_3ph_DDSRF_F *spll_obj)
{
	spll_obj->d_p=(float32)(0.0);
	spll_obj->d_n=(float32)(0.0);

	spll_obj->q_p=(float32)(0.0);
	spll_obj->q_n=(float32)(0.0);

	spll_obj->d_p_decoupl=(float32)(0.0);
	spll_obj->d_n_decoupl=(float32)(0.0);

	spll_obj->q_p_decoupl=(float32)(0.0);
	spll_obj->q_n_decoupl=(float32)(0.0);

	spll_obj->d_p_decoupl_lpf=(float32)(0.0);
	spll_obj->d_n_decoupl_lpf=(float32)(0.0);

	spll_obj->q_p_decoupl_lpf=(float32)(0.0);
	spll_obj->q_n_decoupl_lpf=(float32)(0.0);

	spll_obj->y[0]=(float32)(0.0);
	spll_obj->y[1]=(float32)(0.0);

	spll_obj->x[0]=(float32)(0.0);
	spll_obj->x[1]=(float32)(0.0);

	spll_obj->w[0]=(float32)(0.0);
	spll_obj->w[1]=(float32)(0.0);

	spll_obj->z[0]=(float32)(0.0);
	spll_obj->z[1]=(float32)(0.0);

	spll_obj->k1=k1;
	spll_obj->k2=k2;

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


	spll_obj->delta_T=DELTA_T;
}

//*********** Function Definition ********//
void SPLL_3ph_DDSRF_F_FUNC(SPLL_3ph_DDSRF_F *spll_obj)
{
	// before calling this routine run the ABC_DQ0_Pos_Neg and update the values for d_p,d_n,q_p,q_n
	// and update the cos_2theta and sin_2theta values with the prev angle

	//-------------------------//
	// Decoupling Network      //
	//-------------------------//
	spll_obj->d_p_decoupl=spll_obj->d_p - (spll_obj->d_n_decoupl_lpf*spll_obj->cos_2theta) - (spll_obj->q_n_decoupl*spll_obj->sin_2theta);
	spll_obj->q_p_decoupl=spll_obj->q_p + (spll_obj->d_n_decoupl_lpf*spll_obj->sin_2theta) - (spll_obj->q_n_decoupl*spll_obj->cos_2theta);

	spll_obj->d_n_decoupl=spll_obj->d_n - (spll_obj->d_p_decoupl_lpf*spll_obj->cos_2theta) + (spll_obj->q_p_decoupl*spll_obj->sin_2theta);
	spll_obj->q_n_decoupl=spll_obj->q_n - (spll_obj->d_p_decoupl_lpf*spll_obj->sin_2theta) - (spll_obj->q_p_decoupl*spll_obj->cos_2theta);

	//-------------------------//
	// Low pass filter         //
	//-------------------------//

	spll_obj->y[1]=(spll_obj->d_p_decoupl*spll_obj->k1) - (spll_obj->y[0]*spll_obj->k2);
	spll_obj->d_p_decoupl_lpf=spll_obj->y[1] + spll_obj->y[0];
	spll_obj->y[0]=spll_obj->y[1];

	spll_obj->x[1]=(spll_obj->q_p_decoupl*spll_obj->k1) - (spll_obj->x[0]*spll_obj->k2);
	spll_obj->q_p_decoupl_lpf=spll_obj->x[1] + spll_obj->x[0];
	spll_obj->x[0]=spll_obj->x[1];

	spll_obj->w[1]=(spll_obj->d_n_decoupl*spll_obj->k1) - (spll_obj->w[0]*spll_obj->k2);
	spll_obj->d_n_decoupl_lpf=spll_obj->w[1] + spll_obj->w[0];
	spll_obj->w[0]=spll_obj->w[1];

	spll_obj->z[1]=(spll_obj->q_n_decoupl*spll_obj->k1) - (spll_obj->z[0]*spll_obj->k2);
	spll_obj->q_n_decoupl_lpf=spll_obj->z[1] + spll_obj->z[0];
	spll_obj->z[0]=spll_obj->z[1];

	spll_obj->v_q[0]=spll_obj->q_p_decoupl;

	//---------------------------------//
	// Loop Filter                     //
	//---------------------------------//
	spll_obj->ylf[0]=spll_obj->ylf[1] + (spll_obj->lpf_coeff.B0_lf*spll_obj->v_q[0]) + (spll_obj->lpf_coeff.B1_lf*spll_obj->v_q[1]);
	spll_obj->ylf[1]=spll_obj->ylf[0];
	spll_obj->v_q[1]=spll_obj->v_q[0];

	//---------------------------------//
	// VCO                             //
	//---------------------------------//
	spll_obj->fo=spll_obj->fn+spll_obj->ylf[0];

	spll_obj->theta[0]=spll_obj->theta[1] + ((spll_obj->fo*spll_obj->delta_T)*(float32)(2*3.1415926));
	if(spll_obj->theta[0]>(float32)(2*3.1415926))
		spll_obj->theta[0]=spll_obj->theta[0] - (float32)(2*3.1415926);

	spll_obj->theta[1]=spll_obj->theta[0];
}

