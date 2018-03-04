#include "Solar_F.h"

//*********** Structure Init Function ****//
void SPLL_1ph_SOGI_F_init(int Grid_freq, float32 DELTA_T, SPLL_1ph_SOGI_F *spll_obj)
{
	spll_obj->u[0]=(float32)(0.0);
	spll_obj->u[1]=(float32)(0.0);
	spll_obj->u[2]=(float32)(0.0);
	
	spll_obj->osg_u[0]=(float32)(0.0);
	spll_obj->osg_u[1]=(float32)(0.0);
	spll_obj->osg_u[2]=(float32)(0.0);
	
	spll_obj->osg_qu[0]=(float32)(0.0);
	spll_obj->osg_qu[1]=(float32)(0.0);
	spll_obj->osg_qu[2]=(float32)(0.0);
	
	spll_obj->u_Q[0]=(float32)(0.0);
	spll_obj->u_Q[1]=(float32)(0.0);
	
	spll_obj->u_D[0]=(float32)(0.0);
	spll_obj->u_D[1]=(float32)(0.0);
	
	spll_obj->ylf[0]=(float32)(0.0);
	spll_obj->ylf[1]=(float32)(0.0);
	
	spll_obj->fo=(float32)(0.0);
	spll_obj->fn=(float32)(Grid_freq);
	
	spll_obj->theta[0]=(float32)(0.0);
	spll_obj->theta[1]=(float32)(0.0);
	
	spll_obj->sin=(float32)(0.0);
	spll_obj->cos=(float32)(0.0);

	// loop filter coefficients for 20kHz
	spll_obj->lpf_coeff.B0_lf=(float32)(166.9743);
	spll_obj->lpf_coeff.B1_lf=(float32)(-166.266);
	spll_obj->lpf_coeff.A1_lf=(float32)(-1.0);
	
	spll_obj->delta_T=DELTA_T;
}

//*********** Structure Coeff Update *****//
void SPLL_1ph_SOGI_F_coeff_update(float32 delta_T, float32 wn, SPLL_1ph_SOGI_F *spll)
{
	float32 osgx,osgy,temp;
	spll->osg_coeff.osg_k=(float32)(0.5);
	osgx=(float32)(2.0*0.5*wn*delta_T);
	spll->osg_coeff.osg_x=(float32)(osgx);
	osgy=(float32)(wn*delta_T*wn*delta_T);
	spll->osg_coeff.osg_y=(float32)(osgy);
	temp=(float32)1.0/(osgx+osgy+4.0);
	spll->osg_coeff.osg_b0=((float32)osgx*temp);
	spll->osg_coeff.osg_b2=((float32)(-1.0)*spll->osg_coeff.osg_b0);
	spll->osg_coeff.osg_a1=((float32)(2.0*(4.0-osgy))*temp);
	spll->osg_coeff.osg_a2=((float32)(osgx-osgy-4)*temp);
	spll->osg_coeff.osg_qb0=((float32)(0.5*osgy)*temp);
	spll->osg_coeff.osg_qb1=(spll->osg_coeff.osg_qb0*(float32)(2.0));
	spll->osg_coeff.osg_qb2=spll->osg_coeff.osg_qb0;
}

//*********** Function Definition ********//
void SPLL_1ph_SOGI_F_FUNC(SPLL_1ph_SOGI_F *spll_obj)
{
	// Update the spll_obj->u[0] with the grid value before calling this routine

	//-------------------------------//
	// Orthogonal Signal Generator 	 //
	//-------------------------------//
	spll_obj->osg_u[0]=(spll_obj->osg_coeff.osg_b0*(spll_obj->u[0]-spll_obj->u[2])) + (spll_obj->osg_coeff.osg_a1*spll_obj->osg_u[1]) + (spll_obj->osg_coeff.osg_a2*spll_obj->osg_u[2]);

	spll_obj->osg_u[2]=spll_obj->osg_u[1];
	spll_obj->osg_u[1]=spll_obj->osg_u[0];

	spll_obj->osg_qu[0]=(spll_obj->osg_coeff.osg_qb0*spll_obj->u[0]) + (spll_obj->osg_coeff.osg_qb1*spll_obj->u[1]) + (spll_obj->osg_coeff.osg_qb2*spll_obj->u[2]) + (spll_obj->osg_coeff.osg_a1*spll_obj->osg_qu[1]) + (spll_obj->osg_coeff.osg_a2*spll_obj->osg_qu[2]);

	spll_obj->osg_qu[2]=spll_obj->osg_qu[1];
	spll_obj->osg_qu[1]=spll_obj->osg_qu[0];

	spll_obj->u[2]=spll_obj->u[1];
	spll_obj->u[1]=spll_obj->u[0];
	
	//-------------------------------------------------------//
	// Park Transform from alpha beta to d-q axis 			 //
	//-------------------------------------------------------//
	spll_obj->u_Q[0]=(spll_obj->cos*spll_obj->osg_u[0]) + (spll_obj->sin*spll_obj->osg_qu[0]);
	spll_obj->u_D[0]=(spll_obj->cos*spll_obj->osg_qu[0]) - (spll_obj->sin*spll_obj->osg_u[0]);

	//---------------------------------//
	// Loop Filter                     //
	//---------------------------------//
	spll_obj->ylf[0]=spll_obj->ylf[1] + (spll_obj->lpf_coeff.B0_lf*spll_obj->u_Q[0]) + (spll_obj->lpf_coeff.B1_lf*spll_obj->u_Q[1]);
	spll_obj->ylf[1]=spll_obj->ylf[0];

	spll_obj->u_Q[1]=spll_obj->u_Q[0];

	//---------------------------------//
	// VCO                             //
	//---------------------------------//
	spll_obj->fo=spll_obj->fn+spll_obj->ylf[0];
	
	spll_obj->theta[0]=spll_obj->theta[1] + (spll_obj->fo*spll_obj->delta_T)*(float32)(2.0*3.1415926);
	if(spll_obj->theta[0]>(float32)(2.0*3.1415926))
		spll_obj->theta[0]=(float32)(0.0);
	
	spll_obj->theta[1]=spll_obj->theta[0];
	
	spll_obj->sin=(float32)sin(spll_obj->theta[0]);
	spll_obj->cos=(float32)cos(spll_obj->theta[0]);
}

