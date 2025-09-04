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
 * \file src/vec.c
 * \brief Implementation for the vec library.
 * \details This file contains the definitions of the public functions.
 * */

#include "vec.h"
#include <stdlib.h>
#include <string.h>

_Thread_local const char *g_err = NULL;

#define DEFAULT_CAPACITY 4

struct vec {
	void *data;
	size_t len;
	size_t size;
	size_t capacity;
};

vec_t *vec_new(size_t size) {
	if (!size || size & (size - 1)) {
		g_err = "Invalid argument.";
		return NULL;
	}
	vec_t *vec = malloc(sizeof(vec_t));
	if (!vec) {
		g_err = "Failed to allocate vec.";
		return NULL;
	}
	vec->data = malloc(size * DEFAULT_CAPACITY);
	if (!vec->data) {
		g_err = "Failed to allocate vec->data.";
		free(vec);
		return NULL;
	}
	vec->len = 0;
	vec->capacity = DEFAULT_CAPACITY;
	vec->size = size;
	return vec;
}

void vec_del(vec_t *vec) {
	if (!vec) {
		g_err = "Invalid argument.";
		return;
	}
	if (!vec->data) return;
	free(vec->data);
	free(vec);
}

size_t vec_len(const vec_t *vec) {
	if (!vec) {
		g_err = "Invalid argument.";
		return (size_t)-1;
	}
	return vec->len;
}

size_t vec_capacity(const vec_t *vec) {
	if (!vec) {
		g_err = "Invalid argument.";
		return (size_t)-1;
	}
	return vec->capacity;
}

size_t vec_size(const vec_t *vec) {
	if (!vec) {
		g_err = "Invalid argument.";
		return (size_t)-1;
	}
	return vec->size;
}

static inline int resize(vec_t *vec, size_t new_capacity) {
	void *tmp = realloc(vec->data, new_capacity * vec->size);
	if (!tmp) {
		g_err = "realloc() failed.";
		return 1;
	}
	vec->data = tmp;
	vec->capacity = new_capacity;
	return 0;
}

int vec_push(vec_t *vec, const void *value, size_t size) {
	if (!vec || !value || size != vec->size) {
		g_err = "Invalid argument";
		return 1;
	}
	if (vec->len + 1 > vec->capacity) {
		if (resize(vec, vec->capacity * 2)) {
			g_err = "resize() failed.";
			return 1;
		}
	}
	memcpy(vec->data, value, size);
	vec->len++;
	return 0;
}

int vec_pop(vec_t *vec, void *value, size_t size) {
	if (!vec || size != vec->size) {
		g_err = "Invalid argument.";
		return 1;
	}
	if (value)
		memcpy(value, vec->data, size);
	if (vec->len - 1 <= vec->capacity / 2 && vec->capacity / 2 >= DEFAULT_CAPACITY) {
		if (resize(vec, vec->capacity / 2)) {
			g_err = "resize() failed.";
			return 1;
		}
	}
	vec->len--;
	return 0;
}

const char *vec_get_error() {
	return g_err;
}

void vec_reset_error() {
	g_err = NULL;
}
