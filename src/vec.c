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

/** \file src/vec.c 
 * \brief Implementation file for the vec library.
 * \details This file contains the implementation of all the functions 
 * in the vec library. */

#include "vec.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VEC_DEFAULT_CAPACITY 32LU

#define VEC_ERR_BUFF_SIZE 512LU
/** Global error string. */
static char g_err[VEC_ERR_BUFF_SIZE];

/** Returns a pointer to the internal global error string. */
const char *vec_get_err() {
	return g_err;
}

/** Sets the global error string. */
static inline void set_err(const char *msg) {
	const char *vec_err_header = "[VEC_ERROR]: ";
	if ((strlen(msg) + strlen(vec_err_header) + 1) > VEC_ERR_BUFF_SIZE) {
		msg = "Vec error buffer overflow.";
	}
	sprintf(g_err, "%s %s\n", vec_err_header, msg);
}

/** Opaque vector type. */
struct vec {

	/** A pointer to the encapsulated vector data. */
	uint8_t *data;

	/** The current maximum number of elements. */
	size_t capacity;

	/** The size of the underlying type. */
	size_t sizeof_type;

	/** The current number of elements */
	size_t sizeof_vec;
};

/** Creates a new vec_t on the heap with the default capacity.
 * \param sizeof_type The size of the desired tpye.
 * \returns A pointer to the allocated vector object or NULL
 * on failure.
 * In the event of failure, the generated error string can be queried with
 * vec_get_err(). */
vec_t *vec_new(size_t sizeof_type) {
	return vec_new_with_capacity(sizeof_type, VEC_DEFAULT_CAPACITY);
}

/** Creates a new vec_t on the heap with the specified capacity.
 * \param sizeof_type The size of the underlying type.
 * \param capacity The desired capacity expressed by the number of elements
 * and not bytes.
 * \returns A pointer to the allocated vector object or NULL
 * on failure.
 * In the event of failure, the generated error string can be queried with
 * vec_get_err(). */
vec_t *vec_new_with_capacity(size_t sizeof_type, size_t capacity) {
	vec_t *vec = calloc(1, sizeof(vec_t));
	if (!vec) {
		set_err("Failed to allocate vec_t.");
		return NULL;
	}

	vec->data = calloc(capacity, sizeof_type);
	if (!vec->data) {
		set_err("Failed to allocate vec->data.");
		free(vec);
		return NULL;
	}

	vec->capacity = VEC_DEFAULT_CAPACITY;
	vec->sizeof_type = sizeof_type;
	vec->sizeof_vec = 0;

	return vec;
}

/** Appends an element at the end of the vector, reallocating it if necessary.
 * \param vec A pointer to the vector.
 * \param sizeof_type The size of the underlying type.
 * \param data A pointer to the data to be appended.
 * \returns 0 on success or 1 on failure.
 * In the event of failure, the generated error string can be queried with
 * vec_get_err(). */
int vec_push(vec_t *vec, size_t sizeof_type, const void *data) {
	if (!vec || !vec->data || !data || sizeof_type != vec->sizeof_type) {
		set_err("Invalid arguments in vec_push().");
		return 1;
	}

	if ((vec->sizeof_vec + 1) * sizeof_type > vec->capacity * sizeof_type) {
		uint8_t *tmp = (uint8_t*)realloc(
			vec->data, (size_t)((float)vec->capacity * 1.5f) * sizeof_type
		);
		if (!tmp) {
			set_err("Failed to expand vector.");
			return 1;
		}
		vec->data = tmp;
	}

	memcpy(vec->data + vec->sizeof_vec * sizeof_type, data, sizeof_type);
	vec->sizeof_vec++;

	return 0;
}

/** Remove the last element of the vector, shrinking it if necessary.
 * \param vec A pointer to the vector.
 * \param sizeof_type The size of the underlying type.
 * \returns 0 on success or 1 on failure.
 * In the event of failure, the generated error string can be queried with
 * vec_get_err(). */
int vec_pop(vec_t *vec, size_t sizeof_type) {
	if (!vec || !vec->data || !vec->sizeof_vec || sizeof_type != vec->sizeof_type) {
		set_err("Invalid arguments in vec_pop().");
		return 1;
	}

	if (vec->sizeof_vec - 1 <= vec->capacity / 2 &&
		vec->capacity / 2 >= VEC_DEFAULT_CAPACITY
	) {
		uint8_t *tmp = (uint8_t*)realloc(vec->data, vec->capacity * sizeof_type / 2);
		if (!tmp) {
			set_err("Failed to shrink vector.");
			return 1;
		}
	}

	vec->sizeof_vec--;

	return 0;
}

/** Get a non-const reference to a specific member of the vector.
 * \param vec A pointer to the vector.
 * \param sizeof_type The size of the underlying type.
 * \param index The index of the element.
 * \returns A non-const pointer to the element or NULL on failure.
 * In the event of failure, the generated error string can be queried with
 * vec_get_err(). */
void *vec_at(vec_t *vec, size_t sizeof_type, size_t index) {
	if (!vec || !vec->data || sizeof_type != vec->sizeof_type) {
		set_err("Invalid arguments in vec_at().");
		return NULL;
	}

	if (index >= vec->sizeof_vec) {
		set_err("Out of bounds index passed to vec_at().");
		return NULL;
	}

	return (void*)&vec->data[index * sizeof_type];
}

/** Get a const reference to a specific member of the vector.
 * \param vec A pointer to the vector.
 * \param sizeof_type The size of the underlying type.
 * \param index The index of the element.
 * \returns A non-const pointer to the element or NULL on failure.
 * In the event of failure, the generated error string can be queried with
 * vec_get_err(). */
