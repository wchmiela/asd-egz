#include <iostream>
#include <algorithm>
using namespace std;

int backpack(int r[], int h[], int v[], int n, int m, int s) {
	n++; m++; s++;
	int *** f = new int **[n];
	for (int i = 0; i < n; i++)
		f[i] = new int * [m];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			f[i][j] = new int[s];


	for (int i = 0; i < n; i++)
		for (int j = 0; j < s; j++)
			f[i][0][j] = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			f[i][j][0] = 0;
	for (int i = 0; i < m; i++)
		for (int j = 0; j < s; j++)
			f[0][i][j] = 0;

	for (int i = 1; i < n; i++) {
		for (int j = 1; j < m; j++) {
			for (int k = 1; k < s; k++) {
				if (r[i-1] > j || h[i-1] > k )
					f[i][j][k] = f[i - 1][j][k];
				else {
					int w = j - r[i - 1];
					int he = k - h[i - 1];
					if (w < 0) w = 0;
					if (he < 0) he = 0;
					f[i][j][k] = max(f[i - 1][j][k], f[i - 1][w][he] + v[i - 1]);
				}
			}
		}
	}

	return f[n - 1][m - 1][s - 1];
}


int main() {
	int r[] = { 1, 2, 1, 5, 5 };
	int v[] = { 20, 20, 22, 6, 5 };
	int h[] = { 5, 4, 1, 12, 13 };
	int n = 5;
	int m = 10;
	int s = 10;
	cout << backpack(r, h, v, n, m, s) << endl;

	system("pause");
	return 0;
}