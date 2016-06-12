//
// Created by wojtek on 12.06.16.
//

#ifndef KOLOKWIA_K2_ZAD3_15_16_H
#define KOLOKWIA_K2_ZAD3_15_16_H

#include <time.h>
#include <stdbool.h>

const int ID_MAX = 1000;
const int CYCLIST_COUNT = 10;

typedef struct Cyclist {
    int id, n_id;           //identyfiktor rowerzysty oraz tego, ktorego widzi
} Cyclist;

typedef struct Group {
    int first_id;           //identyfikator pierwszej osoby, potem jest identyfikatorem osoby, dla ktorej szukamy osoby, ktora go widzi
    int size;               //rozmiar grupy
} Group;


Cyclist *generate_data() {
    srand(time(NULL));
    bool *B = (bool *) calloc(sizeof(bool), CYCLIST_COUNT);
    Cyclist *C = (Cyclist *) calloc(sizeof(Cyclist), CYCLIST_COUNT);

    for (int i = 0; i < CYCLIST_COUNT; ++i) {
        C[i].id = rand() % ID_MAX;
    }

    C[0].n_id = -1;
    for (int i = 1; i < CYCLIST_COUNT; ++i) {

        if (rand() % 4 == 0)
            C[i].n_id = -1;
        else {
            int x = rand() % CYCLIST_COUNT;
            while (B[x]) {                          //lata na sytuacje, w ktorej dwaj rowerzysci maja przed soba ta sama osobe
                x = rand() % CYCLIST_COUNT;         //jada gesiego => sytuacja niemozliwa
            }

            C[i].n_id = C[x].id;
            B[x] = true;
        }
    }

    return C;
}


int smallest_group(Cyclist *cyclist, int n) {
    Group*G = (Group*)calloc(sizeof(Group),n);

    bool*B = (bool*)calloc(sizeof(bool),n);

    int max_group_size = 0;
    int group_count = 0;
    int j = 0;

    for (int i = 0; i < CYCLIST_COUNT; ++i) {

        if (cyclist[i].n_id == -1){             //znalezienie pierwszych osob w grupie
            G[j].first_id = cyclist[i].id;      //ustawienie
            G[j].size++;

            B[i] = true;                            //ustawienie ze przewtorzono
            group_count++;
            j++;
        }
    }

    for (int i = 0; i < CYCLIST_COUNT; ++i) {
        if (!B[i]) {
            for (int j = 0; j < group_count; ++j) {
                if (cyclist[i].n_id ==  G[j].first_id){
                    G[j].size++;
                    G[j].first_id = cyclist[i].id;
                    B[i] = true;
                    i = -1;
                    break;
                }
            }
        }
    }


    for (int i = 0; i < group_count; ++i) {
        if (G[i].size > max_group_size)
            max_group_size = G[i].size;
    }

    return max_group_size;
}


void run_k2_zad3_15_16(){
    //smallest_group(generate_data(),100);

    Cyclist*c = generate_data();
    for (int i = 0; i < CYCLIST_COUNT; ++i) {
        printf("%d\t",c[i].id);
    }
        printf("\n");

    for (int i = 0; i < CYCLIST_COUNT; ++i) {
        printf("%d\t",c[i].n_id);
    }

    printf("%d",smallest_group(c,CYCLIST_COUNT));

}


#endif //KOLOKWIA_K2_ZAD3_15_16_H
