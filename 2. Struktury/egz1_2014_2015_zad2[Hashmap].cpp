/*
https://wiki.iiet.pl/lib/exe/fetch.php?media=studia:przedmioty:asd:asd_2015_1termin_a.png
Hashmapa z funckja hashujaca, int hash(string key, int size);
Sprawidzić hashmapa jest poprawna.
*/
#include <stdlib.h>
#include <stdio.h>
#include <string>
using namespace std;

struct HT{
    string* key;
    int* data;
    bool free;
    int size;
};

int hash(string key, int size);
bool checkHT(HT* ht, int MAX_SIZE);
void addKeys(HT* ht, int MAX_SIZE, string* keys, int n);
void initHT(HT* ht, int n);

int main(){
    int MAX_SIZE = 15;
    int n=10;
    string keys[] ={ "Bill Gates","Amancio Ortega", "Warren Buffett", "Carlos Slim Helu", "Jeff Bezos", "Mark Zuckerberg", "Larry Ellison", 	"Michael Bloomberg", "David Koch", "Charles Koch"};
    HT* ht = new HT[MAX_SIZE];
    initHT(ht, MAX_SIZE);
    addKeys(ht, MAX_SIZE, keys, n);
    if(checkHT(ht, MAX_SIZE)){
        printf("Hashmap is correct\n");
    }
    else{
        printf("Hashmap contains errors\n");
    }

    //Corect hash for this hey is 4 + shift
    ht[10].data = new int[50];
    ht[10].free = false;
    ht[10].key = new string[1];
    ht[10].key[0] = "Give me some error please";
    ht[10].size = 50;

    if(checkHT(ht, MAX_SIZE)){
        printf("Hashmap is correct\n");
    }
    else{
        printf("Hashmap contains errors\n");
    }
}

void initHT(HT* ht, int n){
    for(int i = 0; i < n; i++){
        ht[i].size = 0;
        ht[i].free = true;
    }
}

int hash(string key, int size){
    int length = key.length();
    int mul = 65599;
    int h = 0;
    for(int i = 0; i < length; i++){
        h *= mul;
        h += (int)key[i];
    }
    h = abs(h);
    return h % size;
}

void addData(HT* ht, string key, int MAX_SIZE){
    int h = hash(key, MAX_SIZE);
    if(ht[h].free){
        ht[h].data = new int[50];
        ht[h].free = false;
        ht[h].key = new string[1];
        ht[h].key[0] = key;
        ht[h].size = 50;
        return;
    }
    if(!ht[h].free){
        int start = h;
        h++;
        while(h!=start){
            if(ht[h].free){
                ht[h].data = new int[50];
                ht[h].free = false;
                ht[h].key = new string[1];
                ht[h].key[0] = key;
                ht[h].size = 50;
                return;
            }
            h = (h + 1) % MAX_SIZE;
        }
    }
}

void addKeys(HT* ht, int MAX_SIZE, string* keys, int n){
    for(int i = 0; i < n; i++){
        addData(ht, keys[i], MAX_SIZE);
    }
}

int findData(HT* ht, string key, int MAX_SIZE){
    int h = hash(key, MAX_SIZE);
    if(ht[h].free) return -1;
    while(!ht[h].free){
        if(ht[h].key[0] == key){
            return h;
        }
        else{
            h++;
            h = h % MAX_SIZE;
        }
    }
    return -1;
}

bool checkHT(HT* ht, int MAX_SIZE){
    for(int i = 0; i < MAX_SIZE; i++){
        if(ht[i].free){
            continue;
        }
        if(i != findData(ht, ht[i].key[0], MAX_SIZE)){
            return false;
        }
    }
    return true;
}
