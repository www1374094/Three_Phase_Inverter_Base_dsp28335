#include "Solar_F.h"

//*********** Structure Init Function ****//
void MPPT_INCC_F_init(MPPT_INCC_F *v)
{
	v->Ipv=0;
	v->Vpv=0;
	v->IpvH=(1.65);
	v->IpvL=0;
	v->VpvH=0;
	v->VpvL=0;
	v->MaxVolt=0;
	v->MinVolt=0;
	v->Stepsize=0;
	v->VmppOut=0;
	v->Cond=0;
	v->IncCond=0;
	v->DeltaV=0;
	v->DeltaI=0;
	v->VpvOld=0;
	v->IpvOld=0;
	v->StepFirst=(0.02);
	v->mppt_enable=1;
	v->mppt_first=1;
}

//*********** Function Definition ********//
void MPPT_INCC_F_FUNC(MPPT_INCC_F *v)
{
	if (v->mppt_enable==1)
	{	/*MPPT mode enable*/
		if (v->mppt_first == 1)
		{
			v->VmppOut= v->Vpv - v->StepFirst;
	    	v->VpvOld=v->Vpv;
	    	v->IpvOld=v->Ipv;
			v->mppt_first=0;
		}
		else
		{
			v->DeltaV = v->Vpv-v->VpvOld ; 				/* PV voltage change */
	    	v->DeltaI = v->Ipv-v->IpvOld ; 				/* PV current change */
//	   		if(v->DeltaV <v->VpvH && v->DeltaV >-v->VpvL )  /* Tolerence limits PV Voaltge Variation */
//	    	v->DeltaV= 0;
//	   		if(v->DeltaI <v->IpvH && v->DeltaI >-v->IpvL )  /* Tolerence limits PV current Variation */
//	    	v->DeltaI = 0;
	    	if(v->DeltaV == 0)    						/* DeltaV=0 */
			{
				if(v->DeltaI !=0 )    					/* dI=0 operating at MPP */
				{
					if ( v->DeltaI > 0 )  				/* climbing towards MPP */
					{v->VmppOut=v->Vpv+v->Stepsize;}		/* Increment Vref */
					else
					{v->VmppOut=v->Vpv-v->Stepsize;} 		/* Decrement Vref */
				}
			}
	    	else
			{
	    	 	v->Cond = v->Ipv*__einvf32(v->Vpv);					/*Cond =-(v->Ipv<<10)/v->Vpv;*/
	    	 	v->IncCond = v->DeltaI*__einvf32(v->DeltaV);			/*IncCond =(DeltaI<<10)/DeltaV;*/
	       		if (v->IncCond != v->Cond)				/* Operating at MPP */
				{
					if (v->IncCond > (-v->Cond))			/* left of MPP */
					{
					v->VmppOut=v->Vpv+v->Stepsize;			/* change Vref */
					}
					else								/* Right of MPP */
					{
					v->VmppOut=v->Vpv-v->Stepsize;			/* change Vref */
					}
	        	}
			}
			v->VpvOld = v->Vpv;
			v->IpvOld = v->Ipv;
		}
	}
}

