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

/** \file include/vec_private.h
 * \brief Private header file for the vec library. 
 * \details This file contains the definitions of the opaque vector object, 
 * macro definitions and internal helper functions for the vec library. */

#ifndef VEC_PRIVATE_H
#define VEC_PRIVATE_H

#include "vec.h"
#include <mem_alloc.h>
#include <string.h>

/** The default capacity of the vector object. */
#define DEFAULT_CAPACITY 8LU

/** The definition of the opaaque vector struct. */
struct vec {
	/** A pointer to the allocated data. */
	void *data;

	/** The size of the type of data stored in the vector. */
	size_t sizeof_type;

	/** The number of items currently stored in the vector. */
	size_t len;

	/** The number of items the vector can currently hold. */
	size_t capacity;
};

/** Expands or shrinks the vector's capacity.
 * \param vec A pointer to the vector to be modified.
 * \param new_capacity The new capacity to be used.
 * \return 0 on failure or 1 on success. */
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
