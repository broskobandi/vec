#include "test_utils.h"

TEST_INIT;

int main(void) {
	test_vec_new();
	test_vec_push();
	test_vec_pop();
	test_vec_at();

	test_print_results();

	return 0;
}
