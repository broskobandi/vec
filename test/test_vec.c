#include "test_utils.h"
#include "vec_utils.h"

void test_vec_new() {
	{ // Normal case
		vec_t *vec = vec_new(sizeof(int));
		ASSERT(vec);
		ASSERT(vec->capacity == DEFAULT_ALLOC(sizeof(int)) - ROUNDUP(sizeof(vec_t)));
		ASSERT(vec->data == (unsigned char*)vec + ROUNDUP(sizeof(vec_t)));
		ASSERT(vec->magic == MAGIC);
		ASSERT(vec->len == 0);
	}
	

}
