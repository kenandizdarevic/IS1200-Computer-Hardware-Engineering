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

int mytime = 0x5957;

char textstring[] = "text, more text, and even more text!";

volatile int* portE = (volatile int*) 0xbf886110;// portE is used in multiple function, therefor global

/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
  volatile int* trisE = (volatile int*) 0xbf886100; // initialize trisE 

  *trisE = *trisE & 0xffffff00;  // set bits 7 - 0 to outputs
  *portE = 0;                    // turns of all the leds

  TRISD &= 0x0fe0;              // initialize port D, 11 - 5 as inputs
  
  /* Sätter ihop timern, den är 16-bitar */
  PR2 = ((80000000/256)/10);    // Vi får 100 ms, prescale 256
  TMR2 = 0;                     // Clearar timern
  T2CONSET = 0x8070;               // Kontrollregister, konfigurerar precalingen. Start & stop för timer

  return;
}

int btns = 0;
int sw = 0;
int timeoutcount = 0;
/* This function is called repetitively from the main program */
void labwork( void ){ // Timer to interuption flag, T2IF
  
  if(IFS(0) & 0x0100){ // IFS hittas på bit 8
    IFS(0) = IFS(0) & 0xfffffeff; // bitwise-and med 1 på alla bitar förutom bit 8 som är 0, set till 0 
    timeoutcount++;
  }

  if(timeoutcount == 10){
    time2string( textstring, mytime );
    display_string( 3, textstring );
    display_update();
    tick( &mytime );
    (*portE)++; // increment portE with  1
    display_image(96, icon);
    timeoutcount = 0;
  }
  

 


  btns = getbtns();
  if(btns){
    sw = getsw();
    if(btns & 4){ // Button 4
      mytime = (mytime & 0x0fff);
      mytime = (sw << 12) | mytime;
    }
    if(btns & 2){ // Button 3
      mytime = (mytime & 0xf0ff);
      mytime = (sw << 8) | mytime ;
    }
    if(btns & 1){ // Button 2
      mytime = (mytime & 0xff0f);
      mytime = (sw << 4) | mytime;
    }
  }
}
