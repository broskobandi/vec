#include "vec.h"
#include <assert.h>
#include <stdio.h>

VEC_TYPEDEF(int);
VEC_TYPEDEF(float);

int main(void) {
	{ // NEW / DEL / CAPACITY
		VEC(int) vec = VEC_NEW(int);
		assert(vec.__priv);
		assert(VEC_CAPACITY(vec) == 32);
		VEC_DEL(vec);
		assert(!vec.__priv);
		VEC(float) vec2 = VEC_NEW_WITH_CAPACITY(float, 512);
		assert(vec2.__priv);
		VEC_DEL(vec2);
		assert(!vec2.__priv);
		assert(VEC_PUSH(vec, 5));
		assert(VEC_PUSH(vec2, 5.5f));
	}

	{ // PUSH / POP
		VEC(int) vec = VEC_NEW(int);
		assert(!VEC_PUSH(vec, 5));
		assert(VEC_SIZE(vec) == 1);
		assert(!VEC_POP(vec));
		assert(VEC_SIZE(vec) == 0);
		assert(VEC_POP(vec));
		VEC_DEL(vec);
	}

	{ // AT
		VEC(int) vec = VEC_NEW(int);
		assert(!VEC_PUSH(vec, 5));
		int *value = VEC_AT(vec, 0);
		assert(*value == 5);
		*value = 3;
		assert(*VEC_AT(vec, 0) == 3);
		VEC_DEL(vec);
	}

	{ // CLEAR / SIZE
		VEC(int) vec = VEC_NEW(int);
		VEC_PUSH(vec, 5);
		assert(VEC_SIZE(vec) == 1);
		VEC_CLEAR(vec);
		assert(VEC_SIZE(vec) == 0);
		VEC_DEL(vec);
	}

	{ // REMOVE
		VEC(int) vec = VEC_NEW(int);
		VEC_PUSH(vec, 1);
		VEC_PUSH(vec, 2);
		VEC_PUSH(vec, 3);
		assert(VEC_SIZE(vec) == 3);
		VEC_REMOVE(vec, 1);
		assert(VEC_SIZE(vec) == 2);
		assert(*VEC_AT_CONST(vec, 0) == 1);
		assert(*VEC_AT_CONST(vec, 1) == 3);
		assert(!VEC_REMOVE(vec, 0));
		assert(!VEC_REMOVE(vec, 0));
		assert(VEC_REMOVE(vec, 0));
		VEC_DEL(vec);
	}

	{ // INSERT
		VEC(int) vec = VEC_NEW(int);
		VEC_PUSH(vec, 1);
		VEC_PUSH(vec, 3);
		assert(VEC_SIZE(vec) == 2);
		VEC_INSERT(vec, 1, 2);
		assert(VEC_SIZE(vec) == 3);
		assert(*VEC_AT_CONST(vec, 0) == 1);
		assert(*VEC_AT_CONST(vec, 1) == 2);
		assert(*VEC_AT_CONST(vec, 2) == 3);
		VEC_DEL(vec);
	}

	printf("All tests passed.\n");
	
	return 0;
}
