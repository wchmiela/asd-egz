#include <iostream>
using namespace std;

/*
	Dana jest struktura danych
	Struct Point { double x,y; };

	Opisuj¹ca punkty w przestrzeni. Proszê zaimplementowaæ funkcjê
	Void heapsort(Point* A, int n);

	Która otrzymuje na wejœciu n elementow¹ tablicê struktur typu Point. I sortuje j¹ w kolejnoœci
	rosn¹cej wzglêdem odleg³oœci punktu od pocz¹tku uk³adu wspó³rzêdnych, korzystaj¹c z algorytmu
	heapsort.
*/

struct Point {
	double x, y;
};

inline int left(int i) { return 2 * i + 1; }
inline int right(int i) { return 2 * i + 2; }
inline int parent(int i) { return (i-1) / 2; }

void heapify(Point * A, double * dist, int i, int hs) {
	int ind_max = i;
	if (left(i) < hs && dist[left(i)] > dist[ind_max]) ind_max = left(i);
	if (right(i) < hs && dist[right(i)] > dist[ind_max]) ind_max = right(i);
	if (i != ind_max) {
		swap(dist[i], dist[ind_max]);
		swap(A[i], A[ind_max]);
		heapify(A, dist, ind_max, hs);
	}
}

void buildheap(Point * A, double * dist, int n) {
	for (int i = parent(n - 1); i >= 0; i--)
		heapify(A, dist, i, n);
}

void heapsort(Point * A, int n) {
	double * dist = new double[n];
	for (int i = 0; i < n; i++)
		dist[i] = A[i].x*A[i].x + A[i].y*A[i].y; 
	// bo jeœli sqrt(x^2+y^2) < sqrt(x2^2+y2^2) => x^2+y^2 < x2^2+y2^2

	buildheap(A, dist, n);
	for (int i = n - 1; i > 0; i--) {
		swap(dist[0], dist[i]);
		swap(A[0], A[i]);
		heapify(A, dist, 0, i);
	}

}

void print(Point * A, int n) {
	for (int i = 0; i < n; i++)
		cout << "x:" << A[i].x << ", y:" << A[i].y << endl;
	cout << endl;
}

int main() {
	const int n = 6;
	Point A[n];
	A[0] = { 55, 32 };
	A[1] = { 5, 5 };
	A[2] = { 3, 3 };
	A[3] = { 2, 2 };
	A[4] = { 4, 4 };
	A[5] = { 1, 1 };

	heapsort(A, n);
	print(A, n);

	system("pause");
	return 0;
}