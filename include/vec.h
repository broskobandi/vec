#ifndef VEC_H
#define VEC_H

#include <stddef.h> /* For size_t */

typedef struct vec vec_t;

/** Creates a new vector.
 * \param sizeof_type Size of the vector type.
 * \return A pointer to the vector. */
vec_t *vec_new(size_t sizeof_type);

/** Deletes a vector.
 * \param vec A pointer to the vector to be deleted.
 * \return 0 on success or 1 on failure. */
int vec_del(vec_t *vec);

/** Returns the length of a vector.
 * \param vec A pointer to the vector.
 * \return The length of the vector or (size_t)-1 on failure. */
size_t vec_len(const vec_t *vec);

/** Returns the capacity of a vector.
 * \param vec A pointer to the vector.
 * \return The capacity of the vector or (size_t)-1 on failure. */
size_t vec_capacity(const vec_t *vec);

/** Returns a pointer to the desired index in a vector.
 * \param vec A pointer to the vector.
 * \param index The element to return a pointer to.
 * \return A pointer to the 'index'-th element or NULL on failure. */
void *vec_data(const vec_t *vec, size_t index);

/** Appends a single element at the end of a vector.
 * \param vec A pointer to the vector.
 * \param value A pointer to the value to be pushed. 
 * \param sizeof_type Size of the vector's type 
 * (must be the same as 'value's type).
 * \return 0 on success or 1 on failure. */
int vec_push_back(vec_t *vec, const void *value, size_t sizeof_type);

/** Appends a single element at the beginning of a vector.
 * \param vec A pointer to the vector.
 * \param value A pointer to the value to be pushed. 
 * \param sizeof_type The size of the vector's type 
 * (size of 'value' must be the same).
 * \return 0 on success or 1 on failure. */
int vec_push_front(vec_t *vec, const void *value, size_t sizeof_type);

/** Removes the last element of a vector and copies it to an out parameter.
 * \param vec A pointer to the vector.
 * \param value A pointer to the variabel to copy the value to 
 * (can be NULL).
 * \param sizeof_type Size of the vector's type 
 * (size of value must be the same).
 * \return 0 on success or 1 on failure. */
int vec_pop_back(vec_t *vec, void *value, size_t sizeof_type);

/** Removes the first element of a vector and copies it to an out parameter.
 * \param vec A pointer to the vector.
 * \param value A pointer to the variabel to copy the value to 
 * (can be NULL).
 * \param sizeof_type The size of the vector's type 
 * (size of value must be the same).
 * \return 0 on success or 1 on failure. */
int vec_pop_front(vec_t *vec, void *value, size_t sizeof_type);

/** Appends an array at the end of a vector. 
 * \param vec A pointer to the vector.
 * \param arr The array to be copied.
 * \param len The length of the array.
 * \param sizeof_type The size of the vector's type 
 * (size of the array's type must be the same).
 * \return 0 on success or 1 on failure. */
int vec_append(vec_t *vec, const void *arr, size_t len, size_t sizeof_type);

/** Prepends an array at the beginning of a vector. 
 * \param vec A pointer to the vector.
 * \param arr The array to be copied.
 * \param len The length of the array.
 * \param sizeof_type The size of the vector's type 
 * (size of the array's type must be the same).
 * \return 0 on success or 1 on failure. */
int vec_prepend(vec_t *vec, const void *arr, size_t len, size_t sizeof_type);

/** Removes the 'index'-th element of a vector.
 * \param vec A pointer to the vector.
 * \param index The index of the element to be removed.
 * \return 0 on success or 1 on failure. */
int vec_remove(vec_t *vec, size_t index);

/** Inserts a new element in a vector.
 * \param vec A pointer to the vector.
 * \param value A pointer to the value to be inserted. 
 * \param index The index where the element is to be inserted.
 * \param sizeof_type The size of the vector's type 
 * (size of the value's type must be the same).
 * \return 0 on success or 1 on failure. */
int vec_insert(vec_t *vec, const void *value, size_t index, size_t sizeof_type);

/** Replaces a range of elements in a vector with an array.
 * \param vec A pointer to the vector.
 * \param arr The array to be inserted.
 * \param index The index where the array is to be inserted.
 * \param arr_len The length of the array to be inserted.
 * \param len_to_replace The range to be replaced. 
 * \param sizeof_type The size of the vector's type 
 * (size of the array's type must be the same).
 * \return 0 on success or 1 on failure. */
int vec_replace_range(
	vec_t *vec,
	const void *arr,
	size_t index,
	size_t arr_len,
	size_t len_to_replace,
	size_t sizeof_type
);

#endif
