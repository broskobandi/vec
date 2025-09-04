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
	test_vec_append();
	test_vec_ptr();
	test_vec_cpy();

	/** 
	 * Generic vector - public functions
	 * */

	test_vec_generic_new();
	test_vec_generic_del();
	test_vec_generic_push();
	test_vec_generic_pop();
	test_vec_generic_at();
	test_vec_generic_remove();
	test_vec_generic_append();
	test_vec_generic_ptr();
	test_vec_generic_cpy();
	test_vec_generic_capacity();

	/** 
	 * Type-specific vector - public functions
	 * */

	test_vec_int_new();
	test_vec_int_del();
	test_vec_int_push();
	test_vec_obj_pop();
	test_vec_int_pop();
	test_vec_obj_at();
	test_vec_int_at();
	test_vec_int_remove();
	test_vec_int_len();
	test_vec_int_append();
	test_vec_int_ptr();
	test_vec_int_cpy();
	test_vec_int_capacity();

	test_print_results();

	return 0;
}
