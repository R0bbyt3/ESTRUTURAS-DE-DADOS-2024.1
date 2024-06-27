#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

typedef struct no No;
struct no {
    int info;
    No* prox;
};

struct fila {
    No* ini;
    No* fim;
};

Fila* fila_cria(void) {
    printf("Fila implementada com lista\n");
    Fila* f = (Fila*)malloc(sizeof(Fila));
    f->ini = f->fim = NULL;
    return f;
}

void fila_insere(Fila* f, int v) {
    No* novo = (No*)malloc(sizeof(No));
    novo->info = v;
    novo->prox = NULL;

    if (f->ini == NULL && f->fim == NULL) {
        f->ini = novo;
        f->fim = novo;
    }
    else {
        (f->fim)->prox = novo;
        f->fim = novo;
    }
}

int fila_retira(Fila* f) {
    No* n = f->ini;
    int v = n->info;
    f->ini = n->prox;
    free(n);
    return v;
}

int fila_vazia(Fila* f) {
    return (f->ini == NULL);
}

void fila_libera(Fila* f) {
    No* n = f->ini;
    while (n != NULL) {
        No* t = n->prox;
        free(n);
        n = t;
    }
    free(f);
}


