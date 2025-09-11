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

/** \file src/vec.c
 * \brief Implementation for the vec libary.
 * \details This file contains the definitions of the public funcions 
 * for the vec library. */

#include "vec_private.h"

/** Creates a new vector.
 * \param sizeof_type The size of the vector's type. 
 * \return A pointer to the vector. */
vec_t *vec_new(size_t sizeof_type) {
	vec_t *vec = mem_alloc(sizeof(vec_t));
	if (!vec) return NULL;
	vec->data = mem_alloc(sizeof_type * DEFAULT_CAPACITY);
	if (!vec->data) return NULL;
	vec->capacity = DEFAULT_CAPACITY;
	vec->len = 0;
	vec->sizeof_type = sizeof_type;
	return vec;
}

/** Deletes a vector.
 * \param vec A pointer to the vector to be deleted.
 * \return 0 on success or 1 on failure. */
int vec_del(vec_t *vec) {
	if (!vec) return 1;
	if (vec->data)
		if (mem_free(vec->data) == -1)
			return 1;
	if (mem_free(vec) == -1)
		return 1;
	return 0;
}

/** Appends an item at the end of the vector.
 * \param vec A pointer to the vector to be modified.
 * \param value A pointer to the value to be appended.
 * \param sizeof_type The size of the item's type (must be the 
 * same as the vector's type's).
 * \return 0 on success or 1 on failure. */
int vec_push_back(vec_t *vec, const void *value, size_t sizeof_type) {
	if (!vec || !value || sizeof_type != vec->sizeof_type)
		return 1;
	if (vec->len + 1 > vec->capacity)
		if (resize(vec, vec->capacity * 2))
			return 1;
	memcpy(&vec->data[vec->len * sizeof_type], value, sizeof_type);
	vec->len++;
	return 0;
}

/** Prepends an item at the beginning of the vector.
 * \param vec A pointer to the vector to be modified.
 * \param value A pointer to the value to be prepended.
 * \param sizeof_type The size of the item's type (must be the 
 * same as the vector's type's).
 * \return 0 on success or 1 on failure. */
int vec_push_front(vec_t *vec, const void *value, size_t sizeof_type) {
	if (!vec || !value || sizeof_type != vec->sizeof_type)
		return 1;
	if (vec->len + 1 > vec->capacity)
		if (resize(vec, vec->capacity * 2))
			return 1;
	memmove(&vec->data[sizeof_type], vec->data, vec->len * sizeof_type);
	memcpy(vec->data, value, sizeof_type);
	vec->len++;
	return 0;
}

/** Removes and copies the value of the last member into 'value'.
 * \param vec A pointer to the vector to be modified.
 * \param value A pointer to the variable to copy the value into
 * (can be NULL).
 * \param sizeof_type The size of the variable's type (must be the 
 * same as the vector's type's).
 * \return 0 on success or 1 on failure. */
int vec_pop_back(vec_t *vec, void *value, size_t sizeof_type) {
	if (!vec || sizeof_type != vec->sizeof_type)
		return 1;
	if (value)
		memcpy(value, &vec->data[(vec->len - 1) * sizeof_type], sizeof_type);
	if (
		vec->len - 1 <= vec->capacity / 2 &&
		vec->capacity / 2 >= DEFAULT_CAPACITY
	) {
		if (resize(vec, vec->capacity / 2))
			return 1;
	}
	vec->len--;
	return 0;
}

/** Removes and copies the value of the first member into 'value'.
 * \param vec A pointer to the vector to be modified.
 * \param value A pointer to the variable to copy the value into
 * (can be NULL).
 * \param sizeof_type The size of the variable's type (must be the 
 * same as the vector's type's).
 * \return 0 on success or 1 on failure. */
int vec_pop_front(vec_t *vec, void *value, size_t sizeof_type) {
	if (!vec || sizeof_type != vec->sizeof_type)
		return 1;
	if (value)
		memcpy(value, vec->data, sizeof_type);
	memmove(vec->data, &vec->data[sizeof_type], vec->len * sizeof_type);
	if (
		vec->len - 1 <= vec->capacity / 2 &&
		vec->capacity / 2 >= DEFAULT_CAPACITY
	) {
		if (resize(vec, vec->capacity / 2))
			return 1;
	}
	vec->len--;
	return 0;
}

/** Returns the length of the vector.
 * \param vec A pointer to the vector to be accessed. 
 * \return The length of the vector or (size_t)-1 on failure. */
size_t vec_len(const vec_t *vec) {
	if (!vec) return (size_t)-1;
	return vec->len;
}

/** Returns the capacity of the vector.
 * \param vec A pointer to the vector to be accessed. 
 * \return The capacity of the vector or (size_t)-1 on failure. */
size_t vec_capacity(const vec_t *vec) {
	if (!vec) return (size_t)-1;
	return vec->capacity;
}

/** Removes a member of the vector (and shrinks the vector).
 * \param vec A pointer to the vector to be modified. 
 * \param index The index of the member to be removed.
 * \return 0 on success or 1 on failure. */
int vec_remove(vec_t *vec, size_t index) {
	if (!vec || index >= vec->len) return 1;

	size_t len_to_move = vec->len - index - 1;
	memmove(
		&vec->data[index * vec->sizeof_type],
		&vec->data[(index + 1) * vec->sizeof_type],
		len_to_move * vec->sizeof_type);
	if (
		vec->len - 1 <= vec->capacity / 2 &&
		vec->capacity / 2 >= DEFAULT_CAPACITY
	) {
		if (resize(vec, vec->capacity / 2))
			return 1;
	}
	vec->len--;

	return 0;
}

