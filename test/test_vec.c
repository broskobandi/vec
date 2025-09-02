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
		// vec_t *vec = vec_new(sizeof(size_t));

		// for (size_t i = 0; i < vec->capacity * 2; i++) {
			// vec_push(vec, &i);
			// ASSERT(vec->capacity == );
			// ASSERT(vec->len == i + 1);
			// size_t *data = (size_t*)vec->data;
			// ASSERT(data[i] == i);
		// }

	}
}
