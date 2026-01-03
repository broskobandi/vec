#ifndef VEC_H
#define VEC_H

#include <stddef.h>

#define VEC(T) vec_##T##_t
#define VEC_NEW(T) vec_##T##_new()
#define VEC_NEW_WITH_CAPACITY(T, capacity) vec_##T##_new_with_capacity((capacity))
#define VEC_DEL(vec) vec.del(&(vec))
#define VEC_PUSH(vec, data) vec.push(&vec, (data))
#define VEC_POP(vec) vec.pop(&vec)
#define VEC_AT(vec, index) vec.at(&vec, index)
#define VEC_AT_CONST(vec, index) vec.at_const(&vec, index)
#define VEC_CLEAR(vec) vec.clear(&vec)
#define VEC_REMOVE(vec, index) vec.remove(&vec, index)
#define VEC_INSERT(vec, index, data) vec.insert(&vec, index, data)
#define VEC_SIZE(vec) vec.size(&vec)
#define VEC_CAPACITY(vec) vec.capacity(&vec)

#define VEC_TYPEDEF(T)\
	typedef struct vec_##T vec_##T##_t;\
	struct vec_##T {\
		vec_t *__priv;\
		int is_init;\
		int (*push)(vec_##T##_t *self, T data);\
		int (*pop)(vec_##T##_t *self);\
		T *(*at)(vec_##T##_t *self, size_t index);\
		const T *(*at_const)(const vec_##T##_t *self, size_t index);\
		int (*clear)(vec_##T##_t *self);\
		int (*remove)(vec_##T##_t *self, size_t index);\
		int (*insert)(vec_##T##_t *self, size_t index, T data);\
		size_t (*size)(const vec_##T##_t *self);\
		size_t (*capacity)(const vec_##T##_t *self);\
		void (*del)(vec_##T##_t *self);\
	};\
	[[maybe_unused]]\
	static inline int vec_##T##_push(vec_##T##_t *self, T data) {\
		return vec_push(self->__priv, sizeof(T), (const void*)&data);\
	}\
	[[maybe_unused]]\
	static inline int vec_##T##_pop(vec_##T##_t *self) {\
		return vec_pop(self->__priv, sizeof(T));\
	}\
	[[maybe_unused]]\
	static inline T *vec_##T##_at(vec_##T##_t *self, size_t index) {\
		return vec_at(self->__priv, sizeof(T), index);\
	}\
	[[maybe_unused]]\
	static inline const T *vec_##T##_at_const(const vec_##T##_t *self, size_t index) {\
		return vec_at_const(self->__priv, sizeof(T), index);\
	}\
	[[maybe_unused]]\
	static inline int vec_##T##_clear(vec_##T##_t *self) {\
		return vec_clear(self->__priv, sizeof(T));\
	}\
	[[maybe_unused]]\
	static inline int vec_##T##_remove(vec_##T##_t *self, size_t index) {\
		return vec_remove(self->__priv, sizeof(T), index);\
	}\
	[[maybe_unused]]\
	static inline int vec_##T##_insert(vec_##T##_t *self, size_t index, T data) {\
		return vec_insert(self->__priv, sizeof(T), index, (const void*)&data);\
	}\
	[[maybe_unused]]\
	static inline size_t vec_##T##_size(const vec_##T##_t *self) {\
		return vec_size(self->__priv, sizeof(T));\
	}\
	[[maybe_unused]]\
	static inline size_t vec_##T##_capacity(const vec_##T##_t *self) {\
		return vec_capacity(self->__priv, sizeof(T));\
	}\
	[[maybe_unused]]\
	static inline void vec_##T##_del(vec_##T##_t *self) {\
		vec_del(self->__priv, sizeof(T));\
		self->__priv = NULL;\
	}\
	vec_##T##_t vec_##T##_new() {\
		vec_##T##_t vec = {0};\
		vec.__priv = vec_new(sizeof(T));\
		if (!vec.__priv) vec.is_init = 0;\
		vec.push = vec_##T##_push;\
		vec.pop = vec_##T##_pop;\
		vec.at = vec_##T##_at;\
		vec.at_const = vec_##T##_at_const;\
		vec.clear = vec_##T##_clear;\
		vec.remove = vec_##T##_remove;\
		vec.insert = vec_##T##_insert;\
		vec.size = vec_##T##_size;\
		vec.capacity = vec_##T##_capacity;\
		vec.del = vec_##T##_del;\
		return vec;\
	}\
	vec_##T##_t vec_##T##_new_with_capacity(size_t capacity) {\
		vec_##T##_t vec = {0};\
		if (!vec.__priv) vec.is_init = 0;\
		vec.__priv = vec_new_with_capacity(sizeof(T), capacity);\
		vec.push = vec_##T##_push;\
		vec.pop = vec_##T##_pop;\
		vec.at = vec_##T##_at;\
		vec.at_const = vec_##T##_at_const;\
		vec.clear = vec_##T##_clear;\
		vec.remove = vec_##T##_remove;\
		vec.insert = vec_##T##_insert;\
		vec.size = vec_##T##_size;\
		vec.capacity = vec_##T##_capacity;\
		vec.del = vec_##T##_del;\
		return vec;\
	}

typedef struct vec vec_t;
vec_t *vec_new(size_t sizeof_type);
vec_t *vec_new_with_capacity(size_t sizeof_type, size_t capacity);
int vec_push(vec_t *vec, size_t sizeof_type, const void *data);
int vec_pop(vec_t *vec, size_t sizeof_type);
void *vec_at(vec_t *vec, size_t sizeof_type, size_t index);
const void *vec_at_const(const vec_t *vec, size_t sizeof_type, size_t index);
int vec_clear(vec_t *vec, size_t sizeof_type);
int vec_remove(vec_t *vec, size_t sizeof_type, size_t index);
int vec_insert(vec_t *vec, size_t sizeof_type, size_t index, const void *data);
size_t vec_size(const vec_t *vec, size_t sizeof_type);
size_t vec_capacity(const vec_t  *vec, size_t sizeof_type);
void vec_del(vec_t *vec, size_t sizeof_type);
const char *vec_get_err();

#endif
