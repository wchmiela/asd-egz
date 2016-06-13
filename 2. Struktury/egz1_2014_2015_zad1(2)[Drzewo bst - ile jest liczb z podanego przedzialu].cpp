#include <stdlib.h>
#include <stdio.h>

using namespace std;

struct Node{
    int val;
    Node* left,* right;
};

void addNode(Node* head, int val);
Node* concatenate(Node* s1, Node* s2);
void print(Node* head);
void add(Node* proot, int val);
int countInterval(Node* proot, int a, int b);
void  print(Node* ptr);
int main(){
    Node* proot = new Node;
    proot->left = proot->right = NULL;
    proot->val = 5;
    add(proot, 3);
    add(proot, 8);
    add(proot, 2);
    add(proot, 4);
    add(proot, 7);
    add(proot, 9);
    //print(proot);
    printf("%d ", countInterval(proot, 4, 7));
    printf("%d ", countInterval(proot, 2, 9));
}

void print(Node* ptr){
    if(!ptr) return;
     print(ptr->left);
    printf("%d ", ptr->val);
    print(ptr->right);
}

int treeSize(Node* proot){
    int sum=0;
    if(proot){
        sum = treeSize(proot->left) + 1 + treeSize(proot->right);
    }
    return sum;
}

int countSmallerNodes(Node* proot, int val){
    int sum=0;
    while(proot && proot->val != val){
        if(proot->val < val){
            sum += treeSize(proot->left) + 1;
            proot = proot->right;
        }
        else{
            proot = proot->left;
        }
    }
    if(proot->val != val) return -1;
    return sum + 1;
}

int countInterval(Node* proot, int a, int b){
    return countSmallerNodes(proot, b) - countSmallerNodes(proot, a) + 1;
}

void add(Node* proot, int val){
    Node* parent;
    Node* ptr = new Node;
    ptr->left = ptr->right = NULL;
    ptr->val = val;
    while(proot){
        parent = proot;
        if(proot->val > val){
            proot = proot->left;
        }
        else{
            proot = proot->right;
        }
    }
    if(parent->val > val){
        parent->left = ptr;
    }
    else{
        parent->right = ptr;
    }
}
