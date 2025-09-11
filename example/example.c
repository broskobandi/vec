/* Include the library. */
#include <vec.h>
#include <assert.h>

int main(void) {
	/* Create a vector of any type. */
	vec_t *vec = vec_new(sizeof(int));

	/* Append a new item at the end. */
	int value = 4;
	vec_push_back(vec, &value, sizeof(int));

	/* Prepend a new item at the beginning. */
	value = 3;
	vec_push_front(vec, &value, sizeof(int));

	/* Remove and return the value at the end. */
	vec_pop_back(vec, &value, sizeof(int));

	/* Remove and return the value at the beginning. */
	vec_pop_front(vec, &value, sizeof(int));

	/* Query the length of the vector. */
	assert(vec_len(vec) == 0);

	/* Query the capacity of the vector. (8 is the default capacity) */
	assert(vec_capacity(vec) == 8);

	/* Append an array at the end. */
	int arr1[] = {9, 4, 5, 6};
	vec_append(vec, arr1, 4, sizeof(int));

	/* Prepend an array at the beginning. */
	int arr2[] = {0, 1, 2};
	vec_prepend(vec, arr2, 3, sizeof(int));

	/* Remove an item. */
	vec_remove(vec, 3);

	/* Insert an item. */
	value = 3;
	vec_insert(vec, &value, 3, sizeof(int));

	/* Receive const pointer to any member. */
	assert(*(int*)vec_view(vec, 3) == 3);

	/* Get a copy of a member. */
	vec_at(vec, &value, 2, sizeof(int));

	/* Replace a member with another value. */
	vec_replace(vec, &value, 4, sizeof(int));

	/* Replace a range of members with an array. */
	int arr3[] = {9, 8, 7, 6, 5, 4, 3};
	vec_replace_range(vec, &arr3, 7, 3, 2, sizeof(int));

	/* Delete the vector. */
	vec_del(vec);

	return 0;
}
