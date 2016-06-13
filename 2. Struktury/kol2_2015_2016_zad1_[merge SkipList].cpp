#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

// maksymalna wysokoœæ skip listy
const int MAX_LEVEL = 4;
const int INF = INT16_MAX;

struct SLNode {
	int value;
	int level;
	SLNode ** next;
};

struct SkipList {
	SLNode * first;
	SLNode * last;
};

// helpers 
void init(SkipList &skip) {
	SLNode * tmp = new SLNode;
	tmp->value = -INF;
	tmp->level = MAX_LEVEL;
	tmp->next = new SLNode *[MAX_LEVEL];

	SLNode * tmp2 = new SLNode;
	tmp2->value = INF;
	tmp2->level = MAX_LEVEL;
	tmp2->next = NULL;
	
	for (int i = MAX_LEVEL - 1; i >= 0; i--)
		tmp->next[i] = tmp2;
	
	skip.first = tmp;
	skip.last = tmp2;
}

// zwraca losow¹ liczbê rzeczywist¹ z przedzia³u [0, 1]
inline double rand48() {
	return (double)(double)rand() / (double)RAND_MAX;
}

int getHeight(double p = 1/2) {
	int h = 1;
	while (h < MAX_LEVEL && rand48() < p)
		h++;
	return h;
}

void insert(SkipList skip, int key) {
	SLNode * it = skip.first;
	int h = getHeight();
	SLNode * newNode = new SLNode;
	newNode->value = key;
	newNode->next = new SLNode *[h];
	newNode->level = h;

	for (int i = MAX_LEVEL - 1; i >= 0; i--) {
		while (key > it->next[i]->value)
			it = it->next[i];
		if (i < h) {
			newNode->next[i] = it->next[i];
			it->next[i] = newNode;
		}
	}
}

SkipList merge(SkipList A, SkipList B) {
	SkipList C = { NULL, NULL };
	init(C);

	SLNode * a = A.first;
	SLNode * b = B.first;
	SLNode * c = C.first;
	SLNode ** t = new SLNode *[MAX_LEVEL];
	for (int i = 0; i < MAX_LEVEL; i++)
		t[i] = c;

	for (int i = MAX_LEVEL - 1; i >= 0; i--) {
		while (a->next[i]->value != INF || b->next[i]->value != INF) {
			SLNode * p;
			if (a->next[i]->value < b->next[i]->value) {
				p = a->next[i];
				a->next[i] = a->next[i]->next[i];

			} else {
				p = b->next[i];
				b->next[i] = b->next[i]->next[i];
			}

			p->next[i] = t[i]->next[i];
			t[i]->next[i] = p;
			t[i] = p;
		}
	}

	delete[] t;

	return C;
}

void show(SkipList skip) {
	SLNode * s = skip.first;
	while (s->next[0]->value != INF) {
		cout << s->next[0]->value << " ";
		s = s->next[0];
	}
	cout << endl;
}

int main() {
	srand(time(NULL));
	SkipList A, B;
	A = B = { NULL, NULL };
	init(A);
	init(B);

	insert(A, 1);
	insert(A, 2);
	insert(A, 3);

	insert(B, 4);
	insert(B, 5);
	insert(B, 8);
	insert(B, 7);

	show(A);
	show(B);

	SkipList C = merge(A, B);
	show(C);

	system("pause");
	return 0;
}