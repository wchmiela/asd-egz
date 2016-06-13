#include <stdlib.h>
#include <stdio.h>

using namespace std;

struct Node{
    int val;
    Node* next;
};

void addNode(Node* head, int val);
Node* concatenate(Node* s1, Node* s2);
void print(Node* head);

int main(){
    Node* s1  = new Node;
    Node* s2  = new Node;
    s1->next = s2->next = NULL;
    addNode(s1, 10);
    addNode(s1, 8);
    addNode(s1, 5);
    addNode(s1, 3);
    addNode(s1, 1);
    addNode(s1, -10);

    addNode(s2, 100);
    addNode(s2, 20);
    addNode(s2, 1);
    addNode(s2, -1);
    addNode(s2, -100);

    print(s1);
    print(s2);

    s1->next = concatenate(s1->next, s2->next);

    print(s1);
}

void print(Node* head){
    while(head->next){
        printf("%d ", head->next->val);
        head = head->next;
    }
    printf("\n");
}

void addNode(Node* head, int val){
    Node* ptr = new Node;
    ptr->val = val;
    ptr->next = head->next;
    head->next = ptr;
}

Node* concatenate(Node* s1, Node* s2){
    if(!s1) return s2;
    if(!s2) return s1;
    Node* ret = new Node;
    ret->next = NULL;
    Node* ptr = ret;
    while(s1 != NULL && s2 != NULL){
        if(s1->val < s2->val){
            ptr->next = s1;
            s1 = s1->next;
        }
        else{
            ptr->next = s2;
            s2 = s2->next;
        }
        ptr = ptr->next;
        ptr->next = NULL;
    }
    if(s1) ptr->next = s1;
    if(s2) ptr->next = s2;

    ptr = ret->next;
    delete ret;
    return ptr;
}
