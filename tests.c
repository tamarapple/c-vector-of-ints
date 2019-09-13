
/* Created by tamarapple on 9/11/19 */

#include <stdio.h>
#include "tests.h"

void vectorCreate_test() {

    /* creates vector with capacity 1000 */
    Vector *vector_3 = vectorCreate(1000);
    vectorDestroy(&vector_3);

    /* tries to create vector with capacity 0 */
    /* Vector *vector_2 = vectorCreate(0);
    vectorDestroy(&vector_2); */

    /* tries to create vector with negative capacity :  program falls (vectorCreate gets size_t) */
    /* Vector *vector_3 = vectorCreate(-2);
    vectorDestroy(&vector_2); */
}

void vectorPush_test() {
    Vector *vector = vectorCreate(3);
    int i = 0;
    for (; i < 1000; ++i) {
        vectorPush(vector, i);
    }
    printVector(vector);
    vectorDestroy(&vector);
}

void vectorInsert_test() {
    ErrorCode errorCode;
    Vector *vector = vectorCreate(6);
    int i = 0;
    for (; i < 15; ++i) {
        vectorPush(vector, i);
    }
    printVector(vector);  /* 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 */

    /* adds value to the end of the vector*/
    vectorInsert(vector, 111, 15);
    printVector(vector);     /* 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 111 */

    /* adds value to the beginning of the vector */
    vectorInsert(vector, 222, 0);
    printVector(vector);     /* 222 0 1 2 3 4 5 6 7 8 9 10 11 12 13 111 */

    /* adds value to the middle of the vector */
    vectorInsert(vector, 333, 8);
    printVector(vector);     /* 222 0 1 2 3 4 5 6 333 7 8 9 10 11 12 13 111 */

    /* adds value to invalid index */
    errorCode = vectorInsert(vector, 333, 20);
    printf("Error Code: %d\n", errorCode);
    printVector(vector);     /* 222 0 1 2 3 4 5 6 333 7 8 9 10 11 12 13 111 */

    vectorDestroy(&vector);
}

void vectorPop_test() {
    int res;
    ErrorCode errorCode;
    Vector *vector = vectorCreate(15);
    int i = 0;
    for (; i < 7; ++i) {
        vectorPush(vector, i);
    }

    printVector(vector);    /* 0 1 2 3 4 5 6 */

    for (i = 0; i < 7; ++i) {
        vectorPop(vector, &res);
        printf("res: %d\n", res);
        printVector(vector);
    }

    /* tries to pop from an empty vector*/
    errorCode = vectorPop(vector, &res);
    printf("Error Code: %d\n", errorCode); /* 2 = E_UNDERFLOW*/
    printVector(vector);

    vectorDestroy(&vector);
}

void vectorRemove_test() {
    int res;
    ErrorCode errorCode;
    Vector *vector = vectorCreate(15);
    int i = 1;
    for (; i < 8; ++i) {
        vectorPush(vector, i);
    }

    printVector(vector);    /*  1 2 3 4 5 6 7 */

    /* remove last element */
    vectorRemove(vector, 6, &res);
    printf("res: %d\n", res); /* 7 */
    printVector(vector);     /* 1 2 3 4 5 6 */

    /* remove first element */
    vectorRemove(vector, 0, &res);
    printf("res: %d\n", res);  /* 1 */
    printVector(vector);       /*  2 3 4 5 6 */

    /* remove middle element */
    vectorRemove(vector, 2, &res);
    printf("res: %d\n", res);  /* 4 */
    printVector(vector);       /*  1 2  5 6 */

    /* tries to remove from invalid index*/
    errorCode = vectorRemove(vector, 7, &res);
    printf("Error Code: %d\n", errorCode); /* 4 = E_BAD_INDEX */
    printVector(vector);
    vectorDestroy(&vector);
}

