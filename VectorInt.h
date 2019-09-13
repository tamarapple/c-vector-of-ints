
/* Created by tamarapple on 9/10/19. */


#ifndef __VECTOR_H__
#define __VECTOR_H__


#include <stddef.h>
#include <glob.h>

typedef enum {
    false, true
} bool;

typedef enum {
    E_OK,
    E_NULL_PTR,
    E_UNDERFLOW,
    E_ALLOCATION_ERROR,
    E_BAD_INDEX
} ErrorCode;

typedef enum {
    E_RIGHT, E_LEFT
} Direction;

typedef struct Vector Vector;

/* Creates instance of vector and returns it  */
Vector *vectorCreate(size_t size);

/* Frees vector's allocations */
void vectorDestroy(Vector **vector);

/* Multiplies the vector capacity */
ErrorCode resizeVector(Vector* vector);

/* Adds an item at the end. Grows if needed (by * 2) */
ErrorCode vectorPush(Vector *vector, int value);

/* Adds an item at a certain position and shifts. Grows if needed (by * 2) */
ErrorCode vectorInsert(Vector *vector, int value, size_t index);

/* Clears the item at the end */
ErrorCode vectorPop(Vector *vector, int *res);

/* Clears an item at a certain position and shifts */
ErrorCode vectorRemove(Vector *vector, size_t index, int *res);

/* Gets element from vector in specific index */
ErrorCode vectorGetElement(const Vector *vector, size_t index, int *res);

/* sets element in specific index in vector */
ErrorCode vectorSetElement(Vector *vector, size_t index, int value);

/* Gets vector size */
size_t vectorGetSize(const Vector *vector);

/* Gets vector capacity */
size_t vectorGetCapacity(const Vector *vector);

/* Counts how many instances of a given value there are */
size_t vectorCount(const Vector *vector, int value);

/* Checks if vector is full, If the vector is full returns true, else returns false */
bool isFull(const Vector *vector);

/* Checks if vector is empty, If the vector is empty returns true, else returns false */
bool isEmpty(const Vector *vector);

/* Shifts all the elements in vector according the specific direction right or left  */
ErrorCode shiftVector(Vector *vector, size_t index, Direction direction );

/* Shifts right all the elements in vector */
void shiftRightVector(Vector *vector, size_t index);

/* Shifts left all the elements in vector */
void shiftLeftVector(Vector *vector, size_t index);

/* Prints vector elements */
void printVector(const Vector *vector);

#ifdef _DEBUG
void vectorPrint(Vector *vector);
#endif /* _DEBUG */

#endif /* __VECTOR_H__ */


