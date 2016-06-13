#include "main.h"

int main(void) {
    clock_t start;
    clock_t end;
    float seconds;
    unsigned int size = 10000;

    int *B = generate_array(size);
    int *C = restore_array(B,size);
    int *D = (int*)calloc(sizeof(int),size);

    start = clock();
    bubble_sort(C,size);
    end = clock();
    seconds = (float)(end - start) / CLOCKS_PER_SEC;
    printf("Bubblesort:\t\t\t%f\n",seconds);
    C = restore_array(B,size);

    start = clock();
    insertion_sort(C,size);
    end = clock();
    seconds = (float)(end - start) / CLOCKS_PER_SEC;
    printf("Insertionsort:\t\t%f\n",seconds);
    C = restore_array(B,size);

    start = clock();
    quick_sort(C,0,size-1);
    end = clock();
    seconds = (float)(end - start) / CLOCKS_PER_SEC;
    printf("Quicksort:\t\t\t%f\n",seconds);
    C = restore_array(B,size);

    start = clock();
    merge_sort(C,D,0,size-1);
    end = clock();
    seconds = (float)(end - start) / CLOCKS_PER_SEC;
    printf("Mergesort:\t\t\t%f\n",seconds);
    C = restore_array(B,size);

    start = clock();
    heap_sort(C,size);
    end = clock();
    seconds = (float)(end - start) / CLOCKS_PER_SEC;
    printf("Heapsort:\t\t\t%f\n",seconds);
    C = restore_array(B,size);

    start = clock();
    counting_sort(C,size, get_max_val(C, size));
    end = clock();
    seconds = (float)(end - start) / CLOCKS_PER_SEC;
    printf("Countingsort:\t\t%f\n",seconds);
    C = restore_array(B,size);

    start = clock();
    bucket_sort(C,size,size/20);
    end = clock();
    seconds = (float)(end - start) / CLOCKS_PER_SEC;
    printf("Bucketsort:\t\t\t%f\n",seconds);
    C = restore_array(B,size);

    start = clock();
    radix_sort(C,size);
    end = clock();
    seconds = (float)(end - start) / CLOCKS_PER_SEC;
    printf("Radixsort:\t\t\t%f\n",seconds);
    C = restore_array(B,size);



    return 0;
}