void vectorGetAndVectorSetElement_test() {
    ErrorCode errorCode;
    int res;
    Vector *vector = vectorCreate(9);
    int i = 1;

    for (; i < 8; ++i) {
        vectorPush(vector, i);
    }

    printVector(vector);       /* 1 2 3 4 5 6 7 */


    /* sets first element */
    vectorSetElement(vector, 0, 11);

    /* gets first element */
    vectorGetElement(vector, 0, &res);
    printf("res: %d\n", res);  /* 11 */

    printVector(vector);       /* 11 2 3 4 5 6 */

    /* sets last element */
    vectorSetElement(vector, vectorGetSize(vector) - 1, 66);

    /* gets last element */
    vectorGetElement(vector, vectorGetSize(vector) - 1, &res);
    printf("res: %d\n", res);  /* 66 */

    printVector(vector);       /* 11 2 3 4 5 66 */

    /* sets middle element */
    vectorSetElement(vector, vectorGetSize(vector) / 2, 44);

    /* gets middle element */
    vectorGetElement(vector, vectorGetSize(vector) / 2, &res);
    printf("res: %d\n", res);  /* 44 */

    printVector(vector);       /* 11 2 3 44 5 66 */

    /* sets  element at invalid index */
    errorCode = vectorSetElement(vector, vectorGetSize(vector) + 2, 44);
    printf("Error Code: %d\n", errorCode); /* 4 = E_BAD_INDEX */

    /* gets  element from invalid index */
    errorCode = vectorGetElement(vector, vectorGetSize(vector) + 2, &res);
    printf("Error Code: %d\n", errorCode); /* 4 = E_BAD_INDEX */
    printf("res: %d\n", res);  /* 66 */

    printVector(vector);       /* 11 2 3 44 5 66 */
    vectorDestroy(&vector);
}

void vectorCount_test() {
    Vector *vector = vectorCreate(20);
    int i = 1;

    for (; i < 8; ++i) {
        vectorPush(vector, i);
    }

    printVector(vector);       /* 1 2 3 4 5 6 7 */

    printf("%ld\n", vectorCount(vector, 22)); /* 0 */
    printf("%ld\n", vectorCount(vector, 1));  /* 1 */
    printf("%ld\n", vectorCount(vector, 7));  /* 1 */
    printf("%ld\n", vectorCount(vector, 4));  /* 1 */

    for (i = 1; i < 8; ++i) {
        vectorPush(vector, 1);
    }

    printf("%ld\n", vectorCount(vector, 1));  /* 8 */

    vectorDestroy(&vector);
}

void vector_test_temp() {
    int res;
    Vector *vector = vectorCreate(3);

    vectorPush(vector, 6);
    vectorPush(vector, 1);
    vectorPush(vector, 2);
    vectorPush(vector, 3);
    vectorPush(vector, 4);
    printVector(vector); /* 6,1,2,3,4 */

    vectorInsert(vector, 7, 2);
    printf("after insert value of index 2:\n");
    printVector(vector); /* 6,1,7,2,3,4 */

    vectorPop(vector, &res);
    printf("after pop\n"); /* 4 */
    printf("poped value: %d\n", res);
    printVector(vector); /* 6,1,7,2,3 */

    vectorRemove(vector, 2, &res);
    printf("after remove value of index 2:\n");
    printf("removed value: %d\n", res); /* 7 */
    printVector(vector); /* 6,1,2,3 */


    vectorRemove(vector, 1, &res);
    printf("removed value: %d\n", res); /* 1 */
    printf("after remove values of index 1  \n");
    printVector(vector);   /* 6,2,3 */

    vectorRemove(vector, 2, &res);
    printf("after remove values of index 2  \n");
    printf("removed value: %d\n", res); /* 3 */
    printVector(vector);   /* 6,2 */

    vectorPush(vector, 66);
    vectorPush(vector, 11);
    vectorPush(vector, 22);
    vectorPush(vector, 33);

    /* multiplies capacity */
    vectorPush(vector, 44);
    printf("after  adds 5 values:\n");
    printVector(vector); /* 6,2,66,11,22,33,44 */

    vectorGetElement(vector, 2, &res);
    printf("element in index 2: %d\n", res); /* 66 */

    printf("set element in index 2:\n ");
    vectorSetElement(vector, 2, 77);
    printVector(vector); /* 6,2,77,11,22,33,44 */

    printf("times of 11 value in vector: %ld\n", vectorCount(vector, 11)); /* 1 */

    vectorDestroy(&vector);
}

