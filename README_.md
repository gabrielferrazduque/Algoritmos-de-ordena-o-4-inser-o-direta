#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Versão básica para int
void insertion_sort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Versão com contagem de comparações e movimentações (cópias)
void insertion_sort_count(int arr[], int n, long *comparisons, long *moves) {
    *comparisons = 0;
    *moves = 0;
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0) {
            (*comparisons)++; // contando a comparação arr[j] > key
            if (arr[j] > key) {
                arr[j + 1] = arr[j];
                (*moves)++;
                j--;
            } else {
                break;
            }
        }
        arr[j + 1] = key;
        (*moves)++; // cópia do key para a posição final
    }
}

// Busca binária para encontrar o índice onde inserir key em arr[l..r]
// Retorna a posição de inserção (entre l e r+1)
int binary_search_insert_index(int arr[], int l, int r, int key) {
    while (l <= r) {
        int m = l + (r - l) / 2;
        if (arr[m] == key)
            return m + 1; // inserir depois para manter estabilidade relativa opcional
        else if (arr[m] < key)
            l = m + 1;
        else
            r = m - 1;
    }
    return l;
}

// Versão com busca binária (reduz comparações, mas ainda move elementos)
void insertion_sort_binary(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        // encontra posição de inserção no subvetor [0..i-1]
        int pos = binary_search_insert_index(arr, 0, i - 1, key);
        // desloca elementos para a direita para abrir espaço
        memmove(&arr[pos + 1], &arr[pos], (size_t)((i - pos) * sizeof(int)));
        arr[pos] = key;
    }
}

// Versão genérica para qualquer tipo (usando comparador estilo qsort)
// base: ponteiro para início, n: número de elementos, size: tamanho de cada elemento
void insertion_sort_generic(void *base, size_t n, size_t size,
                            int (*cmp)(const void *, const void *)) {
    if (n <= 1) return;
    void *key = malloc(size);
    if (!key) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 1; i < n; i++) {
        void *pi = (char *)base + i * size;
        memcpy(key, pi, size);
        ssize_t j = (ssize_t)i - 1;
        while (j >= 0) {
            void *pj = (char *)base + j * size;
            if (cmp(pj, key) > 0) {
                // move pj para pj+1
                memcpy((char *)base + (j + 1) * size, pj, size);
                j--;
            } else {
                break;
            }
        }
        memcpy((char *)base + (j + 1) * size, key, size);
    }

    free(key);
}

// Função utilitária para imprimir int[]
void print_int_array(const int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d%c", arr[i], (i + 1 == n) ? '\n' : ' ');
    }
}

// Exemplo de uso e teste
int main(void) {
    int arr1[] = {12, 11, 13, 5, 6};
    int n = sizeof(arr1) / sizeof(arr1[0]);

    printf("Original: ");
    print_int_array(arr1, n);

    int a1[5];
    memcpy(a1, arr1, sizeof(arr1));
    insertion_sort(a1, n);
    printf("Ordenado (insertion_sort): ");
    print_int_array(a1, n);

    int a2[5];
    memcpy(a2, arr1, sizeof(arr1));
    long comps, moves;
    insertion_sort_count(a2, n, &comps, &moves);
    printf("Ordenado (insertion_sort_count): ");
    print_int_array(a2, n);
    printf("Comparações: %ld, Movimentações: %ld\n", comps, moves);

    int a3[5];
    memcpy(a3, arr1, sizeof(arr1));
    insertion_sort_binary(a3, n);
    printf("Ordenado (insertion_sort_binary): ");
    print_int_array(a3, n);

    // Exemplo genérico: ordenar doubles
    double darr[] = {3.2, 1.1, 5.0, 2.7};
    size_t dn = sizeof(darr) / sizeof(darr[0]);
    int cmp_double(const void *x, const void *y) {
        double dx = *(const double *)x;
        double dy = *(const double *)y;
        if (dx < dy) return -1;
        if (dx > dy) return 1;
        return 0;
    }
    insertion_sort_generic(darr, dn, sizeof(double), cmp_double);
    printf("Doubles ordenados (generic): ");
    for (size_t i = 0; i < dn; i++) {
        printf("%.2f%c", darr[i], (i + 1 == dn) ? '\n' : ' ');
    }

    return 0;
}
