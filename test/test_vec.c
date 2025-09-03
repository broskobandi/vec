#include "test_utils.h"
#include "vec_utils.h"
#include <error.h>

/** 
 * Helper functions - private functions
 * */

void test_vec_new() {
	{ // Normal case
		vec_t *vec = vec_new(sizeof(int));
		ASSERT(vec);
		ASSERT(vec->capacity == DEFAULT_CAPACITY);
		ASSERT(vec->data == (unsigned char*)vec + ROUNDUP(sizeof(vec_t)));
		ASSERT(vec->len == 0);
		ASSERT(vec->size == sizeof(int));
		vec_del(&vec);
	}
}

void test_vec_del() {
	{ // Normal case
		vec_t *vec = vec_new(sizeof(int));
		vec_del(&vec);
		ASSERT(!vec);
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
		vec_del(&vec);
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
		vec_del(&vec);
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
		vec_del(&vec);
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
		ASSERT(!vec_remove(&vec, DEFAULT_CAPACITY / 2));
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
		vec_del(&vec);
	}
}

/** 
 * Generic vector - public functiong
 * */

void test_vec_generic_new() {
	{ // Normal case
		vec_t *vec = vec_generic_new(sizeof(int));
		ASSERT(vec);
		ASSERT(vec->size == sizeof(int));
		ASSERT(vec->capacity == DEFAULT_CAPACITY);
		ASSERT(vec->len == 0);
		ASSERT(vec->data == (unsigned char*)vec + ROUNDUP(sizeof(vec_t)));
		vec_del(&vec);
	}
	{ // size is 0.
		vec_t *vec = vec_generic_new(0);
		ASSERT(!vec);
		vec_del(&vec);
	}
}

void test_vec_generic_del() {
	{ // Normal case
		vec_t *vec = vec_generic_new(sizeof(int));
		ASSERT(!vec_generic_del(&vec, sizeof(int)));
		ASSERT(!vec);
		vec_del(&vec);
	}
	{ // no ptr
		ASSERT(vec_generic_del(NULL, sizeof(int)));
	}
	{ // vec is NULL
		vec_t *vec = NULL;
		ASSERT(vec_generic_del(&vec, sizeof(int)));
	}
	{ // invalid ptr
		vec_t *vec = vec_new(sizeof(char));
		ASSERT(vec_generic_del(&vec, sizeof(int)));
		vec_del(&vec);
	}
}

void test_vec_generic_push() {
	{ // Normal case
		vec_t *vec = vec_new(sizeof(int));
		int value = 5;
		ASSERT(!vec_generic_push(&vec, &value, sizeof(int)));
		vec_del(&vec);
	}
	{ // Invalid arguments
		vec_t *vec = NULL;
		int value = 5;
		ASSERT(vec_generic_push(NULL, &value, sizeof(int)));
		ASSERT(vec_generic_push(&vec, &value, sizeof(int)));
		vec = vec_generic_new(sizeof(int));
		ASSERT(vec_generic_push(&vec, NULL, sizeof(int)));
		vec_del(&vec);
	}
	{ // Invalid pointer
		vec_t *vec = vec_generic_new(sizeof(char));
		int value = 5;
		ASSERT(vec_generic_push(&vec, &value, sizeof(int)));
		vec_del(&vec);
	}
}

void test_vec_generic_pop() {
	{ // Normal case
		vec_t *vec = vec_generic_new(sizeof(int));
		int in = 5;
		ASSERT(!vec_generic_push(&vec, &in, sizeof(int)));
		int out = 0;
		ASSERT(!vec_generic_pop(&vec, &out, sizeof(int)));
		ASSERT(in == out);
		vec_del(&vec);
	}
	{ // Invalid arguments
		vec_t *vec = NULL;
		int value = 0;
		ASSERT(vec_generic_pop(NULL, &value, sizeof(int)));
		ASSERT(vec_generic_pop(&vec, &value, sizeof(int)));
		vec = vec_generic_new(sizeof(int));
		ASSERT(vec_generic_pop(&vec, NULL, sizeof(int)));
		vec_del(&vec);
	}
	{ // Invlaid pointer
		vec_t *vec = vec_generic_new(sizeof(char));
		int value = 0;
		ASSERT(vec_generic_pop(&vec, &value, sizeof(int)));
		vec_del(&vec);
	}
	{ // Empty vector
		vec_t *vec = vec_generic_new(sizeof(int));
		int value = 0;
		ASSERT(vec_generic_pop(&vec, &value, sizeof(int)));
		vec_del(&vec);
	}
}

void test_vec_generic_at() {
	{ // Normal case
		vec_t *vec = vec_generic_new(sizeof(int));
		int in = 5;
		ASSERT(!vec_generic_push(&vec, &in, sizeof(int)));
		int out = 0;
		ASSERT(!vec_generic_at(vec, 0, &out, sizeof(int)));
		vec_del(&vec);
	}
	{ // Invalid argument
		vec_t *vec = vec_generic_new(sizeof(int));
		int value = 0;
		ASSERT(vec_generic_at(NULL, 0, &value, sizeof(int)));
		ASSERT(vec_generic_at(vec, 0, NULL, sizeof(int)));
		vec_del(&vec);
	}
	{ // Invalid ptr
		vec_t *vec = vec_generic_new(sizeof(char));
		int value = 0;
		ASSERT(vec_generic_at(vec, 0, &value, sizeof(int)));
		vec_del(&vec);
	}
	{ // Out of bounds
		vec_t *vec = vec_generic_new(sizeof(int));
		int value = 0;
		ASSERT(vec_generic_at(vec, 1, &value, sizeof(int)));
		vec_del(&vec);
	}
}

