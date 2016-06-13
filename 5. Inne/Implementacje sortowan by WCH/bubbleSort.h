//
// Created by wojtek on 27.05.16.
//

void swap(int *A, int x, int y) {
    int temp = A[x];
    A[x] = A[y];
    A[y] = temp;
}

void bubble_sort(int *A, unsigned int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size - 1; ++j) {
            if (A[j] > A[j + 1])
                swap(A, j, j + 1);
        }
    }
}


