#include "vec_private.h"
#include <test.h>

TEST_INIT;

void test_vec_new_del() {
	vec_generic_t *vec = vec_generic_new(sizeof(int));
	ASSERT(vec);
	ASSERT(vec->sizeof_type == sizeof(int));
	ASSERT(vec->data);
	ASSERT(!vec->len);
	ASSERT(vec->capacity == DEFAULT_CAPACITY);
	ASSERT(!vec_generic_del(vec));
}

void test_resize() {
	vec_generic_t *vec = vec_generic_new(sizeof(int));
	ASSERT(!resize(vec, DEFAULT_CAPACITY * 2));
	ASSERT(vec->capacity == DEFAULT_CAPACITY * 2);
	vec_generic_del(vec);
}

void test_push_back() {
	{ // no resize
		vec_generic_t *vec = vec_generic_new(sizeof(int));
		int value = 5;
		ASSERT(!vec_generic_push_back(vec, &value, sizeof(int)));
		ASSERT(*(int*)&vec->data[(vec->len - 1) * sizeof(int)] == value);
		ASSERT(vec->capacity == DEFAULT_CAPACITY);
		vec_generic_del(vec);
	}
	{ // resize
		vec_generic_t *vec = vec_generic_new(sizeof(int));
		int value = 5;
		vec->len = vec->capacity;
		ASSERT(!vec_generic_push_back(vec, &value, sizeof(int)));
		ASSERT(*(int*)&vec->data[(vec->len - 1) * sizeof(int)] == value);
		ASSERT(vec->capacity == DEFAULT_CAPACITY * 2);
		vec_generic_del(vec);
	}
}



void test_push_front() {
	{ // no resize
		vec_generic_t *vec = vec_generic_new(sizeof(int));
		for (int i = 0; i < 7; i++)
			vec_generic_push_back(vec, &i, sizeof(int));
		int value = -1;
		vec_generic_push_front(vec, &value, sizeof(int));
		ASSERT(vec->capacity == DEFAULT_CAPACITY);
		ASSERT(*(int*)&vec->data[0] == value);
		ASSERT(*(int*)&vec->data[(vec->len - 1) * sizeof(int)] == 6);
		vec_generic_del(vec);
	}
	{ // resize
		vec_generic_t *vec = vec_generic_new(sizeof(int));
		for (int i = 0; i < 8; i++)
			vec_generic_push_back(vec, &i, sizeof(int));
		int value = -1;
		vec_generic_push_front(vec, &value, sizeof(int));
		ASSERT(vec->capacity == DEFAULT_CAPACITY * 2);
		ASSERT(*(int*)&vec->data[(vec->len - 1) * sizeof(int)] == 7);
		ASSERT(*(int*)&vec->data[0] == value);
		vec_generic_del(vec);
	}
}

void test_pop_back() {
	{ // no resize
		vec_generic_t *vec = vec_generic_new(sizeof(int));
		for (int i = 0; i < 8; i++)
			vec_generic_push_back(vec, &i, sizeof(int));
		ASSERT(vec->capacity == DEFAULT_CAPACITY);
		int value = 0;
		vec_generic_pop_back(vec, &value, sizeof(int));
		ASSERT(vec->capacity == DEFAULT_CAPACITY);
		ASSERT(value == 7);
		vec_generic_del(vec);
	}
	{ // resize
		vec_generic_t *vec = vec_generic_new(sizeof(int));
		for (int i = 0; i < 9; i++)
			vec_generic_push_back(vec, &i, sizeof(int));
		ASSERT(vec->capacity == DEFAULT_CAPACITY * 2);
		int value = 0;
		vec_generic_pop_back(vec, &value, sizeof(int));
		ASSERT(vec->capacity == DEFAULT_CAPACITY);
		ASSERT(value == 8);
		vec_generic_del(vec);
	}
}

