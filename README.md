# vec
## Yet another dynamic vector written in C.
The goal of the project is to provide a simple dynamic 
vector tool for C programs. The old version can be found
[here](https://github.com/broskobandi/cvec.git). The new
version is redesigned from ground up and provides a much 
simpler api. This new version has fewer dependencies as 
it uses the native C allocator instead of my [my custom one](https://github.com/broskobandi/carena.git).
It also avoids using posix specific keywords, such as 
_Thread_local, which makes it non-thread-safe but improves
cross platform compatibility. The main reason for creating
the library in such a way is to provide my SDL2 games with 
a simple vector utility that allows the games to be 
cross-compiled for windows. I am aware that this problem 
could have been addressed in different ways, but I 
wanted to keep things simple.
Regardless of all this, the library still provides 
type-safety to an extent the language allows with as 
little overhead as possible.
## Installation:
Download and clone [the repo](https://github.com/broskobandi/vec.git) and 
run the relevant shell script or command:
```bash
# For building the Linux debug version simply run:
make
# For installing the Linux debug version, run:
sudo make install
# For building the Linux release version run:
./release.sh
# For installing the Linux release version run:
sudo ./install-release.sh
# For building the Windows debug version run:
./win-debug.sh
# For building the Windows release version run:
./win-release.sh

```
## Usage:
```c
#include <vec.h>
#include <assert.h>
#include <stdio.h>

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

	/* Don't forget to delete the vector as the underlying data is 
	 * dynamically allocated. */
	VEC_DEL(vec);

	return 0;
}
```
