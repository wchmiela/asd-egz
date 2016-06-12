#include <iostream>
#include <queue>          // std::priority_queue
#include <vector>         // std::vector
#include <string>
using namespace std;

struct Vertex {
	bool shop; // true - shop, false - house
	int * distance;
	int * edges;
	int edge;
	int d_store;
};

void printLen(unsigned int ** d, int n) {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			cout << "d[" << i << "]" << "[" << j << "] = ";
			if (d[i][j] == INT16_MAX)
				cout << "NO PATH";
			else
				cout << d[i][j];
			cout << endl;
		}

}

void distanceToClosestStore(int n, Vertex * village) {
	unsigned int ** d = new unsigned int *[n];
	for (int i = 0; i < n; i++)
		d[i] = new unsigned int[n];

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j)
				d[i][j] = 0;
			else
				d[i][j] = INT16_MAX;
		}
	}

	for (int i = 0; i < n; i++)
		for (int j = 0; j < village[i].edge; j++)
			d[i][village[i].edges[j]] = village[i].distance[j];

	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				unsigned int p = d[i][k] + d[k][j];
				if (d[i][j] > p)
					d[i][j] = p;
			}
		}
	}

	//printLen(d, n);

	for (int i = 0; i < n; i++) {
		if (village[i].shop) {
			village[i].d_store = 0;
			continue;
		}
		unsigned int min = INT16_MAX;

		for (int j = 0; j < n; j++) {
			if (d[i][j] < min && village[j].shop)
				min = d[i][j];
		}
		village[i].d_store = min;
	}

}

//
struct Data {
	int d;
	bool visited;
	int parent;
};

struct vertexId {
	int v;
	int d;
};

struct compare {
	bool operator()(const vertexId &l, const vertexId &r) {
		return l.d > r.d;
	}
};

// graf musi mieæ n-1 wierzcho³ek po³¹czony ze wszystkimi sklepami krawêdziami o wadze 0
void distanceToClosestStore_dijkstra(int n, Vertex * village) {
	Data * data = new Data[n];
	for (int i = 0; i < n; i++) {
		data[i].d = INT16_MAX;
		data[i].parent = -1;
		data[i].visited = false;
	}
	data[n - 1].d = 0;

	priority_queue<vertexId, vector< vertexId >, compare> Q;
	vertexId s = { n - 1, 0 };
	Q.push(s);

	while (!Q.empty()) {
		int v = Q.top().v; Q.pop();
		if (data[v].visited) continue;
		data[v].visited = true;

		for (int i = 0; i < village[v].edge; i++) {
			int u = village[v].edges[i];
			int sum = data[v].d + village[v].distance[i];
			if (data[u].d > sum) {
				data[u].d = sum;
				data[u].parent = v;
				
				s = { u, sum };
				Q.push(s);
			}
		}
	}

	for (int i = 0; i < n; i++)
		village[i].d_store = data[i].d;
}

//
#define V_SIZE 10

// reprezentacja macierzowa 
int graph[V_SIZE][V_SIZE] = {
	// 0  1  2  3  4  5  6  7  8  9  
	{ 0, 6, 4, 0, 0, 0, 0, 0, 0, 0 }, // 0 
	{ 6, 0, 0, 3, 0, 0, 0, 0, 0, 0 }, // 1
	{ 4, 0, 0, 5, 0, 0, 0, 0, 0, 0 }, // 2
	{ 0, 3, 5, 0, 3, 0, 0, 2, 0, 4 }, // 3
	{ 0, 0, 0, 3, 0, 5, 2, 0, 0, 0 }, // 4
	{ 0, 0, 0, 0, 5, 0, 1, 0, 0, 0 }, // 5
	{ 0, 0, 0, 0, 2, 1, 0, 0, 0, 0 }, // 6
	{ 0, 0, 0, 2, 0, 0, 0, 0, 1, 0 }, // 7
	{ 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 }, // 8
	{ 0, 0, 0, 4, 0, 0, 0, 0, 0, 0 }  // 9
};

// 0      1      2      3      4      5      6      7      8      9  
bool shops[V_SIZE] = { false, true, true, false, false, false, false, false, false, true };

Vertex * makeTable(int g[V_SIZE][V_SIZE], bool shops[]) {
	int n = V_SIZE;
	Vertex * nV = new Vertex[n];

	for (int i = 0; i < n; i++) {
		int c = 0;
		for (int j = 0; j < n; j++)
			if (g[i][j] > 0) c++;

		nV[i].edges = new int[c];
		nV[i].distance = new int[c];
		nV[i].edge = c;
		nV[i].shop = shops[i];

		int k = 0;
		for (int j = 0; j < n; j++) {
			if (g[i][j] > 0) {
				nV[i].edges[k] = j;
				nV[i].distance[k] = g[i][j];
				k++;
			}
		}
	}

	return nV;
}

Vertex * makeTableExtraVertex(int g[V_SIZE][V_SIZE], bool shops[]) {
	int n = V_SIZE;
	Vertex * nV = new Vertex[n+1];

	for (int i = 0; i < n; i++) {
		int c = 0;
		for (int j = 0; j < n; j++)
			if (g[i][j] > 0) c++;

		if (shops[i]) c++;

		nV[i].edges = new int[c];
		nV[i].distance = new int[c];
		nV[i].edge = c;
		nV[i].shop = shops[i];

		int k = 0;
		for (int j = 0; j < n; j++) {
			if (g[i][j] > 0) {
				nV[i].edges[k] = j;
				nV[i].distance[k] = g[i][j];
				k++;
			}
		}
		if (shops[i]) {
			nV[i].edges[c-1] = n;
			nV[i].distance[c-1] = 0;
		}
	}

	int  sho = 0;
	for (int j = 0; j < n; j++)
		if (shops[j]) sho++;
	nV[n].edges = new int[sho];
	nV[n].distance = new int[sho];
	nV[n].edge = sho;
	nV[n].shop = false;

	int k = 0;
	for (int j = 0; j < n; j++) {
		if (shops[j]) {
			nV[n].edges[k] = j;
			nV[n].distance[k] = 0;
			k++;
		}
	}

	return nV;
}

void printAll(int n, Vertex * village) {
	for (int i = 0; i < n; i++) {
		cout << "village[" << i << "] " << endl;
		cout << "	.shop = " << village[i].shop << endl;
		cout << "	.edge = " << village[i].edge << endl;
		cout << "	linked with (edges): " << endl;
		for (int j = 0; j < village[i].edge; j++)
			cout << "		u = " << village[i].edges[j] << ", d(v, u) = " << village[i].distance[j] << endl;
		cout << endl;
	}
}

void printDStore(int n, Vertex * village) {
	for (int i = 0; i < n; i++) {
		cout << "village[" << i << "].d_store: ";
		if (village[i].shop)
			cout << "SHOP";
		else
			cout << village[i].d_store;
		cout << endl;
	}
}

int main() {
	//Vertex * village1 = makeTable(graph, shops);
	//printAll(V_SIZE, village);
	//distanceToClosestStore(V_SIZE, village1);
	//printDStore(V_SIZE, village1);
	
	Vertex * village = makeTableExtraVertex(graph, shops);
	//printAll(V_SIZE+1, village);
	distanceToClosestStore_dijkstra(V_SIZE+1, village);
	printDStore(V_SIZE+1, village);

	system("pause");
	return 0;
}