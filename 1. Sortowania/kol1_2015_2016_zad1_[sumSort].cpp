#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

void r(int A[], int n) {
	for (int i = 0; i < n; i++)
		A[i] = rand() % 100;
}

void print(int A[], int n) {
	for (int i = 0; i < n; i++)
		cout << A[i] << " ";
	cout << endl;
}

struct sum {
	int val;
	int x;
};

void print2(sum A[], int n) {
	for (int i = 0; i < n; i++)
		cout << A[i].val << ", x:" << A[i].x << endl;
	cout << endl;
}

void SumSort(int A[], int B[], int n) {
	sum * sums = new sum[n];
	for (int i = 0; i < n; i++) {
		sums[i].x = i*n;
		sums[i].val = 0;
		for (int j = 0; j < n; j++) {
			sums[i].val += A[i*n + j];
		}
	}
	print2(sums, n);

	sum * sumsS = new sum[n];
	int max, min;
	max = min = sums[0].val;
	for (int i = 0; i < n; i++) {
		if (sums[i].val > max)
			max = sums[i].val;
		if (sums[i].val < min)
			min = sums[i].val;
	}
	int k = (max - min) + 1;
	int * C = new int[k];

	for (int i = 0; i < k; i++)
		C[i] = 0;
	for (int i = 0; i < n; i++)
		C[sums[i].val - min]++;
	for (int i = 0; i < k - 1; i++)
		C[i + 1] += C[i];
	for (int i = 0; i < n; i++)
		sumsS[--C[sums[i].val - min]] = sums[i];

	for (int i = 0; i < n; i++) {
		int b = sumsS[i].x;
		for (int j = 0; j < n; j++) {
			B[i*n + j] = A[j+b];
		}
	}

	delete[] sums;
	delete[] sumsS;
	delete[] C;
	
}

int main() {
	srand(time(NULL));
	const int n = 3;
	int A[n*n], B[n*n];
	r(A, n*n);

	print(A, n*n);
	SumSort(A, B, n);
	print(B, n*n);

	system("pause");
	return 0;
}