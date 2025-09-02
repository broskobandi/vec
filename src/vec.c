#include "vec_utils.h"

void *vec_generic_new(size_t size) {
	if (!size) ERR("size cannot be 0.", NULL);
	OK(vec_new(size));
}

void vec_generic_del(void *vec) {
	if (!vec) ERR("vec cannot be NULL.");
	vec_t *v = (vec_t*)vec;
	if (v->magic != MAGIC) ERR("Invalid pointer.");
	vec_del(v);
}

void vec_generic_push(void *vec, void *value) {
	if (!vec || !value) ERR("Invalid argument.");
	vec_t *v = (vec_t*)vec;
	if (v->magic != MAGIC) ERR("Invalid pointer.");
	vec_push(v, value);
}

// int vec_generic_pop(void *vec, void *value) {
// 	if (!vec || !value) ERR("Invalid argument.");
//
// }

int vec_generic_at(void *vec, size_t index, void *value);
void vec_generic_remove(void *vec, size_t index);
