#include <stdio.h>

void insertionSort(int vetor[], int n) {
    int i, j, atual;
    
    for (i = 1; i < n; i++) {
        atual = vetor[i];
        j = i - 1;
        
        // Move elementos maiores uma posição à direita
        while (j >= 0 && vetor[j] > atual) {
            vetor[j + 1] = vetor[j];
            j--;
        }
        
        vetor[j + 1] = atual;
    }
}

void imprimirVetor(int vetor[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n"); 

ara i de 1 até n-1:
  atual = vetor[i]
  j = i - 1
  
  Enquanto j >= 0 e vetor[j] > atual:
    vetor[j+1] = vetor[j]
    j = j - 1
  
  vetor[j+1] = atual
}

int main() {
    int dados[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(dados) / sizeof(dados[0]);
    
    printf("Vetor original: ");
    imprimirVetor(dados, n);
    
    insertionSort(dados, n);
    
    printf("Vetor ordenado: ");
    imprimirVetor(dados, n);
    
    return 0;
}
