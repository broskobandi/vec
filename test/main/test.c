#include "test_utils.h"

TEST_INIT;

int main(void) {
	/**
	 * Helper functions - private functions
	 * */

	test_vec_new();
	test_vec_del();
	test_vec_push();
	test_vec_pop();
	test_vec_at();
	test_vec_remove();

	/** 
	 * Generic vector - public functions
	 * */

	test_vec_generic_new();
	test_vec_generic_del();
	test_vec_generic_push();
	test_vec_generic_pop();
	test_vec_generic_at();
	test_vec_generic_remove();

	/** 
	 * Type-specific vector - public functions
	 * */

	test_vec_int_new();
	test_vec_int_del();
	test_vec_int_push();
	test_vec_int_pop();
	test_vec_int_at();
	test_vec_int_remove();

	test_print_results();

	return 0;
}
