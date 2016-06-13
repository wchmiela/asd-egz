#include <iostream>
using namespace std;

// 2.
struct List {
	List * next;
	int val;
};

List * reverse(List * L) {
	List * n = NULL;
	while (L != NULL) {
		List * p = L;
		L = L->next;
		p->next = n;
		n = p;
	}
	return n;
}

void printList(List * L) {
	while (L != NULL) {
		cout << L->val << endl;
		L = L->next; 
	}
	cout << endl;
}

int main() {
	List c = { NULL, 3 };
	List b = { &c, 2 };
	List a = { &b, 1 };
	List * L = &a;
	printList(reverse(L));

	system("pause");
	return 0;
}