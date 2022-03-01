/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog 

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */
//#include "standard.h" /* function rand() */


volatile int* portE = (volatile int*) 0xbf886110;// portE is used in multiple function, therefor global

/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
  TRISF &= 0x2;
  TRISD &= 0x0070;
 
  PR2 = ((80000000/256)/10);    
  TMR2 = 0;                     
  T2CON = 0x8070;            
  return;
}

void start(){
  display_update();
  display_string(0, "SNAKE");
  display_string(1, " ");
  display_string(2, "Press BTN1 to");
  display_string(3, "PLAY ");
}


/* This function is called repetitively from the main program */
void snake( void )
{
  start();
}
