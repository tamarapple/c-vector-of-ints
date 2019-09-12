
/* Created by tamarapple on 9/11/19 */

#include <stdio.h>
#include "tests.h"

void test() {
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
    /*vectorPush(vector,44);*/
    printf("after  adds 5 values:\n");
    printVector(vector); /* 6,2,66,11,22,33,44 */

    vectorGetElement(vector, 2, &res);
    printf("element in index 2: %d\n", res); /* 66 */

    printf(" set element in index 2:\n ");
    vectorSetElement(vector, 2, 77);
    printVector(vector); /* 6,2,77,11,22,33,44 */

    printf("times of 11 value in vector: %ld\n", vectorCount(vector, 11)); /* 1 */

    vectorDestroy(&vector);
}
