#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"

// indice andando de forma circular
// i = (i+1) % dim;              // usando operacao modulo
// i = (i == (dim-1)) ? 0 : i+1; // usando condicional

// proxima posicao vazia
// fim = (init+n) % dim

struct fila {
	int n; // numero de elementos
	int ini; // inicio da fila
	int dim; // dimensao corrente do vetor
	int* vet; // elementos
};

Fila* fila_cria(void) {
	printf("Fila implementada com vetor\n");
	Fila* f = (Fila*)malloc(sizeof(Fila));
	f->n = 0;   // zero elementos
	f->ini = 0; // posicao inicial
	f->dim = 8; // dimensão inicial
	f->vet = (int*)malloc(f->dim * sizeof(int));
	return f;
}

void fila_insere(Fila* f, int v) {
	if (f->n == f->dim) {
		int novaDim = f->dim * 2;
		int* novoVet = (int*)realloc(f->vet, novaDim * sizeof(int));
		f->vet = novoVet;
		f->dim = novaDim;
	}

		f->vet[(f->ini + f->n) % f->dim] = v;
		f->n++;
	
}

int fila_retira(Fila* f) {
	int valor = f->vet[f->ini];
	f->vet[f->ini] = NULL;
	f->ini = (f->ini + 1) % f->dim;
	f->n--;
	return valor;
}

int fila_vazia(Fila* f) {
	return (f->n == 0);
}

void fila_libera(Fila* f) {
	free(f->vet);
	free(f);
}


