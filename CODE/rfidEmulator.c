/** ###################################################################
**     Filename  : rfidEmulator.C
**     Project   : rfidEmulator
**     Processor : MC56F8006_32_LQFP
**     Version   : Driver 01.14
**     Compiler  : Metrowerks DSP C Compiler
**     Date/Time : 5/13/2010, 8:52 PM
**     Abstract  :
**         Main module.
**         This module contains user's application code.
**     Settings  :
**     Contents  :
**         No public methods
**
** ###################################################################*/
/* MODULE rfidEmulator */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "TI1.h"
#include "Bit1.h"
#include "FC81.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "rfidEmulator.h"

int cnt;
int data_to_spoof[64] = {1,1,1,1,1,1,1,1,1, 1,1,1,1,0 ,1,1,1,1,0, 1,1,1,1,0 ,1,1,1,1,0, 1,1,1,1,0 ,1,1,1,1,0, 1,1,1,1,0 ,1,1,1,1,0, 1,1,1,1,0 ,1,1,1,1,0, 0,0,0,0,0};

int clock = 0;

int i = 0;

unsigned int delayTime = 256;

void main(void)
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
 
  for(;;) 
  {
    for(i = 0; i < 64; i++)
    {
      set_pin_manchester(0, data_to_spoof[i]);
      delayUS(delayTime);
    
      set_pin_manchester(1, data_to_spoof[i]);
      delayUS(delayTime); 
    }
  }
}

void delayUS(long delayTime)
{
    unsigned int curTime;
    FC81_GetTimeUS(&curTime);
	while(curTime < delayTime)
    {
    	FC81_GetTimeUS(&curTime);
    }
    FC81_Reset();
}


void set_pin_manchester(int clock_half, int signal)
{
  //manchester encoding is xoring the clock with the signal
  int man_encoded = clock_half ^ signal;
  
  //if it's 1, set the pin LOW (this will tune the antenna and the reader sees this as a high signal)
  //if it's 0, set the pin to HIGH  (this will detune the antenna and the reader sees this as a low signal)
  if(man_encoded == 1)
  {
     Bit1_ClrVal();
  }
  else
  {
    Bit1_SetVal();
  }
}

/* END rfidEmulator */
/*
** ###################################################################
**
**     This file was created by Processor Expert 3.00 [04.35]
**     for the Freescale 56800 series of microcontrollers.
**
** ###################################################################
*/
