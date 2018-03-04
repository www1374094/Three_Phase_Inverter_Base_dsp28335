/*
// TI File $Revision: /main/3 $
// Checkin $Date: July 9, 2008   14:12:45 $
//###########################################################################
//
// FILE:    28335_RAM_lnk.cmd
//
// TITLE:   Linker Command File For fastRTS examples that run out of RAM
//
// NOTE; The example project uses memory protected by the
//       Code Security Module (CSM).  Make sure the CSM is
//       unlocked before you load the project.  One quick way
//       to do this on an erased device is to open a memory
//       window to the CSM password locations.  If these locations
//       read back 0xFFFF (or non-zero), then the CSM is unlocked:
//
//      Device    Password locations
//      28335:    0x33FFF8 - 0x33FFFF
//
//###########################################################################
// $TI Release: Release 1.5c $
// $Release Date: June 8, 2010 $
//###########################################################################
*/




MEMORY
{
PAGE 0 :
   BEGIN      : origin = 0x000000, length = 0x000002     /* Boot to M0 will go here                      */
   BOOT_RSVD  : origin = 0x000002, length = 0x00004E     /* Part of M0, BOOT rom will use this for stack */
   RAMM0      : origin = 0x000050, length = 0x0003B0

   RAML0      : origin = 0x008000, length = 0x001000
   RAML1L2    : origin = 0x009000, length = 0x002000
   RAML3      : origin = 0x00B000, length = 0x001000
   ZONE7A     : origin = 0x200000, length = 0x00FC00    /* XINTF zone 7 - program space */
   CSM_RSVD   : origin = 0x33FF80, length = 0x000076     /* Part of FLASHA.  Program with all 0x0000 when CSM is in use. */
   CSM_PWL    : origin = 0x33FFF8, length = 0x000008     /* Part of FLASHA.  CSM password locations in FLASHA            */
   ADC_CAL    : origin = 0x380080, length = 0x000009
   RESET      : origin = 0x3FFFC0, length = 0x000002

   /* IQTABLES and IQTABLES2 are part of the boot ROM.
      The boot ROM is available in both program or
      data space so this can be defined on page 0 or page 1
   */

   IQTABLES   : origin = 0x3FE000, length = 0x000b50
   IQTABLES2  : origin = 0x3FEB50, length = 0x00008c
   FPUTABLES  : origin = 0x3FEBDC, length = 0x0006A0
   BOOTROM    : origin = 0x3FF27C, length = 0x000D44


PAGE 1 :
   RAMM1      : origin = 0x000400, length = 0x000400     /* on-chip RAM block M1 */
   RAML4      : origin = 0x00C000, length = 0x001000
   RAML5      : origin = 0x00D000, length = 0x001000
   RAML6      : origin = 0x00E000, length = 0x001000
   RAML7      : origin = 0x00F000, length = 0x001000
   ZONE7B     : origin = 0x20FC00, length = 0x000400     /* XINTF zone 7 - data space */
}


SECTIONS
{

   /* IQmath inclues the assembly routines in the IQmath library
      IQmathTables is used by division, IQsin, IQcos, IQatan, IQatan2
                   this is in boot ROM so we make it NOLOAD.  Using
                   the ROM version saves space at the cost of 1 cycle
                   per access (boot ROM is 1 wait).
      IQmathTablesRam is used by IQasin, IQacos, and IQexp
                   on 2833x and 2823x the IQNexpTable is in ROM so it
                   is placed in its own section.  If IQexp or IQNexp is
                   not called by the program, this will cause a linker
                   warning.
   */

/* Not used by this example

   IQmath           : > RAML1L2,   PAGE = 0
   IQmathTables     : > IQTABLES,  PAGE = 0, TYPE = NOLOAD
   IQmathTables2    : > IQTABLES2, PAGE = 0, TYPE = NOLOAD
   {
        IQmath_fpu32.lib<IQNexpTable.obj> (IQmathTablesRam)
   }
   IQmathTablesRam  : > RAML4,     PAGE = 1
*/

   FPUmathTables    : > FPUTABLES, PAGE = 0, TYPE = NOLOAD

   /* Setup for "boot to SARAM" mode:
      The codestart section (found in DSP28_CodeStartBranch.asm)
      re-directs execution to the start of user code.  */

   codestart        : > BEGIN,     PAGE = 0
   ramfuncs         : > RAML0,     PAGE = 0
   .text            : > RAML1L2,   PAGE = 0
   .cinit           : > RAML0,     PAGE = 0
   .pinit           : > RAML0,     PAGE = 0
   .switch          : > RAML0,     PAGE = 0

   .stack           : > RAMM1,     PAGE = 1
   .ebss            : > RAML4,     PAGE = 1
   .econst          : > RAML5,     PAGE = 1
   .esysmem         : > RAMM1,     PAGE = 1

   .cio             : > RAML4,     PAGE = 1
   ZONE7DATA        : > ZONE7B,    PAGE = 1

   .reset           : > RESET,     PAGE = 0, TYPE = DSECT /* not used                    */
   csm_rsvd         : > CSM_RSVD   PAGE = 0, TYPE = DSECT /* not used for SARAM examples */
   csmpasswds       : > CSM_PWL    PAGE = 0, TYPE = DSECT /* not used for SARAM examples */

   /* Allocate ADC_cal function (pre-programmed by factory into TI reserved memory) */
   .adc_cal     : load = ADC_CAL,   PAGE = 0, TYPE = NOLOAD

}

/*
//===========================================================================
// End of file.
//===========================================================================
*/
