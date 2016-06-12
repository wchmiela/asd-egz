//
// Created by wojtek on 11.06.16.
//

#ifndef KOLOKWIA_MAIN_H
#define KOLOKWIA_MAIN_H

#include "k1-zad1-15-16.h"
#include "k1-zad3-15-16.h"
#include "k2-zad1-15-16.h"
#include "k2-zad3-15-16.h"

const int MAX_LEVEL = 10;

typedef struct node {
    int val;
    struct node*next;
} node;

typedef struct SLNode{
    int value;
    int level;
    struct SLNode** next;
}SLNode;

typedef struct Skiplist{
    struct SLNode*first;
    struct SLNode*last;
}Skiplist;


Skiplist merge(Skiplist A, Skiplist B){


}


#endif //KOLOKWIA_MAIN_H
