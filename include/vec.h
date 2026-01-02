#ifndef VEC_H
#define VEC_H

#include <stddef.h>

#define VEC(T) vec_##T##_t
#define VEC_NEW(T) vec_##T##_new()
#define VEC_NEW_WITH_CAPACITY(T, capacity) vec_##T##_new_with_capacity((capacity))
#define VEC_DEL(vec) vec.del(&(vec))

#define VEC_TYPEDEF(T)\
	typedef struct vec_##T vec_##T##_t;\
	struct vec_##T {\
		T __type;\
		vec_t *__priv;\
		int (*push)(vec_##T##_t *self, T data);\
		int (*at)(vec_##T##_t *self, T *element_out);\
		int (*at_const)(const vec_##T##_t *self, const T *element_out);\
		int (*clear)(vec_##T##_t *self);\
		int (*remove)(vec_##T##_t *self, size_t index);\
		int (*insert)(vec_##T##_t *self, size_t index, T data);\
		int (*size)(const vec_##T##_t *self, size_t *size_out);\
		void (*del)(vec_##T##_t *self);\
	};\
	int vec_##T##_push(vec_##T##_t *self, T data) {\
		return vec_push(self->__priv, sizeof(T), (void*)&data);\
	}\
	int vec_##T##_at(vec_##T##_t *self, T *element_out) {\
		return vec_at(self->__priv, sizeof(T), element_out);\
	}\
	int vec_##T##_at_const(const vec_##T##_t *self, const T *element_out) {\
		return vec_at_const(self->__priv, sizeof(T), element_out);\
	}\
	int vec_##T##_clear(vec_##T##_t *self) {\
		return vec_clear(self->__priv, sizeof(T));\
	}\
	int vec_##T##_remove(vec_##T##_t *self, size_t index) {\
		return vec_remove(self->__priv, sizeof(T), index);\
	}\
	int vec_##T##_insert(vec_##T##_t *self, size_t index, T data) {\
		return vec_insert(self->__priv, sizeof(T), index, (void*)&data);\
	}\
	int vec_##T##_size(const vec_##T##_t *self, size_t *size_out) {\
		return vec_size(self->__priv, sizeof(T), size_out);\
	}\
	void vec_##T##_del(vec_##T##_t *self) {\
		return vec_del(self->__priv, sizeof(T));\
	}\
	vec_##T##_t vec_##T##_new() {\
		vec_##T##_t vec = {0};\
		vec.__priv = vec_new(sizeof(T));\
		vec.push = vec_##T##_push;\
		vec.at = vec_##T##_at;\
		vec.at_const = vec_##T##_at_const;\
		vec.clear = vec_##T##_clear;\
		vec.remove = vec_##T##_remove;\
		vec.insert = vec_##T##_insert;\
		vec.size = vec_##T##_size;\
		vec.del = vec_##T##_del;\
		return vec;\
	}

typedef struct vec vec_t;
vec_t *vec_new(size_t sizeof_type);
vec_t *vec_new_with_capacity(size_t sizeof_type, size_t capacity);
int vec_push(vec_t *vec, size_t sizeof_type, const void *data);
int vec_at(vec_t *vec, size_t sizeof_type, void *element_out);
int vec_at_const(const vec_t *vec, size_t sizeof_type, const void *element_out);
int vec_clear(vec_t *vec, size_t sizeof_type);
int vec_remove(vec_t *vec, size_t sizeof_type, size_t index);
int vec_insert(vec_t *vec, size_t sizeof_type, size_t index, const void *data);
int vec_size(const vec_t *vec, size_t sizeof_type, size_t *size_out);
void vec_del(vec_t *vec, size_t sizeof_type);
const char *vec_get_err();

#endif
