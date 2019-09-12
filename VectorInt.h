
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


int *getArr(const Vector *vector);

size_t getCapacity(const Vector *vector);

size_t getSize(const Vector *vector);

Vector *vectorCreate(size_t size);

void vectorDestroy(Vector **vector);

ErrorCode resizeVector(Vector* vector);

/* Adds an item at the end. Grows if needed (by * 2) */
ErrorCode vectorPush(Vector *vector, int value);

/* Adds an item at a certain position and shifts. Grows if needed (by * 2) */
ErrorCode vectorInsert(Vector *vector, int value, size_t index);

/* Clears the item at the end */
ErrorCode vectorPop(Vector *vector, int *res);

/* Clears an item at a certain position and shifts. */
ErrorCode vectorRemove(Vector *vector, size_t index, int *res);

ErrorCode vectorGetElement(const Vector *vector, size_t index, int *res);

ErrorCode vectorSetElement(Vector *vector, size_t index, int value);

size_t vectorGetSize(const Vector *vector);

size_t vectorGetCapacity(const Vector *vector);

/* Counts how many instances of a given value there are */
size_t vectorCount(const Vector *vector, int value);

bool isFull(const Vector *vector);

bool isEmpty(const Vector *vector);

ErrorCode shiftVector(Vector *vector, size_t index, Direction direction );

void shiftRightVector(Vector *vector, size_t index);

void shiftLeftVector(Vector *vector, size_t index);

void printVector(const Vector *vector);

#ifdef _DEBUG
void vectorPrint(Vector *vector);
#endif /* _DEBUG */

#endif /* __VECTOR_H__ */


