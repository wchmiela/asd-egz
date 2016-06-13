//
// Created by wojtek on 27.05.16.
//

int left(int n) { return 2*n+1; }
int right(int n) { return 2*n+2; }
int parent(int n) { return (n-1)/2; }

void heapify(int *A, int n, int i) {
    int ind_max = i;

    if (left(i) < n && A[left(i)] > A[i])
        ind_max = left(i);
    else
        ind_max = i;

    if (right(i) < n && A[right(i)] > A[ind_max])
        ind_max = right(i);


    if (ind_max != i) {
        swap(A, i, ind_max);
        heapify(A, n, ind_max);
    }
}


void build_heap(int *A, int n) {
    for (int i = parent(n - 1); i >= 0; --i) {
        heapify(A, n, i);
    }
}

void heap_sort(int *A, int n) {
    build_heap(A, n);
    for (int i = n - 1; i >= 0; --i) {
        swap(A,0,i);
        heapify(A, i, 0);
    }
}
