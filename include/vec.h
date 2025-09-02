#ifndef VEC_H
#define VEC_H

#include <stddef.h>

#define TYPEDEF_VEC(T)\
	typedef struct vec_##T vec_##T##_t;\
	static inline vec_##T##_t *vec_##T##_new() {\
		return (vec_##T##_t*)vec_generic_new(sizeof(T));\
	}\
	static inline int vec_##T##_del(vec_##T##_t *vec) {\
		return vec_generic_del(vec);\
	}\
	static inline int vec_##T##_push(vec_##T##_t *vec, T value) {\
		return vec_generic_push(vec, &value);\
	}\
	static inline int vec_##T##_pop(vec_##T##_t *vec, T *value) {\
		return vec_generic_pop(vec, value);\
	}\
	static inline int vec_##T##_at(vec_##T##_t *vec, size_t index, T *value) {\
		return vec_generic_at(vec, index, value);\
	}\
	static inline int vec_##T##_remove(vec_##T##_t *vec, size_t index) {\
		return vec_generic_remove(vec, index);\
	}


void *vec_generic_new(size_t size);
int vec_generic_del(void *vec);
int vec_generic_push(void *vec, void *value);
int vec_generic_pop(void *vec, void *value);
int vec_generic_at(void *vec, size_t index, void *value);
int vec_generic_remove(void *vec, size_t index);

TYPEDEF_VEC(int);

#endif
