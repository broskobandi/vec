#ifndef VEC_H
#define VEC_H

#include <stddef.h>

#define VEC(T) vec_##T##_t
#define VEC_NEW(T) vec_##T##_new()
#define VEC_DEL(T, vec) vec_##T##_del((vec))
#define VEC_PUSH(T, vec, value) vec_##T##_push((vec), (value))
#define VEC_POP(T, vec) vec_##T##_pop((vec))
#define VEC_AT(T, vec, index)  vec_##T##_at((vec), (index))
#define VEC_REMOVE(T, vec, index) vec_##T##_remove((vec), (index))
#define VEC_LEN(T, vec) vec_##T##_len((vec))

/** Defines an opaque vector handle for the desired type and creates type-safe 
 * static inline function wrappers around the generic vector functions.
 * Please refer to the documentation of vec_generic* functions for details 
 * about usage of the wrapped up functions.
 * \param T The type of the vector. */
#define TYPEDEF_VEC(T)\
	typedef struct vec_##T vec_##T##_t;\
	static inline vec_##T##_t *vec_##T##_new() {\
		return (vec_##T##_t*)vec_generic_new(sizeof(T));\
	}\
	static inline void vec_##T##_del(vec_##T##_t **vec) {\
		vec_generic_del((vec_t**)vec, sizeof(T));\
	}\
	static inline int vec_##T##_push(vec_##T##_t **vec, T value) {\
		return vec_generic_push((vec_t**)vec, &value, sizeof(T));\
	}\
	static inline T vec_##T##_pop(vec_##T##_t **vec) {\
		T value;\
		if (vec_generic_pop((vec_t**)vec, &value, sizeof(T))) {\
			T empty = {0};\
			return empty;\
		}\
		return value;\
	}\
	static inline T vec_##T##_at(const vec_##T##_t *vec, size_t index) {\
		T value;\
		if (vec_generic_at((vec_t*)vec, index, &value, sizeof(T))) {\
			T empty = {0};\
			return empty;\
		}\
		return value;\
	}\
	static inline int vec_##T##_remove(vec_##T##_t **vec, size_t index) {\
		return vec_generic_remove((vec_t**)vec, index, sizeof(T));\
	}\
	static inline size_t vec_##T##_len(const vec_##T##_t *vec) {\
		return vec_generic_len((vec_t*)vec);\
	}

/** Opaque handle for the generic vector type. */
typedef struct vec vec_t;

/** Creates a new generic vector.
 * \param size The size of the type of data to be stored in the vector. 
 * \return A pointer to the new vector. */
vec_t *vec_generic_new(size_t size);

/** Deletes a generic vector.
 * \param vec A pointer to the vector to be deleted.
 * \return 0 on success or 1 on failure. */
int vec_generic_del(vec_t **vec, size_t sizeof_type);

/** Appends data at the end of 'vec'.
 * \param vec A pointer to the vector to be modified.
 * \param value A pointer to the variable holding the value
 * to be pushed at the end of 'vec'.
 * \return 0 on success or 1 on failure. */
int vec_generic_push(vec_t **vec, const void *value, size_t sizeof_type);

/** Removes the last element of 'vec' and copies its value into 'value'.
 * \param vec A pointer to the vector to be modified. 
 * \param value A pointer to the variable to copy the data into. 
 * \return Returns 0 on success or 1 on failure. */
int vec_generic_pop(vec_t **vec, void *value, size_t sizeof_type);

/** Copies the value of the element stored at the 'index'-th element of 'vec'.
 * \param vec The vector whose data to be accessed. 
 * \param index The index of the element to be accessed. 
 * \param value A pointer to the variable to copy the data into.
 * \return 0 on success or 1 on failure. */
int vec_generic_at(const vec_t *vec, size_t index, void *value, size_t sizeof_type);

/** Remove the element found at the 'index'-th element in 'vec'.
 * \param vec The vector to be modified.
 * \param index The index of the lement to be removed.
 * \return 0 on success or 1 on failure. */
int vec_generic_remove(vec_t **vec, size_t index, size_t sizeof_type);

/** Return the length of the vector.
 * \param vec The vector object to access.
 * \return The length of the vector.*/
size_t vec_generic_len(const vec_t *vec);

#endif
