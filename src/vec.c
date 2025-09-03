#include "vec_utils.h"

void *vec_generic_new(size_t size) {
	if (!size) RET_ERR("size cannot be 0.", NULL);
	RET_OK(vec_new(size));
}

void vec_generic_del(void **vec) {
	if (!vec || !*vec) RET_ERR("vec cannot be NULL.");
	vec_t **v = (vec_t**)vec;
	if ((*v)->magic != MAGIC) RET_ERR("Invalid pointer.");
	vec_del(v);
}

void vec_generic_push(void **vec, const void *value) {
	if (!vec || !*vec || !value) RET_ERR("Invalid argument.");
	vec_t **v = (vec_t**)vec;
	if ((*v)->magic != MAGIC) RET_ERR("Invalid pointer.");
	vec_push(v, value);
}

int vec_generic_pop(void **vec, void *value) {
	if (!vec || !*vec || !value) RET_ERR("Invalid argument.", 1);
	vec_t **v = (vec_t**)vec;
	if ((*v)->magic != MAGIC) RET_ERR("Invalid pointer.", 1);
	if (!(*v)->len) RET_ERR("Empty vector cannot be popped.", 1);
	RET_OK(0);
}

int vec_generic_at(const void *vec, size_t index, void *value) {
	if (!vec || !value) RET_ERR("Invalid argument.", 1);
	vec_t *v = (vec_t*)vec;
	if (v->magic != MAGIC) RET_ERR("Invalid pointer.", 1);
	if (index >= v->len) RET_ERR("Requested index is out of bounds.", 1);
	RET_OK(0);
}

// void vec_generic_remove(void *vec, size_t index);
