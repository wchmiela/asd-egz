#include <iostream>
using namespace std;

// 1.
void countingSort(int A[], int n) {
	int * B = new int[n];
	int max = A[0], min = A[0];
	for (int i = 1; i < n; i++) {
		if (A[i] > max)
			max = A[i];
		if (A[i] < min)
			min = A[i];
	}
	int k = (max - min) + 1;
	int * C = new int[k];

	for (int i = 0; i < k; i++)
		C[i] = 0;
	for (int i = 0; i < n; i++)
		C[A[i]-min]++;
	for (int i = 0; i < k - 1; i++)
		C[i + 1] += C[i];
	for (int i = 0; i < n; i++)
		B[--C[A[i]-min]] = A[i];
	for (int i = 0; i < n; i++)
		A[i] = B[i];

	delete[] B;
	delete[] C;
}

void print(int A[], int n) {
	for (int i = 0; i < n; i++) 
		cout << A[i] << endl;
	cout << endl;
}

int main() {
	int A[] = { 5, 6, 10, 7, 8, 9 };
	int n = sizeof(A) / sizeof(*A);
	countingSort(A, n);
	print(A, n);

	system("pause");
	return 0;
}