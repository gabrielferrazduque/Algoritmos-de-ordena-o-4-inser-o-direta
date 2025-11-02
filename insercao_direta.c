#include <stdio.h>

// Função para realizar a ordenação por inserção direta
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i]; // Elemento a ser inserido na posição correta
        int j = i - 1;

        // Move os elementos do array que são maiores que a chave
        // uma posição à frente da sua posição atual
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key; // Insere a chave na posição correta
    }
}

// Função para imprimir o array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {12, 11, 13, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Array original:\n");
    printArray(arr, n);

    insertionSort(arr, n);

    printf("Array ordenado:\n");
    printArray(arr, n);

    return 0;
}