void test_vec_generic_remove() {
	{ // Normal case
		vec_t *vec = vec_generic_new(sizeof(int));
		int value = 5;
		ASSERT(!vec_generic_push(&vec, &value, sizeof(int)));
		ASSERT(!vec_generic_push(&vec, &value, sizeof(int)));
		ASSERT(!vec_generic_push(&vec, &value, sizeof(int)));
		ASSERT(!vec_generic_remove(&vec, 1, sizeof(int)));
		ASSERT(vec->len == 2);
		vec_del(&vec);
	}
	{ // Invalid argument
		vec_t *vec = NULL;
		ASSERT(vec_generic_remove(NULL, 0, sizeof(int)));
		ASSERT(vec_generic_remove(&vec, 0, sizeof(int)));
	}
	{ // Invalid pointer
		vec_t *vec = vec_generic_new(sizeof(char));
		ASSERT(vec_generic_remove(&vec, 0, sizeof(int)));
		vec_del(&vec);
	}
	{ // Out of bounds
		vec_t *vec = vec_generic_new(sizeof(int));
		int value = 5;
		ASSERT(!vec_generic_push(&vec, &value, sizeof(int)));
		ASSERT(vec_generic_remove(&vec, 1, sizeof(int)));
		vec_del(&vec);
	}
	{ // Empty vec
		vec_t *vec = vec_generic_new(sizeof(int));
		ASSERT(vec_generic_remove(&vec, 0, sizeof(int)));
		vec_del(&vec);
	}
}

/** 
 * Type-specific vector - public functions
 * */

TYPEDEF_VEC(int);

void test_vec_int_new() {
	vec_int_t *vec = vec_int_new();
	ASSERT(vec);
	vec_int_del(&vec);
}

void test_vec_int_del() {
	vec_int_t *vec = vec_int_new();
	vec_int_del(&vec);
	ASSERT(!vec);
	vec_int_del(&vec);
}

void test_vec_int_push() {
	vec_int_t *vec = vec_int_new();
	ASSERT(!vec_int_push(&vec, 5));
	vec_int_del(&vec);
}

typedef struct obj {
	const char *str;
	float f;
	int x;
} obj_t;

TYPEDEF_VEC(obj_t);

void test_vec_obj_pop() {
	{ // Normal case
		vec_obj_t_t *vec = vec_obj_t_new();
		obj_t in = {.f = 2.3f, .x = 5, .str = "src"};
		ASSERT(!vec_obj_t_push(&vec, in));
		obj_t out = vec_obj_t_pop(&vec);
		ASSERT(!memcmp(&in, &out, sizeof(obj_t)));
		vec_obj_t_del(&vec);
	}
	{ // Empty vec
		obj_t empty = {0};
		vec_obj_t_t *vec = vec_obj_t_new();
		obj_t out = vec_obj_t_pop(&vec);
		ASSERT(!memcmp(&empty, &out, sizeof(obj_t)));
		vec_obj_t_del(&vec);
	}
}

void test_vec_int_pop() {
	{ // Normal case
		vec_int_t *vec = vec_int_new();
		vec_int_push(&vec, 5);
		ASSERT(vec_int_pop(&vec) == 5);
		vec_int_del(&vec);
	}
	{ // empty vec
		vec_int_t *vec = vec_int_new();
		ASSERT(vec_int_pop(&vec) == 0);
		vec_int_del(&vec);
	}
}

void test_vec_obj_at() {
	{ // Normal case
		vec_obj_t_t *vec = vec_obj_t_new();
		obj_t in = {.f = 2.3f, .x = 5, .str = "src"};
		ASSERT(!vec_obj_t_push(&vec, in));
		obj_t out = vec_obj_t_at(vec, 0);
		ASSERT(!memcmp(&in, &out, sizeof(obj_t)));
		vec_obj_t_del(&vec);
	}
	{ // Empty vec
		obj_t empty = {0};
		vec_obj_t_t *vec = vec_obj_t_new();
		obj_t out = vec_obj_t_at(vec, 0);
		ASSERT(!memcmp(&empty, &out, sizeof(obj_t)));
		vec_obj_t_del(&vec);
	}
}

void test_vec_int_at() {
	{ // Normal case
		vec_int_t *vec = vec_int_new();
		vec_int_push(&vec, 5);
		ASSERT(vec_int_at(vec, 0) == 5);
		vec_int_del(&vec);
	}
	{ // empty vec
		vec_int_t *vec = vec_int_new();
		ASSERT(vec_int_at(vec, 0) == 0);
		vec_int_del(&vec);
	}
}

void test_vec_int_remove() {
	{ // Normal case
		vec_int_t *vec = vec_int_new();
		vec_int_push(&vec, 5);
		ASSERT(!vec_int_remove(&vec, 0));
		vec_int_del(&vec);
	}
	{ // out of bounds
		vec_int_t *vec = vec_int_new();
		ASSERT(vec_int_remove(&vec, 0));
		vec_int_del(&vec);
	}
}

void test_vec_int_len() {
	{ // Normal case
		vec_int_t *vec = vec_int_new();
		vec_int_push(&vec, 1);
		vec_int_push(&vec, 2);
		vec_int_push(&vec, 3);
		ASSERT(vec_int_len(vec) == 3);
	}
}
