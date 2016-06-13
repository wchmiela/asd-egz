//
// Created by wojtek on 27.05.16.
//

#ifndef IMPLEMENTACJE_SORTOWAN_MAIN_H
#define IMPLEMENTACJE_SORTOWAN_MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node{
    int val;
    struct node* next;
} node;

void print_array(int*A, unsigned int size){
    for (int i = 0; i < size; ++i) {
        printf("%d\t",A[i]);
    }
    printf("\n");
}

int* generate_array(unsigned int size){
    int*A = (int*)calloc(sizeof(int),size);
    for (int i = 0; i < size; ++i) {
        A[i] = rand()%100;
    }

    return A;
}

int *restore_array(int*S, unsigned int size){
    int*A = (int*)calloc(sizeof(int),size);
    for (int i = 0; i < size; ++i) {
        A[i] = S[i];
    }
    return A;
}

#include "bubbleSort.h"
#include "insertionSort.h"
#include "heapSort.h"
#include "quickSort.h"
#include "mergeSort.h"
#include "countingSort.h"
#include "radixSort.h"
#include "bucketSort.h"



#endif //IMPLEMENTACJE_SORTOWAN_MAIN_H
