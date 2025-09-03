#include "vec_utils.h"

vec_t *vec_generic_new(size_t size) {
	if (!size) RET_ERR("size cannot be 0.", NULL);
	RET_OK(vec_new(size));
}

int vec_generic_del(vec_t **vec, size_t sizeof_type) {
	if (!vec || !*vec) RET_ERR("vec cannot be NULL.", 1);
	if ((*vec)->size != sizeof_type) RET_ERR("Invalid pointer.", 1);
	vec_del(vec);
	RET_OK(0);
}

int vec_generic_push(vec_t **vec, const void *value, size_t sizeof_type) {
	if (!vec || !*vec || !value) RET_ERR("Invalid argument.", 1);
	if ((*vec)->size != sizeof_type) RET_ERR("Invalid pointer.", 1);
	if (vec_push(vec, value)) RET_ERR("vec_push() failed.", 1);
	RET_OK(0);
}

int vec_generic_pop(vec_t **vec, void *value, size_t sizeof_type) {
	if (!vec || !*vec || !value) RET_ERR("Invalid argument.", 1);
	if ((*vec)->size != sizeof_type) RET_ERR("Invalid pointer.", 1);
	if (!(*vec)->len) RET_ERR("Empty vector cannot be popped.", 1);
	if (vec_pop(vec, value)) RET_ERR("vec_pop() failed.", 1);
	RET_OK(0);
}

int vec_generic_at(const vec_t *vec, size_t index, void *value, size_t sizeof_type) {
	if (!vec || !value) RET_ERR("Invalid argument.", 1);
	if (vec->size != sizeof_type) RET_ERR("Invalid pointer.", 1);
	if (index >= vec->len) RET_ERR("Requested index is out of bounds.", 1);
	vec_at(vec, index, value);
	RET_OK(0);
}

int vec_generic_remove(vec_t **vec, size_t index, size_t sizeof_type) {
	if (!vec || !*vec)  RET_ERR("Invalid argument.", 1);
	if ((*vec)->size != sizeof_type) RET_ERR("Invalid pointer.", 1);
	if (index >= (*vec)->len) RET_ERR("Requested index is out of bounds.", 1);
	if (!(*vec)->len) RET_ERR("Cannot call vec_remove() on empty vector.", 1);
	if (vec_remove(vec, index)) RET_ERR("vec_remove() failed.", 1);
	RET_OK(0);
}
