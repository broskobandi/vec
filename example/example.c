#include <assert.h>
#include <stdio.h>
#include <vec.h>

/* Generate code for the desired vector type.
 * (Be sure to use a type alias for pointer types
 * as the generator doesn't support the '*' pointer
 * syntax.) */
VEC_TYPEDEF(int);

int main(void) {

	/* Create a new vector. */
	VEC(int) vec = VEC_NEW(int);
	if (!vec.is_init) fprintf(stderr, "%s\n", vec_get_err());

	/* Add data to the vector. */
	VEC_PUSH(vec, 0);
	VEC_PUSH(vec, 11);
	VEC_PUSH(vec, 2);
	VEC_PUSH(vec, 9);

	/* Query the size of the vector. */
	assert(VEC_SIZE(vec) == 4);

	/* Remove the last element */
	VEC_POP(vec);

	/* Remove an arbitrary element. */
	VEC_REMOVE(vec, 1);

	/* Insert a new element. */
	VEC_INSERT(vec, 1, 1);

	/* Get a const reference of an element. */
	for (size_t i = 0; i < VEC_SIZE(vec); i++) {
		assert(*VEC_AT_CONST(vec, i) == (int)i);
	}

	/* Get a mutable reference of an element. */
	for (size_t i = 0; i < VEC_SIZE(vec); i++) {
		*VEC_AT(vec, i) = (int)i + 1;
	}
	for (size_t i = 0; i < VEC_SIZE(vec); i++) {
		assert(*VEC_AT_CONST(vec, i) == (int)i + 1);
	}

	/* Clear the vector. */
	VEC_CLEAR(vec);

	/* All functions return 1, (size_t)-1, or NULL on failure 
	 * and 0, valid size_t or pointer value on success. */
	assert(VEC_POP(vec) == 1);

	/* The error message can be queried in case of a failure. */
	fprintf(stderr, "%s\n", vec_get_err());

	/* As an alternative to the macro based workflow, 
	 * you can either use the function pointers (this is what 
	 * the macros do under the hood)... */
	vec.push(&vec, 5);

	/* ...or to avoid the overhead associated with function pointers, 
	 * use the generated functions directly. */
	vec_int_push(&vec, 5);

	/* For maximum performance but minimal type-safety, you
	 * can also use the generic functions directly. These are what the 
	 * generated funtions call under the hood. */
	int value = 5;
	vec_push(vec.__priv, sizeof(int), &value);

	/* Don't forget to delete the vector as the underlying data is 
	 * dynamically allocated. */
	VEC_DEL(vec);

	return 0;
}
