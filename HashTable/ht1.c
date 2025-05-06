#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

typedef struct Node {
    int key;
    int value;
    struct Node* next;
} Node;

Node* hashTable[SIZE] = {NULL};

int hash(int key) {
    return key % SIZE;
}

void insert(int key, int value) {
    int index = hash(key);
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->value = value;
    newNode->next = hashTable[index];
    hashTable[index] = newNode;
}

int search(int key) {
    int index = hash(key);
    Node* temp = hashTable[index];
    while (temp) {
        if (temp->key == key) return temp->value;
        temp = temp->next;
    }
    return -1; // not found
}

void display() {
    for (int i = 0; i < SIZE; i++) {
        printf("%d: ", i);
        Node* temp = hashTable[i];
        while (temp) {
            printf("(%d, %d) -> ", temp->key, temp->value);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

int main() {
    insert(1, 10);
    insert(11, 20);
    insert(21, 30);
    insert(2, 40);

    display();

    printf("Search key 11: %d\n", search(11));
    printf("Search key 5: %d\n", search(5));

    // Free memory
    for (int i = 0; i < SIZE; i++) {
        Node* temp = hashTable[i];
        while (temp) {
            Node* toDelete = temp;
            temp = temp->next;
            free(toDelete);
        }
    }

    return 0;
}