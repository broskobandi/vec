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
 * \file include/vec.h
 * \brief Public header for the vec library.
 * */

#ifndef VEC_H
#define VEC_H

#include <stddef.h>

typedef struct vec vec_t;

vec_t *vec_new(size_t size);
int vec_del(vec_t *vec);

int vec_push(vec_t *vec, const void *value, size_t size);
int vec_pop(vec_t *vec, void *value, size_t size);
int vec_append(vec_t *vec, void *arr, size_t len, size_t size);
int vec_prepend(vec_t *vec, void *arr, size_t len, size_t size);
size_t vec_len(const vec_t *vec);
size_t vec_capacity(const vec_t *vec);
int vec_remove(vec_t *vec, size_t index, size_t size);
int vec_remove_range(const vec_t *vec, size_t index, size_t len, size_t size);
int vec_insert(vec_t *vec, size_t index, void *value, size_t size);
int vec_insert_arr(vec_t *vec, size_t index, void *value, size_t len, size_t size);
int vec_replace_range(vec_t *vec, size_t index, size_t replace, void *value, size_t len, size_t size);
const void *vec_view(const vec_t *vec);
const void *vec_cpy(vec_t *dst, const vec_t *src);
int vec_cmp(const vec_t *vec1, const vec_t *vec2);
int vec_at(const vec_t *vec, void *value, size_t index, size_t size);

const char *vec_geterror();

#endif
