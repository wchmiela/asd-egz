//
// Created by wojtek on 12.06.16.
//

#ifndef IMPLEMENTACJE_SORTOWAN_RADIXSORT_H
#define IMPLEMENTACJE_SORTOWAN_RADIXSORT_H

#include <stdlib.h>

int get_max_val(int *A, int n){
    int max = A[0];
    for (int i = 1; i < n; ++i) {
        if (A[i] > max)
            max = A[i];
    }

    return max;
}

void radix_sort_counting(int*A, int n, int x){
    int*B = (int*)calloc(sizeof(int),n);
    int*C = (int*)calloc(sizeof(int),10);
    int idx = 0;


    for (int i = 0; i < n; ++i) {
        idx = (A[i]/x)%10;
        C[idx]++;
    }

    for (int i = 1; i < 10; ++i) {
        C[i] += C[i-1];
    }

    for (int i = n-1; i >= 0; --i) {
        idx = (A[i]/x)%10;

        B[C[idx]-1] = A[i];
        C[idx]--;
    }

    for (int i = 0; i < n; ++i) {
        A[i] = B[i];
    }

    free(B);
    free(C);
}

void radix_sort(int*A, int n){
    int max = get_max_val(A, n);

    for (int i = 1; max/i > 0; i*=10) {
        radix_sort_counting(A,n,i);
    }
}



#endif //IMPLEMENTACJE_SORTOWAN_RADIXSORT_H
