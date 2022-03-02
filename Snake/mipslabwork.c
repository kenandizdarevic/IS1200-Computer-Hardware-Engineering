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
#include <stdlib.h>
#include <stdio.h>
#include "displaysetup.h"

       
int gameStarted = 0;
int snakeX = 15;
int snakeY = 15;
int foodX = 30;
int foodY = 30;
int score = 0;
int speed = 0;

void resetGame(){
  int gameStarted = 0;
  int snakeX = 15;
  int snakeY = 15;
  int foodX = 30;
  int foodY = 30;
  int score = 0;
  int speed = 0;
}

/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}

/* Lab-specific initialization goes here */
void labinit( void ){
  TRISF &= 0x2;
  TRISD &= 0x0070;
 
 /* TIMER */
  PR2 = ((80000000/256)/10);    
  TMR2 = 0;                     
  T2CON = 0x8070;            
  return;
}


  uint8_t game[128*32] = {0}; 

  void clear(){    
   int i;     
    for (i = 0; i < sizeof(game); i++){ 
      game[i] = 0; 
    } 
  } 

  void displayScreen(uint8_t arr[]) {     
    int i, j;     
    for(i = 0; i < 4; i++)     {         
      DISPLAY_COMMAND_DATA_PORT &= ~DISPLAY_COMMAND_DATA_MASK;         
      spi_send_recv(0x22);         
      spi_send_recv(i);         
      spi_send_recv(0 & 0xF);         
      spi_send_recv(0x10 | ((0 >> 4) & 0xF));         
      DISPLAY_COMMAND_DATA_PORT |= DISPLAY_COMMAND_DATA_MASK;         
      for(j = 0; j < 128; j++)             
        spi_send_recv(arr[i*128 + j]);     
   } 
 }    

void set_pixel(int x, int y){
  short offset = 0;
  if(y > 0){
    offset = y / 8;
  }
  game[offset * 128 + x] |= 1 << (y - offset * 8);
}

void move_right(){
  snakeX++;
  speed = 1;
}
void move_up(){
  snakeY--;
  speed = 32;
}
void move_down(){
  snakeY++;
  speed = -32;
}
void move_left(){
  snakeX--;
  
}

void movement(){
  clear();
  int button = getbtns();
  int button1 = getbtn1();
  if(button){
    if(button == 4){
     move_left();
    }
    if(button & 1){
      move_up();
    }
    if(button & 2){
      move_down();
    }
  }
  if(button1){
    move_right();
  }
}


void food(){
  set_pixel(foodX, foodY);
  score++;
}

void startup_screen(){
  display_update();
  display_string(0, "SNAKE");
  display_string(2, "Press BTN1 to");
  display_string(3, "PLAY ");
 
 int button1 = getbtn1();
  if(button1){
    gameStarted = 1;
  }
}



/* This function is called repetitively from the main program */
void snake( void )
{
  if(!gameStarted){
    startup_screen();
  }
  if(gameStarted){
    delay(50);
    movement();
    food();
    set_pixel(snakeX, snakeY);
  
    displayScreen(game);
  
  }
}
