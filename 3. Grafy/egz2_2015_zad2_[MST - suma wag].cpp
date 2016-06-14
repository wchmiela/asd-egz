#include <iostream>       // std::cout
using namespace std;
#define V_SIZE 8

// reprezentacja macierzowa 
int graph[][V_SIZE] = {
	// 0  1  2  3  4  5  6  7    
	{ -1, 5, 0, 9, 0, 0, 3, 0 },  // 0
	{ 0, -1, 9, 0, 8, 6, 0, 7 },  // 1
	{ 0,  0, -1, 9, 4, 0, 5, 3 }, // 2
	{ 0,  0, 0, -1, 0, 0, 8, 0 }, // 3
	{ 0,  0, 0, 0, -1, 2, 1, 0 }, // 4
	{ 0,  0, 0, 0, 0, -1, 6, 0 }, // 5
	{ 0,  0, 0, 0, 0, 0, -1, 9 }, // 6  
	{ 0,  0, 0, 0, 0, 0, 0, -1 }  // 7  
};

struct List {
	int u, v;
	int w;
	List * next;
};

List * sort(List *);

// find and union
struct Set {
	Set * up;
	int rank;
};

void makeSet(Set ** Z, int i) {
	Set * s = new Set;
	s->rank = 0;
	s->up = s;
	Z[i] = s;
};

Set * findSet(Set * s) {
	if (s->up == s) {
		return s;
	} else {
		Set * y = findSet(s->up);
		s->up = y;
		return y;
	}
};

void unionSets(Set ** Z, int x, int y) {
	Set * rx = findSet(Z[x]);
	Set * ry = findSet(Z[y]);

	if (rx->rank < ry->rank) {
		rx->up = ry;
	} else if (rx->rank > ry->rank) {
		ry->up = rx;
	} else if(rx != ry){
		ry->up = rx;
		rx->rank++;
	}
};

inline void add(List * edges, List * nnode) {
	nnode->next = edges->next;
	edges->next = nnode;
};

List * get(List * edges) {
	List * s = edges->next;
	if(s!= NULL) edges->next = s->next;
	s->next = NULL;
	return s;
};

void addToSorted(List * list, List * nnode) {
	while (list->next != NULL && nnode->w > list->next->w)
		list = list->next;
	nnode->next = list->next;
	list->next = nnode;
}

List * sort(List * edges) {
	List * list = new List{ 0, 0, 0, NULL };
	while (edges->next != NULL) {
		List * s = get(edges);
		addToSorted(list, s);
	}
	delete edges;
	return list;
};

// kruskal
int MST(int g[][V_SIZE], int n) {
	List * edges = new List{0, 0, 0, NULL};
	Set ** Z = new Set * [n];
	for (int i = 0; i < n; i++) {
		makeSet(Z, i);

		for (int j = 0; j < n; j++) {
			if (g[i][j] > 0) {
				List * e = new List{i, j, g[i][j], NULL};
				add(edges, e);
			}
		}
	}

	edges = sort(edges);
	
	int sum = 0;
	List * e;
	for (int i = 0; i < n - 1; i++) {
		do {
			e = get(edges);
		} while (findSet(Z[e->u]) == findSet(Z[e->v]));
		unionSets(Z, e->u, e->v);
		sum += e->w;
	}

	return sum;
}

int main() {
	cout << MST(graph, V_SIZE) << endl;

	system("pause");
	return 0;
}