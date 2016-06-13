//
// Created by wojtek on 28.05.16.
//

#ifndef IMPLEMENTACJE_SORTOWAN_COUNTINGSORT_H
#define IMPLEMENTACJE_SORTOWAN_COUNTINGSORT_H

void counting_sort(int *A, int n, int k) {
    int *B = (int *) calloc(sizeof(int), n);
    int *C = (int *) calloc(sizeof(int), k);

    for (int i = 0; i < n; ++i) {
        C[A[i]]++;
    }

    for (int i = 1; i < k; ++i) {
        C[i] = C[i] + C[i - 1];
    }

    for (int i = n-1; i >= 0; --i) {
        B[C[A[i]-1]] = A[i];
        C[A[i]]--;
    }


    for (int i = 0; i < n; ++i) {
        A[i] = B[i];
    }

    free(B);
    free(C);
}


#endif //IMPLEMENTACJE_SORTOWAN_COUNTINGSORT_H
