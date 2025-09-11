#ifndef VEC_PRIVATE_H
#define VEC_PRIVATE_H

#include "vec.h"
#include <mem_alloc.h>
#include <string.h>

#define DEFAULT_CAPACITY 8LU

struct vec {
	void *data;
	size_t sizeof_type;
	size_t len;
	size_t capacity;
};

static inline int resize(vec_t *vec, size_t new_capacity) {
	void *tmp = mem_realloc(vec->data, new_capacity);
	if (tmp) {
		vec->data = tmp;
		vec->capacity = new_capacity;
		return 0;
	} else {
		return 1;
	}
}

#endif
