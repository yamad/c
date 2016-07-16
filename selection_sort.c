/* selection sort for integer array
 *
 * invariants:
 *  - a[lo] to a[i] is fully sorted
 *  - a[i] < a[k] for all k in a[i+1,hi]
 *
 * process:
 *  - (in short, find min of unsorted section and put at end of sorted section)
 *  - set i <- lo
 *  - find minimum value in a[i, hi]
 *  - swap minimum value with a[i]
 *  - stop if i = hi
 *
 *  by Jason Yamada-Hanff, 2015-09-18
 */

#include <stdio.h>
#include <stdlib.h>
#include "util.h"

int ncompares;
int nswaps;

/* selection sort array from lo to hi */
int selection_sort(int a[], int lo, int hi) {
	int i, j, min;
	ncompares = 0;
	nswaps = 0;
	for (i = lo; i <= hi; i++) {
		min = i;
		for (j = i; j <= hi; j++) {
			if (a[j] < a[min]) {
				min = j;
			}
			ncompares++;
		}
		swap_int(&a[i], &a[min]);
		nswaps++;
	}
	return nswaps;
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
	create_and_sort_random_array(size, max_int, &selection_sort);
	printf("swaps: %d\n", nswaps);
	printf("compares: %d\n", ncompares);
	return 0;
}
