#include <stdio.h>
#include <stdlib.h>

int main() {
    int n = 5;
    int* vector = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        vector[i] = i * 10;
    }

    for (int i = 0; i < n; i++) {
        printf("%d ", vector[i]);
    }

    free(vector);
    return 0;
}