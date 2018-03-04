#ifndef MPPT_INCC_F_H_
#define MPPT_INCC_F_H_

//*********** Structure Definition ********//
typedef struct {
	float32  Ipv;
	float32  Vpv;
	float32  IpvH;
	float32  IpvL;
	float32  VpvH;
	float32  VpvL;
	float32  MaxVolt;
	float32  MinVolt;
	float32  Stepsize;
	float32  VmppOut;
	// internal variables
	float32  Cond;
	float32  IncCond;
	float32  DeltaV;
	float32  DeltaI;
	float32  VpvOld;
	float32  IpvOld;
	float32  StepFirst;
	int16 mppt_enable;
	int16 mppt_first;
} MPPT_INCC_F;

typedef MPPT_INCC_F *mppt_incc_handle;

//*********** Function Declarations *******//
void MPPT_INCC_F_init(MPPT_INCC_F *v);
void MPPT_INCC_F_FUNC(MPPT_INCC_F *v);

//*********** Macro Definition ***********//
#define MPPT_INCC_F_MACRO(v)																		\
if (v.mppt_enable==1)																				\
{	/*MPPT mode enable*/																			\
	if (v.mppt_first == 1)																			\
	{																								\
		v.VmppOut= v.Vpv - v.StepFirst;																\
    	v.VpvOld=v.Vpv;																				\
    	v.IpvOld=v.Ipv;																				\
		v.mppt_first=0;																				\
	}                                                                       						\
	else 																							\
	{																								\
		v.DeltaV = v.Vpv-v.VpvOld ; 				/* PV voltage change */							\
    	v.DeltaI = v.Ipv-v.IpvOld ; 				/* PV current change */							\
   		/*if(v.DeltaV <v.VpvH && v.DeltaV >-v.VpvL )*/  /* Tolerence limits PV Voaltge Variation */	\
   		/*v.DeltaV= 0;*/																			\
   		/*if(v.DeltaI <v.IpvH && v.DeltaI >-v.IpvL )*/  /* Tolerence limits PV current Variation */	\
   		/*v.DeltaI = 0;*/																			\
    	if(v.DeltaV == 0)    						/* DeltaV=0 */									\
		{																							\
			if(v.DeltaI !=0 )    					/* dI=0 operating at MPP */						\
			{																						\
				if ( v.DeltaI > 0 )  				/* climbing towards MPP */						\
				{v.VmppOut=v.Vpv+v.Stepsize;}		/* Increment Vref */							\
				else																				\
				{v.VmppOut=v.Vpv-v.Stepsize;} 		/* Decrement Vref */							\
			}																						\
		}																							\
    	else  																						\
		{																							\
    	 	v.Cond = v.Ipv*__einvf32(v.Vpv);				/*Cond =-(v.Ipv<<10)/v.Vpv;*/			\
    	 	v.IncCond = v.DeltaI*__einvf32(v.DeltaV);		/*IncCond =(DeltaI<<10)/DeltaV;*/		\
       		if (v.IncCond != v.Cond)				/* Operating at MPP */							\
			{																						\
				if (v.IncCond > (-v.Cond))			/* left of MPP */								\
				{																					\
				v.VmppOut=v.Vpv+v.Stepsize;			/* change Vref */								\
				}																					\
				else								/* Right of MPP */								\
				{																					\
				v.VmppOut=v.Vpv-v.Stepsize;			/* change Vref */								\
				}																					\
        	}																						\
		}																							\
	    v.VmppOut=(v.VmppOut<v.MinVolt)?v.MinVolt: v.VmppOut;	 /*Min. MPP Current */  			\
		v.VmppOut=(v.VmppOut>v.MaxVolt)?v.MaxVolt: v.VmppOut;  /*Max. MPP Current	*/				\
		v.VpvOld = v.Vpv;																			\
		v.IpvOld = v.Ipv;																			\
	}																								\
}


#endif /*MPPT_INCC_F_H_*/
