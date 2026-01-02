#include "vec.h"

#define VEC_DEFAULT_CAPACITY 32LU

_Thread_local static const char *g_err;

const char *vec_get_err() {
	return g_err;
}

void set_err(const char *msg) {
	g_err = msg;
}

struct vec {
	void *data;
	size_t capacity;
	size_t sizeof_type;
	size_t sizeof_vec;
};


