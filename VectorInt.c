
/* Created by tamarapple on 9/10/19. */


#include "VectorInt.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


struct Vector {
    int *m_arr;
    size_t m_capacity;
    size_t m_size;
};



/* Creates instance of vector and returns it  */
Vector *vectorCreate(size_t size) {
    Vector *vector;

    /* if size == 0 assert aborts the program */
    assert(size != 0);

    vector = malloc(sizeof(Vector));

    /* if vector allocation failed assert aborts the program*/
    assert(vector);

    if (vector) {
        vector->m_capacity = size;
        vector->m_size = 0;
        vector->m_arr = malloc(size * sizeof(int));

        /* if vector->arr allocation failed, frees the vector and puts there NULL */
        if (!vector->m_arr) {
            free(vector);

            /* the function returns NULL  */
            vector = NULL;
        }
    }

    return vector;
}

/* Frees vector's allocations */
void vectorDestroy(Vector **vector) {

    if (vector && *vector) {
        free((*vector)->m_arr);
        free(*vector);

        (*vector)->m_arr = NULL;

        /* needs to do it because we want that the user's vector will point to NULL and not to some address  */
        *vector = NULL;
    }
}


/* Multiplies the vector capacity */
ErrorCode resizeVector(Vector *vector) {
    ErrorCode errorCode;
    int *temp;

    vector->m_capacity *= 2;
    temp = realloc(vector->m_arr, vector->m_capacity * sizeof(int));

    /* if allocation failed, realloc returns NULL, then needs to free vector's allocation */
    if (!temp) {
        vectorDestroy(&vector);
        errorCode = E_ALLOCATION_ERROR;
    } else {
        vector->m_arr = temp;
        errorCode = E_OK;
    }

    return errorCode;
}

/* Adds an item at the end. Grows if needed (by * 2) */
ErrorCode vectorPush(Vector *vector, int value) {
    ErrorCode errorCode = E_OK;

    /* if vector = NULL, can't push and assert abort thr program  */
    assert(vector);

    if (isFull(vector)) {
        errorCode = resizeVector(vector);
    }

    *(vector->m_arr + vector->m_size++) = value;

    return errorCode;
}

/* Adds an item at a certain position and shifts. Grows if needed (by * 2) */
ErrorCode vectorInsert(Vector *vector, int value, size_t index) {
    ErrorCode errorCode;

    /* if the index is in the end of the vector, calls vectorPush function */
    if (index == vectorGetSize(vector)) {
        vectorPush(vector, value);
        return E_OK;
    }
    else if (index > vectorGetSize(vector))
        errorCode = E_BAD_INDEX;
    else {
        shiftVector(vector, index, E_RIGHT);
        ++vector->m_size;
        *(vector->m_arr + index) = value;
    }

    return errorCode;
}

/* Clears the item at the end */
ErrorCode vectorPop(Vector *vector, int *res) {
    ErrorCode errorCode = E_OK;

    if (isEmpty(vector))
        errorCode = E_UNDERFLOW;
    else {
        *res = *(vector->m_arr + vector->m_size - 1);
        --vector->m_size;
    }
    return errorCode;
}

/* Clears an item at a certain position and shifts. */
ErrorCode vectorRemove(Vector *vector, size_t index, int *res) {
    ErrorCode errorCode = E_OK;

    /* if vector=NULL, aborts thr program  */
    assert(vector);
    if (index == vectorGetSize(vector) - 1) {
        errorCode = vectorPop(vector, res);
    }

    /* if the index is bigger than the vector size */
    else if (index > (vectorGetSize(vector) - 1))
        errorCode = E_BAD_INDEX;
    else {
        *res = *(vector->m_arr + index);
        shiftLeftVector(vector, index);
        --vector->m_size;
    }

    return errorCode;
}

