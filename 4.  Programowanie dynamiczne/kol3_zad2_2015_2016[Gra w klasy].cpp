/*
2. struct field{
		int value;
		int long_j;
		int short_j;
}
Z kazdego pola mozna skakc tylko o ilosc pol zapisana w long_j lub short_j.
Napisac program który zwróci maksymalną wartość jaką możemy osiągnąć poprzez przejscie z pola 0 do n-1. 
Mozna założyć ze z każdego pola da się dojsc do polna n-1.
*/
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;

struct field{
    int value;
    int long_j;
    int short_j;
};

int findBestPath(field f[], int n);

int main(){
    int n = 10;
    field f[10];
    for(int i = 0; i < 7; i++){
        f[i].long_j = 3;
        f[i].short_j = 2;
        f[i].value = i;
    }
    for(int i = 7; i < n; i++){
        f[i].long_j  = f[i].short_j = f[i].value = 1;
        //Uproszczenie dozwolone w zadaniu ktore zaklada ze z kazdego pola da sie dojsc do pola n-1

    }
    f[5].value=10;
    /*
    field:
    val         short_j     long_j
        0       2           3
        1       wszedzie 2 3
        2
        3
        4
        10
        6       2           3
        1       1           1
        1       1           1
        1       1           1

        Optymalna sciezka 0->3->10->1->1->1=16
        */
        printf("%d ", findBestPath(f, n));
}

int findPath(field f[], int v[], int l, int r){
    if(v[l]>-1) return v[l];
    if(l == r){
        v[l] = f[l].value;
        return v[l];
    }
    int max_val = max(findPath(f, v, l + f[l].short_j, r), findPath(f, v, l+f[l].long_j, r)) + f[l].value;
    v[l] = max_val;
    return max_val;
}

int findBestPath(field f[], int n){
    int val[n];
    for(int i = 0; i < n; i++) val[i]=-1;

    return findPath(f, val, 0, n-1);
}
