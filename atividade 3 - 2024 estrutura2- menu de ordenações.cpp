#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOMES 1000  // Número máximo de nomes
#define TAM_NOME 100    // Tamanho máximo de cada nome

void bubbleSort(char nomes[][TAM_NOME], int n);
void selectionSort(char nomes[][TAM_NOME], int n);
void insertionSort(char nomes[][TAM_NOME], int n);
void mergeSort(char nomes[][TAM_NOME], int l, int r);
void merge(char nomes[][TAM_NOME], int l, int m, int r);
void imprimirNomes(char nomes[][TAM_NOME], int n);
void lerArquivo(char nomes[][TAM_NOME], int *n);

int main() {
    char nomes[MAX_NOMES][TAM_NOME];
    int n = 0;  // Contador de nomes lidos
    int opcao;

    lerArquivo(nomes, &n);

    do {
        printf("\nEscolha um algoritmo de ordenação:\n");
        printf("1 - Bubble Sort\n");
        printf("2 - Selection Sort\n");
        printf("3 - Insertion Sort\n");
        printf("4 - Merge Sort\n");
        printf("5 - Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                bubbleSort(nomes, n);
                printf("Nomes ordenados com Bubble Sort:\n");
                imprimirNomes(nomes, n);
                break;
            case 2:
                selectionSort(nomes, n);
                printf("Nomes ordenados com Selection Sort:\n");
                imprimirNomes(nomes, n);
                break;
            case 3:
                insertionSort(nomes, n);
                printf("Nomes ordenados com Insertion Sort:\n");
                imprimirNomes(nomes, n);
                break;
            case 4:
                mergeSort(nomes, 0, n - 1);
                printf("Nomes ordenados com Merge Sort:\n");
                imprimirNomes(nomes, n);
                break;
            case 5:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 5);

    return 0;
}

void lerArquivo(char nomes[][TAM_NOME], int *n) {
    FILE *arquivo = fopen("nomes2.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    while (fgets(nomes[*n], TAM_NOME, arquivo) != NULL) {
        // Remove o caractere de nova linha (\n) no final da string
        nomes[*n][strcspn(nomes[*n], "\n")] = '\0';
        (*n)++;
    }

    fclose(arquivo);
}

void imprimirNomes(char nomes[][TAM_NOME], int n) {
    for (int i = 0; i < n; i++) {
        printf("%s\n", nomes[i]);
    }
}

void bubbleSort(char nomes[][TAM_NOME], int n) {
    char temp[TAM_NOME];
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(nomes[j], nomes[j + 1]) > 0) {
                strcpy(temp, nomes[j]);
                strcpy(nomes[j], nomes[j + 1]);
                strcpy(nomes[j + 1], temp);
            }
        }
    }
}

void selectionSort(char nomes[][TAM_NOME], int n) {
    char temp[TAM_NOME];
    int min_idx;
    for (int i = 0; i < n - 1; i++) {
        min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (strcmp(nomes[j], nomes[min_idx]) < 0) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            strcpy(temp, nomes[i]);
            strcpy(nomes[i], nomes[min_idx]);
            strcpy(nomes[min_idx], temp);
        }
    }
}

void insertionSort(char nomes[][TAM_NOME], int n) {
    char key[TAM_NOME];
    int j;
    for (int i = 1; i < n; i++) {
        strcpy(key, nomes[i]);
        j = i - 1;
        while (j >= 0 && strcmp(nomes[j], key) > 0) {
            strcpy(nomes[j + 1], nomes[j]);
            j = j - 1;
        }
        strcpy(nomes[j + 1], key);
    }
}

void mergeSort(char nomes[][TAM_NOME], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(nomes, l, m);
        mergeSort(nomes, m + 1, r);
        merge(nomes, l, m, r);
    }
}

void merge(char nomes[][TAM_NOME], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    char L[n1][TAM_NOME], R[n2][TAM_NOME];

    for (i = 0; i < n1; i++)
        strcpy(L[i], nomes[l + i]);
    for (j = 0; j < n2; j++)
        strcpy(R[j], nomes[m + 1 + j]);

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (strcmp(L[i], R[j]) <= 0) {
            strcpy(nomes[k], L[i]);
            i++;
        } else {
            strcpy(nomes[k], R[j]);
            j++;
        }
        k++;
    }

    while (i < n1) {
        strcpy(nomes[k], L[i]);
        i++;
        k++;
    }

    while (j < n2) {
        strcpy(nomes[k], R[j]);
        j++;
        k++;
    }
}
