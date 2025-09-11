#ifndef VEC_H
#define VEC_H

#include <stddef.h> /* For size_t */

typedef struct vec vec_t;

vec_t *vec_new(size_t sizeof_type);
int vec_del(vec_t *vec);
int vec_push_back(vec_t *vec, const void *value, size_t sizeof_type);
int vec_push_front(vec_t *vec, const void *value, size_t sizeof_type);
int vec_pop_back(vec_t *vec, void *value, size_t sizeof_type);
int vec_pop_front(vec_t *vec, void *value, size_t sizeof_type);
size_t vec_len(const vec_t *vec);
size_t vec_capacity(const vec_t *vec);
int vec_remove(vec_t *vec, size_t index);
int vec_insert(vec_t *vec, const void *value, size_t index, size_t sizeof_type);
int vec_at(const vec_t *vec, void *value, size_t index, size_t sizeof_type);
int vec_append(vec_t *vec, const void *arr, size_t len, size_t sizeof_type);
int vec_prepend(vec_t *vec, const void *arr, size_t len, size_t sizeof_type);
int vec_replace(vec_t *vec, const void *value, size_t index, size_t sizeof_type);
int vec_replace_range(
	vec_t *vec, const void *arr, size_t len,
	size_t index, size_t range, size_t sizeof_type
);
const void *vec_view(const vec_t *vec, size_t index);

#endif
