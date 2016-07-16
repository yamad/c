/* shell sort for integer array
 *
 * process:
 *  - use insertion sort to sort sequences that are h apart (instead of 1 apart)
 *  - reduce h and repeat insertion sort
 * */
#include "util.h"

int insertion_sort_span(int a[], int lo, int hi, int span);
static int nswaps, ncompares;

/* shellsort array `a` using Knuth increments */
int shellsort(int a[], int lo, int hi) {
	int h, hn;
	int N = (hi - lo) + 1;
	/* from Knuth TAOCP Vol 3, 2e, pg. 95, increment seqeunce */
	h = hn = 1;
	/* find largest h interval to use */
	while (hn <= N) {
		h = hn;
		hn = 3*hn + 1;
	}

	/* sort h-spans */
	while (h >= 1) {
		printf("h: %d\n", h);
		insertion_sort_span(a, lo, hi, h);
		h = (h - 1) / 3;
	}
	return 0;
}

int insertion_sort_span(int a[], int lo, int hi, int span) {
	int i, j;
	nswaps = 0;
	ncompares = 0;
	for (i = lo+span; i <= hi; i++) {
		printf("i: %d\n", i);
		for (j = i; j >= span && a[j] < a[j-span]; j -= span) {
			swap_int(&a[j], &a[j-span]);
			nswaps++;
			ncompares++;
			print_int_array(a, (hi-lo)+1);
		}
		ncompares++;	/* count extra compare that breaks inner loop */
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
	create_and_sort_random_array(size, max_int, &shellsort);
	printf("swaps: %d\n", nswaps);
	printf("compares: %d\n", ncompares);
	return 0;
}
