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
int list1[50];
int list2[50];
                //    $a0         $a1        $a2
void copycodes(char *text, int *list, int *count){
  // beq $t0,$0,done
  while(*text != 0){
    // copy value from text to list
    *list = *text; 
    // lb $t0, 0($a0)

    // increment the pointers list and text
    list += 1;
    text += 1;

    (*count)++;
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
