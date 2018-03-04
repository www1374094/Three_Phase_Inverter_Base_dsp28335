#ifndef SPLL_1ph_SOGI_F_H
#define SPLL_1ph_SOGI_F_H

//*********** Structure Definition ********//
typedef struct{
	float32	osg_k;
	float32	osg_x;
	float32	osg_y;
	float32	osg_b0;
	float32	osg_b2;
	float32	osg_a1;
	float32	osg_a2;
	float32	osg_qb0;
	float32	osg_qb1;
	float32	osg_qb2;
}SPLL_1ph_SOGI_F_OSG_COEFF;

typedef struct{
	float32	B1_lf;
	float32	B0_lf;
	float32	A1_lf;
}SPLL_1ph_SOGI_F_LPF_COEFF;

typedef struct{
	float32	u[3];  // Ac Input
	float32   osg_u[3];
	float32   osg_qu[3];
	float32   u_Q[2];
	float32   u_D[2];
	float32   ylf[2];
	float32   fo; // output frequency of PLL
	float32   fn; //nominal frequency
	float32	theta[2];
	float32	cos;
	float32	sin;
	float32   delta_T;
	SPLL_1ph_SOGI_F_OSG_COEFF osg_coeff;
	SPLL_1ph_SOGI_F_LPF_COEFF lpf_coeff;
}SPLL_1ph_SOGI_F;

//*********** Function Declarations *******//
void SPLL_1ph_SOGI_F_init(int Grid_freq, float32 DELTA_T, SPLL_1ph_SOGI_F *spll);
void SPLL_1ph_SOGI_F_coeff_update(float32 delta_T, float32 wn, SPLL_1ph_SOGI_F *spll);
void SPLL_1ph_SOGI_F_FUNC(SPLL_1ph_SOGI_F *spll1);

//*********** Macro Definition ***********//
#define SPLL_1ph_SOGI_F_MACRO(v) 																																					\
	v.osg_u[0]=(v.osg_coeff.osg_b0*(v.u[0]-v.u[2])) + (v.osg_coeff.osg_a1*v.osg_u[1]) + (v.osg_coeff.osg_a2*v.osg_u[2]); 															\
	v.osg_u[2]=v.osg_u[1];																																							\
	v.osg_u[1]=v.osg_u[0];																																							\
	v.osg_qu[0]=(v.osg_coeff.osg_qb0*v.u[0]) + (v.osg_coeff.osg_qb1*v.u[1]) + (v.osg_coeff.osg_qb2*v.u[2]) + (v.osg_coeff.osg_a1*v.osg_qu[1]) + (v.osg_coeff.osg_a2*v.osg_qu[2]); 	\
	v.osg_qu[2]=v.osg_qu[1];																																						\
	v.osg_qu[1]=v.osg_qu[0];																																						\
	v.u[2]=v.u[1];																																									\
	v.u[1]=v.u[0];																																									\
	v.u_Q[0]=(v.cos*v.osg_u[0]) + (v.sin*v.osg_qu[0]);																																\
	v.u_D[0]=(v.cos*v.osg_qu[0]) - (v.sin*v.osg_u[0]);																																\
	v.ylf[0]=v.ylf[1] + (v.lpf_coeff.B0_lf*v.u_Q[0]) + (v.lpf_coeff.B1_lf*v.u_Q[1]);																								\
	v.ylf[1]=v.ylf[0];																																								\
	v.u_Q[1]=v.u_Q[0];																																								\
	v.fo=v.fn + v.ylf[0]; 																																							\
	v.theta[0]=v.theta[1] + ((v.fo*v.delta_T)*(float32)(2.0*3.1415926)); 																												\
	if(v.theta[0]>(float32)(2.0*3.1415926)) 																																			\
		v.theta[0]=(float32)(0.0); 																																					\
	v.theta[1]=v.theta[0]; 																																							\
	v.sin=(float32)(sin(v.theta[0])); 																																				\
	v.cos=(float32)(cos(v.theta[0]));


#endif /* SPLL_1ph_SOGI_F_H_ */
