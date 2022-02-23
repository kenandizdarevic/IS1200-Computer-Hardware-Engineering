/*
 print-prime.c
 By David Broman.
 Last modified: 2015-09-15
 This file is in the public domain.
*/


#include <stdio.h>
#include <stdlib.h>

#define COLUMNS 6

int count = 0; // global counter for print_number

void print_number(int n){

  printf("%10d ", n);	        // print number n whit the space 10 as in print_primes
  count++;			// increase count with 1 because we printed a number
 
  int full = count % COLUMNS;   // remainder of amount of printed numbers / COLUMNS

  if(full == 0){		// if there is no remainder we will print a new line
  printf("\n");	
  }
}

int is_prime(int n){
  int counted = 0; // our count and return variable

  for(int i = 2; i < n; i++)	// start at i = 2 because n % 1 = 0 and n % n = 0, end loop before i = n 	
  {
     if(n % i == 0)
     {
	counted++;	// count = count + 1 to know by which numbers n can be divided with
     }
  }

  if(counted > 0)			// if count > 0 then n is not a prime
  {
	  counted = 0;
  }	
  else if(counted == 0)		// if count == 0 then n is a prime
  {
	  counted = 1;
  }

  return counted;
}

void print_primes(int n){
  // Should print out all prime numbers less than 'n'
  // with the following formatting. Note that
  // the number of columns is stated in the define
  // COLUMNS

  for(int i = 2; i < n; i++){ // start at 2 becaus we do not want to print out 1
	   if( is_prime(i) ){       // call function is_prime to check for prime	
	     print_number(i);     // prints the number
	    }
  }
  printf("\n");   // new line
}


// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[]){
  
 if(argc == 2)
    print_primes(atoi(argv[1]));
  else
    printf("Please state an interger number.\n");
  return 0;
}



