/* Include the library. */
#include <vec.h>
#include <assert.h>

/* Generate type-safe function declarations (if using type-safe wrapeprs) */
typedef_vec(int);

int main(void) {
	/**********************************************************************
	 * Type-safe functions
	 *********************************************************************/

	/* Create a vector of any type */
	vec(int) vec_int = vec_new(int);

	/* Append a new item at the end. */
	vec_push_back(vec_int, 4);

	/* Prepend a new item at the beginning. */
	vec_push_front(vec_int, 3);

	/* Remove and return the value at the end. */
	assert(vec_pop_back(vec_int) == 4);

	/* Remove and return the value at the beginning. */
	assert(vec_pop_front(vec_int) == 3);

	/* Query the length of the vector. */
	assert(vec_len(vec_int) == 0);

	/* Query the capacity of the vector. (8 is the default capacity) */
	assert(vec_capacity(vec_int) == 8);

	/* Append an array at the end. */
	int arr_int1[] = {9, 4, 5, 6};
	vec_append(vec_int, arr_int1, sizeof(arr_int1));

	/* Prepend an array at the beginning. */
	int arr_int2[] = {0, 1, 2};
	vec_prepend(vec_int, arr_int2, sizeof(arr_int2));

	/* Remove an item. */
	vec_remove(vec_int, 3);

	/* Insert an item. */
	vec_insert(vec_int, 3, 3);

	/* Receive const pointer to any member. */
	assert(*(int*)vec_view(vec_int, 3) == 3);

	/* Get a copy of a member. */
	assert(vec_at(vec_int, 2) == 2);

	/* Replace a member with another value. */
	vec_replace(vec_int, 3, 3);

	/* Replace a range of members with an array. */
	int arr_int3[] = {9, 8, 7, 6, 5, 4, 3};
	vec_replace_range(vec_int, arr_int3, sizeof(arr_int3), 3, 2);

	/* Delete the vector. */
	vec_del(vec_int);

	/**********************************************************************
	 * Generic functions
	 *********************************************************************/

	/* Create a vector of any type. */
	vec_generic_t *vec = vec_generic_new(sizeof(int));

	/* Append a new item at the end. */
	int value = 4;
	vec_generic_push_back(vec, &value, sizeof(int));

	/* Prepend a new item at the beginning. */
	value = 3;
	vec_generic_push_front(vec, &value, sizeof(int));

	/* Remove and return the value at the end. */
	vec_generic_pop_back(vec, &value, sizeof(int));

	/* Remove and return the value at the beginning. */
	vec_generic_pop_front(vec, &value, sizeof(int));

	/* Query the length of the vector. */
	assert(vec_generic_len(vec) == 0);

	/* Query the capacity of the vector. (8 is the default capacity) */
	assert(vec_generic_capacity(vec) == 8);

	/* Append an array at the end. */
	int arr1[] = {9, 4, 5, 6};
	vec_generic_append(vec, arr1, 4, sizeof(int));

	/* Prepend an array at the beginning. */
	int arr2[] = {0, 1, 2};
	vec_generic_prepend(vec, arr2, 3, sizeof(int));

	/* Remove an item. */
	vec_generic_remove(vec, 3);

	/* Insert an item. */
	value = 3;
	vec_generic_insert(vec, &value, 3, sizeof(int));

	/* Receive const pointer to any member. */
	assert(*(int*)vec_generic_view(vec, 3) == 3);

	/* Get a copy of a member. */
	vec_generic_at(vec, &value, 2, sizeof(int));

	/* Replace a member with another value. */
	vec_generic_replace(vec, &value, 4, sizeof(int));

	/* Replace a range of members with an array. */
	int arr3[] = {9, 8, 7, 6, 5, 4, 3};
	vec_generic_replace_range(vec, &arr3, 7, 3, 2, sizeof(int));

	/* Delete the vector. */
	vec_generic_del(vec);

	return 0;
}
