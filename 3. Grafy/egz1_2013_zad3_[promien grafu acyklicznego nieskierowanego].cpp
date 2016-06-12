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
		Niech = G( V,E ) b�dzie pewnym sp�jnym nieskierowanym grafem. Dla ka�dych
	dw�ch wierzcho�k�w , ? , przez ( , ) rozumiemy d�ugo�� najkr�tszej �cie�ki mi�dzy i
	(mierzon� liczb� kraw�dzi). D�ugo�ci� przek�tnej grafu nazywamy warto�� max , ? ( , ).
	Prosz� opisa� mo�liwie jak najszybszy algorytm, kt�ry maj�c na wej�ciu acykliczny graf nieskierowany
	(reprezentowany przez listy s�siedztwa) oblicza d�ugo�� jego przek�tnej (podpowied�: nasz graf jest
	do�� szczeg�lnej postaci, co bardzo u�atwia zadanie).
*/

struct Vertex {
	int * edges;
	int edge;
	int d;
	int visited;
};

// To jest zwyk�y BFS tylko najpierw znajduj� wierzcho�ek, kt�ry ma stopie� 1
// potem ju� znajduj� wysko�� drzewa, 
// poniewa� nasz graf to w�a�nie drzewo z kraw�dziami nieskierowanymi
int radius(Vertex * g, int n) {
	int * wch = new int[n];
	for (int i = 0; i < n; i++) 
		for (int j = 0; j < g[i].edge; i++) 
			wch[g[i].edges[j]]++;
	int s = 0;
	for (int i = 0; i < n; i++)
		if (wch[i] == 1) { s = i; break; }
	delete [] wch;
	
	for (int i = 0; i < n; i++) {
		g[i].d = 0;
		g[i].visited = false;
	}
	queue< int > Q;
	g[s].visited = true;
	Q.push(s);

	while (!Q.empty()) {
		int v = Q.front(); Q.pop();

		for (int i = 0; i < g[v].edge; i++) {
			int u = g[v].edges[i];
			if (!g[u].visited) {
				g[u].visited = true;
				g[u].d = g[v].d + 1;
				
				Q.push(u);
			}
		}
	}

	int max_d = g[0].d;
	for (int i = 1; i < n; i++)
		if (g[i].d > max_d) max_d = g[i].d;

	return max_d;
}

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

int main() {
	Vertex * A = makeTable(graph, V_SIZE);
	cout << radius(A, V_SIZE) << endl; 

	system("pause");
	return 0;
}