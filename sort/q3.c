#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[])
{
	int N = atoi(argv[1]);
	long long nsteps = 0;
	for (int i = 1; i <= N*N; i = i*2) {
		for (int j = 0; j < i; j++) {
			nsteps++;
		}
	}
	printf("s: %lld\n", nsteps);
	printf("g: %f\n", pow(N, 2.5));
	return 0;
}
