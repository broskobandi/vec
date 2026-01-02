#include "vec.h"
#include <stdio.h>
#include <stdlib.h>

#define VEC_DEFAULT_CAPACITY 32LU
#define VALIDATE(expr, err_msg, ...)\
	do {\
		if (!(expr)) {\
			set_err((err_msg));\
			return __VA_ARGS__;\
		}\
	} while(0)

_Thread_local static const char *g_err;

const char *vec_get_err() {
	return g_err;
}

void set_err(const char *msg) {
	g_err = msg;
}

struct vec {
	void *data;
	size_t capacity;
	size_t sizeof_type;
	size_t sizeof_vec;
};

vec_t *vec_new(size_t sizeof_type) {
	return vec_new_with_capacity(sizeof_type, VEC_DEFAULT_CAPACITY);
}

vec_t *vec_new_with_capacity(size_t sizeof_type, size_t capacity) {
	vec_t *vec = calloc(1, sizeof(vec_t));
	VALIDATE(vec, "Failed to allocated vec_t.", NULL);

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

int vec_push(vec_t *vec, size_t sizeof_type, void *ptr_to_data);
int vec_at(vec_t *vec, size_t sizeof_type, void *element_out);
int vec_at_const(const vec_t *vec, size_t sizeof_type, const void *element_out);
int vec_clear(vec_t *vec, size_t sizeof_type);
int vec_remove(vec_t *vec, size_t sizeof_type, size_t index);
int vec_insert(vec_t *vec, size_t sizeof_type, size_t index);
int vec_size(const vec_t *vec, size_t sizeof_type, size_t *size_out);
void vec_del(vec_t *vec, size_t sizeof_type);
const char *vec_get_err();
