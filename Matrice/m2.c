#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Cafea {
    int id;
    char* nume;
    float pret;
    char calificativ;
};

struct Cafea initializare(int id, const char* nume, float pret, char calificativ) {
    struct Cafea c;
    c.id = id;
    c.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
    strcpy(c.nume, nume);
    c.pret = pret;
    c.calificativ = calificativ;
    return c;
}

void afisare(struct Cafea c) {
    printf("%d. %s -> Calificativ: %c, %.2f \n", c.id, c.nume, c.calificativ, c.pret);
}

int main() {
    int rows = 2, cols = 3;
    struct Cafea** matriceCafele = (struct Cafea**)malloc(rows * sizeof(struct Cafea*));

    for (int i = 0; i < rows; i++) {
        matriceCafele[i] = (struct Cafea*)malloc(cols * sizeof(struct Cafea));
    }

    matriceCafele[0][0] = initializare(1, "Lavazza", 123.5, 'A');
    matriceCafele[0][1] = initializare(2, "Latte", 12.5, 'B');
    matriceCafele[0][2] = initializare(3, "Espresso", 130.4, 'C');
    matriceCafele[1][0] = initializare(4, "Cappuccino", 100.0, 'A');
    matriceCafele[1][1] = initializare(5, "Mocha", 140.5, 'B');
    matriceCafele[1][2] = initializare(6, "Americano", 90.0, 'C');

    printf("Afisare matrice cafele:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            afisare(matriceCafele[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matriceCafele[i][j].nume) {
                free(matriceCafele[i][j].nume);
            }
        }
        free(matriceCafele[i]);
    }
    free(matriceCafele);

    return 0;
}