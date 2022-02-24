/*
  Written by Kenan Dizdarevic
  11/02/2022
  */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

char* text1 = "This is a string.";
char* text2 = "Yet another thing.";
int count;
int list1[20];  // 80/4 = 20
int list2[20];

                //   $a0    $a1        $a2
void copycodes(char *text, int *list, int *count){
  // beq $t0,$0,done
  while(*text != 0){ // runs until the array is empty
    /* dereferencing means to manipulate data contained in memory that
    is being pointed to by a pointer */
    // copy value from ""text" to ""list" aka dereferencing
    *list = *text; 

    // increment the pointers for list and text
    list++; /* here is the difference between
               the assembly and C code        */
    text++;

    *count = *count + 1; // increase count with 1
  }

}

// work just calls copy codes twice
void work(){
  copycodes(text1, list1, &count);
  copycodes(text2, list2, &count);
}


void printlist(const int* lst){
  printf("ASCII codes and corresponding characters.\n");
  while(*lst != 0){
    printf("0x%03X '%c' ", *lst, (char)*lst);
    lst++;
  }
  printf("\n");
}

void endian_proof(const char* c){
  printf("\nEndian experiment: 0x%02x,0x%02x,0x%02x,0x%02x\n", 
         (int)*c,(int)*(c+1), (int)*(c+2), (int)*(c+3));
  
}

int main(void){
  work();

  printf("\nlist1: ");
  printlist(list1);
  printf("\nlist2: ");
  printlist(list2);
  printf("\nCount = %d\n", count);

  endian_proof((char*) &count);
}
