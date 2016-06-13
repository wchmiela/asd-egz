#include <iostream>
#include <stack>
using namespace std;

// sta³e
int const prime = 6599;
typedef unsigned int hashType;

// struktury
struct Cyclist {
	int id, n_id;
};

struct CyclistH {
	int id_n, id;
	hashType hash;
	int wch; // iloœæ wskaŸników wchodzacych
};
CyclistH *EMPTY = new CyclistH{ 0, 0, 0 };

struct {
	int l_p; // rozmiar tablicy, liczba pierwsza
	CyclistH ** val; // tablica wsk na cyklistów
} hashTab;

//
bool isPrime(int num) {
	if (num <= 1) return false;
	if (num == 2) return true;
	if (num % 2 == 0) return false;

	for (int i = 3; i*i <= num; i += 2) 
		if (num % i == 0) return false;
	return true;
}

int closestPrime(int n) {
	while (!isPrime(n))
		(n % 2 == 0) ? n++ : n += 2;
	return n;
}

// hashmap functions
inline hashType getHash(int id) {
	return id*prime;
}

bool insert(Cyclist c) {
	hashType h = getHash(c.id);
	int start = h % hashTab.l_p;
	int i = 1;
	CyclistH * nc = new CyclistH;
	nc->id = c.id;
	nc->id_n = c.n_id;
	nc->wch = 0;
	nc->hash = h;

	if (hashTab.val[start] == NULL || hashTab.val[start] == EMPTY) {
		hashTab.val[start] = nc;
		return true;
	}

	start = (start+i*i)%hashTab.l_p;
	while (i != hashTab.l_p) {
		if (hashTab.val[start] == NULL || hashTab.val[start] == EMPTY) {
			hashTab.val[start] = nc;
			return true;
		}
		i++;
		start = (start + i*i) % hashTab.l_p;
	}
	return false;
}

int search(int id) {
	hashType h = getHash(id);

	for (int i = 0; i < hashTab.l_p; i++) {
		int ind = (h + i*i) % hashTab.l_p;
		if (hashTab.val[ind] == NULL) break;
		if (hashTab.val[ind] == EMPTY) continue;
		if (hashTab.val[ind]->hash != h) continue;
		if (hashTab.val[ind]->hash == h && hashTab.val[ind]->id == id) return ind;
	}
	return -1;
}

// funkcja inicjalizuj¹ca hashmapê
void init(Cyclist cyclist[], int n) {
	hashTab.l_p = closestPrime(n);
	hashTab.val = new CyclistH * [hashTab.l_p];
	for (int i = 0; i < hashTab.l_p; i++)
		hashTab.val[i] = NULL;

	for (int i = 0; i < n; i++)
		insert(cyclist[i]);
}

// wyœwietla zawartoœæ hashmapy
void show() {
	cout << "size: " << hashTab.l_p << endl << endl;
	for (int i = 0; i < hashTab.l_p; i++) {
		if (hashTab.val[i] != NULL && hashTab.val[i] != EMPTY) {
			cout << "n_id: " << hashTab.val[i]->id_n << endl;
			cout << "wsk wch: " << hashTab.val[i]->wch << endl;
			cout << "hash: " << hashTab.val[i]->hash << endl;
			cout << "ind: " << hashTab.val[i]->hash % hashTab.l_p << endl << endl;
		}
	}
}

// funckja zwraca iloœæ najmniejszej grupy kolarzy 
int smallestGroup(Cyclist cyclist[], int n) {
	init(cyclist, n); // zainicjuj hashmape
	
	for (int i = 0; i < n; i++)
		if(cyclist[i].n_id != -1 && search(cyclist[i].n_id) != -1)
			hashTab.val[search(cyclist[i].n_id)]->wch++;

	//show();

	stack< int > stack;
	for (int i = 0; i < n; i++) {
		int ind = search(cyclist[i].id);
		if (ind != -1 && hashTab.val[ind]->wch == 0)
			stack.push(ind);
	}

	int min = INT16_MAX;
	while (!stack.empty()) {
		int i = stack.top(); stack.pop();
		int d = 1;
		while (i != -1 && hashTab.val[i]->id_n != -1) {
			int id = hashTab.val[i]->id_n;
			i = search(id);
			d++;
		}
		if (d < min) min = d;
	}

	return min;
}

int main() {
	const int n = 10;
	Cyclist cyclist[n];
	cyclist[0] = { 10, 13 };
	cyclist[1] = { 11, 17};
	cyclist[2] = { 12, 15 };
	cyclist[3] = { 13, 11 };
	cyclist[4] = { 14, 12 };
	cyclist[5] = { 15, -1 };
	cyclist[6] = { 16, 19 };
	cyclist[7] = { 17, -1 };
	cyclist[8] = { 18, 14 };
	cyclist[9] = { 19, -1 };

	cout << smallestGroup(cyclist, n) << endl;

	system("pause");
	return 0;
}