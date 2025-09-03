#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <test.h>

/**
 * Helper functions - private functions
 * */

void test_vec_new();
void test_vec_del();
void test_vec_push();
void test_vec_pop();
void test_vec_at();
void test_vec_remove();

/** 
 * Generic vector - public functions
 * */

void test_vec_generic_new();
void test_vec_generic_del();
void test_vec_generic_push();
void test_vec_generic_pop();
void test_vec_generic_at();
void test_vec_generic_remove();

/** 
 * Type-specific vector - public functions
 * */

void test_vec_int_new();
void test_vec_int_del();
void test_vec_int_push();
void test_vec_obj_pop();
void test_vec_int_pop();
void test_vec_obj_at();
void test_vec_int_at();
void test_vec_int_remove();
void test_vec_int_len();

#endif
