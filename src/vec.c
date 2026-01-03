#include "vec.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VEC_DEFAULT_CAPACITY 32LU

#define VEC_ERR_BUFF_SIZE 512LU
static char g_err[VEC_ERR_BUFF_SIZE];

const char *vec_get_err() {
	return g_err;
}

void set_err(const char *msg) {
	const char *vec_err_header = "[VEC_ERROR]: ";
	if ((strlen(msg) + strlen(vec_err_header) + 1) > VEC_ERR_BUFF_SIZE) {
		msg = "Vec error buffer overflow.";
	}
	sprintf(g_err, "%s %s\n", vec_err_header, msg);
}

struct vec {
	uint8_t *data;
	size_t capacity;
	size_t sizeof_type;
	size_t sizeof_vec;
};

vec_t *vec_new(size_t sizeof_type) {
	return vec_new_with_capacity(sizeof_type, VEC_DEFAULT_CAPACITY);
}

vec_t *vec_new_with_capacity(size_t sizeof_type, size_t capacity) {
	vec_t *vec = calloc(1, sizeof(vec_t));
	if (!vec) {
		set_err("Failed to allocate vec_t.");
		return NULL;
	}

	vec->data = calloc(capacity, sizeof_type);
	if (!vec->data) {
		set_err("Failed to allocate vec->data.");
		free(vec);
		return NULL;
	}

	vec->capacity = VEC_DEFAULT_CAPACITY;
	vec->sizeof_type = sizeof_type;
	vec->sizeof_vec = 0;

	return vec;
}

int vec_push(vec_t *vec, size_t sizeof_type, const void *data) {
	if (!vec || !vec->data || !data || sizeof_type != vec->sizeof_type) {
		set_err("Invalid arguments in vec_push().");
		return 1;
	}

	if ((vec->sizeof_vec + 1) * sizeof_type > vec->capacity * sizeof_type) {
		uint8_t *tmp = (uint8_t*)realloc(
			vec->data, (size_t)((float)vec->capacity * 1.5f) * sizeof_type
		);
		if (!tmp) {
			set_err("Failed to expand vector.");
			return 1;
		}
		vec->data = tmp;
	}

	memcpy(vec->data + vec->sizeof_vec * sizeof_type, data, sizeof_type);
	vec->sizeof_vec++;

	return 0;
}

int vec_pop(vec_t *vec, size_t sizeof_type) {
	if (!vec || !vec->data || !vec->sizeof_vec || sizeof_type != vec->sizeof_type) {
		set_err("Invalid arguments in vec_pop().");
		return 1;
	}

	if (vec->sizeof_vec - 1 <= vec->capacity / 2 &&
		vec->capacity / 2 >= VEC_DEFAULT_CAPACITY
	) {
		uint8_t *tmp = (uint8_t*)realloc(vec->data, vec->capacity * sizeof_type / 2);
		if (!tmp) {
			set_err("Failed to shrink vector.");
			return 1;
		}
	}

	vec->sizeof_vec--;

	return 0;
}

void *vec_at(vec_t *vec, size_t sizeof_type, size_t index) {
	if (!vec || !vec->data || sizeof_type != vec->sizeof_type) {
		set_err("Invalid arguments in vec_at().");
		return NULL;
	}

	if (index >= vec->sizeof_vec) {
		set_err("Out of bounds index passed to vec_at().");
		return NULL;
	}

	return (void*)&vec->data[index * sizeof_type];
}

const void *vec_at_const(const vec_t *vec, size_t sizeof_type, size_t index) {
	if (!vec || !vec->data || sizeof_type != vec->sizeof_type) {
		set_err("Invalid arguments in vec_at().");
		return NULL;
	}

	if (index >= vec->sizeof_vec) {
		set_err("Out of bounds index passed to vec_at().");
		return NULL;
	}

	return (const void*)&vec->data[index * sizeof_type];
}

int vec_clear(vec_t *vec, size_t sizeof_type) {
	if (!vec || !vec->data || sizeof_type != vec->sizeof_type) {
		set_err("Invalid arguments in vec_clear().");
		return 1;
	}

	if (!vec->sizeof_vec) {
		return 0;
	}

	uint8_t *tmp = (uint8_t*)realloc(vec->data, VEC_DEFAULT_CAPACITY);
	if (!tmp) {
		set_err("Failed to shrink vector.");
		return 1;
	}

	vec->data = tmp;
	vec->capacity = VEC_DEFAULT_CAPACITY;
	vec->sizeof_vec = 0;

	return 0;
}

int vec_remove(vec_t *vec, size_t sizeof_type, size_t index){
	if (!vec || !vec->data || sizeof_type != vec->sizeof_type) {
		set_err("Invalid arguments in vec_remove().");
		return 1;
	}

	if (index >= vec->sizeof_vec) {
		set_err("Out of bounds index passed to vec_remove().");
		return 1;
	}

	memmove(
		vec->data + sizeof_type * index,
		vec->data + sizeof_type * (index + 1),
		vec->sizeof_vec * sizeof_type - (index + 1) * sizeof_type
	);

	if (vec->sizeof_vec - 1 <= vec->capacity / 2 &&
		vec->capacity / 2 >= VEC_DEFAULT_CAPACITY
	) {
		uint8_t *tmp = (uint8_t*)realloc(vec->data, vec->capacity * sizeof_type / 2);
		if (!tmp) {
			set_err("Failed to shrink vector.");
			return 1;
		}
	}

	vec->sizeof_vec--;

	return 0;
}

int vec_insert(vec_t *vec, size_t sizeof_type, size_t index, const void *data) {
	if (!vec || !vec->data || sizeof_type != vec->sizeof_type || !data) {
		set_err("Invalid arguments in vec_insert().");
		return 1;
	}

	if (index >= vec->sizeof_vec) {
		set_err("Out of bounds index passed to vec_insert().");
		return 1;
	}

	if (vec->sizeof_vec + 1 > vec->capacity) {
		uint8_t *tmp = (uint8_t*)realloc(
			vec->data, (size_t)((float)vec->capacity * 1.5) * sizeof_type
		);
		if (!tmp) {
			set_err("Failed to expand vector.");
			return 1;
		}
		vec->data = tmp;
		vec->capacity = (size_t)((float)vec->capacity * 1.5);
	}

	memmove(
		vec->data + (index + 1) * sizeof_type,
		vec->data + index * sizeof_type,
		vec->sizeof_vec * sizeof_type - index * sizeof_type
	);

	memcpy(vec->data + index * sizeof_type, data, sizeof_type);
	vec->sizeof_vec++;

	return 0;
}

size_t vec_size(const vec_t *vec, size_t sizeof_type) {
	if (!vec || !vec->data || sizeof_type != vec->sizeof_type) {
		set_err("Invalid arguments in vec_size().");
		return (size_t)-1;
	}

	return vec->sizeof_vec;
}

size_t vec_capacity(const vec_t  *vec, size_t sizeof_type) {
	if (!vec || !vec->data || sizeof_type != vec->sizeof_type) {
		set_err("Invalid arguments in vec_capacity().");
		return (size_t)-1;
	}

	return vec->capacity;
}

void vec_del(vec_t *vec, size_t sizeof_type) {
	if (vec && vec->data && vec->sizeof_type == sizeof_type) {
		free(vec->data);
		free(vec);
	}
}
