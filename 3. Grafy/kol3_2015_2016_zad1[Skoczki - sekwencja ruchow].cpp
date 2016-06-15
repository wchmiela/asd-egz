#include <stdlib.h>
#include <stdio.h>

using namespace std;

bool prepareSequenceDFS(bool** A, int n);
bool prepareSequenceEuler(bool** A, int n);

int main(){
    int n ;
    scanf("%d", &n);
    bool** A = new bool*[n];
    bool** B = new bool*[n];
    for(int i = 0; i < n; i++){
        A[i] = new bool[n];
        B[i] = new bool[n];
        for(int j = 0; j < n; j++){
            A[i][j] = B[i][j] = false;
        }
    }
    A[0][1] = B[0][1] = true;
    //A[3][1] = B[3][1] = true;
    A[5][0] = B[5][0] = true;
    A[5][2] = B[5][2] = true;
   // A[1][3] = B[1][3] = true;
    A[2][5] = B[2][5] = true;
    A[4][4] = true;//B przypadek gdy nie ma sekwenji ruchow
    if(prepareSequenceDFS(A, n)) printf("Znalazlem\n"); else printf("Nie znalazlem\n");
    if(prepareSequenceDFS(B, n)) printf("Znalazlem\n"); else printf("Nie znalazlem\n");
}

int pozK(int x, int i){
    if(i == 0 || i == 7) return x - 2;
    if(i == 1 || i == 6) return x - 1;
    if(i == 2 || i == 5) return x + 1;
    if(i == 3 || i == 4) return x + 2;
}

int pozW(int x, int i){
    if(i == 0 || i == 3) return x - 1;
    if(i == 1 || i == 2) return x - 2;
    if(i == 4 || i == 7) return x + 1;
    if(i == 5 || i == 6) return x + 2;
}

/*
    Tutaj mozna dodac rozwiazanie bazujace na sciezce hamiltona
*/

/*
    Rozwiazanie bazujace na DFS
*/

bool sequenceDFS(bool** A, int n, int w, int k, int c){
    if(c == 1) return true;
    A[w][k] = false;
    for(int s = 0; s < 8; s++){
        int wcopy = pozW(w, s);
        int kcopy = pozK(k, s);
        if(wcopy < n && wcopy >=0 && kcopy < n && kcopy >= 0 && A[wcopy][kcopy]==true){
            if(sequenceDFS(A, n, wcopy, kcopy, c-1)){
                A[w][k] = true;
                return true;
            }
        }
    }
    A[w][k] = true;
    return false;
}

bool prepareSequenceDFS(bool** A, int n){
    int c = 0;
    int d = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(A[i][j]){
                c++;
            }
        }
    }
    int poz[c][2];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(A[i][j]){
                poz[d][0] = i;
                poz[d][1] = j;
                d++;
            }
        }
    }

    for(int i = 0; i < c; i++){
        if(sequenceDFS(A, n, poz[i][0], poz[i][1], c)) return true;
    }
    return false;
}