void test_pop_front() {
	{ // no resize
		vec_generic_t *vec = vec_generic_new(sizeof(int));
		for (int i = 0; i < 8; i++)
			vec_generic_push_back(vec, &i, sizeof(int));
		ASSERT(vec->capacity == DEFAULT_CAPACITY);
		int value = -1;
		vec_generic_pop_front(vec, &value, sizeof(int));
		ASSERT(*(int*)&vec->data[(vec->len - 1) * sizeof(int)] == 7);
		ASSERT(vec->capacity == DEFAULT_CAPACITY);
		ASSERT(value == 0);
		vec_generic_del(vec);
	}
	{ // resize
		vec_generic_t *vec = vec_generic_new(sizeof(int));
		for (int i = 0; i < 9; i++)
			vec_generic_push_back(vec, &i, sizeof(int));
		ASSERT(vec->capacity == DEFAULT_CAPACITY * 2);
		int value = -1;
		vec_generic_pop_front(vec, &value, sizeof(int));
		ASSERT(*(int*)&vec->data[(vec->len - 1) * sizeof(int)] == 8);
		ASSERT(vec->capacity == DEFAULT_CAPACITY);
		ASSERT(value == 0);
		vec_generic_del(vec);
	}
}

void test_len_and_capacity() {
	vec_generic_t *vec = vec_generic_new(sizeof(int));
	for (int i = 0; i < 9; i++) {
		vec_generic_push_back(vec, &i, sizeof(int));
		ASSERT(vec_generic_len(vec) == vec->len);
		ASSERT(vec_generic_capacity(vec) == vec->capacity);
	}
	vec_generic_del(vec);
}

void test_remove() {
	{ // no resize
		vec_generic_t *vec = vec_generic_new(sizeof(int));
		for (int i = 0; i < 8; i++)
			vec_generic_push_back(vec, &i, sizeof(int));
		ASSERT(vec->capacity == DEFAULT_CAPACITY);
		ASSERT(vec->len == 8);
		vec_generic_remove(vec, 4);
		ASSERT(*(int*)&vec->data[4 * sizeof(int)] == 5);
		ASSERT(vec->len == 7);
		ASSERT(*(int*)&vec->data[(vec->len - 1) * sizeof(int)] == 7);
		ASSERT(vec->capacity == DEFAULT_CAPACITY);
		vec_generic_del(vec);
	}
	{ // resize
		vec_generic_t *vec = vec_generic_new(sizeof(int));
		for (int i = 0; i < 9; i++)
			vec_generic_push_back(vec, &i, sizeof(int));
		ASSERT(vec->capacity == DEFAULT_CAPACITY * 2);
		ASSERT(vec->len == 9);
		vec_generic_remove(vec, 2);
		ASSERT(*(int*)&vec->data[2 * sizeof(int)] == 3);
		ASSERT(vec->len == 8);
		ASSERT(*(int*)&vec->data[(vec->len - 1) * sizeof(int)] == 8);
		ASSERT(vec->capacity == DEFAULT_CAPACITY);
		vec_generic_del(vec);
	}
}

void test_insert() {
	{ // no resize
		vec_generic_t *vec = vec_generic_new(sizeof(int));
		for (int i = 0; i < 7; i++)
			vec_generic_push_back(vec, &i, sizeof(int));
		int value = 5;
		vec_generic_insert(vec, &value, 2, sizeof(int));
		ASSERT(*(int*)&vec->data[3 * sizeof(int)] == 2);
		ASSERT(vec->capacity == DEFAULT_CAPACITY);
		ASSERT(*(int*)&vec->data[2 * sizeof(int)] == value);
		ASSERT(*(int*)&vec->data[(vec->len - 1) * sizeof(int)] == 6);
		vec_generic_del(vec);
	}
	{ // resize
		vec_generic_t *vec = vec_generic_new(sizeof(int));
		for (int i = 0; i < 8; i++)
			vec_generic_push_back(vec, &i, sizeof(int));
		int value = 5;
		vec_generic_insert(vec, &value, 4, sizeof(int));
		ASSERT(*(int*)&vec->data[5 * sizeof(int)] == 4);
		ASSERT(vec->capacity == DEFAULT_CAPACITY * 2);
		ASSERT(*(int*)&vec->data[(vec->len - 1) * sizeof(int)] == 7);
		ASSERT(*(int*)&vec->data[4 * sizeof(int)] == value);
		vec_generic_del(vec);
	}
}

void test_vec_generic_at() {
	{ // no resize
		vec_generic_t *vec = vec_generic_new(sizeof(int));
		for (int i = 0; i < 10; i++) {
			vec_generic_push_back(vec, &i, sizeof(int));
			int value = 0;
			vec_generic_at(vec, &value, (size_t)i, sizeof(int));
			ASSERT(value == i);
		}
		vec_generic_del(vec);
	}
}

