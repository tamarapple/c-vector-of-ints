
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

int *getArr(const Vector *vector) {
    return vector->m_arr;
}

size_t getCapacity(const Vector *vector) {
    return vector->m_capacity;
}

size_t getSize(const Vector *vector) {
    return vector->m_size;
}

/* take care return error allocation */
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

/* frees allocation */
void vectorDestroy(Vector **vector) {
    if (vector && *vector) {
        free((*vector)->m_arr);
        free(*vector);

        (*vector)->m_arr = NULL;

        /* needs to do it because we want that the user's vector will point to NULL and not to some address  */
        *vector = NULL;
    }
}


/* multiplies the vector capacity */
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
    /*int *tmp;*/
    ErrorCode errorCode = E_OK;
    /* if vector=NULL, can't push and assert abort thr program  */
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
    if (index == getSize(vector)) {
        vectorPush(vector, value);
        return E_OK;
    } else if (index > getSize(vector))
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

    if (index == getSize(vector) - 1) {
        *res = *(vector->m_arr + vector->m_size - 1);
        errorCode = vectorPop(vector, &res);
    }
    else if (index > (getSize(vector) - 1))
        errorCode = E_BAD_INDEX;
    else {
        *res = *(vector->m_arr + index);
        shiftLeftVector(vector,index);
        --vector->m_size;
    }

    return errorCode;
}

ErrorCode vectorGetElement(const Vector *vector, size_t index, int *res) {
    if (index > vector->m_size - 1)
        return E_BAD_INDEX;
    else {
        *res = *(vector->m_arr + index);
        return E_OK;
    }
}

ErrorCode vectorSetElement(Vector *vector, size_t index, int value) {
    if (index > vector->m_size - 1)
        return E_BAD_INDEX;
    else {
        *(vector->m_arr + index) = value;
        return E_OK;
    }
}

size_t vectorGetSize(const Vector *vector) {
    return vector->m_size;
}

size_t vectorGetCapacity(const Vector *vector) {
    return vector->m_capacity;
}

/* Counts how many instances of a given value there are. */
size_t vectorCount(const Vector *vector, int value) {
    int i = 0;
    size_t counter = 0;
    for (; i < vector->m_size; ++i) {
        if (*(vector->m_arr + i) == value)
            ++counter;
        /* counter+=(*(vector->m_arr+i)==value) */
    }
    return counter;
}

void printVector(const Vector *vector) {
    int i = 0;
    for (; i < vector->m_size; ++i) {
        printf("%d ", *(vector->m_arr + i));
    }
    printf("\n");
}

bool isFull(const Vector *vector) {
    if (getCapacity(vector) <= getSize(vector)) {
        return true;
    } else
        return false;
}

bool isEmpty(const Vector *vector) {
    return !(vector->m_size);
}

ErrorCode shiftVector(Vector *vector, size_t index, Direction direction) {
    ErrorCode errorCode = E_OK;

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

void shiftRightVector(Vector *vector, size_t index) {
    size_t i = getSize(vector);
    /* I added condition i>0 because when index = 0 , in the last loop iteration i will get 0 and then reduced by one
     * and get a big number- because size_t is unsigned, and so the loop will be endless
     * */
    while (i >= index && i > 0) {
        *(vector->m_arr + i) = *(vector->m_arr + i - 1);
        --i;
    }
}

void shiftLeftVector(Vector *vector, size_t index) {
    size_t i = index;
    while (i < getSize(vector)) {
        *(vector->m_arr + i) = *(vector->m_arr + i + 1);
        i++;
    }
}