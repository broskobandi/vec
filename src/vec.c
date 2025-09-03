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
 * \file src/vec.c
 * \brief Implementation for the vec library.
 * \details This file contains the definitions of the public functions.
 * */

#include "vec_utils.h"

/** Creates a new generic vector.
 * \param size The size of the type of data to be stored in the vector. 
 * \return A pointer to the new vector. */
vec_t *vec_generic_new(size_t size) {
	if (!size) RET_ERR("size cannot be 0.", NULL);
	RET_OK(vec_new(size));
}

/** Deletes a generic vector.
 * \param vec A pointer to the vector to be deleted.
 * \return 0 on success or 1 on failure. */
int vec_generic_del(vec_t **vec, size_t sizeof_type) {
	if (!vec || !*vec) RET_ERR("vec cannot be NULL.", 1);
	if ((*vec)->size != sizeof_type) RET_ERR("Invalid pointer.", 1);
	vec_del(vec);
	RET_OK(0);
}

/** Appends data at the end of 'vec'.
 * \param vec A pointer to the vector to be modified.
 * \param value A pointer to the variable holding the value
 * to be pushed at the end of 'vec'.
 * \return 0 on success or 1 on failure. */
int vec_generic_push(vec_t **vec, const void *value, size_t sizeof_type) {
	if (!vec || !*vec || !value) RET_ERR("Invalid argument.", 1);
	if ((*vec)->size != sizeof_type) RET_ERR("Invalid pointer.", 1);
	if (vec_push(vec, value)) RET_ERR("vec_push() failed.", 1);
	RET_OK(0);
}

/** Removes the last element of 'vec' and copies its value into 'value'.
 * \param vec A pointer to the vector to be modified. 
 * \param value A pointer to the variable to copy the data into. 
 * \return Returns 0 on success or 1 on failure. */
int vec_generic_pop(vec_t **vec, void *value, size_t sizeof_type) {
	if (!vec || !*vec || !value) RET_ERR("Invalid argument.", 1);
	if ((*vec)->size != sizeof_type) RET_ERR("Invalid pointer.", 1);
	if (!(*vec)->len) RET_ERR("Empty vector cannot be popped.", 1);
	if (vec_pop(vec, value)) RET_ERR("vec_pop() failed.", 1);
	RET_OK(0);
}

/** Copies the value of the element stored at the 'index'-th element of 'vec'.
 * \param vec The vector whose data to be accessed. 
 * \param index The index of the element to be accessed. 
 * \param value A pointer to the variable to copy the data into.
 * \return 0 on success or 1 on failure. */
int vec_generic_at(const vec_t *vec, size_t index, void *value, size_t sizeof_type) {
	if (!vec || !value) RET_ERR("Invalid argument.", 1);
	if (vec->size != sizeof_type) RET_ERR("Invalid pointer.", 1);
	if (index >= vec->len) RET_ERR("Requested index is out of bounds.", 1);
	vec_at(vec, index, value);
	RET_OK(0);
}

/** Remove the element found at the 'index'-th element in 'vec'.
 * \param vec The vector to be modified.
 * \param index The index of the lement to be removed.
 * \return 0 on success or 1 on failure. */
int vec_generic_remove(vec_t **vec, size_t index, size_t sizeof_type) {
	if (!vec || !*vec)  RET_ERR("Invalid argument.", 1);
	if ((*vec)->size != sizeof_type) RET_ERR("Invalid pointer.", 1);
	if (index >= (*vec)->len) RET_ERR("Requested index is out of bounds.", 1);
	if (!(*vec)->len) RET_ERR("Cannot call vec_remove() on empty vector.", 1);
	if (vec_remove(vec, index)) RET_ERR("vec_remove() failed.", 1);
	RET_OK(0);
}

/** Return the length of the vector.
 * \param vec The vector object to access.
 * \return The length of the vector.*/
size_t vec_generic_len(const vec_t *vec) {
	if (!vec) RET_ERR("'vec' cannot be NULL.", (size_t)-1);
	return vec->len;
}
