//
// Created by wojtek on 27.05.16.
//

#ifndef IMPLEMENTACJE_SORTOWAN_QUICKSORT_H
#define IMPLEMENTACJE_SORTOWAN_QUICKSORT_H

int partiton(int *A, int l, int r) {
    int i = l - 1;
    int j = r + 1;
    int pivot = A[l];
    while (1) {
        do j--;
        while (A[j] > pivot);

        do i++;
        while (A[i] < pivot);

        if (i < j)
            swap(A, i, j);
        else
            return j;
    }
}


int partition_lomuto(int*A,int l, int p){
    int pivot =A[p];
    int i = l - 1;
    for (int j = l; j < p; ++j) {
        if (A[j] <= pivot)
            i++;
        swap(A,i,j);
    }

    if (i < p){
        return i;
    } else {
        return i-1;
    }

}


void quick_sort(int *A, int l, int r) {
    if (l < r) {
        int q = partiton(A, l, r);
        quick_sort(A, l, q);
        quick_sort(A, q + 1, r);
    }
}

#endif //IMPLEMENTACJE_SORTOWAN_QUICKSORT_H
