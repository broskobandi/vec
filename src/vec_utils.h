#ifndef VEC_UTILS_H
#define VEC_UTILS_H

#include "vec.h"
#include <error.h>
#include <stdlib.h>
#include <stdalign.h>
#include <string.h>

/** Default number of elements that can be stored in the vector. */
#define DEFAULT_CAPACITY 4

/** Rounds the value up to the nearest multiple of alignof(max_align_t)
 * \param size The value to be rounded up. */
#define ROUNDUP(size)\
	(((size) + alignof(max_align_t) - 1) & ~(alignof(max_align_t) - 1))

/** Magic value for testing pointer validity. */
#define MAGIC (size_t)(0xC001D00D)

/** Stets the start of 'data' in vec.
 * \param vec The vector whose data is to be set. */
#define SET_DATA_PTR(vec)\
do {\
	(vec)->data =\
	(void*)((unsigned char*)vec + ROUNDUP(sizeof(vec_t)));\
} while(0)

/** Generic vector object to represent vecs of all types. */
typedef struct vec {
	/** Pointer to the start of the data. */
	void *data;
	/** The number of elements of 'size' that can be stored in vec. */
	size_t capacity;
	/** The number of elements currently stored in vec. */
	size_t len;
	/** The size of an element. */
	size_t size;
	/** Magic value for testing pointer validity. */
	size_t magic;
} vec_t;

/** Allocate a new instance of vec.
 * \param size The size of the type of data to be stored in the vec. 
 * \return Returns a new instance of vec or NULL on failure. */
static inline vec_t *vec_new(size_t size) {
	size_t alloc_size = ROUNDUP(sizeof(vec_t)) + size * DEFAULT_CAPACITY;
	vec_t *vec = malloc(alloc_size);
	if (!vec) ERR("malloc() failed.", NULL);
	vec->size = size;
	vec->capacity = DEFAULT_CAPACITY;
	SET_DATA_PTR(vec);
	vec->magic = MAGIC;
	vec->len = 0;
	OK(vec);
}

/** Frees all data associated with 'vec'.
 * \param vec The vector to be freed. */
static inline void vec_del(vec_t *vec) {
	free(vec);
}

/** Appends new data at the end of 'vec'.
 * \param vec The vector to extend.
 * \param value A pointer to a variable holding the value to be pushed to the end of vec. */
static inline void vec_push(vec_t *vec, const void *value) {
	if (vec->len + 1 > vec->capacity) {
		size_t new_capacity = vec->capacity * 2;
		vec_t *tmp = realloc(vec, new_capacity * vec->size + ROUNDUP(sizeof(vec_t)));
		if (!tmp) ERR("Failed to realloc memory.");
		vec = tmp;
		vec->capacity = new_capacity;
		SET_DATA_PTR(vec);
	}
	unsigned char *chardata = (unsigned char*)vec->data;
	memcpy(&chardata[vec->len * vec->size], value, vec->size);
	vec->len++;
}

#endif
