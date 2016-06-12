//
// Created by wojtek on 11.06.16.
//

#ifndef KOLOKWIA_ZAD1_15_16_H
#define KOLOKWIA_ZAD1_15_16_H

#include <stdlib.h>
#include <stdio.h>

typedef struct sum {
    int sum;
    int x;
} sum;

int* generate_array(int size){
    int*A = (int*)calloc(sizeof(int),size);

    for (int i = 0; i < size; ++i) {
        A[i] = rand()%100;
    }

    return A;
}

void print_array(int*A,int size){
    for (int i = 0; i < size; ++i) {
        printf("%d\t",A[i]);
    }
        printf("\n");
}

void print_sum_array(sum*A,int size){
    for (int i = 0; i < size; ++i) {
        printf("%d\t",A[i].sum);
    }
    printf("\n");
}


void swap(sum *A, int i, int j) {
    sum x = A[i];
    A[i] = A[j];
    A[j] = x;
}

int partition(sum*A, int l, int r){
    int i = l - 1;
    int j = r + 1;
    int pivot = A[l].sum;
    while(1){
        do j--;
        while (A[j].sum > pivot);
        do i++;
        while(A[i].sum < pivot);

        if (i < j)
            swap(A,i,j);
        else
            return j;
    }
}

void quick_sort(sum*A, int l, int r){
    if (l < r){
        int q = partition(A,l,r);
        quick_sort(A,l,q);
        quick_sort(A,q+1,r);
    }
}

void sum_sort(int*A, int*B, int n){
    sum*C = (sum*)calloc(sizeof(sum),n);
    int k = 0;
    for (int i = 0; i < n*n; ) {
        for (int j = 0; j < n; ++j) {
            C[k].sum+=A[i];
            i++;
        }
        k++;
        C[k].x = i/n;
    }


    print_array(A,n*n);
    print_sum_array(C,n);

    quick_sort(C,0,n-1);
    print_sum_array(C,n);

    k = 0;
    for (int i = 0; i < n*n; ) {
        for (int j = 0; j < n; ++j) {
            B[i] = A[C[k].x*n+j];
            i++;
        }
        k++;
    }
    print_array(B,n*n);
}


#endif //KOLOKWIA_ZAD1_15_16_H
