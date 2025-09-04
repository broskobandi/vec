#include <stdio.h>
#include <stdlib.h>

/* Include the header. */
#include <vec.h>

/* Define the desired vector types. */
/* For built-in types */
TYPEDEF_VEC(int);
TYPEDEF_VEC(float);

/* Or for user defined types. */

typedef struct obj {
	const char *txt;
	float f;
	int i;
} obj_t;

TYPEDEF_VEC(obj_t);

/* Use custom typedef aliases for pointers to create vectors of pointers. */
typedef int* intptr;

TYPEDEF_VEC(intptr);

int main(void) {
	/* Create new instances. */

	VEC(int) *vec_int = VEC_NEW(int);
	VEC(float) *vec_float = VEC_NEW(float);
	VEC(obj_t) *vec_obj  = VEC_NEW(obj_t);
	VEC(intptr) *vec_intptr = VEC_NEW(intptr);

	/* Push new values to the vectors. */
	VEC_PUSH(int, &vec_int, 1);
	VEC_PUSH(int, &vec_int, 2);
	VEC_PUSH(int, &vec_int, 3);
	VEC_PUSH(int, &vec_int, 4);
	VEC_PUSH(float, &vec_float, 1.0f);
	VEC_PUSH(float, &vec_float, 2.0f);
	VEC_PUSH(float, &vec_float, 3.0f);
	VEC_PUSH(float, &vec_float, 4.0f);
	VEC_PUSH(obj_t, &vec_obj, ((obj_t){.f = 1.0f, .i = 1, .txt = "one"}));
	VEC_PUSH(obj_t, &vec_obj, ((obj_t){.f = 2.0f, .i = 2, .txt = "two"}));
	VEC_PUSH(obj_t, &vec_obj, ((obj_t){.f = 3.0f, .i = 3, .txt = "three"}));
	VEC_PUSH(obj_t, &vec_obj, ((obj_t){.f = 4.0f, .i = 4, .txt = "four"}));
	int value = 5;
	VEC_PUSH(intptr, &vec_intptr, &value);
	VEC_PUSH(intptr, &vec_intptr, &value);
	VEC_PUSH(intptr, &vec_intptr, &value);
	VEC_PUSH(intptr, &vec_intptr, &value);

	/* Pop the last element off the vectors and return them.
	 * Out param can be NULL if only the removal of the last element is desired
	 * but the actual value is not important. */
	int last_int = 0;
	VEC_POP(int, &vec_int, &last_int);
	float last_float = 0;
	VEC_POP(float, &vec_float, &last_float);
	obj_t last_obj = {0};
	VEC_POP(obj_t, &vec_obj, &last_obj);
	int *last_ptr = NULL;
	VEC_POP(intptr, &vec_intptr, &last_ptr);

	/* Return a copy of an element. */
	int second_int = 0;
	VEC_AT(int, vec_int, 1, &second_int);
	float second_float = 0;
	VEC_AT(float, vec_float, 1, &second_float);
	obj_t second_obj = {0};
	VEC_AT(obj_t, vec_obj, 1, &second_obj);
	int *second_ptr = NULL;
	VEC_AT(intptr, vec_intptr, 1, &second_ptr);

	/* Remove an element */
	VEC_REMOVE(int, &vec_int, 1);
	VEC_REMOVE(float, &vec_float, 1);
	VEC_REMOVE(obj_t, &vec_obj, 1);
	VEC_REMOVE(intptr, &vec_intptr, 1);

	/* Get the length of the vector. */
	printf("Length of integer vec: %lu\n", VEC_LEN(int, vec_int));
	printf("Length of float vec: %lu\n", VEC_LEN(float, vec_float));
	printf("Length of obj vec: %lu\n", VEC_LEN(obj_t, vec_obj));
	printf("Length of ptr vec: %lu\n", VEC_LEN(intptr, vec_intptr));

	/* Append an array at the end of the vector. */
	VEC_APPEND(int, &vec_int, ((int[]){1, 2, 3}), 3);
	VEC_APPEND(float, &vec_float, ((float[]){1.1f, 2.2f, 3.3f}), 3);
	VEC_APPEND(obj_t, &vec_obj, ((obj_t[]){{0}, {0}, {0}}), 3);
	// int *ptr1 = malloc(sizeof(int));
	// int *ptr2 = malloc(sizeof(int));
	// int *ptr3 = malloc(sizeof(int));
	// int *ptrarr[] = {
	// 	malloc(sizeof(int)),
	// 	malloc(sizeof(int)),
	// 	malloc(sizeof(int)),
	// };
	// VEC_APPEND(intptr, &vec_intptr, ((intptr[]){&value, &value, &value}), 3);
	// VEC_APPEND(intptr, &vec_intptr, ((int*[]){NULL, NULL, NULL}), 3);
	vec_intptr_append(&vec_intptr, (int*[]){NULL, NULL, NULL}, 3);
	// VEC_APPEND(intptr, &vec_intptr, ((intptr[]){ptr1, ptr2, ptr3}), 3);
	// VEC_APPEND(intptr, &vec_intptr, ptrarr, 3);

	/* Don't forget to delete the vectors. */
	VEC_DEL(int, &vec_int);
	VEC_DEL(float, &vec_float);
	VEC_DEL(obj_t, &vec_obj);
	VEC_DEL(intptr, &vec_intptr);

	return 0;
}
