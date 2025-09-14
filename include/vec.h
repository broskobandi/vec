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
 * \brief Public header file for the vec library. 
 * \details This file contains the forward declarations of public funcions 
 * for the vec library. */

#ifndef VEC_H
#define VEC_H

#include <stddef.h> /* For size_t */
#include <mem_alloc.h> /* For function pointers */

/** Opaque handle for a generic vec object. */
typedef struct vec_generic vec_generic_t;

/** Creates a new generic vector.
 * \param sizeof_type The size of the vector's type. 
 * \return A pointer to the vector. */
vec_generic_t *vec_generic_new(size_t sizeof_type);

/** Deletes a vector.
 * \param vec A pointer to the vector to be deleted.
 * \return 0 on success or 1 on failure. */
int vec_generic_del(vec_generic_t *vec);

/** Appends an item at the end of the vector.
 * \param vec A pointer to the vector to be modified.
 * \param value A pointer to the value to be appended.
 * \param sizeof_type The size of the item's type (must be the 
 * same as the vector's type's).
 * \return 0 on success or 1 on failure. */
int vec_generic_push_back(
	vec_generic_t *vec, const void *value, size_t sizeof_type);

/** Prepends an item at the beginning of the vector.
 * \param vec A pointer to the vector to be modified.
 * \param value A pointer to the value to be prepended.
 * \param sizeof_type The size of the item's type (must be the 
 * same as the vector's type's).
 * \return 0 on success or 1 on failure. */
int vec_generic_push_front(
		vec_generic_t *vec, const void *value, size_t sizeof_type);

/** Removes and copies the value of the last member into 'value'.
 * \param vec A pointer to the vector to be modified.
 * \param value A pointer to the variable to copy the value into
 * (can be NULL).
 * \param sizeof_type The size of the variable's type (must be the 
 * same as the vector's type's).
 * \return 0 on success or 1 on failure. */
int vec_generic_pop_back(
		vec_generic_t *vec, void *value, size_t sizeof_type);

/** Removes and copies the value of the first member into 'value'.
 * \param vec A pointer to the vector to be modified.
 * \param value A pointer to the variable to copy the value into
 * (can be NULL).
 * \param sizeof_type The size of the variable's type (must be the 
 * same as the vector's type's).
 * \return 0 on success or 1 on failure. */
int vec_generic_pop_front(
		vec_generic_t *vec, void *value, size_t sizeof_type);

/** Returns the length of the vector.
 * \param vec A pointer to the vector to be accessed. 
 * \return The length of the vector or (size_t)-1 on failure. */
size_t vec_generic_len(const vec_generic_t *vec);

/** Returns the capacity of the vector.
 * \param vec A pointer to the vector to be accessed. 
 * \return The capacity of the vector or (size_t)-1 on failure. */
size_t vec_generic_capacity(const vec_generic_t *vec);

/** Removes a member of the vector (and shrinks the vector).
 * \param vec A pointer to the vector to be modified. 
 * \param index The index of the member to be removed.
 * \return 0 on success or 1 on failure. */
int vec_generic_remove(vec_generic_t *vec, size_t index);

/** Inserts an item into the vector.
 * \param vec A pointer to the vector to be modified. 
 * \param value A pointer to the value to be inserted. 
 * \param index The index at which the value is to be inserted.
 * \param sizeof_type The size of the item's type (must be the same as the 
 * vector's type's).
 * \return 0 on success or 1 on failure. */
int vec_generic_insert(
		vec_generic_t *vec,
		const void *value,
		size_t index,
		size_t sizeof_type);

/** Copies the value of the vector's member into 'value'.
 * \param vec A pointer to the vecetor to be accessed.
 * \param value A pointer to the variable to copy the value into.
 * \param index The index of the member whose value is to be copied. 
 * \param sizeof_type The size of the variable's type (must be the same 
 * vector's type's).
 * \return 0 on success or 1 on failure. */
int vec_generic_at(
		const vec_generic_t *vec,
		void *value,
		size_t index,
		size_t sizeof_type);

/** Appends an array at the end of the vector.
 * \param vec A pointer to the vector tobe modified.
 * \param arr The array to be appended.
 * \param len The length of the array.
 * \param sizeof_type The size of the array's type (must be the same 
 * as the vector's type's).
 * \return 0 on success or 1 on failure. */