/** Inserts an item into the vector.
 * \param vec A pointer to the vector to be modified. 
 * \param value A pointer to the value to be inserted. 
 * \param index The index at which the value is to be inserted.
 * \param sizeof_type The size of the item's type (must be the same as the 
 * vector's type's).
 * \return 0 on success or 1 on failure. */
int vec_insert(vec_t *vec, const void *value, size_t index, size_t sizeof_type) {
	if (
		!vec || !value || index >= vec->len ||
		sizeof_type != vec->sizeof_type
	) {
		return 1;
	}

	if (vec->len + 1 > vec->capacity)
		if (resize(vec, vec->capacity * 2))
			return 1;
	size_t len_to_move = vec->len - index;
	memmove(
		&vec->data[(index + 1) * sizeof_type],
		&vec->data[index * sizeof_type], len_to_move * sizeof_type
	);
	memcpy(&vec->data[index * sizeof_type], value, sizeof_type);
	vec->len++;

	return 0;
}

/** Copies the value of the vector's member into 'value'.
 * \param vec A pointer to the vecetor to be accessed.
 * \param value A pointer to the variable to copy the value into.
 * \param index The index of the member whose value is to be copied. 
 * \param sizeof_type The size of the variable's type (must be the same 
 * vector's type's).
 * \return 0 on success or 1 on failure. */
int vec_at(const vec_t *vec, void *value, size_t index, size_t sizeof_type) {
	if (
		!vec || !value || index >= vec->len ||
		sizeof_type != vec->sizeof_type
	) {
		return 1;
	}

	memcpy(value, &vec->data[index * sizeof_type], sizeof_type);

	return 0;
}

/** Appends an array at the end of the vector.
 * \param vec A pointer to the vector tobe modified.
 * \param arr The array to be appended.
 * \param len The length of the array.
 * \param sizeof_type The size of the array's type (must be the same 
 * as the vector's type's).
 * \return 0 on success or 1 on failure. */
int vec_append(vec_t *vec, const void *arr, size_t len, size_t sizeof_type) {
	if (!vec || !arr || sizeof_type != vec->sizeof_type)
		return 1;

	size_t required_capacity =
		((vec->len + len + DEFAULT_CAPACITY - 1) &
		 ~(DEFAULT_CAPACITY - 1));
	if (required_capacity > vec->capacity)
		if (resize(vec, required_capacity))
			return 1;

	memcpy(&vec->data[vec->len * sizeof_type], arr, len * sizeof_type);

	vec->len += len;

	return 0;
}

/** Prepends an array at the beginning of the vector.
 * \param vec A pointer to the vector tobe modified.
 * \param arr The array to be prepended.
 * \param len The length of the array.
 * \param sizeof_type The size of the array's type (must be the same 
 * as the vector's type's).
 * \return 0 on success or 1 on failure. */
int vec_prepend(vec_t *vec, const void *arr, size_t len, size_t sizeof_type) {
	if (!vec || !arr || sizeof_type != vec->sizeof_type)
		return 1;

	size_t required_capacity =
		((vec->len + len + DEFAULT_CAPACITY - 1) &
		 ~(DEFAULT_CAPACITY - 1));
	if (required_capacity > vec->capacity)
		if (resize(vec, required_capacity))
			return 1;

	memmove(&vec->data[len * sizeof_type], vec->data, vec->len * sizeof_type);
	memcpy(vec->data, arr, len * sizeof_type);

	vec->len += len;

	return 0;
}

/** Replaces a member of the vector.
 * \param vec A pointer to the verctor to be modified.
 * \param value A pointer to the varible whose value is to be copied.
 * \param index The index of the member to be replaced.
 * \param sizeof_type The size of the item's type (must be the same 
 * as the vector's type's).*/
int vec_replace(vec_t *vec, const void *value, size_t index, size_t sizeof_type) {
	if (!vec || !value || index >= vec->len || sizeof_type != vec->sizeof_type)
		return 1;

	memcpy(&vec->data[index * sizeof_type], value, sizeof_type);

	return 0;
}

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
) {
	if (
		!vec || !arr || index >= vec->len || range > vec->len ||
		sizeof_type != vec->sizeof_type)
	{
		return 1;
	} 

	size_t required_capacity =
		((vec->len - range + len + DEFAULT_CAPACITY - 1) &
		 ~(DEFAULT_CAPACITY - 1));
	if (
		required_capacity > vec->capacity ||
		(required_capacity <= vec->capacity / 2 &&
		 vec->capacity / 2 >= DEFAULT_CAPACITY)
	) {
		if (resize(vec, required_capacity))
			return 1;
	}

	void *src = &vec->data[(index + range) * sizeof_type];
	void *dst = &vec->data[(index + len) * sizeof_type];
	memmove(dst, src, (vec->len - index + range) * sizeof_type);
	memcpy(&vec->data[index * sizeof_type], arr, len * sizeof_type);

	vec->len = vec->len - range + len;

	return 0;
}

/** Returns a const pointer to a member of the vector.
 * \param vec A pointer to the vector to be accessed.
 * \param index The index to return a pointer to.
 * \return A pointer to the member or NULL on failure. */
const void *vec_view(const vec_t *vec, size_t index) {
	if (!index || index >= vec->len) return NULL;
	return &vec->data[index * vec->sizeof_type];
}
