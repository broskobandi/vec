#include "vec.h"
#include <test.h>
#include <string.h>

TEST_INIT;

#define DEFAULT_CAPACITY 4

int main(void) {

	{ // vec_new, vec_len, vec_capacity, vec_size
		vec_t *vec = vec_new(sizeof(int));
		ASSERT(vec);
		ASSERT(!vec_len(vec));
		ASSERT(vec_capacity(vec) == DEFAULT_CAPACITY);
		ASSERT(vec_size(vec) == sizeof(int));
		ASSERT(!vec_get_error());
		vec_del(vec);
	}
	{ // Invalid argument
		vec_t *vec = vec_new(3);
		ASSERT(!vec);
		ASSERT(!strcmp(vec_get_error(), "Invalid argument."));
	}
	{ // vec_push and vec_pop
		vec_t *vec = vec_new(sizeof(int));
		int in = 5;
		int out = 0;
		ASSERT(!vec_push(vec, &in, sizeof(int)));
		ASSERT(!vec_pop(vec, &out, sizeof(int)));
		ASSERT(in == out);
		vec_del(vec);
	}
	{ // resize
		const size_t ITER = 1000;
		vec_t *vec = vec_new(sizeof(size_t));
		size_t expected_capacity = vec_capacity(vec);
		for (size_t i = 0; i < ITER; i++) {
			if (vec_len(vec) + 1 > vec_capacity(vec))
				expected_capacity *= 2;
			ASSERT(!vec_push(vec, &i, sizeof(i)));
			ASSERT(vec_capacity(vec) == expected_capacity);
			ASSERT(vec_len(vec) == i + 1);
		}
		for (size_t i = ITER; i > 0; i--) {
			if (
				vec_len(vec) - 1 <= vec_capacity(vec) / 2 &&
				vec_capacity(vec) / 2 >= DEFAULT_CAPACITY
			) {
				expected_capacity /= 2;
			}
			vec_pop(vec, NULL, sizeof(i));
			ASSERT(vec_capacity(vec) == expected_capacity);
			ASSERT(vec_len(vec) == i - 1);
		}
		vec_del(vec);
	}

	test_print_results();

	return 0;
}
