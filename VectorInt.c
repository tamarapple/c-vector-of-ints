
/* Created by tamarapple on 9/10/19. */


#include "VectorInt.h"
#include <stdlib.h>
#include <stdio.h>

Vector* vectorCreate(size_t size){
    Vector *vector= malloc(sizeof(Vector));
    vector->m_capacity=size;
    vector->m_size=0;
    vector->m_arr= malloc(size * sizeof(int));
    return vector;
}

void vectorDestroy(Vector **vector){
    free((*vector)-> m_arr);
    free(*vector);
}

/* Adds an item at the end. Grows if needed (by * 2) */
ErrorCode vectorPush(Vector *vector, int value){
    if (isFull(vector)) {
        vector->m_capacity *= 2;
        vector->m_arr = realloc(vector->m_arr, vector->m_capacity * sizeof(int));
    }
    *(vector->m_arr + vector->m_size++)=value;
    return E_OK;
}

/* Adds an item at a certain position and shifts. Grows if needed (by * 2) */
ErrorCode vectorInsert(Vector *vector, int value, size_t index){
    if ( index > (vector->m_size ))
        return E_BAD_INDEX;
    else if (isFull(vector)){
        vector->m_capacity *= 2;
        vector-> m_arr=realloc(vector->m_arr ,vector->m_capacity * sizeof(int) );
    }
    else if (index == vector->m_size){
        *(vector->m_arr+ vector->m_size++)=value;
    }
    else{
        size_t num=++vector->m_size;
        while(num >= index) {
            *(vector-> m_arr+num) =*(vector->m_arr+num-1);
            num--;
        }
        *(vector->m_arr+index)=value;
    }
    return E_OK;
}

/* Clears the item at the end */
ErrorCode vectorPop(Vector *vector, int *res){
    if (isEmpty(vector))
        return E_UNDERFLOW;
    else{
        *res = *(vector->m_arr+vector->m_size-1);
        --vector->m_size;
    }
    return E_OK;
}

/* Clears an item at a certain position and shifts. */
ErrorCode vectorRemove(Vector *vector, size_t index, int *res){
    if ( index > (vector->m_size-1 ))
        return E_BAD_INDEX;
    else{
        size_t num=index;
        *res= *(vector->m_arr + index);
        while(num < vector->m_size) {
            *(vector->m_arr + num) = *(vector->m_arr + num + 1);
            num++;
        }
    }

    --vector->m_size;
    return E_OK;
}

ErrorCode vectorGetElement(const Vector *vector, size_t index, int *res){
    if (index > vector->m_size-1)
        return E_BAD_INDEX;
    else {
        *res = *(vector->m_arr + index);
        return E_OK;
    }
}

ErrorCode vectorSetElement(Vector *vector, size_t index, int value){
    if (index > vector->m_size-1)
        return E_BAD_INDEX;
    else {
        *(vector->m_arr+index) = value;
        return E_OK;
    }
}

size_t vectorGetSize(const Vector *vector){
    return vector->m_size;
}
size_t vectorGetCapacity(const Vector *vector){
    return vector->m_capacity;
}

/* Counts how many instances of a given value there are. */
size_t vectorCount(const Vector *vector, int value){
    int i=0;
    size_t counter=0;
    for(; i<vector->m_size; ++i){
        if (*(vector->m_arr+i)==value)
            ++counter;
    }
    return counter;
}

void printVector(const Vector *vector){
    int i=0;
    for(; i < vector->m_size; ++i){
        printf("%d ",*(vector->m_arr+i) );
    }
    printf("\n");
}

bool isFull(const Vector* vector){
    return (vector->m_capacity==vector->m_size);
}

bool isEmpty(const Vector* vector){
    return !(vector->m_size);
}
