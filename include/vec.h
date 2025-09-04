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
 * \details This file contains macro and static inline function wrappers 
 * and forward declarations for the vec library.
 * */

#ifndef VEC_H
#define VEC_H

#include <stddef.h>

/*****************************************************************************
 * Type-safe api
 *****************************************************************************/

/** Defines an opaque vector handle for the desired type and creates type-safe 
 * static inline function wrappers around the generic vector functions.
 * Please refer to the documentation of vec_generic* functions for details 
 * about usage of the wrapped up functions.
 * \param T The type of the vector. */
#define TYPEDEF_VEC(T)\
	typedef struct vec_##T vec_##T##_t;\
	__attribute__((unused))\
	static inline vec_##T##_t *vec_##T##_new() {\
		return (vec_##T##_t*)vec_generic_new(sizeof(T));\
	}\
	__attribute__((unused))\
	static inline int vec_##T##_del(vec_##T##_t **vec) {\
		return vec_generic_del((vec_t**)vec, sizeof(T));\
	}\
	__attribute__((unused))\
	static inline int vec_##T##_push(vec_##T##_t **vec, T value) {\
		return vec_generic_push((vec_t**)vec, &value, sizeof(T));\
	}\
	__attribute__((unused))\
	static inline int vec_##T##_pop(vec_##T##_t **vec, T *value) {\
		return vec_generic_pop((vec_t**)vec, value, sizeof(T));\
	}\
	__attribute__((unused))\
	static inline int vec_##T##_at(const vec_##T##_t *vec, size_t index, T *value) {\
		return vec_generic_at((vec_t*)vec, index, value, sizeof(T));\
	}\
	__attribute__((unused))\
	static inline int vec_##T##_remove(vec_##T##_t **vec, size_t index) {\
		return vec_generic_remove((vec_t**)vec, index, sizeof(T));\
	}\
	__attribute__((unused))\
	static inline size_t vec_##T##_len(const vec_##T##_t *vec) {\
		return vec_generic_len((vec_t*)vec);\
	}\
	__attribute__((unused))\
	static inline int vec_##T##_append(vec_##T##_t **vec, const T *array, size_t len) {\
		return vec_generic_append((vec_t**)vec, (void*)array, len, sizeof(T));\
	}\
	__attribute__((unused))\
	static inline const T *vec_##T##_ptr(const vec_##T##_t *vec, size_t index) {\
		return (T*)vec_generic_ptr((vec_t*)vec, index, sizeof(T));\
	}\
	__attribute__((unused))\
	static inline int vec_##T##_cpy(vec_##T##_t **dst, const vec_##T##_t *src) {\
		return vec_generic_cpy((vec_t**)dst, (const vec_t*)src, sizeof(T));\
	}\
	__attribute__((unused))\
	static inline size_t vec_##T##_capacity(const vec_##T##_t *vec) {\
		return vec_generic_capacity((const vec_t*)vec, sizeof(T));\
	}\
	__attribute__((unused))\
	static inline int vec_##T##_prepend(vec_##T##_t **vec, const T *array, size_t len) {\
		return vec_generic_prepend((vec_t**)vec, (void*)array, len, sizeof(T));\
	}\

/** Convenient type alias for the generated vectors. */
#define VEC(T) vec_##T##_t

/** Creates a new vector of type 'T'.
 * \param T The type of vector to create.
 * \return A pointer to the vector object or NULL on failure. */
#define VEC_NEW(T) vec_##T##_new()

/** Deletes vector of type 'T'.
 * \param T The type of vector to create.
 * \param vec The vector to be deleted.
 * \return 0 on success or 1 on failure. */
#define VEC_DEL(T, vec) vec_##T##_del((vec))

/** Appends 'value' at the end of 'vec'
 * \param T The type of the vector.
 * \param vec The vector to be modified.
 * \param value The value to be appended.
 * \return Returns 0 on success or 1 on failure. */
#define VEC_PUSH(T, vec, value) vec_##T##_push((vec), (value))

/** Removes and copies the last element of 'vec' into 'value'.
 * \param T The type of the vector.
 * \param vec The vector to be modified.
 * \param value A pointer to the variable to copy data into (can be NULL).
 * \return 0 on success or 1 on failure.  */
#define VEC_POP(T, vec, value) vec_##T##_pop((vec), (value))

/** Copies the value of the element at 'index' into 'value'.
 * \param T The type of the vector.
 * \param vec The vector to be modified.
 * \param index The index to access.
 * \param value A pointer to the variable to copy data into.
 * \return 0 on success or 1 on failure. */
#define VEC_AT(T, vec, index, value)  vec_##T##_at((vec), (index), (value))

/** Removes the 'index'-th element.
 * \param T The type of the vector.
 * \param vec The vector to be modified.
 * \param index The index to remove.
 * \return 0 on success or 1 on failure. */
#define VEC_REMOVE(T, vec, index) vec_##T##_remove((vec), (index))

