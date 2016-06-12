#include <iostream>
#include <queue>
using namespace std;

/*
		Proszê zaimplementowaæ algorytm, który maj¹c na wejœciu dwa drzewa BST
	(przechowuj¹ce liczby typu int; proszê zadeklarowaæ odpowiednie struktury danych) zwraca nowe
	drzewo BST, zawieraj¹ce wy³¹cznie te liczby, które wystêpuj¹ w obu drzewach. Algorytm powinien
	byæ jak najszybszy i wykorzystywaæ jak najmniej pamiêci. Jaka jest z³o¿onoœæ zaproponowanego
	algorytmu? Co mo¿na powiedzieæ o zrównowa¿eniu drzew tworzonych przez zaproponowany
	algorytm?

	TODO:

*/

struct BSTNode {
	BSTNode * left, * right;
	int val;
};

BSTNode * makeNode(int val) {
	BSTNode * nnode = new BSTNode;
	nnode->val = val;
	return nnode;
}

void addNode(BSTNode * node, BSTNode * &root) {
	node->left = node->right = NULL;

	if (root == NULL) {
		root = node;
	} else {
		BSTNode * p = root;

		while (1) {	
			if (node->val < p->val) {
				if (p->left == NULL) break;
				p = p->left;
			} else {
				if (p->right == NULL) break;
				p = p->right;
			}
		}

		if (node->val < p->val)
			p->left = node;
		else 
			p->right = node;

	}
}

bool find(int val, BSTNode * root) {
	BSTNode * p = root;
	while (p != NULL) {
		if (val == p->val)
			return true;
		else if (val < p->val) 
			p = p->left;
		else
			p = p->right;
	}
	return false;
}

// Przy zrównowa¿onych drzewach O(nlogn), pes. O(nmk), gdzie n iloœc el. A, m iloœc el. B, k iloœæ el. C
// Z³. pam. O(2^h) gdzie h to wys. B
BSTNode * BFS(BSTNode * A, BSTNode * B) {
	queue< BSTNode * > Q; // iloœæ el. w kolejce nie przekroczy iloœci liœci w drzewie B
	if(A != NULL) 
		Q.push(A);
	else 
		return NULL;
	BSTNode * C = NULL;

	while (!Q.empty()) { // n
		BSTNode * u = Q.front(); Q.pop();
		if(u->left != NULL) Q.push(u->left);
		if (u->right != NULL) Q.push(u->right);

		if (find(u->val, B)) { // logn , pes. n
			cout << u->val << endl;
			addNode(u, C); // logn, pes. n (dodajemy bez u¿ycia dodatkowej pamiêci)
		} else
			delete u;
	}
	
	return C;
}

int main() {
	BSTNode * A = NULL;
	BSTNode * B = NULL;
	addNode(makeNode(8), A);
	addNode(makeNode(4), A);
	addNode(makeNode(10), A);
	addNode(makeNode(3), A);
	addNode(makeNode(5), A);
	addNode(makeNode(9), A);
	addNode(makeNode(11), A);

	addNode(makeNode(7), B);
	addNode(makeNode(4), B);
	addNode(makeNode(9), B);
	addNode(makeNode(3), B);
	addNode(makeNode(6), B);
	addNode(makeNode(8), B);
	addNode(makeNode(10), B);
	addNode(makeNode(11), B);

	BSTNode * C = BFS(A, B);

	system("pause");
	return 0;
}