void test_append() {
	{ // no resize
		vec_generic_t *vec = vec_generic_new(sizeof(int));
		for (int i = 0; i < 5; i++)
			vec_generic_push_back(vec, &i, sizeof(int));
		ASSERT(vec->capacity == DEFAULT_CAPACITY);
		int arr[] = {5, 6, 7};
		vec_generic_append(vec, arr, 3, sizeof(int));
		ASSERT(vec->capacity == DEFAULT_CAPACITY);
		for (int i = 0; i < 8; i++) {
			int value = -1;
			vec_generic_at(vec, &value, (size_t)i, sizeof(int));
			ASSERT(value == i);
		}
		ASSERT(vec->len == 8);
		vec_generic_del(vec);
	}
	{ // resize
		vec_generic_t *vec = vec_generic_new(sizeof(int));
		for (int i = 0; i < 8; i++)
			vec_generic_push_back(vec, &i, sizeof(int));
		ASSERT(vec->capacity == DEFAULT_CAPACITY);
		int arr[] = {8, 9, 10, 11, 12};
		vec_generic_append(vec, arr, 5, sizeof(int));
		ASSERT(vec->capacity == DEFAULT_CAPACITY * 2);
		for (int i = 0; i < 13; i++) {
			int value = -1;
			vec_generic_at(vec, &value, (size_t)i, sizeof(int));
			ASSERT(value == i);
		}
		ASSERT(vec->len == 13);
		vec_generic_del(vec);
	}
	{ // arr len 0
		vec_generic_t *vec = vec_generic_new(sizeof(int));
		for (int i = 0; i < 5; i++)
			vec_generic_push_back(vec, &i, sizeof(int));
		ASSERT(vec->capacity == DEFAULT_CAPACITY);
		int arr[0];
		vec_generic_append(vec, arr, 0, sizeof(int));
		ASSERT(vec->capacity == DEFAULT_CAPACITY);
		for (int i = 0; i < 5; i++) {
			int value = -1;
			vec_generic_at(vec, &value, (size_t)i, sizeof(int));
			ASSERT(value == i);
		}
		ASSERT(vec->len == 5);
		vec_generic_del(vec);
	}
}

void test_prepend() {
	{ // no resize
		vec_generic_t *vec = vec_generic_new(sizeof(int));
		for (int i = 3; i < 8; i++)
			vec_generic_push_back(vec, &i, sizeof(int));
		ASSERT(vec->capacity == DEFAULT_CAPACITY);
		int arr[] = {0, 1, 2};
		vec_generic_prepend(vec, arr, 3, sizeof(int));
		ASSERT(vec->capacity == DEFAULT_CAPACITY);
		for (int i = 0; i < 8; i++) {
			int value = -1;
			vec_generic_at(vec, &value, (size_t)i, sizeof(int));
			ASSERT(value == i);
		}
		ASSERT(vec->len == 8);
		vec_generic_del(vec);
	}
	{ // resize
		vec_generic_t *vec = vec_generic_new(sizeof(int));
		for (int i = 8; i < 13; i++)
			vec_generic_push_back(vec, &i, sizeof(int));
		ASSERT(vec->capacity == DEFAULT_CAPACITY);
		int arr[] = {0, 1, 2, 3, 4, 5, 6, 7};
		vec_generic_prepend(vec, arr, 8, sizeof(int));
		ASSERT(vec->capacity == DEFAULT_CAPACITY * 2);
		for (int i = 0; i < 13; i++) {
			int value = -1;
			vec_generic_at(vec, &value, (size_t)i, sizeof(int));
			ASSERT(value == i);
		}
		ASSERT(vec->len == 13);
		vec_generic_del(vec);
	}
	{ // no resize
		vec_generic_t *vec = vec_generic_new(sizeof(int));
		for (int i = 3; i < 8; i++)
			vec_generic_push_back(vec, &i, sizeof(int));
		ASSERT(vec->capacity == DEFAULT_CAPACITY);
		int arr[0];
		vec_generic_prepend(vec, arr, 0, sizeof(int));
		ASSERT(vec->capacity == DEFAULT_CAPACITY);
		for (int i = 0; i < 5; i++) {
			int value = -1;
			vec_generic_at(vec, &value, (size_t)i, sizeof(int));
			ASSERT(value == i + 3);
		}
		ASSERT(vec->len == 5);
		vec_generic_del(vec);
	}
}

