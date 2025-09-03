#include "test_utils.h"
#include "vec_utils.h"
#include <error.h>

void test_vec_new() {
	{ // Normal case
		vec_t *vec = vec_new(sizeof(int));
		ASSERT(vec);
		ASSERT(vec->capacity == DEFAULT_CAPACITY);
		ASSERT(vec->data == (unsigned char*)vec + ROUNDUP(sizeof(vec_t)));
		ASSERT(vec->magic == MAGIC);
		ASSERT(vec->len == 0);
		ASSERT(vec->size == sizeof(int));
	}
}

void test_vec_push() {
	{ // Normal case
		vec_t *vec = vec_new(sizeof(size_t));

		size_t expected_capacity = DEFAULT_CAPACITY;
		for (size_t i = 0; i < DEFAULT_CAPACITY * 10; i++) {
			ASSERT(!vec_push(&vec, &i));
			if (vec->len > expected_capacity)
				expected_capacity *= 2;
			ASSERT(vec->capacity == expected_capacity);
			ASSERT(vec->len == i + 1);
			size_t *data = (size_t*)vec->data;
			ASSERT(data[i] == i);
		}

	}
}

void test_vec_pop() {
	{ // Normal case 
		vec_t *vec = vec_new(sizeof(size_t));
		const size_t ITER = DEFAULT_CAPACITY * 10;
		for (size_t i = 0; i < ITER; i++) {
			ASSERT(!vec_push(&vec, &i));
		}
		size_t expected_capacity = vec->capacity;
		for (size_t i = ITER; i > 0; i--) {
			size_t value = 0;
			ASSERT(!vec_pop(&vec, &value));
			ASSERT(value == i - 1);
			ASSERT(vec->len == i - 1);
			if (
				vec->len <= expected_capacity / 2 &&
				expected_capacity / 2 >= DEFAULT_CAPACITY
			) {
				expected_capacity /= 2;
			}
			ASSERT(vec->capacity == expected_capacity);
		}
	}
}

void test_vec_at() {
	{ // Normal case
		vec_t *vec = vec_new(sizeof(int));
		int value1 = 1;
		int value2 = 2;
		int value3 = 3;
		ASSERT(!vec_push(&vec, &value1));
		ASSERT(!vec_push(&vec, &value2));
		ASSERT(!vec_push(&vec, &value3));
		int value4 = 0;
		int value5 = 0;
		int value6 = 0;
		vec_at(vec, 0, &value4);
		vec_at(vec, 1, &value5);
		vec_at(vec, 2, &value6);
		ASSERT(value4 == value1);
		ASSERT(value5 == value2);
		ASSERT(value6 == value3);
	}
}

void test_vec_remove() {
	{ // Normal case
		vec_t *vec = vec_new(sizeof(size_t));
		for (size_t i = 0; i < DEFAULT_CAPACITY + 1; i++) {
			ASSERT(!vec_push(&vec, &i));
		}
		ASSERT(vec->len == DEFAULT_CAPACITY + 1);
		ASSERT(vec->capacity == DEFAULT_CAPACITY * 2);
		vec_remove(&vec, DEFAULT_CAPACITY / 2);
		ASSERT(vec->capacity == DEFAULT_CAPACITY);
		ASSERT(vec->len == DEFAULT_CAPACITY);
		for (size_t i = 0; i < DEFAULT_CAPACITY; i++) {
			size_t value = 0;
			vec_at(vec, i, &value);
			if (i >= DEFAULT_CAPACITY / 2) {
				ASSERT(value == i + 1);
			} else {
				ASSERT(value == i);
			}
		}
	}
}
