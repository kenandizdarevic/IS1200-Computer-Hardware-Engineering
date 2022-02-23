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

char[12] prime = "Din Mamma!";
int mytime = 0x5957;

char textstring[] = "text, more text, and even more text!";

volatile int* portE = (volatile int*) 0xbf886110;// portE is used in multiple function, therefor global
int timeoutcount = 0; 

/* Interrupt Service Routine */
void user_isr( void )
{
  if(IFS(0) & 0x0100){ // IFS hittas på bit 8
      IFS(0) = IFS(0) & 0xfffffeff; // bitwise-and med 1 på alla bitar förutom bit 8 som är 0, set till 0 
      timeoutcount++;
  }

  if(timeoutcount == 10){
    time2string( textstring, mytime );
    display_string( 3, textstring);
    display_update();
    tick( &mytime );
    timeoutcount = 0;
  }
}

/* Lab-specific initialization goes here */
void labinit( void )
{
  volatile int* trisE = (volatile int*) 0xbf886100; // initialize trisE 

  *trisE = *trisE & 0xffffff00;  // set bits 7 - 0 to outputs
  *portE = 0;                   // turns of all the leds

  TRISD &= 0x0fe0;              // initialize port D, 11 - 5 as inputs
  
  PR2 = ((80000000/256)/10);    // Vi får 100 ms, prescale 256
  TMR2 = 0;                     // Clearar timern
  T2CONSET = 0x8070;               // Kontrollregister, konfigurerar precalingen. Start & stop för timer


  IEC(0) = IEC(0) | 0x0100;     // Enable interrupt for Timer 2
  IPC(2) = IPC(2) | 0x001C;
  enable_interrupt();


  return;
}

/* This function is called repetitively from the main program */
void labwork( void )
{
  prime = nextprime( prime );
  display_string( 0, itoaconv( prime ) );
  display_update;
}
