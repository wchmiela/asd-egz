#include <iostream>
using namespace std;

struct BSTNode {
	BSTNode * left;
	BSTNode * right;
	int key;
};

void countIntervalRec(BSTNode * v, int a, int b, int &sum) {
	if (v != NULL) {
		countIntervalRec(v->left, a, b, sum);
		if (a <= v->key && v->key <= b) sum++;
		if (v->key >= b) return;
		countIntervalRec(v->right, a, b, sum);
	}
}

int countInterval(BSTNode * v, int a, int b) {
	int sum = 0;
	countIntervalRec(v, a, b, sum);
	return sum;
}

void addNode(BSTNode * &tree, int key) {
	BSTNode * tmp = new BSTNode;
	tmp->key = key;
	tmp->left = tmp->right = NULL;

	if (tree == NULL) 
		tree = tmp;
	else {
		BSTNode * cp = tree;
		while (1) {
			if (key <= cp->key) {
				if (cp->left == NULL) break;
				cp = cp->left;
			} else {
				if (cp->right == NULL) break;
				cp = cp->right;
			}
		}
		
		if (key <= cp->key)
			cp->left = tmp;
		else
			cp->right = tmp;
	}
}

int main() {
	BSTNode * tree = NULL;
	addNode(tree, 8);
	addNode(tree, 5);
	addNode(tree, 10);
	addNode(tree, 1);
	addNode(tree, 6);
	addNode(tree, 11);
	addNode(tree, 7);
	addNode(tree, 20);

	cout << countInterval(tree, 5, 7) << endl;
	cout << countInterval(tree, 1, 20) << endl;
	cout << countInterval(tree, 4, 6) << endl;

	system("pause");
	return 0;
}