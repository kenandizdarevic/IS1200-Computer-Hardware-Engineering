/*
 prime.c
 By David Broman.
 Last modified: 2015-09-15
 This file is in the public domain.
*/


#include <stdio.h>

int is_prime(int n){
	int count = 0; // our count and return variable

       	for(int i = 2; i < n; i++)	// start at i = 2 because n % 1 = 0 and n % n = 0, end loop before i = n 
	{
		int mod = n % i;	// if mod = 0 then the number is not a prime
		if(mod == 0)
		{
			count++;	// count = count + 1 to know by which numbers n can be divided with
		}
	}

	if(count > 0)			// if count > 0 then n is not a prime
	{
		count = 0;
	}	
	else if(count == 0)		// if count == 0 then n is a prime
	{
		count = 1;
	}

	return count;
}

int main(void){
  printf("%d\n", is_prime(11));  // 11 is a prime.      Should print 1.
  printf("%d\n", is_prime(383)); // 383 is a prime.     Should print 1.
  printf("%d\n", is_prime(987)); // 987 is not a prime. Should print 0.
  printf("%d\n", is_prime(32145)); // my own test
}
