//
// Created by wojtek on 12.06.16.
//

#ifndef KOLOKWIA_KOL1_2014_2015_ZAD2_H
#define KOLOKWIA_KOL1_2014_2015_ZAD2_H

//dostajemy wskaznik na liste
//funkcja ma rozdzielic liste na 2, w jednej sa parzyste, a w drugiej nieparzyste


TwoLists* split(node*list){
    TwoLists*A = (TwoLists*)malloc(sizeof(TwoLists));
    node*odd = (node*)malloc(sizeof(node));
    node*even = (node*)malloc(sizeof(node));
    node*r = (node*)malloc(sizeof(node));
    node*s = (node*)malloc(sizeof(node));
    node*p,*q;   //wskazniki robocze
    //p - roboczy na wejsciwa liste
    //q - poprzednik p
    odd->next = r;
    even->next = s;

    p = list;
    q = p;
    while (p != NULL){
        if (p->val % 2 == 0){
            q->next = p->next;
            r->next = p;
            r = r->next;

        } else {
            q->next = p->next;
            s->next = p;
            s = s->next;
        }

        q = p;
        p = p->next;
    }

    A->even = even->next->next;
    A->odd = odd->next->next;

    return A;
}

void run_k1_zad2_14_15(){
    node*a = generate_list(21);
    TwoLists*B = split(a);
    print_list(B->even);
    print_list(B->odd);

}

#endif //KOLOKWIA_KOL1_2014_2015_ZAD2_H
