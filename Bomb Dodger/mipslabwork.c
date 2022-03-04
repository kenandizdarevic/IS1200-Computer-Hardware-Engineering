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
#include <stdio.h>
#include <stdlib.h>

int i,j;
int direction = 4;

int blobY;
int blobX;
int bombX;
int bombY;
int score;       

int timeoutcount;

/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}
void clear_screen(){
    for(i = 0; i < 32; i++)
        for(j = 0; j < 128; j++)
          if(!bombs[i][j] && pixel[i][j]){
              pixel[i][j] = 0;
          }
}

void save_pixel(){
  for(i = 0; i < 32; i++)
    for(j = 0; j < 128; j++)
      if(bombs[i][j]){
        pixel[i][j] = 1;
  }
}

/* Lab-specific initialization goes here */
void labinit( void ){
    TRISD &= 0xfe0;
    
    //Timer
    T2CON = 0x0;    
    TMR2 = 0x0;     
    PR2 = 0x7a12;   
    T2CONSET = 0x8070;
    
    IFSCLR(0);      
    
    IEC(0) = IEC(0) | 0x100;
    IPC(2) = IPC(2) | 0x1F;
    
    i=0;
    j=0;

    direction = 4;

    blobY = 16;
    blobX = 64;

    timeoutcount = 0;

  return;
}

void move_right(){
  blobX++;
}
void move_up(){
  blobY--;
}
void move_down(){
  blobY++;
}
void move_left(){
  blobX--;
}

void set_direction(int n){
    switch (n) {
        case 1:
            move_left();
            break;
        case 2:
            move_down();
            break;
        case 3:
            move_up();
            break;
        case 4:
            move_right();
            break;
            
        default:
            break;
    }
}
//Lights up the bombs
void airstrike(bombX,bombY){
    int x = bombX;
    int y = bombY;
    bombs[x][y] = 1; 
}
// Checks if blob has hit bomb or frame
void gameover(){
  if(blobY < 0 || blobY > 31 || blobX < 0 || blobX > 127){
    gameStarted = 2;
  }
  for(i = 0; i < 32; i++){
    for(j = 0; j < 128; j++){
      if(bombs[i][j]){
        if((i == blobY && j == blobX) || (i == blobY+1 && j == blobX) || (i == blobY+2 && j == blobX)
          || (i == blobY && j == blobX+1) || (i == blobY+1 && j == blobX+1) || (i == blobY+2 && j == blobX+1)
          || (i == blobY && j == blobX+2) || (i == blobY + 1 && j == blobX+2) || (i == blobY+2 && j == blobX+2)){
          gameStarted = 2;
        }
      }
    }
  }
}

// Sets the blob
void player(blobY,blobX){
    pixel[blobY][blobX] = 1;
    pixel[blobY][blobX+1] = 1;
    pixel[blobY][blobX+2] = 1;
    
    pixel[blobY+1][blobX] = 1;
    pixel[blobY+1][blobX+1] = 1;
    pixel[blobY+1][blobX+2] = 1;
    
    pixel[blobY+2][blobX] = 1;
    pixel[blobY+2][blobX+1] = 1;
    pixel[blobY+2][blobX+2] = 1;
}

// Spawns the bombs and increases the score
void spawn_bomb(){
  bombX = ((TMR2) % 28) + 2;
  bombY = ((TMR2) % 124) + 2;

  airstrike(bombX,bombY);
  score++;
}

//Used to reset the game when gameover
void clear_bomb(){
    for(i = 0; i < 32; i++)
        for(j = 0; j < 128; j++)
            bombs[i][j] = 0;
}

//Draws the frame
void frame(){
  //Vertical
  for(i = 0; i < 32; i++){
      pixel[i][0] = 1;
      pixel[i][127] = 1;
  }
  //Horizontal
  for(j = 0; j < 128; j++){
      pixel[0][j] = 1;
      pixel[31][j] = 1;
  }
}
//Used to reset the values and clear the screen when dead
void restart(){
  direction = 4;
  blobY = 16;
  blobX = 12;
  bombX = ((TMR2) % 28) + 2;
  bombY = ((TMR2) % 124) + 2;
  score = 1; 
  clear_screen();
  clear_bomb();
}
//Displays when gameover
void blown_up(){
  clear_screen();
  display_string(0, "    BLOWN UP!");
  display_string(1, "Score: ");
  display_string(2, itoaconv(score));
  display_string(3, "BTN1 to PLAY!");
  restart();
  display_update_menu();
}


/* This function is called repetitively from the main program */
void game( void )
{
    //Controls updatespeed
    delay(100);
    //Clears the Display
    clear_screen();
    //Draws frame
    frame();
    //Draw bomb
    airstrike(bombX,bombY);
    //Draw blob
    player(blobY,blobX);    
    //Blob Movement
    //Left
    int btnstate = getbtns();
    if(btnstate & 0x8 && direction != 4)
        direction = 1;
    //Down
    else if(btnstate & 0x4 && direction != 3)
        direction = 2;
    //Up
    else if(btnstate & 0x2 && direction != 2)
        direction = 3;
    //Right
    else if(btnstate & 0x1 && direction != 1)
        direction = 4;
    //Set direction of the blob
    set_direction(direction);
    //Gameover
    gameover();
    //Update the display
    save_pixel();
    display_update();
    //Interruption flag for spawning the bombs
   if(IFS(0) & 0x0100){ 
      IFS(0) = IFS(0) & 0xfffffeff;  
      timeoutcount++; 
    }

    if(timeoutcount == 20){
        spawn_bomb();
        timeoutcount = 0;
      }
    
}
