#ifndef SOLAR_F_H
#define SOLAR_F_H

#ifndef F28_DATA_TYPES
#define F28_DATA_TYPES
#ifndef DSP28_DATA_TYPES
#define DSP28_DATA_TYPES
typedef int             	int16;
typedef long            	int32;
typedef long long			int64;
typedef unsigned long long	Uint64;
typedef float           	float32;
typedef long double     	float64;
#endif
#endif

#ifndef _TI_STD_TYPES
#define _TI_STD_TYPES
typedef int             Int;
typedef unsigned        Uns;
typedef char            Char;
typedef char            *String;
typedef void            *Ptr;
typedef unsigned short	Bool;

typedef unsigned long   Uint32;
typedef unsigned int    Uint16;
typedef unsigned char   Uint8;

typedef long            Int32;
typedef int             Int16;
typedef char            Int8;
#endif

#include "math.h"

#include "ABC_DQ0_POS_F.h"
#include "ABC_DQ0_NEG_F.h"
#include "CLARKE_F.h"
#include "CNTL_2P2Z_F.h"
#include "CNTL_3P3Z_F.h"
#include "CNTL_PI_F.h"
#include "DLOG_1CH_F.h"
#include "DLOG_4CH_F.h"
#include "DQ0_ABC_F.h"
#include "iCLARKE_F.h"
#include "iPARK_F.h"
#include "MATH_EMAVG_F.h"
#include "MPPT_INCC_F.h"
#include "MPPT_INCC_I_F.h"
#include "MPPT_PNO_F.h"
#include "NOTCH_FLTR_F.h"
#include "PARK_F.h"
#include "PID_GRANDO_F.h"
#include "RAMPGEN_F.h"
#include "SINEANALYZER_DIFF_F.h"
#include "SINEANALYZER_DIFF_wPWR_F.h"
#include "SPLL_1ph_F.h"
#include "SPLL_1ph_SOGI_F.h"
#include "SPLL_3PH_DDSRF_F.h"
#include "SPLL_3PH_SRF_F.h"


#endif
