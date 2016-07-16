/* insertion sort for integer array
 *
 * invariants:
 *  - a[lo] to a[i] is in ascending order
 *  - a[i+1] to a[hi] is unknown status
 *
 * process:
 *  - (in short, each element is moved into relative order/position)
 *  #. set i = lo+1 (initial element is already in place)
 *  #. move a[i] "into position", by shifting a[k] in a[lo,i-1] to the right until a[i] > a[k].
 *  #. increment i and repeat
 *
 * performance notes:
 *   - number of compares is # of swaps + N (or close)
 * */
#include <stdio.h>
#include "util.h"

static int nswaps, ncompares;

int insertion_sort(int a[], int lo, int hi) {
	int i, j;
	nswaps = 0;
	ncompares = 0;
	for (i = lo+1; i <= hi; i++) {
		for (j = i; j >= 1 && a[j] < a[j-1]; j--) {
			swap_int(&a[j], &a[j-1]);
			nswaps++;
			ncompares++;
		}
		ncompares++;	/* count extra compare that breaks inner loop */
	}
}

/* implementation of CLRS pseudo-code */
int insertion_sort2(int a[], int lo, int hi) {
	int i, j, k;
	nswaps = 0;
	ncompares = 0;
	for (i = lo+1; i <= hi; i++) {
		k = a[i];
		j = i-1;
		while (j >= 0 && a[j] > k) {
			ncompares++;
			swap_int(&a[j+1], &a[j]);
			nswaps++;
			j--;
		}
		ncompares++;
		a[j+1] = k;
		nswaps++;
	}
}

/* initial version. failed to recognize that k is always j+1 (and thus not needed) */
int insertion_sort3(int a[], int lo, int hi) {
	int i, j, k;
	nswaps = 0;
	ncompares = 0;
	for (i = lo+1; i <= hi; i++) {
		k = i;
		j = i-1;
		while (j >= 0 && a[j] > a[k]) {
			ncompares++;
			swap_int(&a[j], &a[k]);
			nswaps++;
			k = j;
			j--;
		}
		ncompares++;
	}
}

/* test client: generates an array of random integers and sorts them */
int main(int argc, char *argv[])
{
	if (argc < 3) {
		printf("Usage: %s <array_size> <max_integer>\n", argv[0]);
		return -1;
	}
	int size = atoi(argv[1]);
	int max_int = atoi(argv[2]);
	create_and_sort_random_array(size, max_int, &insertion_sort);
	printf("swaps: %d\n", nswaps);
	printf("compares: %d\n", ncompares);
	return 0;
}
