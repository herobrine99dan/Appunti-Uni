#include <stdio.h>

int main() {
	int N = 4;
	int M = 0;
	int P = 1;
	do {
		printf("%d \n", P);
		P = P*2;
		M = M+1;
	} while(M<=N);
}
