//
// Created by wojtek on 11.06.16.
//

#ifndef KOLOKWIA_ZAD3_15_16_H
#define KOLOKWIA_ZAD3_15_16_H

node *get_max(node **pNode);

#include <stdlib.h>
#include <stdio.h>

node *generate_list(int size) {
    node *head = NULL;
    for (int i = 0; i < size; i++) {
        node *p = (node *) malloc(sizeof(node));
        p->val = rand() % 100;
        p->next = head;
        head = p;
    }

    return head;
}

void print_list(node *head) {
    while (head != NULL) {
        printf("%d\t", head->val);
        head = head->next;
    }
    printf("\n");
}

node*sort_list(node*head){
    node*res = NULL;
    node*p;

    while (head){
        p = get_max(&head);
        p->next = res;
        res = p;
    }

    return res;
}

node *get_max(node **head) {
    node *w = (node*)malloc(sizeof(node));      //wartownik
    w->next = *head;
    node*p = *head;     //wskaznik roboczy
    node*q = w;         //wskaznik na element poprzedzajacy element max

    while (p->next != NULL){
        if (p->next->val > q->next->val)
            q = p;

        p = p->next;
    }

    node*max = q->next;
    q->next = q->next->next;
    max->next = NULL;

    *head = w->next;
    free(w);

    return max;
}

void change_random_value(node*head, int size){
    node*p = head;         //wskaznik roboczy
    int r = rand()%size;
    int i = 0;

    while (p != NULL){
        if (i == r){
            p->val = (rand()%100+rand()%100)%100;
            return;
        }

        i++;
        p = p->next;
    }
}


node*fix_sorted_list(node*head){
    node*p = head;
    node*q = NULL;
    node*r = NULL;

    while (p->next != NULL){
        if (p->val > p->next->val) {
            q = p;
            r->next = p->next;
        }
        r = p;
        p = p->next;
    }

    p = head;
    r = NULL;

    while (p != NULL){
        if (p->val > q->val){
            q->next = p;
            r->next = q;
            break;
        }
        r = p;
        p = p->next;
    }

    return head;
}




#endif //KOLOKWIA_ZAD3_15_16_H
