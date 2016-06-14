//
// Created by wojtek on 12.06.16.
//

#ifndef KOLOKWIA_KOL1_2014_2015_ZAD1_H
#define KOLOKWIA_KOL1_2014_2015_ZAD1_H

//napisac funkcje, ktora sortuje tablice n stringow, stringi skladaja sie z malych liter alfabetu lacinskiego
//alfabet lacinski ma 26 liter

const int LETTERS_COUNT = 26;

char **generate_char_array(int size, int max_length) {
    char **A = (char **) calloc(sizeof(char *), size);

    for (int i = 0; i < size; ++i) {
        int x = rand() % max_length;
        A[i] = (char *) calloc(sizeof(char), x);
        for (int j = 0; j < x; ++j) {
            char randomChar = (char) ('a' + (rand() % 26));
            A[i][j] = randomChar;
        }
    }
    return A;
}


void counting(char **A, int size, int n, int m, int k) {
    char **B = (char **) calloc(sizeof(char *), size);
    for (int i = 0; i < size; ++i) {
        B[i] = (char *) calloc(sizeof(char), m);
    }

    int *C = (int *) calloc(sizeof(int), k);
    char x;
    int y;

    for (int i = 0; i < size; ++i) {
        x = A[i][n];
        if (x == '\0')
            continue;
        else {
            y = (int) x - 97;
            C[y]++;
        }
    }

    for (int i = 1; i < k; ++i) {
        C[i] += C[i - 1];
    }

    for (int i = size - 1; i >= 0; --i) {
        x = A[i][n];
        if (x == '\0')
            continue;
        else {
            y = (int) x - 97;
            B[C[y]-1][n] = A[i][n];
            C[y]--;
        }
    }

    for (int i = 0; i < size; ++i) {
        A[i][n] = B[i][n];
    }


}

void sort_strings(char **A, int n) {
    int max_len = (int) strlen(A[0]);
    for (int i = 1; i < n; ++i) {
        if (strlen(A[i]) > max_len)
            max_len = (int) strlen(A[i]);
    }

    for (int i = max_len - 1; i >= 0; --i) {
        counting(A, n, i, max_len, LETTERS_COUNT);
    }
}


void run_kol1_2014_2015_zad1() {
    int size = 4;
    int max_length = 5;

    char **A = generate_char_array(size,max_length);


    for (int i = 0; i < size; ++i) {
        printf("%s\n",A[i]);
    }
        printf("\nPo posortowaniu:\n");

    sort_strings(A, size);

    for (int i = 0; i < size; ++i) {
        printf("%s\n",A[i]);
    }

}


#endif //KOLOKWIA_KOL1_2014_2015_ZAD1_H