/** Returns the number of elements stored in 'vec'.
 * \param T The type of the vector.
 * \param vec The vector to access. 
 * \return The number of elements stored in vec or (size_t)-1 on failure. */
#define VEC_LEN(T, vec) vec_##T##_len((vec))

/** Appends an array at the end of the vector.
 * \param T The type of the array (must be the same as the vector)
 * \param vec A pointer to the vector to be modified. 
 * \param array The array to be appeneded at the end of the vector.
 * \param len The length of the array to be appended.
 * \return 0 on success or 1 on failure. */
#define VEC_APPEND(T, vec, array, len) vec_##T##_append((vec), (array), (len))

/** Returns a const pointer to the 'index'-th element.
 * \param T the Type of the vector.
 * \param vec The vector to be accessed.
 * \param index The index of the element to access.
 * \return A const pointer to the element. */
#define VEC_PTR(T, vec, index) vec_##T##_ptr((vec), (index))

/** Copies the content of a vector to another vector.
 * \param T The type of the vectors (they must be of the same type!).
 * \param dst The destination vector. 
 * \param src The source vector.
 * \return 0 on success or 1 on failure. */
#define VEC_CPY(T, dst, src) vec_##T##_cpy((dst), (src))

#define VEC_CAPACITY(T, vec) vec_##T##_capacity((vec))

#define VEC_PREPEND(T, vec, arr, len) vec_##T##_prepend((vec), (arr), (len))

/*****************************************************************************
 * Generic api
 *****************************************************************************/

/** Opaque handle for the generic vector type. */
typedef struct vec vec_t;

/** Creates a new generic vector.
 * \param sizeof_type The size of the type of data to be stored in the vector. 
 * \return A pointer to the new vector. */
vec_t *vec_generic_new(size_t sizeof_type);

/** Deletes a generic vector.
 * \param vec A pointer to the vector to be deleted.
 * \return 0 on success or 1 on failure. */
int vec_generic_del(vec_t **vec, size_t sizeof_type);

/** Appends data at the end of 'vec'.
 * \param vec A pointer to the vector to be modified.
 * \param value A pointer to the variable holding the value
 * to be pushed at the end of 'vec'.
 * \return 0 on success or 1 on failure. */
int vec_generic_push(vec_t **vec, const void *value, size_t sizeof_type);

/** Removes the last element of 'vec' and copies its value into 'value'.
 * \param vec A pointer to the vector to be modified. 
 * \param value A pointer to the variable to copy the data into (can be NULL).
 * \return Returns 0 on success or 1 on failure. */
int vec_generic_pop(vec_t **vec, void *value, size_t sizeof_type);

/** Copies the value of the element stored at the 'index'-th element of 'vec'.
 * \param vec The vector whose data to be accessed. 
 * \param index The index of the element to be accessed. 
 * \param value A pointer to the variable to copy the data into.
 * \return 0 on success or 1 on failure. */
int vec_generic_at(const vec_t *vec, size_t index, void *value, size_t sizeof_type);

/** Remove the element found at the 'index'-th element in 'vec'.
 * \param vec The vector to be modified.
 * \param index The index of the lement to be removed.
 * \return 0 on success or 1 on failure. */
int vec_generic_remove(vec_t **vec, size_t index, size_t sizeof_type);

/** Return the length of the vector.
 * \param vec The vector object to access.
 * \return The length of the vector or (size_t)-1 on failure.*/
size_t vec_generic_len(const vec_t *vec);

/** Appends an array at the end of the vector.
 * \param vec A pointer to the vector to be modified. 
 * \param arr The array to be appeneded at the end of the vector.
 * \param len The length of the array to be appended.
 * \param sizeof_type The size of the array type (must be the same as the vec type).
 * \return 0 on success or 1 on failure. */
int vec_generic_append(vec_t **vec, const void *arr, size_t len, size_t sizeof_type);

/** Returns a const pointer to the 'index'-th element.
 * \param vec The vector to be accessed.
 * \param index The index of the element to access.
 * \param sizeof_type The size of the vector type.
 * \return A const pointer to the element. */
const void *vec_generic_ptr(const vec_t *vec, size_t index, size_t sizeof_type);

/** Copies the content of a vector to another vector.
 * \param dst The destination vector. 
 * \param src The source vector.
 * \param sizeof_type The size of the vector type (they must be the same!).
 * \return 0 on success or 1 on failure. */
int vec_generic_cpy(vec_t **dst, const vec_t *src, size_t sizeof_type);

/** Returns the capacity of the vector.
 * \param vec The vector to be accessed.
 * \param sizeof_type The size of the vector type.
 * \return The capacity of the vector or (size_t)-1 on failure. */
size_t vec_generic_capacity(const vec_t *vec, size_t sizeof_type);

int vec_generic_prepend(vec_t **vec, const void *array, size_t len, size_t sizeof_type);

#endif
