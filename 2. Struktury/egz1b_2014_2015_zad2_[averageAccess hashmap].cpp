#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;
typedef unsigned int hashType;

struct HT {
	string * key;
	int * data;
	bool * free;
	int size;
};

int getHash(string key, int size) {
	hashType h = 0;
	const int w = 791;
	for (int i = 0; key[i] != 0; i++)
		h += i*w + key[i];

	return h % size;
}

bool add(HT * ht, string key, int data) {
	hashType h = getHash(key, ht->size);
	int i = h;

	if (ht->free[i]) {
		ht->data[i] = data;
		ht->free[i] = false;
		ht->key[i] = key;
		return true;
	}

	i = (h + 1) % ht->size;
	while (i != h) {
		if (ht->free[i]) {
			ht->data[i] = data;
			ht->free[i] = false;
			ht->key[i] = key;
			return true;
		}
		i = (i+1) % ht->size;
	}
	return false;
}


int find(HT * ht, string key) {
	hashType h = getHash(key, ht->size);
	int i = h;

	for (int j = 0; j < ht->size; j++) {
		if (ht->free[i]) break;
		if (ht->key[i] == key)
			return ht->data[h];

		i = (i + 1) % ht->size;
	}
	return -1;
}

int findCount(HT * ht, string key) {
	hashType h = getHash(key, ht->size);
	int i = h;
	int count = 0;

	for (int j = 0; j < ht->size; j++) {
		if (ht->free[i]) break;
		if (ht->key[i] == key) 
			return count;
		
		count++;
		i = (i + 1) % ht->size;
	}
	return -1;
}

double averageAccess(HT * ht, string keys[], int n) {
	srand(time(NULL));
	const int testNum = 10e3;
	double avr = 0;

	for (int i = 0; i < testNum; i++) {
		string rkey = keys[rand() % n];
		int c = findCount(ht, rkey);
		if (c == -1) break;
		avr += c;
	}

	return avr/testNum;
}

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

HT * init(string keys[], int n) {
	srand(time(NULL));

	HT * ht = new HT;
	int size = closestPrime(n);
	ht->size = size;
	ht->data = new int[size];
	ht->key = new string[size];
	ht->free = new bool[size];

	for (int i = 0; i < size; i++)
		ht->free[i] = true;

	for (int i = 0; i < n; i++) 
		add(ht, keys[i], rand() % 1000);
	
	return ht;
}

int main() {
	int n = 20;
	string keys[] = { "Bill Gates","Amancio Ortega", "Warren Buffett", "Carlos Slim Helu", "Jeff Bezos", "Charles Koch","Mark Zuckerberg", "Larry Ellison", "Michael Bloomberg", "David Koch",
		"Marek Iksniwel","Najmad Kajsunah", "Aztekwoj Chmiel", "Grzegorz Jasiiksn", "Ducdam Ianke", "Heszke Wmeszke","Gwynbleidd", "Larry Czerwonooki", "dQw4w9WgXcQ", "SbAVowo2fXE" };
	HT * ht = init(keys, n);

	cout.precision(17);
	cout << averageAccess(ht, keys, n) << endl;

	system("pause");
	return 0;
}