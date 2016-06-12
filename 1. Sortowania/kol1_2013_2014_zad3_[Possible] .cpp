//https://wiki.iiet.pl/lib/exe/fetch.php?media=studia:przedmioty:asd:2013-1kolos.jpg
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;
bool possible(char *u, char *v, char *w);
int main()
{
    char u[10];
    char v[10];
    char w[10];
    gets(u);
    gets(v);
    gets(w);
    if(possible(u,v,w)) printf("Possible");
        else printf("Not possible");
}

bool possible(char *u, char *v, char *w){
        int len;
        int A[26];
        for(int i=0;i<26;i++)A[i]=0;
        len=strlen(u);
        for(int i=0;i<len;i++) A[(int)u[i]-97]++;
        len=strlen(v);
        for(int i=0;i<len;i++) A[(int)v[i]-97]++;
        len=strlen(w);
        for(int i=0;i<len;i++) A[(int)w[i]-97]--;
        for(int i=0;i<26;i++){
            if(A[i]<0) return false;
        }
        return true;
}
