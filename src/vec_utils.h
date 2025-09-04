/*
MIT License

Copyright (c) 2025 broskobandi

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/**
 * \file src/vec_utils.h
 * \brief Private header for the vec library.
 * \details This file contains global constants and helper functions.
 * */

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

/** Stets the start of 'data' in vec.
 * \param vec The vector whose data is to be set. */
#define SET_DATA_PTR(vec)\
do {\
	(vec)->data =\
	(void*)((unsigned char*)(vec) + ROUNDUP(sizeof(vec_t)));\
} while(0)

/** Generic vector object that represents vecs of all types internally. */
struct vec {
	/** Pointer to the start of the data. */
	void *data;
	/** The number of elements of 'size' that can be stored in vec. */
	size_t capacity;
	/** The number of elements currently stored in vec. */
	size_t len;
	/** The size of an element. */
	size_t size;
};

/** Allocate a new instance of vec.
 * \param size The size of the type of data to be stored in the vec. 
 * \return Returns a new instance of vec or NULL on failure. */
static inline vec_t *vec_new(size_t size) {
	size_t alloc_size = ROUNDUP(sizeof(vec_t)) + size * DEFAULT_CAPACITY;
	vec_t *vec = (vec_t*)malloc(alloc_size);
	if (!vec) RET_ERR("malloc() failed.", NULL);
	vec->size = size;
	vec->capacity = DEFAULT_CAPACITY;
	SET_DATA_PTR(vec);
	vec->len = 0;
	RET_OK(vec);
}

/** Frees all data associated with 'vec'.
 * \param vec The vector to be freed. */
static inline void vec_del(vec_t **vec) {
	free(*vec);
	*vec = NULL;
}

static inline int resize(vec_t **vec, size_t new_capacity) {
	vec_t *tmp = realloc(*vec, new_capacity * (*vec)->size + ROUNDUP(sizeof(vec_t)));
	if (!tmp) RET_ERR("realloc() failed.", 1);
	*vec = tmp;
	(*vec)->capacity = new_capacity;
	SET_DATA_PTR(*vec);
	return 0;
}

/** Appends new data at the end of 'vec'.
 * \param vec The vector to extend.
 * \param value A pointer to a variable holding the value to be pushed to the end of vec. */
static inline int vec_push(vec_t **vec, const void *value) {
	if ((*vec)->len + 1 > (*vec)->capacity) {
		// size_t new_capacity = (*vec)->capacity * 2;
		// vec_t *tmp = realloc(*vec, new_capacity * (*vec)->size + ROUNDUP(sizeof(vec_t)));
		// if (!tmp) RET_ERR("Failed to realloc memory.", 1);
		// *vec = tmp;
		// (*vec)->capacity = new_capacity;
		// SET_DATA_PTR(*vec);
		if (resize(vec, (*vec)->capacity * 2))
			RET_ERR("Failed to resize vector", 1);
	}
	unsigned char *chardata = (unsigned char*)(*vec)->data;
	memcpy(&chardata[(*vec)->len * (*vec)->size], value, (*vec)->size);
	(*vec)->len++;
	RET_OK(0);
}

/** Removes the last element of 'vec' and copies its value into the varible 
 * 'value' is pointing to.
 * \param vec A pointer to the vec object to be modified. 
 * \param value A pointer to the variable the data is to be copied into (can be NULL).
 * \return 0 on success and 1 on failure. */
static inline int vec_pop(vec_t **vec, void *value) {
	unsigned char *chardata = (unsigned char*)(*vec)->data;
	if (value)
		memcpy(value, &chardata[((*vec)->len - 1) * (*vec)->size], (*vec)->size);
	if ((*vec)->len - 1 <= (*vec)->capacity / 2 && (*vec)->capacity / 2 >= DEFAULT_CAPACITY) {
		// size_t new_capacity = (*vec)->capacity / 2;
		// vec_t *tmp = realloc(*vec, ROUNDUP(sizeof(vec_t)) + new_capacity * (*vec)->size);
		// if (!tmp) RET_ERR("Failed to realloc memory.", 1);
		// *vec = tmp;
		// (*vec)->capacity = new_capacity;
		// SET_DATA_PTR(*vec);
		if (resize(vec, (*vec)->capacity / 2))
			RET_ERR("Failed to resize vector.", 1);
	}
	(*vec)->len--;
	RET_OK(0);
}

/** Copies the value of the member found at 'index'-th element into 'value'.
 * \param vec The vector to copy the data from.
 * \param index The index of the element to access.
 * \param value A pointer to the variable to copy the data into.*/
static inline void vec_at(const vec_t *vec, size_t index, void *value) {
	unsigned char *chardata = (unsigned char*)vec->data;
	memcpy(value, &chardata[index * vec->size], vec->size);
}

/** Removes the 'index'-th element from 'vec' and shrinks the vector appropriately.
 * \param vec A pointer to the vector to be modified. 
 * \param index The index of the element to remove. */
static inline int vec_remove(vec_t **vec, size_t index) {
	unsigned char *chardata = (unsigned char*)(*vec)->data;
	size_t len_to_copy = (*vec)->len - index - 1;
	size_t dst_index = index * (*vec)->size;
	size_t src_index = dst_index + (*vec)->size;
	memmove(&chardata[dst_index], &chardata[src_index], len_to_copy * (*vec)->size);
	if ((*vec)->len - 1 <= (*vec)->capacity / 2 && (*vec)->capacity / 2 >= DEFAULT_CAPACITY) {
		// size_t new_capacity = (*vec)->capacity / 2;
		// vec_t *tmp = realloc(*vec, ROUNDUP(sizeof(vec_t)) + new_capacity * (*vec)->size);
		// if (!tmp) RET_ERR("Failed to realloc memory.", 1);
		// *vec = tmp;
		// (*vec)->capacity = new_capacity;
		// SET_DATA_PTR(*vec);
		if (resize(vec, (*vec)->capacity / 2))
			RET_ERR("Failed to resize vec.", 1);
	}
	(*vec)->len--;
	RET_OK(0);
}

/** Appends an array at the end of a vector.
 * \param vec The vector to be modified.
 * \param arr The array to be appended.
 * \param len The length of the array to be appended.
 * \return 0 on success or 1 on failure. */
static inline int vec_append(vec_t **vec, const void *arr, size_t len) {
	while ((*vec)->len + len > (*vec)->capacity) {
		if (resize(vec, (*vec)->capacity * 2))
			RET_ERR("Failed to resize vector.", 1);
	}
	unsigned char *chardata = (unsigned char*)(*vec)->data;
	memcpy(&chardata[(*vec)->len * (*vec)->size], arr, len * (*vec)->size);
	(*vec)->len += len;
	RET_OK(0);
}

#endif
