#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Masina {
    int id;
    int nrUsi;
    float pret;
    char* model;
    char* numeSofer;
    char serie;
} Masina;

Masina creareMasina(int id, int nrUsi, float pret, const char* model, const char* numeSofer, char serie) {
    Masina m;
    m.id = id;
    m.nrUsi = nrUsi;
    m.pret = pret;
    m.model = strdup(model);
    m.numeSofer = strdup(numeSofer);
    m.serie = serie;
    return m;
}

void afisareMasina(Masina m) {
    printf("%d | %d usi | %.2f RON | %s | %s | %c\n", m.id, m.nrUsi, m.pret, m.model, m.numeSofer, m.serie);
}

void dezalocareMasina(Masina* m) {
    free(m->model);
    free(m->numeSofer);
}

// AVL Node
typedef struct Node {
    Masina data;
    struct Node* left;
    struct Node* right;
    int height;
} Node;

int height(Node* n) {
    return n ? n->height : 0;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

int getBalance(Node* n) {
    return n ? height(n->left) - height(n->right) : 0;
}

Node* insert(Node* node, Masina data) {
    if (!node) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->data = data;
        newNode->left = newNode->right = NULL;
        newNode->height = 1;
        return newNode;
    }

    if (data.id < node->data.id)
        node->left = insert(node->left, data);
    else if (data.id > node->data.id)
        node->right = insert(node->right, data);
    else
        return node;  // Duplicate IDs not allowed

    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);

    // Balancing
    if (balance > 1 && data.id < node->left->data.id)
        return rightRotate(node);

    if (balance < -1 && data.id > node->right->data.id)
        return leftRotate(node);

    if (balance > 1 && data.id > node->left->data.id) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && data.id < node->right->data.id) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void inOrder(Node* root) {
    if (root) {
        inOrder(root->left);
        afisareMasina(root->data);
        inOrder(root->right);
    }
}

void freeTree(Node* root) {
    if (root) {
        freeTree(root->left);
        freeTree(root->right);
        dezalocareMasina(&root->data);
        free(root);
    }
}

int main() {
    FILE* f = fopen("masini.txt", "r");
    if (!f) {
        printf("Eroare la deschiderea fisierului!\n");
        return 1;
    }

    Node* root = NULL;
    char line[256];
    while (fgets(line, sizeof(line), f)) {
        int id, nrUsi;
        float pret;
        char model[50], sofer[50], serie;
        if (sscanf(line, "%d,%d,%f,%[^,],%[^,],%c", &id, &nrUsi, &pret, model, sofer, &serie) == 6) {
            Masina m = creareMasina(id, nrUsi, pret, model, sofer, serie);
            root = insert(root, m);
        }
    }
    fclose(f);

    printf("Masini ordonate dupa ID (AVL in-order):\n");
    inOrder(root);

    freeTree(root);
    return 0;
}