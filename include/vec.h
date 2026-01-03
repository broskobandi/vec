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

/** \file include/vec.h
 * \brief Public header file fod the vec library. 
 * \details This file contains the macro wrappers, static inline function 
 * declarations and the generic function prototypes and the corresponding 
 * vector typedefs. */

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
	static inline int vec_##T##_push(vec_##T##_t *self, T data) {\
		return vec_push(self->__priv, sizeof(T), (const void*)&data);\
	}\
	static inline int vec_##T##_pop(vec_##T##_t *self) {\
		return vec_pop(self->__priv, sizeof(T));\
	}\
	static inline T *vec_##T##_at(vec_##T##_t *self, size_t index) {\
		return vec_at(self->__priv, sizeof(T), index);\
	}\
	static inline const T *vec_##T##_at_const(const vec_##T##_t *self, size_t index) {\
		return vec_at_const(self->__priv, sizeof(T), index);\
	}\
	static inline int vec_##T##_clear(vec_##T##_t *self) {\
		return vec_clear(self->__priv, sizeof(T));\
	}\
	static inline int vec_##T##_remove(vec_##T##_t *self, size_t index) {\
		return vec_remove(self->__priv, sizeof(T), index);\
	}\
	static inline int vec_##T##_insert(vec_##T##_t *self, size_t index, T data) {\
		return vec_insert(self->__priv, sizeof(T), index, (const void*)&data);\
	}\
	static inline size_t vec_##T##_size(const vec_##T##_t *self) {\
		return vec_size(self->__priv, sizeof(T));\
	}\
	static inline size_t vec_##T##_capacity(const vec_##T##_t *self) {\
		return vec_capacity(self->__priv, sizeof(T));\
	}\
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

/** Opaque vector type. */
typedef struct vec vec_t;

/** Creates a new vec_t on the heap with the default capacity.
 * \param sizeof_type The size of the desired tpye.
 * \returns A pointer to the allocated vector object or NULL
 * on failure.
 * In the event of failure, the generated error string can be queried with
 * vec_get_err(). */
vec_t *vec_new(size_t sizeof_type);

/** Creates a new vec_t on the heap with the specified capacity.
 * \param sizeof_type The size of the underlying type.
 * \param capacity The desired capacity expressed by the number of elements
 * and not bytes.
 * \returns A pointer to the allocated vector object or NULL
 * on failure.
 * In the event of failure, the generated error string can be queried with
 * vec_get_err(). */
vec_t *vec_new_with_capacity(size_t sizeof_type, size_t capacity);

/** Appends an element at the end of the vector, reallocating it if necessary.
 * \param vec A pointer to the vector.
 * \param sizeof_type The size of the underlying type.
 * \param data A pointer to the data to be appended.
 * \returns 0 on success or 1 on failure.
 * In the event of failure, the generated error string can be queried with
 * vec_get_err(). */
int vec_push(vec_t *vec, size_t sizeof_type, const void *data);

/** Remove the last element of the vector, shrinking it if necessary.
 * \param vec A pointer to the vector.
 * \param sizeof_type The size of the underlying type.
 * \returns 0 on success or 1 on failure.
 * In the event of failure, the generated error string can be queried with
 * vec_get_err(). */
int vec_pop(vec_t *vec, size_t sizeof_type);

/** Get a non-const reference to a specific member of the vector.
 * \param vec A pointer to the vector.
 * \param sizeof_type The size of the underlying type.
 * \param index The index of the element.
 * \returns A non-const pointer to the element or NULL on failure.
 * In the event of failure, the generated error string can be queried with
 * vec_get_err(). */
void *vec_at(vec_t *vec, size_t sizeof_type, size_t index);

/** Get a const reference to a specific member of the vector.
 * \param vec A pointer to the vector.
 * \param sizeof_type The size of the underlying type.
 * \param index The index of the element.
 * \returns A non-const pointer to the element or NULL on failure.
 * In the event of failure, the generated error string can be queried with
 * vec_get_err(). */
const void *vec_at_const(const vec_t *vec, size_t sizeof_type, size_t index);

/** Clear the vector shrinking it to the default capacity if necessary.
 * \param vec A pointer to the vector.
 * \param sizeof_type The size of the underlying type.
 * \returns 0 on sucecss or 1 on failure.
 * In the event of failure, the generated error string can be queried with
 * vec_get_err(). */
int vec_clear(vec_t *vec, size_t sizeof_type);

/** Remove a specific element in the vector, shrinking it if necessary.
 * \param vec A pointer to the vector.
 * \param sizeof_type The size of the underlying type.
 * \param index The index of the element.
 * \returns 0 on sucecss or 1 on failure.
 * In the event of failure, the generated error string can be queried with
 * vec_get_err(). */
int vec_remove(vec_t *vec, size_t sizeof_type, size_t index);

/** Insert data into the vector, expanding it if necessary.
 * \param vec A pointer to the vector.
 * \param sizeof_type The size of the underlying type.
 * \param index The index of the element.
 * \param data A pointer to the data to be inserted.
 * \returns 0 on sucecss or 1 on failure.
 * In the event of failure, the generated error string can be queried with
 * vec_get_err(). */
int vec_insert(vec_t *vec, size_t sizeof_type, size_t index, const void *data);

/** Get the number of elements in the vector.
 * \param vec A pointer to the vector.
 * \param sizeof_type The size of the underlying type.
 * \returns The number of elements or (size_t)-1 on failure.
 * In the event of failure, the generated error string can be queried with
 * vec_get_err(). */
size_t vec_size(const vec_t *vec, size_t sizeof_type);

/** Get the capacity of the vector expressed by the current maximum
 * number of elements.
 * \param vec A pointer to the vector.
 * \param sizeof_type The size of the underlying type.
 * \returns The capacity or (size_t)-1 on failure.
 * In the event of failure, the generated error string can be queried with
 * vec_get_err(). */
size_t vec_capacity(const vec_t  *vec, size_t sizeof_type);

/** Cleans up all the allocated data associated with the vector.
 * \param vec A pointer to the vector.
 * \param sizeof_type The size of the underlying type. */
void vec_del(vec_t *vec, size_t sizeof_type);

/** Returns a pointer to the internal global error string. */
const char *vec_get_err();

#endif
