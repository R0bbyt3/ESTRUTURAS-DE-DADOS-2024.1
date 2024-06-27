#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include "grafo.h"
#include "heap.h"
#include "ub.h"

typedef struct _viz Viz;
struct _viz {
  int noj;
  int peso;
  Viz*  prox;
};

struct _grafo {
  int nv;    /* numero de nos ou vertices */
  int na;    /* numero de arestas */
  Viz** viz; /* viz[i] aponta para a lista de arestas vizinhas do no i */
};

static Viz* criaViz (Viz* head, int noj, int peso) {
/* insere vizinho no inicio da lista */
  Viz* no = (Viz*) malloc(sizeof(Viz));
  assert(no);
  no->noj = noj;
  no->peso = peso;
  no->prox = head;
  return no;
}

static Grafo* grafoCria (int nv) {
  int i;
  Grafo* g = (Grafo *) malloc(sizeof(Grafo));
  assert(g);
  g->nv = nv;
  g->na = 0;
  g->viz = (Viz **) malloc(sizeof(Viz *) * nv);
  assert(g->viz);
  for (i = 0; i < nv; i++)
    g->viz[i] = NULL;
  return g;
}


Grafo* grafoLe (const char* filename) {
/* cria grafo nao orientado - supoe que arquivo esta correto! */

  FILE *arq = fopen(filename,"rt");
  int nv, na, no1, no2 = 0;
  int peso;
  Grafo* novo;
	
  fscanf(arq, "%d %d", &nv, &na);
  novo = grafoCria(nv);
  assert(novo);
  while (fscanf(arq, "%d %d %d", &no1, &no2, &peso) == 3) {
    novo->viz[no1] = criaViz(novo->viz[no1], no2, peso);
    novo->viz[no2] = criaViz(novo->viz[no2], no1, peso);
    novo->na++;
  }
  return novo;
}

Grafo* grafoLibera (Grafo* grafo) {
  if (grafo) {
    int i = 0;
    Viz* no,*aux;
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

void grafoMostra (Grafo* grafo) {
  int i;
  if (grafo) {
    printf("NV: %d, NA: %d\n", grafo->nv, grafo->na);
    for (i = 0; i < grafo->nv; i++){
      Viz* viz = grafo->viz[i];
      printf("[%d]->", i);
      while (viz) {
        printf(" {%d, %d}", viz->noj, viz->peso);
        viz = viz->prox;
      }
      printf("\n");
    }
  }
}

Grafo* primArvoreCustoMinimo(Grafo* g, int inicial) {
    // Cria array auxiliar com nós já inseridos no heap, valor passa a ser 1 no momento em que for adicionado no heap.
    int* inserido = (int*)malloc(g->nv * sizeof(int));
    for (int i = 0; i < g->nv; i++)
        inserido[i] = 0;

    // Cria o heap com os vértices a partir do vértice inicial.
    Heap* heap = heap_cria(g->nv, g->nv);

    // Insere o vértice inicial no heap e define seu custo como 0
    heap_insere(heap, 0, inicial, inicial);

    // Cria a árvore de custo mínimo
    Grafo* acm = grafoCria(g->nv);

    while (!heap_vazio(heap)) {
        int u, v;
        int peso;

        // Busca próximo vértice (ainda não adicionado na ACM) com aresta de menor peso no heap.
        peso = heap_remove(heap, &u, &v);

        // Verifica se o vértice já foi inserido na árvore de custo mínimo
        if (inserido[u])
            continue;

        // Adiciona aresta na vizinhança do grafo ACM (adicionando o novo vértice).
        if (u != v) { // Ignora a primeira iteração quando u == v
            acm->viz[u] = criaViz(acm->viz[u], v, peso);
            acm->viz[v] = criaViz(acm->viz[v], u, peso);
            acm->na++;
        }

        // Marca o vértice como inserido
        inserido[u] = 1;

        // Verifica vizinhos do vértice adicionado e atualiza o heap.
        Viz* adj = g->viz[u];
        while (adj != NULL) {
            if (!inserido[adj->noj]) {
                heap_insere(heap, adj->peso, adj->noj, u);
            }
            adj = adj->prox;
        }
    }

    // Libera a memória alocada
    free(inserido);
    heap_libera(heap);

    return acm;
}


Grafo* kruskalArvoreCustoMinimo(Grafo* g) {
    /* Cria a estrutura de uniao e busca com a particao. */
    UniaoBusca* ub = ub_cria(g->nv);

    /* Cria o heap com as arestas. */
    Heap* heap = heap_cria(g->na, 0);

    // Adiciona todas as arestas do grafo ao heap
    for (int i = 0; i < g->nv; i++) {
        Viz* adj = g->viz[i];
        while (adj != NULL) {
            if (i < adj->noj) { // Adicionar a aresta apenas uma vez
                heap_insere(heap, adj->peso, i, adj->noj);
            }
            adj = adj->prox;
        }
    }

    /* Cria a arvore de custo minimo */
    Grafo* acm = grafoCria(g->nv);

    // Loop até que o heap esteja vazio ou que tenhamos n-1 arestas na árvore
    while (!heap_vazio(heap) && acm->na < (g->nv - 1)) {
        int peso, u, v;
        /* Retira proxima aresta. */
        int prio = heap_remove(heap, &u, &v);

        /* Verifica se aresta deve ser adicionada no grafo acm. Se for,
           realiza a insercao, utilizando a estrutura de Uniao e Busca. */
        if (ub_busca(ub, u) != ub_busca(ub, v)) {
            acm->viz[u] = criaViz(acm->viz[u], v, prio);
            acm->viz[v] = criaViz(acm->viz[v], u, prio);
            acm->na++;
            ub_uniao(ub, u, v); // Une os conjuntos
        }
    }

    // Libera a memória alocada para o heap e a estrutura de união e busca
    heap_libera(heap);
    ub_libera(ub);

    return acm;
}
