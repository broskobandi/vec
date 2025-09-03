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
	(void*)((unsigned char*)(vec) + ROUNDUP(sizeof(vec_t)));\
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
	if (!vec) RET_ERR("malloc() failed.", NULL);
	vec->size = size;
	vec->capacity = DEFAULT_CAPACITY;
	SET_DATA_PTR(vec);
	vec->magic = MAGIC;
	vec->len = 0;
	RET_OK(vec);
}

/** Frees all data associated with 'vec'.
 * \param vec The vector to be freed. */
static inline void vec_del(vec_t **vec) {
	free(*vec);
	*vec = NULL;
}

/** Appends new data at the end of 'vec'.
 * \param vec The vector to extend.
 * \param value A pointer to a variable holding the value to be pushed to the end of vec. */
static inline int vec_push(vec_t **vec, const void *value) {
	if ((*vec)->len + 1 > (*vec)->capacity) {
		size_t new_capacity = (*vec)->capacity * 2;
		vec_t *tmp = realloc(*vec, new_capacity * (*vec)->size + ROUNDUP(sizeof(vec_t)));
		if (!tmp) RET_ERR("Failed to realloc memory.", 1);
		*vec = tmp;
		(*vec)->capacity = new_capacity;
		SET_DATA_PTR(*vec);
	}
	unsigned char *chardata = (unsigned char*)(*vec)->data;
	memcpy(&chardata[(*vec)->len * (*vec)->size], value, (*vec)->size);
	(*vec)->len++;
	RET_OK(0);
}

/** Removes the last element of 'vec' and copies its value into the varible 
 * 'value' is pointing to.
 * \param vec A pointer to the vec object to be modified. 
 * \param value A pointer to the variable the data is to be copied into.
 * \return 0 on success and 1 on failure. */
static inline int vec_pop(vec_t **vec, void *value) {
	unsigned char *chardata = (unsigned char*)(*vec)->data;
	memcpy(value, &chardata[((*vec)->len - 1) * (*vec)->size], (*vec)->size);
	if ((*vec)->len - 1 <= (*vec)->capacity / 2 && (*vec)->capacity / 2 >= DEFAULT_CAPACITY) {
		size_t new_capacity = (*vec)->capacity / 2;
		vec_t *tmp = realloc(*vec, ROUNDUP(sizeof(vec_t)) + new_capacity * (*vec)->size);
		if (!tmp) RET_ERR("Failed to realloc memory.", 1);
		*vec = tmp;
		(*vec)->capacity = new_capacity;
		SET_DATA_PTR(*vec);
	}
	(*vec)->len--;
	RET_OK(0);
}

// static inline void vec_at(const vec_t *vec, size_t index, void *value) {
// 	memcpy(value, &vec->data[index * vec->size], vec->size);
// }

#endif