int vec_generic_append(
		vec_generic_t *vec,
		const void *arr,
		size_t len,
		size_t sizeof_type);

/** Prepends an array at the beginning of the vector.
 * \param vec A pointer to the vector tobe modified.
 * \param arr The array to be prepended.
 * \param len The length of the array.
 * \param sizeof_type The size of the array's type (must be the same 
 * as the vector's type's).
 * \return 0 on success or 1 on failure. */
int vec_generic_prepend(
		vec_generic_t *vec,
		const void *arr,
		size_t len,
		size_t sizeof_type);

/** Replaces a member of the vector.
 * \param vec A pointer to the verctor to be modified.
 * \param value A pointer to the varible whose value is to be copied.
 * \param index The index of the member to be replaced.
 * \param sizeof_type The size of the item's type (must be the same 
 * as the vector's type's).*/
int vec_generic_replace(
		vec_generic_t *vec,
		const void *value,
		size_t index,
		size_t sizeof_type);

/** Replaces a range of members in a vector with an array.
 * \param vec A pointer to the vector to be modified.
 * \param arr The array to be inserted. 
 * \param len The length of the array.
 * \param index The index at which the array is t obe inserted.
 * \param range The range of members to be removed from the vector.
 * \param sizeof_type The size of the array's type (must be the same as 
 * the vector's type's).*/
int vec_generic_replace_range(
	vec_generic_t *vec,
	const void *arr,
	size_t len,
	size_t index,
	size_t range,
	size_t sizeof_type);

/** Returns a const pointer to a member of the vector.
 * \param vec A pointer to the vector to be accessed.
 * \param index The index to return a pointer to.
 * \return A pointer to the member or NULL on failure. */
const void *vec_generic_view(
		const vec_generic_t *vec, size_t index);

/** Prints error information if exists. */
void vec_print_err();

/******************************************************************************
 * Type-safe wrappers
 *****************************************************************************/

#define vec(T) vec_##T##_t
#define vec_new(T) vec_##T##_new()
#define vec_del(vec) vec.fn->del((vec))
#define vec_push_back(vec, value) vec.fn->push_back((vec), (value))
#define vec_push_front(vec, value) vec.fn->push_front((vec), (value))
#define vec_pop_back(vec) vec.fn->pop_back((vec))
#define vec_pop_front(vec) vec.fn->pop_front((vec))
#define vec_len(vec) vec.fn->len((vec))
#define vec_capacity(vec) vec.fn->capacity((vec))
#define vec_remove(vec, index) vec.fn->remove((vec), (index))
#define vec_insert(vec, value, index) vec.fn->insert((vec), (value), (index))
#define vec_at(vec, index) vec.fn->at((vec), (index))
#define vec_append(vec, arr, len) vec.fn->append((vec), (arr), (len)) 
#define vec_prepend(vec, arr, len) vec.fn->prepend((vec), (arr), (len)) 
#define vec_replace(vec, value, index) vec.fn->replace((vec), (value), (index))
#define vec_replace_range(vec, arr, len, index, range)\
	vec.fn->replace_range((vec), (arr), (len), (index), (range))
#define vec_view(vec, index) vec.fn->view((vec), (index))

