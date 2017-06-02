#include <stddef.h>

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
