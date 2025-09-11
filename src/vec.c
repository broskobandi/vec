#include "vec_private.h"

vec_t *vec_new(size_t sizeof_type) {
	vec_t *vec = mem_alloc(sizeof(vec_t));
	if (!vec) return NULL;
	vec->data = mem_alloc(sizeof_type * DEFAULT_CAPACITY);
	if (!vec->data) return NULL;
	vec->capacity = DEFAULT_CAPACITY;
	vec->len = 0;
	vec->sizeof_type = sizeof_type;
	return vec;
}

int vec_del(vec_t *vec) {
	if (!vec) return 1;
	if (vec->data)
		if (mem_free(vec->data) == -1)
			return 1;
	if (mem_free(vec) == -1)
		return 1;
	return 0;
}

int vec_push_back(vec_t *vec, const void *value, size_t sizeof_type) {
	if (!vec || !value || sizeof_type != vec->sizeof_type)
		return 1;
	if (vec->len + 1 > vec->capacity)
		if (resize(vec, vec->capacity * 2))
			return 1;
	memcpy(&vec->data[vec->len * sizeof_type], value, sizeof_type);
	vec->len++;
	return 0;
}

int vec_push_front(vec_t *vec, const void *value, size_t sizeof_type) {
	if (!vec || !value || sizeof_type != vec->sizeof_type)
		return 1;
	if (vec->len + 1 > vec->capacity)
		if (resize(vec, vec->capacity * 2))
			return 1;
	memmove(&vec->data[sizeof_type], vec->data, vec->len * sizeof_type);
	memcpy(vec->data, value, sizeof_type);
	vec->len++;
	return 0;
}

int vec_pop_back(vec_t *vec, void *value, size_t sizeof_type) {
	if (!vec || sizeof_type != vec->sizeof_type)
		return 1;
	memcpy(value, &vec->data[(vec->len - 1) * sizeof_type], sizeof_type);
	if (
		vec->len - 1 <= vec->capacity / 2 &&
		vec->capacity / 2 >= DEFAULT_CAPACITY
	) {
		if (resize(vec, vec->capacity / 2))
			return 1;
	}
	vec->len--;
	return 0;
}

int vec_pop_front(vec_t *vec, void *value, size_t sizeof_type) {
	if (!vec || sizeof_type != vec->sizeof_type)
		return 1;
	memcpy(value, vec->data, sizeof_type);
	memmove(vec->data, &vec->data[sizeof_type], vec->len * sizeof_type);
	if (
		vec->len - 1 <= vec->capacity / 2 &&
		vec->capacity / 2 >= DEFAULT_CAPACITY
	) {
		if (resize(vec, vec->capacity / 2))
			return 1;
	}
	vec->len--;
	return 0;
}

size_t vec_len(const vec_t *vec) {
	if (!vec) return (size_t)-1;
	return vec->len;
}

size_t vec_capacity(const vec_t *vec) {
	if (!vec) return (size_t)-1;
	return vec->capacity;
}

int vec_remove(vec_t *vec, size_t index) {
	if (!vec || index >= vec->len) return 1;

	size_t len_to_move = vec->len - index - 1;
	memmove(
		&vec->data[index * vec->sizeof_type],
		&vec->data[(index + 1) * vec->sizeof_type],
		len_to_move * vec->sizeof_type);
	if (
		vec->len - 1 <= vec->capacity / 2 &&
		vec->capacity / 2 >= DEFAULT_CAPACITY
	) {
		if (resize(vec, vec->capacity / 2))
			return 1;
	}
	vec->len--;

	return 0;
}

int vec_insert(vec_t *vec, const void *value, size_t index, size_t sizeof_type) {
	if (
		!vec || !value || index >= vec->len ||
		sizeof_type != vec->sizeof_type
	) {
		return 1;
	}

	if (vec->len + 1 > vec->capacity)
		if (resize(vec, vec->capacity * 2))
			return 1;
	size_t len_to_move = vec->len - index;
	memmove(
		&vec->data[(index + 1) * sizeof_type],
		&vec->data[index * sizeof_type], len_to_move * sizeof_type
	);
	memcpy(&vec->data[index * sizeof_type], value, sizeof_type);
	vec->len++;

	return 0;
}

int vec_at(const vec_t *vec, void *value, size_t index, size_t sizeof_type) {
	if (
		!vec || !value || index >= vec->len ||
		sizeof_type != vec->sizeof_type
	) {
		return 1;
	}

	memcpy(value, &vec->data[index * sizeof_type], sizeof_type);

	return 0;
}

int vec_append(vec_t *vec, const void *arr, size_t len, size_t sizeof_type) {
	if (!vec || !arr || sizeof_type != vec->sizeof_type)
		return 1;

	size_t required_capacity =
		((vec->len + len + DEFAULT_CAPACITY - 1) &
		 ~(DEFAULT_CAPACITY - 1));
	if (required_capacity > vec->capacity)
		if (resize(vec, required_capacity))
			return 1;

	memcpy(&vec->data[vec->len * sizeof_type], arr, len * sizeof_type);

	vec->len += len;

	return 0;
}

int vec_prepend(vec_t *vec, const void *arr, size_t len, size_t sizeof_type) {
	if (!vec || !arr || sizeof_type != vec->sizeof_type)
		return 1;

	size_t required_capacity =
		((vec->len + len + DEFAULT_CAPACITY - 1) &
		 ~(DEFAULT_CAPACITY - 1));
	if (required_capacity > vec->capacity)
		if (resize(vec, required_capacity))
			return 1;

	memmove(&vec->data[len * sizeof_type], vec->data, vec->len * sizeof_type);
	memcpy(vec->data, arr, len * sizeof_type);

	vec->len += len;

	return 0;
}

int vec_replace(vec_t *vec, const void *value, size_t index, size_t sizeof_type) {
	if (!vec || !value || index >= vec->len || sizeof_type != vec->sizeof_type)
		return 1;

	memcpy(&vec->data[index * sizeof_type], value, sizeof_type);

	return 0;
}

int vec_replace_range(
	vec_t *vec, const void *arr, size_t len,
	size_t index, size_t range, size_t sizeof_type
) {
	if (
		!vec || !arr || index >= vec->len || range > vec->len ||
		sizeof_type != vec->sizeof_type)
	{
		return 1;
	} 

	size_t required_capacity =
		((vec->len - range + len + DEFAULT_CAPACITY - 1) &
		 ~(DEFAULT_CAPACITY - 1));
	if (
		required_capacity > vec->capacity ||
		(required_capacity <= vec->capacity / 2 &&
		 vec->capacity / 2 >= DEFAULT_CAPACITY)
	) {
		if (resize(vec, required_capacity))
			return 1;
	}

	void *src = &vec->data[(index + range) * sizeof_type];
	void *dst = &vec->data[(index + len) * sizeof_type];
	memmove(dst, src, (vec->len - index + range) * sizeof_type);
	memcpy(&vec->data[index * sizeof_type], arr, len * sizeof_type);

	vec->len = vec->len - range + len;

	return 0;
}

const void *vec_view(const vec_t *vec, size_t index) {
	if (!index || index >= vec->len) return NULL;
	return &vec->data[index * vec->sizeof_type];
}
