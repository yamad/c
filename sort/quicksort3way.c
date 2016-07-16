#include <stdio.h>
#include <stdlib.h>

void swap(int a[], int i, int j);

/* Djikstra's 3-way quicksort algorithm
 *
 * a[lo..lt-1], less than v
 * a[lt..i-1], equal to v
 * a[i..gt], unknown
 * a[gt+1..hi], greater than v
 *
 * based on Sedgewick Algorithms 4th ed, pg. 299 code */
int qsort3(int a[], int lo, int hi, int depth) {
	printf("depth: %d, %d --> %d\n", depth, lo, hi);
	if (hi <= lo) return 0;
	int lt = lo, i = lo+1, gt = hi;
	int v = a[lo];

	while (i <= gt) {
		if      (a[i] < v) swap(a, lt++, i++);
		else if (a[i] > v) swap(a, i, gt--);
		else               i++;
	}
	qsort3(a, lo, lt-1, depth+1);
	qsort3(a, gt+1, hi, depth+1);
}

void swap(int a[], int i, int j) {
	int t = a[i];
	a[i] = a[j];
	a[j] = t;
}

int sort(int a[], int len) {
	qsort3(a, 0, len-1, 0);
}

int main(int argc, char *argv[]) {
	if (argc < 3) {
		printf("Usage: qs3 <array size> <unique terms>\n");
		return -1;
	}
	int len = atoi(argv[1]);
	int nunique = atoi(argv[2]);
	int *in;
	in = (int *) malloc(sizeof(int)*len);
	for (int i = 0; i < len; i++) {
		in[i] = i % nunique;
		printf("%d ", in[i]);
	}
	printf("\n");
	sort(in, len);

	for (int i = 0; i < len; i++) {
		printf("%d ", in[i]);
	}
	printf("\n");
	return 0;
}
