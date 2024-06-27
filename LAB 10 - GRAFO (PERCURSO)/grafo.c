#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "grafo.h"

/* estrutura auxiliar para fila pilha(stack) / fila(queue) */
typedef struct _lista Lista;
struct _lista {
  int info;
  Lista* prox;
};

static Lista* criaLista () {
  return NULL;
}

static Lista* enfileira (Lista* fila, int info) {
  Lista* novo = (Lista*)malloc(sizeof(Lista));
  Lista* aux = fila;
  assert(novo);
  novo->info = info;
  novo->prox = NULL;
  if (!fila) {
    return novo;
  }
  while (aux->prox) {
    aux = aux->prox;
  }
  aux->prox = novo;
  return fila;
}

static Lista* desenfileira (Lista* fila, int* info) {
  Lista* removido;
  if (!fila) {
    *info = -1;
    return NULL;
  }
  *info = fila->info;
  removido = fila;
  fila = fila->prox;
  free(removido);
  return fila;
}

static Lista* empilha (Lista* pilha, int info) {
  Lista* novo = (Lista*)malloc(sizeof(Lista));
  assert(novo);
  novo->info = info;
  novo->prox = pilha;
  return novo;
}

static Lista* desempilha (Lista* pilha, int* info) {
  Lista* removido;
  if (!pilha){
    *info = -1;
    return NULL;
  }
  *info = pilha->info;
  removido = pilha;
  pilha = pilha->prox;
  free(removido);
  return pilha;
}

typedef struct _viz Viz;
struct _viz {
  int   noj;
  float peso;
  Viz*  prox;
};

struct _grafo {
  int   nv;  /* numero de nos ou vertices */
  int   na;  /* numero de arestas */
  Viz** viz; /* viz[i] aponta para a lista de arestas vizinhas do no i */
};

static Viz* criaViz (Viz* head, int noj, float peso) {
/* insere vizinho no inicio da lista */
  Viz* no = (Viz*) malloc(sizeof(Viz));
  assert(no);
  no->noj = noj;
  no->peso = peso;
  no->prox = head;
  return no;
}

static Grafo* grafoCria (int nv, int na) {
  int i;
  Grafo* g = (Grafo *) malloc(sizeof(Grafo));
  g->nv = nv;
  g->na = na;
  g->viz = (Viz **) malloc(sizeof(Viz *) * nv);
  for (i = 0; i < nv; i++)
    g->viz[i] = NULL;
  return g;
}

Grafo* grafoLe (char* filename) {
  /* cria grafo nao orientado - supoe que arquivo esta correto! */
  FILE *arq = fopen(filename, "r");
  int nv, na, no1, no2;
  float peso;
  Grafo* novo;

  fscanf(arq, "%d %d", &nv, &na);
  novo = grafoCria(nv, na);
  assert(novo);
  while (fscanf(arq, "%d %d %f", &no1, &no2, &peso) == 3) {
    novo->viz[no1] = criaViz(novo->viz[no1], no2, peso);
    novo->viz[no2] = criaViz(novo->viz[no2], no1, peso);
  }
  fclose(arq);
  return novo;
}

Grafo*  grafoLibera (Grafo* grafo) {
  if (grafo) {
    int i = 0;
    Viz*no,*aux;
    for (i = 0; i < grafo->nv; i++){
      no = grafo->viz[i];
      while (no){
        aux = no->prox;
        free(no);
        no = aux;
      }
    }
    free(grafo->viz);
    free(grafo);
  }
  return NULL;
}

void grafoMostra (char* title, Grafo * grafo) {
  int i;
  if (title)
    printf("%s", title);
  if (grafo) {
    printf("NV: %d, NA: %d\n", grafo->nv, grafo->na);
    for (i = 0; i < grafo->nv; i++){
    Viz* viz = grafo->viz[i];
    printf("[%d]->", i);
    while (viz) {
      printf("{%d, %g}->", viz->noj, viz->peso);
      viz = viz->prox;
    }
    printf("NULL\n");
    }
  }
}

void grafoPercorreProfundidadeRecAux(Grafo* grafo, int v, int* visitado) {
    visitado[v] = 1;
    printf("%d ", v);
    Viz* viz = grafo->viz[v];
    while (viz) {
        if (!visitado[viz->noj]) {
            grafoPercorreProfundidadeRecAux(grafo, viz->noj, visitado);
        }
        viz = viz->prox;
    }
}

void grafoPercorreProfundidadeRec(Grafo* grafo, int no_inicial) {
    int* visitado = (int*)calloc(grafo->nv, sizeof(int));
    grafoPercorreProfundidadeRecAux(grafo, no_inicial, visitado);
    free(visitado);
    printf("\n");
}

void grafoPercorreLargura (Grafo *grafo, int no_inicial) {
  int *enfileirado = (int *)calloc(grafo->nv, sizeof(int));
  Lista *fila = criaLista();
  fila = enfileira(fila, no_inicial);
  enfileirado[no_inicial] = 1;
  
  while (fila) {
    int v;
    fila = desenfileira(fila, &v);
    printf("%d ", v);
    Viz *viz = grafo->viz[v];
    while (viz) {
      if (!enfileirado[viz->noj]) {
        fila = enfileira(fila, viz->noj);
        enfileirado[viz->noj] = 1;
      }
      viz = viz->prox;
    }
  }
  free(enfileirado);
  printf("\n");
} 

void grafoPercorreProfundidade (Grafo *grafo, int no_inicial) {
  int *empilhado = (int *)calloc(grafo->nv, sizeof(int));
  Lista *pilha = criaLista();
  pilha = empilha(pilha, no_inicial);
  empilhado[no_inicial] = 1;
  
  while (pilha) {
    int v;
    pilha = desempilha(pilha, &v);
    printf("%d ", v);
    Viz *viz = grafo->viz[v];
    Lista *pilha_temp = criaLista();
    while (viz) {
      if (!empilhado[viz->noj]) {
        pilha_temp = empilha(pilha_temp, viz->noj);
      }
      viz = viz->prox;
    }
    while (pilha_temp) {
      int u;
      pilha_temp = desempilha(pilha_temp, &u);
      pilha = empilha(pilha, u);
      empilhado[u] = 1;
    }
  }
  free(empilhado);
  printf("\n");
}
