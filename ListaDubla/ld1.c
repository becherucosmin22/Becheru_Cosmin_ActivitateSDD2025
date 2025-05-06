#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

void printList(Node* head) {
    while (head != NULL) {
        printf("%d <-> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

int main() {
    Node* head = (Node*)malloc(sizeof(Node));
    Node* second = (Node*)malloc(sizeof(Node));
    Node* third = (Node*)malloc(sizeof(Node));

    head->data = 1;
    head->prev = NULL;
    head->next = second;

    second->data = 2;
    second->prev = head;
    second->next = third;

    third->data = 3;
    third->prev = second;
    third->next = NULL;

    printList(head);

    free(third);
    free(second);
    free(head);

    return 0;
}