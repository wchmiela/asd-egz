//https://wiki.iiet.pl/lib/exe/fetch.php?media=studia:przedmioty:asd:2013-1kolos.jpg
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

using namespace std;

struct Node{
    int val;
    Node* next;
};

Node* buildList(int i, int range);
Node* QuickerSort(Node* head);
void print(Node* head);

int main(){
    Node* head = buildList(40, 5);
    print(head);
    head->next = QuickerSort(head->next);
    print(head);
}

//Bez straznika
Node* QuickerSort(Node* head){
    if(head == NULL) return NULL;
    Node* lesser,* equal,* greater,* l,* e,* g,* ret,* retTail;
    lesser = new Node;
    equal = new Node;
    greater = new Node;
    lesser->next = equal->next = greater->next = NULL;
    l = lesser;
    e = equal;
    g = greater;
    int c = head->val;

    while(head != NULL){
        if(head->val == c){
            e->next = head;
            head = head->next;
            e = e->next;
            e->next = NULL;
        }
        else{
            if(head->val < c){
                l->next = head;
                head = head->next;
                l = l->next;
                l->next = NULL;
            }
            else{
                g->next = head;
                head = head->next;
                g = g->next;
                g->next = NULL;
            }
        }
    }

    lesser->next = QuickerSort(lesser->next);
    greater->next = QuickerSort(greater->next);
    ret = new Node;
    ret->next = NULL;
    retTail = ret;

    ret->next = lesser->next;
    while(retTail->next != NULL){
        retTail = retTail->next;
    }

    retTail->next = equal->next;
    while(retTail->next != NULL){
        retTail = retTail->next;
    }

    retTail->next = greater->next;

    retTail = ret->next;
    delete lesser, equal, greater, ret;
    return retTail;
}

//Dla listy z straznikiem
void addNode(Node* h, int val){
    Node* tmp = new Node;
    tmp->next = h->next;
    tmp->val = val;
    h->next = tmp;
}

//Dla listy z straznikiem
Node* buildList(int i, int range){
    Node* head = new Node;
    head->next = NULL;
    srand(time(NULL));
    for(i; i >= 0; i--){
        addNode(head, rand()%range);
    }
    return head;
}

void print(Node* head){
    while(head->next != NULL){
        printf("%d ", head->next->val);
        head = head->next;
    }
    printf("\n");
}
