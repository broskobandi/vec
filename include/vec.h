#ifndef VEC_H
#define VEC_H

#include <stddef.h>

#define VEC(T) vec_##T##_t

#define VEC_TYPEDEF(T)\
	typedef struct vec_##T vec_##T##_t;\
	struct vec_##T {\
		T __type;\
		vec_t *__priv;\
	};

typedef struct vec vec_t;
vec_t *vec_new(size_t sizeof_type);
vec_t *vec_new_with_capacity(size_t sizeof_type, size_t capacity);
int vec_push(vec_t *vec, size_t sizeof_type, void *ptr_to_data);
int vec_at(vec_t *vec, size_t sizeof_type, void *element_out);
int vec_at_const(const vec_t *vec, size_t sizeof_type, const void *element_out);
int vec_clear(vec_t *vec, size_t sizeof_type);
int vec_remove(vec_t *vec, size_t sizeof_type, size_t index);
int vec_insert(vec_t *vec, size_t sizeof_type, size_t index);
int vec_size(const vec_t *vec, size_t sizeof_type, size_t *size_out);
void vec_del(vec_t *vec, size_t sizeof_type);
const char *vec_get_err();

#endif
