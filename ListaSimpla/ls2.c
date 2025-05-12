#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Cafea {
    int id;
    char* nume;
    float pret;
    char calificativ;
} Cafea;

void afisareCafea(Cafea c) {
    printf("%d. %s -> Calificativ: %c, %.2f \n", c.id, c.nume, c.calificativ, c.pret);
}

void afisareVector(struct Cafea* vector, int nrElemente) {
    for (int i =0; i<nrElemente; i++) {
        afisareCafea(vector[i]);
    }
}

void adaugaCafeaInVector(Cafea** cafele, int * nrCafele, Cafea cafeaNoua) {
    Cafea* aux = (Cafea*)malloc(sizeof (Cafea)* ((*nrCafele)+1));
    for(int i=0;i<(*nrCafele);i++) {
        aux[i] = (*cafele)[i];
    }
    aux[(*nrCafele)] = cafeaNoua;
    free(*cafele);
    *cafele = aux;
    (*nrCafele)++;
}

Cafea citireCafeaFisier(FILE* file) {
	Cafea c;
	char buffer[100];
	char sep[4] = ",;\n";
    char* aux;
    if (fgets(buffer, 100, file) == NULL) {
        c.id = -1;
        return c;
    }
	c.id = atoi(strtok(buffer, sep));
    aux = strtok(NULL, sep);
    c.nume = (char*)malloc(sizeof(char)*strlen(aux)+1);
    strcpy(c.nume, aux);
    c.pret = atof(strtok(NULL, sep));
    c.calificativ=strtok(NULL,sep)[0];
	return c;
}

Cafea* citireVectorCafeleFisier(const char* numeFisier, int* nrCafeleCitite) {
	FILE* file = fopen(numeFisier, "r");
    if (!file) {
        printf("Eroare: Nu s-a putut deschide fisierul!\n");
        return NULL;
    }
	Cafea* cafele = NULL;
	(*nrCafeleCitite) = 0;
    while (1) {
        Cafea cafea = citireCafeaFisier(file);
        if (cafea.id == -1) break;
        adaugaCafeaInVector(&cafele, nrCafeleCitite, cafea);
    }
	fclose(file);
	return cafele;
}
Cafea* cafelePestePrag(Cafea* cafele, int nrCafele, float prag, int* nrCafeleScumpe) {
    *nrCafeleScumpe = 0;

    // Numărăm câte trec pragul
    for (int i = 0; i < nrCafele; i++) {
        if (cafele[i].pret > prag) {
            (*nrCafeleScumpe)++;
        }
    }

    // Alocăm vector nou
    Cafea* rezultat = (Cafea*)malloc(sizeof(Cafea) * (*nrCafeleScumpe));
    int k = 0;
    for (int i = 0; i < nrCafele; i++) {
        if (cafele[i].pret > prag) {
            rezultat[k].id = cafele[i].id;
            rezultat[k].pret = cafele[i].pret;
            rezultat[k].calificativ = cafele[i].calificativ;
            rezultat[k].nume = (char*)malloc(strlen(cafele[i].nume) + 1);
            strcpy(rezultat[k].nume, cafele[i].nume);
            k++;
        }
    }

    return rezultat;
}
void scrieCafeleInFisier(const char* numeFisier, Cafea* cafele, int nrCafele) {
    FILE* file = fopen(numeFisier, "w");
    if (!file) {
        printf("Eroare: Nu s-a putut deschide fisierul %s pentru scriere.\n", numeFisier);
        return;
    }

    for (int i = 0; i < nrCafele; i++) {
        fprintf(file, "%d,%s,%.2f,%c\n",
                cafele[i].id,
                cafele[i].nume,
                cafele[i].pret,
                cafele[i].calificativ);
    }

    fclose(file);
}
void dezalocareVectorCafele(Cafea** vector, int* nrCafele) {
	for (int i = 0; i < *nrCafele; i++) {
		if ((*vector)[i].nume != NULL) {
			free((*vector)[i].nume);
		}
	}
	free(*vector);
	(*vector) = NULL;
	(*nrCafele) = 0;
}

int main() {
    int nrCafele = 0;
    Cafea * cafele = citireVectorCafeleFisier("cafele.txt", &nrCafele);
    afisareVector(cafele, nrCafele);
    int nrCafeleScumpe = 0;
    float prag = 10.0;
    Cafea* cafeleScumpe = cafelePestePrag(cafele, nrCafele, prag, &nrCafeleScumpe);

    if (nrCafeleScumpe > 0) {
        scrieCafeleInFisier("cafeleScumpe.txt", cafeleScumpe, nrCafeleScumpe);
        printf("Am salvat %d cafele scumpe in fisier.\n", nrCafeleScumpe);
    } else {
        printf("Nu exista cafele peste pragul de %.2f.\n", prag);
    }

// Eliberăm memoria pentru vectorul nou
    for (int i = 0; i < nrCafeleScumpe; i++) {
        free(cafeleScumpe[i].nume);
    }
    free(cafeleScumpe);

    dezalocareVectorCafele(&cafele, &nrCafele);
	return 0;
}