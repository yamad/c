/* Binary Min Heap -- 2017-06-02, jyh */
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


struct heap {
	int *array;
	size_t capacity;
	size_t size;
};

enum HeapError {
	HeapError_Success = 0,
	HeapError_NoEntries = 1,
	HeapError_NoMemory = 2
};
typedef enum HeapError heap_err;

heap_err heap_init(struct heap **h, size_t capacity);
heap_err heap_push(struct heap *h, int entry);
heap_err heap_pop(struct heap *h, int *entry);
heap_err heap_grow_array(struct heap *h);
heap_err heap_fixup(struct heap *h);
heap_err heap_fixdown(struct heap *h);
void heap_print(struct heap *h);
void swap(int *i, int *j);


#define parent_index(i)			((i-1) / 2)
#define left_child_index(i)		(i*2 + 1)
#define right_child_index(i)	(i*2 + 2)
#define entry_at(heap, i)       (heap->array[i])
#define parent(heap, i)         (entry_at(heap, parent_index(i)))
#define left_child(heap, i)     (entry_at(heap, left_child_index(i)))
#define right_child(heap, i)    (entry_at(heap, right_child_index(i)))

#define has_parent(i)	(i != 0)

int has_left_child(struct heap *h, size_t i) {
	return left_child_index(i) < h->size;
}
int has_right_child(struct heap *h, size_t i) {
	return right_child_index(i) < h->size;
}


heap_err heap_init(struct heap **h, size_t capacity) {
	struct heap *htmp;
	htmp = (struct heap *) malloc(sizeof(struct heap));
	if (!htmp) return HeapError_NoMemory;

	htmp->array = (int *) malloc(sizeof(int) * capacity);
	if (!htmp->array) return HeapError_NoMemory;

	htmp->capacity = capacity;
	htmp->size = 0;
	*h = htmp;

	return HeapError_Success;
}

heap_err heap_push(struct heap *h, int entry) {
	heap_err err;
	if (h->size == h->capacity)
		if ((err = heap_grow_array(h)) != HeapError_Success)
			return err;

	h->array[h->size++] = entry;
	err = heap_fixup(h);
	return err;
}

heap_err heap_pop(struct heap *h, int *entry) {
	heap_err err = HeapError_Success;
	if (h->size == 0)
		return HeapError_NoEntries;

	*entry = h->array[0];
	swap(h->array, h->array+(--h->size));
	err = heap_fixdown(h);
	return err;
}

heap_err heap_fixup(struct heap *h) {
	size_t i = h->size - 1;
	while (has_parent(i) &&
		   entry_at(h, i) < parent(h, i)) {
		swap(&entry_at(h, i), &parent(h, i));
		i = parent_index(i);
	}
	return HeapError_Success;
}

heap_err heap_fixdown(struct heap *h) {
	size_t i = 0;
	size_t ichild;
	while (has_left_child(h, i)) {
		ichild = left_child_index(i);

		if (has_right_child(h, i) &&
			left_child(h, i) > right_child(h, i))
			ichild = right_child_index(i);

		if (entry_at(h, i) > entry_at(h, ichild))
			swap(&entry_at(h, i), &entry_at(h, ichild));
		i = ichild;
	}
	return HeapError_Success;
}

void swap(int* i, int* j) {
	int tmp = *i;
	*i = *j;
	*j = tmp;
}

heap_err heap_grow_array(struct heap *h) {
	size_t new_capacity = h->capacity * 2;
	int *new = (int *) malloc(sizeof(int) * new_capacity);
	if (!new)
		return HeapError_NoMemory;

	memcpy(new, h->array, sizeof(int) * h->size);
	free(h->array);
	h->array = new;
	h->capacity = new_capacity;
	return HeapError_Success;
}

void heap_print(struct heap *h) {
	for (size_t i = 0; i < h->size; i++)
		printf("%d ", h->array[i]);
	printf("\n");
}

/* simple test */
int main(int argc, char *argv[]) {
	heap_err err = HeapError_Success;

    struct heap *h;
	err = heap_init(&h, 3);
	if (err != HeapError_Success) return err;

	int entries[] = { 4, 25, 2, 56, 1, 6, 5 };
	for (int i = 0; i < 7; i++) {
		err = heap_push(h, entries[i]);
	}

	heap_print(h);

	int entry;
	while (1) {
		err = heap_pop(h, &entry);
		if (err == HeapError_NoEntries)
			break;
		printf("%d ", entry);
	}
	printf("\n");

    return err;
}
