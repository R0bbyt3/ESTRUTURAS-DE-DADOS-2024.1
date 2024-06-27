#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "heapmax.h"

int main(void) {
    // Monta heap em tempo linear
    int n = 11; // numero de valores do arrayvalores
    int entrada[] = { 21, 19, 16, 22, 17, 20, 23, 12, 34, 15, 60 };
    int ordenado[] = { 60, 34, 23, 22, 21, 20, 19, 17, 16, 15, 12 };
    Heap* h = heap_cria(30, n, entrada);
    heap_debug_show(h, ">>>>> Heap maximo <<<<<");
    printf("\n");
    for (int i = 0; i < n; i++) {
        int info = heap_remove(h);
        printf("removeu %d: %s\n", info, ordenado[i] == info ? "Correto" : "Errado");
    }
    heap_libera(h);

    // Testa formas de criar heap
    int numero_de_valores = 500; // aumente o numero de valores aqui
    int* v = (int*)malloc(sizeof(int) * numero_de_valores);
    for (int i = 0; i < numero_de_valores; i++) {
        v[i] = rand() % 500000;
    }
    ////////////////////////////////////////////////
    printf("Criacao de heap em tempo linear: ");
    clock_t t1_s = clock();
    Heap* h1 = heap_cria(numero_de_valores, numero_de_valores, v);
    clock_t t1_e = clock();
    double t1_t = (double)(t1_e - t1_s) / CLOCKS_PER_SEC;
    printf(" %.10lf segundos\n", t1_t);
    free(h1);
    ////////////////////////////////////////////////
    printf("Criacao de heap em tempo n logaritmico: ");
    clock_t t2_s = clock();
    Heap* h2 = heap_cria(numero_de_valores, 0, NULL);
    for (int i = 0; i < numero_de_valores; i++)
        heap_insere(h2, v[i]);
    clock_t t2_e = clock();
    double t2_t = (double)(t2_e - t2_s) / CLOCKS_PER_SEC;
    printf(" %.10lf segundos\n", t2_t);
    free(h2);
    ////////////////////////////////////////////////
    free(v);

    // Avalia heapsort
    int* vetheapsort = heap_sort(entrada, n);
    printf("vetor ordenado: ");
    for (int i = 0; i < n; i++)
        printf("%d ", vetheapsort[i]);
    printf("\n");
    free(vetheapsort);

    return 0;
}