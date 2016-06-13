//
// Created by wojtek on 29.05.16.
//

#ifndef IMPLEMENTACJE_SORTOWAN_BUCKETSORT_H
#define IMPLEMENTACJE_SORTOWAN_BUCKETSORT_H

node*get_max(node**head){
    node*w = (node*)malloc(sizeof(node));
    w->next = *head;
    node*p = *head; //roboczy
    node*q = w;

    while(p->next !=  NULL){
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

node* sort_bucket(node *head) {
    node*res = NULL;
    node*p;

    while(head){
        p = get_max(&head);
        p->next = res;
        res = p;
    }

    return res;
}





void bucket_sort(int*A, unsigned int size, int k){
    node**B = (node**)calloc(sizeof(node),k);
    node*r; //wskaznik roboczy

    int max = get_max_val(A, size);
    int idx = 0;

    double bucket_size = (double)max / (double)k;

    for (int i = 0; i < size; ++i) {
        idx = A[i]/bucket_size ;
        if (idx == k)
            idx--;

        node*p = (node*)malloc(sizeof(node));
        p->val = A[i];
        p->next = NULL;

        if (B[idx] == NULL){
            B[idx] = p;
        } else {
            r = B[idx];
            while(r->next != NULL){
                r = r->next;
            }
            r->next = p;
        }
    }

    int p = 0;
    for (int i = 0;  i < k; ++ i) {
        B[i] = sort_bucket(B[i]);
        for (node*a = B[i]; a != NULL; a = a->next) {
            A[p] = a->val;
            p++;
        }
    }
}





#endif //IMPLEMENTACJE_SORTOWAN_BUCKETSORT_H
