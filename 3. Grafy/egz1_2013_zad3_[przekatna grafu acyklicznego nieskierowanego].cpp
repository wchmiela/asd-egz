#include <iostream>
#include <vector>
#include <queue>
using namespace std;
#define V_SIZE 6

int graph[][V_SIZE] = {
	// 0  1  2  3  4  5  
	{ 0, 0, 1, 0, 0, 0 }, // 0
	{ 0, 0, 1, 0, 0, 0 }, // 1
	{ 1, 1, 0, 1, 1, 0 }, // 2
	{ 0, 0, 1, 0, 0, 1 }, // 3
	{ 0, 0, 1, 0, 0, 0 }, // 4
	{ 0, 0, 0, 1, 0, 0 }  // 5  
};

/*
		Niech = G( V,E ) bêdzie pewnym spójnym nieskierowanym grafem. Dla ka¿dych
	dwóch wierzcho³ków , ? , przez ( , ) rozumiemy d³ugoœæ najkrótszej œcie¿ki miêdzy i
	(mierzon¹ liczb¹ krawêdzi). D³ugoœci¹ przek¹tnej grafu nazywamy wartoœæ max , ? ( , ).
	Proszê opisaæ mo¿liwie jak najszybszy algorytm, który maj¹c na wejœciu acykliczny graf nieskierowany
	(reprezentowany przez listy s¹siedztwa) oblicza d³ugoœæ jego przek¹tnej (podpowiedŸ: nasz graf jest
	doœæ szczególnej postaci, co bardzo u³atwia zadanie).
*/

struct Vertex {
	int * edges;
	int edge;
	int d;
	int visited;
};

Vertex * makeTable(int g[V_SIZE][V_SIZE], int n) {
	Vertex * nV = new Vertex[n];

	for (int i = 0; i < n; i++) {
		int c = 0;
		for (int j = 0; j < n; j++)
			if (g[i][j] > 0) c++;

		nV[i].edges = new int[c];
		nV[i].edge = c;

		int k = 0;
		for (int j = 0; j < n; j++) {
			if (g[i][j] > 0) {
				nV[i].edges[k] = j;
				k++;
			}
		}
	}

	return nV;
}

void DFS(Vertex * A, int v) {
	A[v].visited = true;

	for (int j = 0; j < A[v].edge; j++) {
		int u = A[v].edges[j];
		if (!A[u].visited) {
			A[u].d += A[v].d + 1;
			DFS(A, u);
		}
	}

}

int getMax(Vertex * A, int n) {
	int max = 0;
	for (int i = 1; i < n; i++)
		if (A[i].d > A[max].d) max = i;
	return max;
}

void reset(Vertex * A, int n) {
	for (int i = 0; i < n; i++) {
		A[i].d = 0;
		A[i].visited = false;
	}
}

int diagonal2(Vertex * A, int n) {
	reset(A, n);

	DFS(A, 2);
	
	int u = getMax(A, n);
	reset(A, n);

	DFS(A, u);
	int v = getMax(A, n);

	return A[v].d;
}

int main() {
	Vertex * A = makeTable(graph, V_SIZE);
	cout << diagonal2(A, V_SIZE) << endl;

	system("pause");
	return 0;
}