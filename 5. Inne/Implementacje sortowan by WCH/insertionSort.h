//
// Created by wojtek on 27.05.16.
//

#ifndef IMPLEMENTACJE_SORTOWAN_INSERTIONSORT_H
#define IMPLEMENTACJE_SORTOWAN_INSERTIONSORT_H


void insertion_sort(int *A, int size) {
    for (int i = 1; i < size; ++i) {
        int x = A[i];
        int j = i;
        while (x < A[j - 1]) {
            swap(A, j, j - 1);
            j--;
        }
        A[j] = x;
    }
}


#endif //IMPLEMENTACJE_SORTOWAN_INSERTIONSORT_H
