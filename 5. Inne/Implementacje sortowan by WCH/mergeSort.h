//
// Created by wojtek on 27.05.16.
//

#ifndef IMPLEMENTACJE_SORTOWAN_MERGESORT_H
#define IMPLEMENTACJE_SORTOWAN_MERGESORT_H

void merge(int*A,int*B,int l, int s, int p){
    int i = l;
    int j = s + 1;
    int k = 0;

    while (i <= s && j <= p){
        if (A[i] < A[j]){
            B[k] = A[i];
            i++;
        } else {
            B[k] = A[j];
            j++;
        }
        k++;
    }

    while (i <= s){
        B[k] = A[i];
        i++;
        k++;
    }

    while (j <= p){
        B[k] = A[j];
        j++;
        k++;
    }

    k = 0;
    for (int m = l; m <= p; ++m) {
        A[m] = B[k];
        k++;
    }

}

void merge_sort(int*A,int*B,int l, int p){
    if (l == p)
        return;

    int s = (l+p)/2;

    merge_sort(A,B,l,s);
    merge_sort(A,B,s+1,p);
    merge(A,B,l,s,p);

}

#endif //IMPLEMENTACJE_SORTOWAN_MERGESORT_H
