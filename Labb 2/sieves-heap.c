#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define COLUMNS 6

int count = 0; 					// global counter for print_number
void print_number(int n){

  printf("%10d ", n);	        // print number n with the space 10 as in print_primes
  count++;			           // increase count with 1 because we printed a number
 
  int full = count % COLUMNS;   // remainder of amount of printed numbers / COLUMNS

  if(full == 0){		// if there is no remainder we will print a new line, 6 new columns
  printf("\n");	
  }
}

void print_sieves(int n){
	/*
		Input an integer n > 1.
		2 is unmarked therefor a prime number.
		Mark all squares of 2 grater than 2, ex. 4, 6, 8, 10, 12...
		3 is unmarked therefor a prime, mark all squares of three.
		Continue doing this until the square of the given number is grater than n
		All unmarked numbers less than n are prime numbers. 						*/
	int size = n;	// increase the size of the array by 1
	char* primes = (char *) malloc(sizeof(char) * size); // we use malloc to allocate memory for the array on the heap

	/* Sieves Algorithm */
	for(int i = 2; i <= n; i++){
		primes[i] = 1;	// set all values in the array to 1
	}
	for(int i = 2; i <= sqrt(n); i++){ // loop until sqrt(n) to save time
		if(primes[i]){	// if at the given index the value is 1 continue
			for(int j = i * i; j <= n; j += i){ // set j to i^2 and loop until j=n
				primes[j] = 0;		// set all multiples of the given number to marked (which is 0)
			}
		}
	}
	for(int i = 2; i <= n; i++){ // loop through the array and print out all indexes which have 1 as data
		if(primes[i]){
			print_number(i);
		}
	}
	
	free(primes);	// deallocate the memory
}

int main(int argc, char *argv[]){
  
 if(argc == 2)
    print_sieves(atoi(argv[1]));
  else
    printf("Please state an interger number.\n");
  return 0;
}
