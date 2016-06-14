/*
Dostajemy graf w postaci listy sasiedztwa, oraz dwa wierzcholki.
Znalesc najkrotsza sciezkie z wierzcholka s do t.
Dodatkowa informacja, wagi krawedzi sa o rozwiarze maksymalnie loglogV, gdzie V ilosc wierzcholkow w grafie
https://wiki.iiet.pl/lib/exe/fetch.php?media=studia:przedmioty:asd:egzamin_grb_2013_2014.jpg
*/

#include <stdio.h>
#include <stdlib.h>
#include <queue>

using namespace std;
struct Vertex{
    int* edge;
    int* weight;
    int edges;
    int parent;
    bool visited;
};

struct qVertex{
    int v;
    int w;
    int p;
};

void printShortestPath(Vertex* G, int n, int s, int t);

int main(){
    int N = 7;
    int A[N][N];
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            A[i][j]=0;
        }
    }
    A[0][1] = A[1][2] = A[4][5] = 1;
    A[0][2] = A[2][3] = A[3][4] = 5;
    A[2][6] = A[6][4] = 2;
    Vertex* v = new Vertex[N];
        //convert data from matrix to lists
        for(int i=0;i<N;i++){
            int c=0;
            for(int j=0;j<N;j++) if(A[i][j]!=-1)c++;
            v[i].edge = new int[c];
            v[i].weight = new int [c];
            v[i].edges = c;
            c=0;
            for(int j=0;j<N;j++){
                if(A[i][j]!=-1){
                    v[i].edge[c]=j;
                    v[i].weight[c]=A[i][j];
                    c++;
                }
            }
        }
        printShortestPath(v, N, 0, 5);
        delete v;
}

void print(Vertex* G, int v){
    if(G[v].parent>-1){
        print(G, G[v].parent);
    }
    printf("%d ", v);
}

//Zmodyfikowany BFS
//Z moich obliczen wynika ze zlozonosc tego algorytmu wynosi
//Ilośc krawedzi - E
//Suma wszystkich krawedzi W
//O(EW) - przy czym wiadomo w poleceniu ze w to maksymalnie W = E * loglog(E)
//)(E*loglogE);
void printShortestPath(Vertex* G, int n, int s, int t){
    queue<qVertex> q;
    qVertex v, tmp;

    for(int i = 0; i < s; i++){
        G[i].visited=false;
    }

    v.v = s;
    v.w = 1;
    v.p = -1;
    q.push(v);

    while(!q.empty()){
        v = q.front();
        q.pop();
        v.w--;
        if(v.w == 0){
            if(G[v.v].visited){
                continue;
            }
            if(v.v == t){
                G[t].parent = v.p;
                break;
            }
            G[v.v].visited = true;
            G[v.v].parent = v.p;
            for(int i = 0; i < G[v.v].edges; i++){
                tmp.v = G[v.v].edge[i];
                if(G[tmp.v].visited){
                    continue;
                }
                tmp.w = G[v.v].weight[i];
                tmp.p =v.v;
                q.push(tmp);
            }
        }
        else{
            q.push(v);
        }
    }
    print(G, t);
}