const void *vec_at_const(const vec_t *vec, size_t sizeof_type, size_t index) {
	if (!vec || !vec->data || sizeof_type != vec->sizeof_type) {
		set_err("Invalid arguments in vec_at().");
		return NULL;
	}

	if (index >= vec->sizeof_vec) {
		set_err("Out of bounds index passed to vec_at().");
		return NULL;
	}

	return (const void*)&vec->data[index * sizeof_type];
}

/** Clear the vector shrinking it to the default capacity if necessary.
 * \param vec A pointer to the vector.
 * \param sizeof_type The size of the underlying type.
 * \returns 0 on sucecss or 1 on failure.
 * In the event of failure, the generated error string can be queried with
 * vec_get_err(). */
int vec_clear(vec_t *vec, size_t sizeof_type) {
	if (!vec || !vec->data || sizeof_type != vec->sizeof_type) {
		set_err("Invalid arguments in vec_clear().");
		return 1;
	}

	if (!vec->sizeof_vec) {
		return 0;
	}

	uint8_t *tmp = (uint8_t*)realloc(vec->data, VEC_DEFAULT_CAPACITY);
	if (!tmp) {
		set_err("Failed to shrink vector.");
		return 1;
	}

	vec->data = tmp;
	vec->capacity = VEC_DEFAULT_CAPACITY;
	vec->sizeof_vec = 0;

	return 0;
}

/** Remove a specific element in the vector, shrinking it if necessary.
 * \param vec A pointer to the vector.
 * \param sizeof_type The size of the underlying type.
 * \param index The index of the element.
 * \returns 0 on sucecss or 1 on failure.
 * In the event of failure, the generated error string can be queried with
 * vec_get_err(). */
int vec_remove(vec_t *vec, size_t sizeof_type, size_t index){
	if (!vec || !vec->data || sizeof_type != vec->sizeof_type) {
		set_err("Invalid arguments in vec_remove().");
		return 1;
	}

	if (index >= vec->sizeof_vec) {
		set_err("Out of bounds index passed to vec_remove().");
		return 1;
	}

	memmove(
		vec->data + sizeof_type * index,
		vec->data + sizeof_type * (index + 1),
		vec->sizeof_vec * sizeof_type - (index + 1) * sizeof_type
	);

	if (vec->sizeof_vec - 1 <= vec->capacity / 2 &&
		vec->capacity / 2 >= VEC_DEFAULT_CAPACITY
	) {
		uint8_t *tmp = (uint8_t*)realloc(vec->data, vec->capacity * sizeof_type / 2);
		if (!tmp) {
			set_err("Failed to shrink vector.");
			return 1;
		}
	}

	vec->sizeof_vec--;

	return 0;
}

/** Insert data into the vector, expanding it if necessary.
 * \param vec A pointer to the vector.
 * \param sizeof_type The size of the underlying type.
 * \param index The index of the element.
 * \param data A pointer to the data to be inserted.
 * \returns 0 on sucecss or 1 on failure.
 * In the event of failure, the generated error string can be queried with
 * vec_get_err(). */
int vec_insert(vec_t *vec, size_t sizeof_type, size_t index, const void *data) {
	if (!vec || !vec->data || sizeof_type != vec->sizeof_type || !data) {
		set_err("Invalid arguments in vec_insert().");
		return 1;
	}

	if (index >= vec->sizeof_vec) {
		set_err("Out of bounds index passed to vec_insert().");
		return 1;
	}

	if (vec->sizeof_vec + 1 > vec->capacity) {
		uint8_t *tmp = (uint8_t*)realloc(
			vec->data, (size_t)((float)vec->capacity * 1.5) * sizeof_type
		);
		if (!tmp) {
			set_err("Failed to expand vector.");
			return 1;
		}
		vec->data = tmp;
		vec->capacity = (size_t)((float)vec->capacity * 1.5);
	}

	memmove(
		vec->data + (index + 1) * sizeof_type,
		vec->data + index * sizeof_type,
		vec->sizeof_vec * sizeof_type - index * sizeof_type
	);

	memcpy(vec->data + index * sizeof_type, data, sizeof_type);
	vec->sizeof_vec++;

	return 0;
}

/** Get the number of elements in the vector.
 * \param vec A pointer to the vector.
 * \param sizeof_type The size of the underlying type.
 * \returns The number of elements or (size_t)-1 on failure.
 * In the event of failure, the generated error string can be queried with
 * vec_get_err(). */
size_t vec_size(const vec_t *vec, size_t sizeof_type) {
	if (!vec || !vec->data || sizeof_type != vec->sizeof_type) {
		set_err("Invalid arguments in vec_size().");
		return (size_t)-1;
	}

	return vec->sizeof_vec;
}

/** Get the capacity of the vector expressed by the current maximum
 * number of elements.
 * \param vec A pointer to the vector.
 * \param sizeof_type The size of the underlying type.
 * \returns The capacity or (size_t)-1 on failure.
 * In the event of failure, the generated error string can be queried with
 * vec_get_err(). */
size_t vec_capacity(const vec_t  *vec, size_t sizeof_type) {
	if (!vec || !vec->data || sizeof_type != vec->sizeof_type) {
		set_err("Invalid arguments in vec_capacity().");
		return (size_t)-1;
	}

	return vec->capacity;
}

/** Cleans up all the allocated data associated with the vector.
 * \param vec A pointer to the vector.
 * \param sizeof_type The size of the underlying type. */
void vec_del(vec_t *vec, size_t sizeof_type) {
	if (vec && vec->data && vec->sizeof_type == sizeof_type) {
		free(vec->data);
		free(vec);
	}
}
