#include<stdio.h>
#include<stdlib.h>
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
    c.nume = (char*)malloc(sizeof (char)*(strlen(nume)+1));
    strcpy(c.nume, nume);
    c.pret = pret;
    c.calificativ = calificativ;
	return c;
}

void afisare(struct Cafea c) {
    printf("%d. %s -> Calificativ: %c, %.2f \n", c.id, c.nume, c.calificativ, c.pret);
}

void afisareVector(struct Cafea* vector, int nrElemente) {
	for (int i =0; i<nrElemente; i++) {
        afisare(vector[i]);
    }
}

struct Cafea* copiazaPrimeleNElemente(struct Cafea* vector, int nrElemente, int nrElementeCopiate) {
	//copiem intr-un vector nou pe care il vom returna primele nrElementeCopiate
	struct Cafea *vectorNou=NULL;
    vectorNou = (struct Cafea*)malloc(sizeof (struct Cafea)* nrElementeCopiate);
    if (nrElementeCopiate >0 && nrElementeCopiate <= nrElemente) {
        for (int i=0; i<nrElementeCopiate; i++) {
            vectorNou[i] = vector[i];
            vectorNou[i].nume = (char*)malloc(sizeof (char)*(strlen(vector[i].nume)+1));
            strcpy(vectorNou[i].nume, vector[i].nume);
        }
    }
	return vectorNou;
}

void dezalocare(struct Cafea** vector, int* nrElemente) {
        for (int i = 0; i<(*nrElemente); i++) {
            if((*vector)[i].nume) {
                free((*vector)[i].nume);
            }
        }
        free(*vector);
        *vector = NULL;
        *nrElemente = 0;
}

void copiazaCafeleScumpe(struct Cafea* vector, int nrElemente, float prag, struct Cafea** vectorNou, int* dimensiune) {
    *dimensiune = 0;
    for(int i =0; i <nrElemente; i++) {
        if(vector[i].pret >=prag) {
            (*dimensiune)++;
        }
    }
    if(*vectorNou!=NULL) {
        free(*vectorNou);
    }
    (*vectorNou) = (struct Cafea*)malloc(sizeof(struct Cafea)*(*dimensiune));
    int k = 0;
    for (int i = 0; i<nrElemente; i++) {
        if (vector[i].pret >= prag) {
            (*vectorNou)[k] = vector[i];
            (*vectorNou)[k].nume = (char*) malloc(sizeof(char)* (strlen(vector[i].nume) +1) );
            strcpy((*vectorNou)[k].nume, vector[i].nume);
            k++;
        }
    }
}

struct Cafea getPrimulElementConditionat(struct Cafea* vector, int nrElemente, const char* conditie) {
	//trebuie cautat elementul care indeplineste o conditie
	//dupa atributul de tip char*. Acesta este returnat.
	struct Cafea c;
	c.id = 1;

	return c;
}



int main() {
    struct Cafea* cafele = NULL;
    int nrCafele = 3;
    cafele = (struct Cafea*) malloc(sizeof(struct Cafea)*nrCafele);
    cafele[0] = initializare(1, "Lavazza", 123.5, 'A');
    cafele[1]=initializare(2, "Latte", 12.5, 'B');
    cafele[2]=initializare(3, "Espresso", 130.4, 'C');
    afisareVector(cafele,nrCafele);

    struct Cafea* cafeleScumpe = NULL;
    struct Cafea* primeleCafele = NULL;
    int nrDeCopiat = 2;
    primeleCafele = copiazaPrimeleNElemente(cafele, nrCafele, nrDeCopiat);
    printf("\nPrimele %d cafele din vector: \n", nrDeCopiat);
    afisareVector(primeleCafele, nrDeCopiat);
    dezalocare(&primeleCafele, &nrDeCopiat);
    float prag = 100.0;
    int nrCafeleScumpe =0;
    copiazaCafeleScumpe(cafele, nrCafele, prag,
                        &cafeleScumpe, &nrCafeleScumpe);

    printf("\nAfisare cafele cu pretul mai mare de %.2f RON\n", prag);
    afisareVector(cafeleScumpe, nrCafeleScumpe);
    dezalocare(&cafeleScumpe, &nrCafeleScumpe);
    dezalocare(&cafele, &nrCafele);
	return 0;
}