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

/** Opaque handle for a vec object. */
typedef struct vec vec_t;

/** Creates a new vector.
 * \param sizeof_type The size of the vector's type. 
 * \return A pointer to the vector. */
vec_t *vec_new(size_t sizeof_type);

/** Deletes a vector.
 * \param vec A pointer to the vector to be deleted.
 * \return 0 on success or 1 on failure. */
int vec_del(vec_t *vec);

/** Appends an item at the end of the vector.
 * \param vec A pointer to the vector to be modified.
 * \param value A pointer to the value to be appended.
 * \param sizeof_type The size of the item's type (must be the 
 * same as the vector's type's).
 * \return 0 on success or 1 on failure. */
int vec_push_back(vec_t *vec, const void *value, size_t sizeof_type);

/** Prepends an item at the beginning of the vector.
 * \param vec A pointer to the vector to be modified.
 * \param value A pointer to the value to be prepended.
 * \param sizeof_type The size of the item's type (must be the 
 * same as the vector's type's).
 * \return 0 on success or 1 on failure. */
int vec_push_front(vec_t *vec, const void *value, size_t sizeof_type);

/** Removes and copies the value of the last member into 'value'.
 * \param vec A pointer to the vector to be modified.
 * \param value A pointer to the variable to copy the value into
 * (can be NULL).
 * \param sizeof_type The size of the variable's type (must be the 
 * same as the vector's type's).
 * \return 0 on success or 1 on failure. */
int vec_pop_back(vec_t *vec, void *value, size_t sizeof_type);

/** Removes and copies the value of the first member into 'value'.
 * \param vec A pointer to the vector to be modified.
 * \param value A pointer to the variable to copy the value into
 * (can be NULL).
 * \param sizeof_type The size of the variable's type (must be the 
 * same as the vector's type's).
 * \return 0 on success or 1 on failure. */
int vec_pop_front(vec_t *vec, void *value, size_t sizeof_type);

/** Returns the length of the vector.
 * \param vec A pointer to the vector to be accessed. 
 * \return The length of the vector or (size_t)-1 on failure. */
size_t vec_len(const vec_t *vec);

/** Returns the capacity of the vector.
 * \param vec A pointer to the vector to be accessed. 
 * \return The capacity of the vector or (size_t)-1 on failure. */
size_t vec_capacity(const vec_t *vec);

/** Removes a member of the vector (and shrinks the vector).
 * \param vec A pointer to the vector to be modified. 
 * \param index The index of the member to be removed.
 * \return 0 on success or 1 on failure. */
int vec_remove(vec_t *vec, size_t index);

/** Inserts an item into the vector.
 * \param vec A pointer to the vector to be modified. 
 * \param value A pointer to the value to be inserted. 
 * \param index The index at which the value is to be inserted.
 * \param sizeof_type The size of the item's type (must be the same as the 
 * vector's type's).
 * \return 0 on success or 1 on failure. */
int vec_insert(vec_t *vec, const void *value, size_t index, size_t sizeof_type);

/** Copies the value of the vector's member into 'value'.
 * \param vec A pointer to the vecetor to be accessed.
 * \param value A pointer to the variable to copy the value into.
 * \param index The index of the member whose value is to be copied. 
 * \param sizeof_type The size of the variable's type (must be the same 
 * vector's type's).
 * \return 0 on success or 1 on failure. */
int vec_at(const vec_t *vec, void *value, size_t index, size_t sizeof_type);

/** Appends an array at the end of the vector.
 * \param vec A pointer to the vector tobe modified.
 * \param arr The array to be appended.
 * \param len The length of the array.
 * \param sizeof_type The size of the array's type (must be the same 
 * as the vector's type's).
 * \return 0 on success or 1 on failure. */
int vec_append(vec_t *vec, const void *arr, size_t len, size_t sizeof_type);

/** Prepends an array at the beginning of the vector.
 * \param vec A pointer to the vector tobe modified.
 * \param arr The array to be prepended.
 * \param len The length of the array.
 * \param sizeof_type The size of the array's type (must be the same 
 * as the vector's type's).
 * \return 0 on success or 1 on failure. */
int vec_prepend(vec_t *vec, const void *arr, size_t len, size_t sizeof_type);

/** Replaces a member of the vector.
 * \param vec A pointer to the verctor to be modified.
 * \param value A pointer to the varible whose value is to be copied.
 * \param index The index of the member to be replaced.
 * \param sizeof_type The size of the item's type (must be the same 
 * as the vector's type's).*/
int vec_replace(vec_t *vec, const void *value, size_t index, size_t sizeof_type);

/** Replaces a range of members in a vector with an array.
 * \param vec A pointer to the vector to be modified.
 * \param arr The array to be inserted. 
 * \param len The length of the array.
 * \param index The index at which the array is t obe inserted.
 * \param range The range of members to be removed from the vector.
 * \param sizeof_type The size of the array's type (must be the same as 
 * the vector's type's).*/
int vec_replace_range(
	vec_t *vec, const void *arr, size_t len,
	size_t index, size_t range, size_t sizeof_type
);

/** Returns a const pointer to a member of the vector.
 * \param vec A pointer to the vector to be accessed.
 * \param index The index to return a pointer to.
 * \return A pointer to the member or NULL on failure. */
const void *vec_view(const vec_t *vec, size_t index);

/** Prints error information if exists. */
void vec_print_err();

#endif
