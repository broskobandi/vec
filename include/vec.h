#ifndef VEC_H
#define VEC_H

#include <stddef.h>

/** Declares a vector of the desired type and defines type-safe 
 * static inline function wrappers around the generic vector functions.
 * \param T The type of the vector. */
#define TYPEDEF_VEC(T)\
	typedef struct vec_##T vec_##T##_t;\
	__attribute__((unused))\
	static inline vec_##T##_t *vec_##T##_new() {\
		return (vec_##T##_t*)vec_generic_new(sizeof(T));\
	}\
	__attribute__((unused))\
	static inline void vec_##T##_del(vec_##T##_t **vec) {\
		vec_generic_del((void**)vec);\
	}\
	__attribute__((unused))\
	static inline void vec_##T##_push(vec_##T##_t **vec, T value) {\
		vec_generic_push((void**)vec, &value);\
	}\
	__attribute__((unused))\
	static inline T vec_##T##_pop(vec_##T##_t **vec) {\
		T value;\
		if (vec_generic_pop((void**)vec, &value))\
			return (T){0};\
		return value;\
	}\
	__attribute__((unused))\
	static inline T vec_##T##_at(const vec_##T##_t *vec, size_t index) {\
		T value;\
		if (vec_generic_at((void*)vec, index, &value))\
			return (T){0};\
		return value;\
	}\
	__attribute__((unused))\
	static inline void vec_##T##_remove(vec_##T##_t **vec, size_t index) {\
		vec_generic_remove((void**)vec, index);\
	}

/** Creates a new generic vector.
 * \param size The size of the type of data to be stored in the vector. 
 * \return A pointer to the new vector. */
void *vec_generic_new(size_t size);

/** Deletes a generic vector.
 * \param vec A pointer to the vector to be deleted. */
void vec_generic_del(void **vec);

/** Appends data at the end of 'vec'.
 * \param vec A pointer to the vector to be modified.
 * \param value A pointer to the variable holding the value
 * to be pushed at the end of 'vec'*/
void vec_generic_push(void **vec, const void *value);

/** Removes the last element of 'vec' and copies its value into 'value'.
 * \param vec A pointer to the vector to be modified. 
 * \param value A pointer to the variable to copy the data into. 
 * \return Returns 0 on success or 1 on failure. */
int vec_generic_pop(void **vec, void *value);

/** Copies the value of the element stored at the 'index'-th element of 'vec'.
 * \param vec The vector whose data to be accessed. 
 * \param index The index of the element to be accessed. 
 * \param value A pointer to the variable to copy the data into. */
int vec_generic_at(const void *vec, size_t index, void *value);

/** Remove the element found at the 'index'-th element in 'vec'.
 * \param vec The vector to be modified.
 * \param index The index of the lement to be removed. */
void vec_generic_remove(void **vec, size_t index);

#endif
