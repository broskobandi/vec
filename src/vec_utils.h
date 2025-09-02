#ifndef VEC_UTILS_H
#define VEC_UTILS_H

#include "vec.h"
#include <error.h>
#include <stdlib.h>
#include <stdalign.h>
#include <string.h>

#define ROUNDUP(size)\
	(((size) + alignof(max_align_t) - 1) & ~(alignof(max_align_t) - 1))
#define DEFAULT_ALLOC(size)\
	(ROUNDUP(sizeof(vec_t)) + ROUNDUP((size) * 4))
#define MAGIC (size_t)(0xC001D00D)
#define SET_DATA_PTR(vec)\
do {\
	(vec)->data =\
	(void*)((unsigned char*)vec + ROUNDUP(sizeof(vec_t)));\
} while(0)

typedef struct vec {
	void *data;
	size_t capacity;
	size_t len;
	size_t size;
	size_t magic;
} vec_t;

static inline vec_t *vec_new(size_t size) {
	vec_t *vec = malloc(DEFAULT_ALLOC(size));
	if (!vec) ERR("malloc() failed.", NULL);
	vec->size = size;
	vec->capacity = DEFAULT_ALLOC(size) - ROUNDUP(sizeof(vec_t));
	SET_DATA_PTR(vec);
	vec->magic = MAGIC;
	vec->len = 0;
	OK(vec);
}

static inline void vec_del(vec_t *vec) {
	free(vec);
}

static inline void vec_push(vec_t *vec, void *value) {
	if (vec->len + vec->size > vec->capacity) {
		size_t new_capacity = 
			ROUNDUP(sizeof(vec_t)) + vec->capacity * 2;
		vec_t *tmp = realloc(vec, new_capacity);
		if (!tmp) ERR("Failed to realloc memory.");
		vec = tmp;
		vec->capacity = new_capacity;
	}
	SET_DATA_PTR(vec);
	unsigned char *chardata = (unsigned char*)vec->data;
	memcpy(&chardata[vec->len * vec->size], value, vec->size);
	vec->len += vec->size;
}

#endif
