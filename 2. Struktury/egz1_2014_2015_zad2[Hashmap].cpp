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
    bool* free;
    int size;
};

int hash(string key, int size);
bool checkHT(HT* ht);
void addKeys(HT* ht, string* keys, int n);
void initHT(HT* ht, int n);
bool checkHTFaster(HT* ht);

int main(){
    int MAX_SIZE = 15;
    int n=10;
    string keys[] ={ "Bill Gates","Amancio Ortega", "Warren Buffett", "Carlos Slim Helu", "Jeff Bezos", "Charles Koch","Mark Zuckerberg", "Larry Ellison", 	"Michael Bloomberg", "David Koch" };
    HT* ht = new HT;
    initHT(ht, MAX_SIZE);
    addKeys(ht, keys, n);
    if(checkHT(ht)){
        printf("Hashmap is correct\n");
    }
    else{
        printf("Hashmap contains errors\n");
    }

    if(checkHTFaster(ht)){
        printf("Hashmap is correct\n");
    }
    else{
        printf("Hashmap contains errors\n");
    }

    //Corect hash for this key is 4 + shift
    ht->free[10] = false;
    ht->key[10] = "Give me some error please";

    if(checkHT(ht)){
        printf("Hashmap is correct\n");
    }
    else{
        printf("Hashmap contains errors\n");
    }

    if(checkHTFaster(ht)){
        printf("Hashmap is correct\n");
    }
    else{
        printf("Hashmap contains errors\n");
    }
}

void initHT(HT* ht, int n){
    ht->size = n;
    ht->data = new int[n];
    ht->key = new string[n];
    ht->free = new bool[n];
    for(int i = 0; i < n; i++){
        ht->free[i] = true;
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

void addData(HT* ht, string key){
    int h = hash(key, ht->size);
    if(ht->free[h]){
        ht->free[h] = false;
        ht->key[h] = key;
        return;
    }
    if(!ht->free[h]){
        int start = h;
        h++;
        while(h!=start){
            if(ht->free){
                ht->free[h] = false;
                ht->key[h] = key;
                return;
            }
            h = (h + 1) % ht->size;
        }
    }
}

void addKeys(HT* ht, string* keys, int n){
    for(int i = 0; i < n; i++){
        addData(ht, keys[i]);
    }

}

int findData(HT* ht, string key){
    int h = hash(key, ht->size);
    if(ht->free[h]) return -1;
    while(!ht->free[h]){
        if(ht->key[h] == key){
            return h;
        }
        else{
            h++;
            h = h % ht->size;
        }
    }
    return -1;
}

//Slaba zlozonosc - O(n^2)
bool checkHT(HT* ht){
    for(int i = 0; i < ht->size; i++){
        if(ht->free[i]){
            continue;
        }
        if(i != findData(ht, ht->key[i])){
            return false;
        }
    }
    return true;
}

bool checkHTFaster(HT* ht){
    int startIndex;
    int i=0;

    while(i < ht->size && !ht->free[i]){
        i++;
    }

    if(i == ht->size){
        return true;
        //przypadek gdy cala tablica jest zajeta wtedy znajdziemy dana zawsze
    }

    while(i < ht->size){
        if(ht->free[i]){
            startIndex = i;
        }
        else{
            int h =hash(ht->key[i], ht->size);
            if(h <= startIndex || h >i){
                return false;
            }
        }
        i++;
    }

    if(ht->free[ht->size-1]){
    //przypadek gdy dane sie nie zapetlaja
    //wtedy jezeli hash jest wiekszy od indeksu zwroc blad
        i = 0;
        while(!ht->free[i]){
            if(hash(ht->key[i], ht->size) > i) return false;
            i++;
        }
    }
    else{
        i = 0;
        while(!ht->free[i]){
            int h =hash(ht->key[i], ht->size);
            if(h > i && h < startIndex) return false;
            i++;
        }
    }
    return true;

}