#define typedef_vec(T)\
	typedef struct vec_##T##_function_pointers vec_##T##_function_pointers_t;\
	typedef struct vec_##T {\
		vec_##T##_function_pointers_t *fn;\
		vec_generic_t *vec;\
	} vec_##T##_t;\
	struct vec_##T##_function_pointers {\
		void (*del)(vec_##T##_t vec);\
		void (*push_back)(vec_##T##_t vec, T value);\
		void (*push_front)(vec_##T##_t vec, T value);\
		T (*pop_back)(vec_##T##_t vec);\
		T (*pop_front)(vec_##T##_t vec);\
		size_t (*len)(vec_##T##_t vec);\
		size_t (*capacity)(vec_##T##_t vec);\
		void (*remove)(vec_##T##_t vec, size_t index);\
		void (*insert)(vec_##T##_t vec, T value, size_t index);\
		T (*at)(vec_##T##_t vec, size_t index);\
		void (*append)(vec_##T##_t vec, const T *arr, size_t len);\
		void (*prepend)(vec_##T##_t vec, const T *arr, size_t len);\
		void (*replace)(vec_##T##_t vec, T value, size_t index);\
		void (*replace_range)(\
			vec_##T##_t vec,\
			const T *arr,\
			size_t len,\
			size_t index,\
			size_t range);\
		const T *(*view)(vec_##T##_t vec, size_t index);\
	};\
	static inline void vec_##T##_del(vec_##T##_t vec) {\
		vec_generic_del(vec.vec);\
		mem_free(vec.fn);\
	}\
	static inline void vec_##T##_push_back(vec_##T##_t vec, T value) {\
		vec_generic_push_back(vec.vec, &value, sizeof(T));\
	}\
	static inline void vec_##T##_push_front(vec_##T##_t vec, T value) {\
		vec_generic_push_front(vec.vec, &value, sizeof(T));\
	}\
	static inline T vec_##T##_pop_back(vec_##T##_t vec) {\
		T value = {0};\
		vec_generic_pop_back(vec.vec, &value, sizeof(T));\
		return value;\
	}\
	static inline T vec_##T##_pop_front(vec_##T##_t vec) {\
		T value = {0};\
		vec_generic_pop_front(vec.vec, &value, sizeof(T));\
		return value;\
	}\
	static inline size_t vec_##T##_len(vec_##T##_t vec) {\
		return vec_generic_len(vec.vec);\
	}\
	static inline size_t vec_##T##_capacity(vec_##T##_t vec) {\
		return vec_generic_capacity(vec.vec);\
	}\
	static inline void vec_##T##_remove(vec_##T##_t vec, size_t index) {\
		vec_generic_remove(vec.vec, index);\
	}\
	static inline void vec_##T##_insert(vec_##T##_t vec, T value, size_t index) {\
		vec_generic_insert(vec.vec, &value, index, sizeof(T));\
	}\
	static inline T vec_##T##_at(vec_##T##_t vec, size_t index) {\
		T value = {0};\
		vec_generic_at(vec.vec, &value, index, sizeof(T));\
		return value;\
	}\
	static inline void vec_##T##_append(vec_##T##_t vec, const T *arr, size_t len) {\
		vec_generic_append(vec.vec, arr, len, sizeof(T));\
	}\
	static inline void vec_##T##_prepend(vec_##T##_t vec, const T *arr, size_t len) {\
		vec_generic_prepend(vec.vec, arr, len, sizeof(T));\
	}\
	static inline void vec_##T##_replace(vec_##T##_t vec, T value, size_t index) {\
		vec_generic_replace(vec.vec, &value, index, sizeof(T));\
	}\
	static inline void vec_##T##_replace_range(vec_##T##_t vec, const T *arr, size_t len, size_t index, size_t range) {\
		vec_generic_replace_range(vec.vec, arr, len, index, range, sizeof(T));\
	}\
	static inline const T *vec_##T##_view(vec_##T##_t vec, size_t index) {\
		return (T*)vec_generic_view(vec.vec, index);\
	}\
	static inline vec_##T##_t vec_##T##_new() {\
		vec_##T##_t vec = {\
			.fn = (vec_##T##_function_pointers_t*)mem_alloc(sizeof(vec_##T##_function_pointers_t)),\
			.vec = (vec_generic_t*)vec_generic_new(sizeof(T))\
		};\
		if (!vec.vec) {\
			mem_free(vec.fn);\
			return vec;\
		}\
		if (!vec.fn) {\
			vec_generic_del(vec.vec);\
			return vec;\
		}\
		vec.fn->del = vec_##T##_del;\
		vec.fn->push_back = vec_##T##_push_back;\
		vec.fn->push_front = vec_##T##_push_front;\
		vec.fn->pop_back = vec_##T##_pop_back;\
		vec.fn->pop_front = vec_##T##_pop_front;\
		vec.fn->len = vec_##T##_len;\
		vec.fn->capacity = vec_##T##_capacity;\
		vec.fn->remove = vec_##T##_remove;\
		vec.fn->insert = vec_##T##_insert;\
		vec.fn->at = vec_##T##_at;\
		vec.fn->append = vec_##T##_append;\
		vec.fn->prepend = vec_##T##_prepend;\
		vec.fn->replace = vec_##T##_replace;\
		vec.fn->replace_range = vec_##T##_replace_range;\
		vec.fn->view = vec_##T##_view;\
		return vec;\
	}

#endif
