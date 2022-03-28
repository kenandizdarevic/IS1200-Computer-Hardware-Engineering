#include <stdio.h>

int main(){
	int n = 3;
	int ans = factorial(n);
	printf("%d ", ans);

	return 0;
}

int factorial(int n){
	int answer = n;

	if(n == 0){
		return 1;
	}
	if(n == 1){
		return answer;
	}

	for(int i = (n - 2); i >= 0; i--){
		int sum = 0;

		for(int j = (n - 2); j >= 0; j--){
			sum += answer;
		}
		answer = sum;
		n--;
	}
	return answer;
}