void test_replace() {
	vec_generic_t *vec = vec_generic_new(sizeof(int));
	int arr[] = {0, 1, 2, 9, 4, 5, 6, 7};
	vec_generic_append(vec, arr, 8, sizeof(int));
	int value = 3;
	vec_generic_replace(vec, &value, 3, sizeof(int));
	for (int i = 0; i < 8; i++) {
		value = -1;
		vec_generic_at(vec, &value, (size_t)i, sizeof(int));
		ASSERT(value == i);
	}
	vec_generic_del(vec);
}

void test_replace_range() {
	{ // shrink
		vec_generic_t *vec = vec_generic_new(sizeof(int));
		int arr1[] = {0, 1, 2, 0, 0, 0, 5, 6};
		vec_generic_append(vec, arr1, 8, sizeof(int));
		ASSERT(vec->len == 8);
		int arr2[] = {3, 4};
		vec_generic_replace_range(vec, arr2, 2, 3, 3, sizeof(int));
		ASSERT(vec->len == 7);
		for (int i = 0; i < 7; i++) {
			int value = -1;
			vec_generic_at(vec, &value, (size_t)i, sizeof(int));
			ASSERT(value == i);
		}
		vec_generic_del(vec);
	}
	{ // expand
		vec_generic_t *vec = vec_generic_new(sizeof(int));
		int arr1[] = {0, 1, 2, 0, 9, 10};
		vec_generic_append(vec, arr1, 6, sizeof(int));
		ASSERT(vec->len == 6);
		int arr2[] = {3, 4, 5, 6, 7, 8};
		vec_generic_replace_range(vec, arr2, 6, 3, 1, sizeof(int));
		ASSERT(vec->len == 11);
		for (int i = 0; i < 11; i++) {
			int value = -1;
			vec_generic_at(vec, &value, (size_t)i, sizeof(int));
			ASSERT(value == i);
		}
		vec_generic_del(vec);
	}
	{ // len 0
		vec_generic_t *vec = vec_generic_new(sizeof(int));
		int arr1[] = {0, 1, 2, 3, 4};
		vec_generic_append(vec, arr1, 5, sizeof(int));
		ASSERT(vec->len == 5);
		int arr2[0];
		vec_generic_replace_range(vec, arr2, 0, 3, 0, sizeof(int));
		ASSERT(vec->len == 5);
		for (int i = 0; i < 5; i++) {
			int value = -1;
			vec_generic_at(vec, &value, (size_t)i, sizeof(int));
			ASSERT(value == i);
		}
		vec_generic_del(vec);
	}
	{ // range 0
		vec_generic_t *vec = vec_generic_new(sizeof(int));
		int arr1[] = {0, 1, 4};
		vec_generic_append(vec, arr1, 3, sizeof(int));
		ASSERT(vec->len == 3);
		int arr2[] = {2, 3};
		vec_generic_replace_range(vec, arr2, 2, 2, 0, sizeof(int));
		ASSERT(vec->len == 5);
		for (int i = 0; i < 5; i++) {
			int value = -1;
			vec_generic_at(vec, &value, (size_t)i, sizeof(int));
			ASSERT(value == i);
		}
		vec_generic_del(vec);
	}
}

void test_vec_generic_view() {
	{ // normal case
		vec_generic_t *vec = vec_generic_new(sizeof(int));
		int arr[] = {0, 1, 2, 3, 4};
		vec_generic_append(vec, arr, 5, sizeof(int));
		ASSERT(*(int*)vec_generic_view(vec, 2) == 2);
		vec_generic_del(vec);
	}
	{ // index 0
		vec_generic_t *vec = vec_generic_new(sizeof(int));
		int arr[] = {0, 1, 2, 3, 4};
		vec_generic_append(vec, arr, 5, sizeof(int));
		ASSERT(*(int*)vec_generic_view(vec, 0) == 0);
		vec_generic_del(vec);
	}
}

int main(void) {
	test_vec_new_del();
	test_resize();
	test_push_back();
	test_push_front();
	test_pop_back();
	test_pop_front();
	test_len_and_capacity();
	test_remove();
	test_insert();
	test_vec_generic_at();
	test_append();
	test_prepend();
	test_replace_range();
	test_replace();
	test_vec_generic_view();

	test_print_results();
	return 0;
}
