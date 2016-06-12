#include <stdlib.h>
#include <stdio.h>
#include <time.h>

using namespace std;

struct Node{
    double val;
    Node* next;
};

Node* buildList(int i);
void print(Node* head);
Node* mergeSort(Node* head);

int main(){
    Node* head = buildList(40);
    print(head);
    head  = mergeSort(head);
    print(head);
}


void nserie(Node* head, Node* s){
    Node* ptr = head->next;
    if(ptr == NULL || ptr->next == NULL){
        s->next = ptr;
        head->next = NULL;
        return;
    }

    while(ptr->next != NULL && ptr->val <= ptr->next->val){
        ptr = ptr->next;
    }

    s->next = head->next;
    head->next = ptr->next;
    ptr->next = NULL;
}

Node* mergeSeries(Node* s1, Node* s2, Node* append_to){
    Node* end = append_to;

    while(s1->next != NULL && s2->next != NULL){
        if(s1->next->val <= s2->next->val){
            end->next = s1->next;
            s1->next = s1->next->next;
        }
        else{
            end->next = s2->next;
            s2->next = s2->next->next;
        }
        end = end->next;
        end->next = NULL;
    }

    if(s1->next != NULL){
        end->next = s1->next;
    }
    if(s2->next != NULL){
        end->next = s2->next;
    }

    while(end->next != NULL){
        end = end->next;
    }
    s1->next = NULL;
    s2->next = NULL;

    return end;
}


Node* mergeSort(Node* head){
    Node* s1,* s2,* end,* h;
    s1 = new Node;
    s2 = new Node;
    h = new Node;
    s1->next = s2->next = h->next = NULL;
    end = h;
    int n;

    do{
        n=0;
        while(head->next != NULL){
            n++;
            nserie(head, s1);
            if(head->next != NULL){
                n++;
                nserie(head, s2);
                end = mergeSeries(s1, s2, end);
            }
            else{
                end->next = s1->next;
            }
        }
        head->next = h->next;
        end = h;
        end->next = NULL;
    }while(n>2);
    delete s1, s2, end;
    return head;
}






void addNode(Node* h, double val){
    Node* tmp = new Node;
    tmp->next = h->next;
    tmp->val = val;
    h->next = tmp;
}


Node* buildList(int i){
    Node* head = new Node;
    head->next = NULL;
    srand(time(NULL));
    for(i; i >= 0; i--){
        addNode(head, 0.0006 * (double)(rand() % 1000));
    }
    return head;
}

void print(Node* head){
    while(head->next != NULL){
        printf("%f ", head->next->val);
        head = head->next;
    }
    printf("\n");
}
