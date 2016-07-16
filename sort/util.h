#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* exchange integers held at x and y */
void swap_int(int *x, int *y);
/* print integer array of length `len` */
void print_int_array(int a[], int len);

/* sort test client
 *
 * generates an array of `size` elements, each a random integer from 0
 * to `max_int`, and sorts it using the sort function given. the sort
 * function takes thress arguments: an integer array `a`, and the low
 * and hi indices for the part of the array to sort. the array is
 * printed before and after sorting.
 */
int create_and_sort_random_array(int size, int max_int,
	int (*sort)(int a[], int lo, int hi));

void swap_int(int *x, int *y) {
	int t = *x;
	*x = *y;
	*y = t;
}

void print_int_array(int a[], int len) {
	int i;
	for (i = 0; i < len; i++) {
		printf("%d ", a[i]);
	}
	putchar('\n');
}

int create_and_sort_random_array(int size, int max_int, int (*sort)(int[], int, int)) {
	/* allocate memory for array */
	int *a = (int *) malloc(size*sizeof(int));
	if (a == NULL) {
		printf("Out of memory error. Goodbye.");
		return -1;
	}

	/* fill array with random values */
	int i;
	srand(time(NULL));
	for (i = 0; i < size; i++) {
		a[i] = rand() * ((double)max_int / RAND_MAX);
	}

	print_int_array(a, size);

	(*sort)(a, 0, size-1);
	print_int_array(a, size);

	free(a);
}
#endif