/* Gets element from vector in specific index */
ErrorCode vectorGetElement(const Vector *vector, size_t index, int *res) {
    ErrorCode errorCode = E_OK;

    /* if vector = NULL, aborts thr program  */
    assert(vector);

    /* if the index is bigger than the vector size */
    if (index > vector->m_size - 1)
        errorCode = E_BAD_INDEX;
    else {
        *res = *(vector->m_arr + index);
        errorCode = E_OK;
    }

    return errorCode;
}

/* Sets element in specific index in vector */
ErrorCode vectorSetElement(Vector *vector, size_t index, int value) {
    ErrorCode errorCode = E_OK;

    /* if vector = NULL, aborts thr program  */
    assert(vector);

    /* if the index is bigger than the vector size */
    if (index > vector->m_size - 1)
        errorCode = E_BAD_INDEX;
    else {
        *(vector->m_arr + index) = value;
        errorCode = E_OK;
    }

    return errorCode;
}

/* Gets vector size */
size_t vectorGetSize(const Vector *vector) {

    /* if vector = NULL, aborts thr program  */
    assert(vector);

    return vector->m_size;
}

/* Gets vector capacity */
size_t vectorGetCapacity(const Vector *vector) {

    /* if vector = NULL, aborts thr program  */
    assert(vector);

    return vector->m_capacity;
}

/* Counts how many instances of a given value there are */
size_t vectorCount(const Vector *vector, int value) {
    int i = 0;
    size_t counter = 0;

    /* if vector = NULL, aborts thr program  */
    assert(vector);

    for (; i < vector->m_size; ++i) {
        /* counter+=(*(vector->m_arr+i)==value) */
        if (*(vector->m_arr + i) == value)
            ++counter;
    }

    return counter;
}

/* Prints vector elements */
void printVector(const Vector *vector) {
    int i = 0;

    /* if vector=NULL, aborts thr program  */
    assert(vector);

    for (; i < vector->m_size; ++i) {
        printf("%d ", *(vector->m_arr + i));
    }
    printf("\n");
}

/* Checks if vector is full, If the vector is full returns true, else returns false */
bool isFull(const Vector *vector) {

    /* if vector = NULL, aborts thr program  */
    assert(vector);

    if (vectorGetCapacity(vector) <= vectorGetSize(vector)) {
        return true;
    } else
        return false;
}

/* Checks if vector is empty, If the vector is empty returns true, else returns false */
bool isEmpty(const Vector *vector) {

    /* if vector = NULL, aborts thr program  */
    assert(vector);

    return !(vector->m_size);
}

/* Shifts all the elements in vector according the specific direction right or left  */
ErrorCode shiftVector(Vector *vector, size_t index, Direction direction) {
    ErrorCode errorCode = E_OK;

    /* if vector = NULL, aborts thr program  */
    assert(vector);

    if (isFull(vector))
        errorCode = resizeVector(vector);

    if (errorCode == E_OK) {

        if (direction == E_LEFT) {
            shiftLeftVector(vector, index);

        } else if (direction == E_RIGHT) {
            shiftRightVector(vector, index);
        }
    }

    return errorCode;
}

/* Shifts right all the elements in vector */
void shiftRightVector(Vector *vector, size_t index) {
    size_t i = vectorGetSize(vector);

    /* if vector = NULL, aborts thr program  */
    assert(vector);

    /* I added condition i>0 because when index = 0 , in the last loop iteration i will get 0 and then reduced by one
     * and get a big number- because size_t is unsigned, and so the loop will be endless
     * */
    while (i >= index && i > 0) {
        *(vector->m_arr + i) = *(vector->m_arr + i - 1);
        --i;
    }
}

/* Shifts left all the elements in vector */
void shiftLeftVector(Vector *vector, size_t index) {
    size_t i = index;

    /* if vector = NULL, aborts thr program  */
    assert(vector);

    while (i < vectorGetSize(vector)) {
        *(vector->m_arr + i) = *(vector->m_arr + i + 1);
        i++;
    }
}