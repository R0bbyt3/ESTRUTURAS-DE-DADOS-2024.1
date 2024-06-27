#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include "heap.h"

struct item {
    int prioridade;
    int n1, n2;
};

struct _heap {
    int max;            /* tamanho maximo do heap */
    int pos;            /* proxima posicao disponivel no vetor */
    struct item* itens; /* array com os itens adicionados no heap */
    int* mapn1topos;    /* realiza o mapeamento de n1 para uma posicao no heap */
};

static void troca(int a, int b, struct item* v, int* mapn1topos) {
    if (mapn1topos != NULL) {
        mapn1topos[v[a].n1] = b;
        mapn1topos[v[b].n1] = a;
    }
    struct item f = v[a];
    v[a] = v[b];
    v[b] = f;
}

static void corrige_acima(Heap* heap, int pos) {
    int pai;
    while (pos > 0) {
        pai = (pos - 1) / 2;

        if (heap->itens[pai].prioridade > heap->itens[pos].prioridade)
            troca(pos, pai, heap->itens, heap->mapn1topos);
        else
            break;

        pos = pai;
    }
}

static void corrige_abaixo(Heap* heap, int atual) {
    int pai = atual;
    int filho_esq, filho_dir, filho;
    while (2 * pai + 1 < heap->pos) {
        filho_esq = 2 * pai + 1;
        filho_dir = 2 * pai + 2;

        if (filho_dir >= heap->pos)
            filho_dir = filho_esq;

        if (heap->itens[filho_esq].prioridade < heap->itens[filho_dir].prioridade)
            filho = filho_esq;
        else
            filho = filho_dir;

        if (heap->itens[pai].prioridade > heap->itens[filho].prioridade)
            troca(pai, filho, heap->itens, heap->mapn1topos);
        else
            break;

        pai = filho;
    }
}

Heap* heap_cria(int heap_max, int n1map_max) {
    Heap* h = (Heap*)malloc(sizeof(Heap));
    h->max = heap_max;
    h->pos = 0;
    h->itens = (struct item*)malloc(heap_max * sizeof(struct item));
    h->mapn1topos = NULL;
    if (n1map_max > 0) {
        h->mapn1topos = (int*)malloc(n1map_max * sizeof(int));
        for (int i = 0; i < n1map_max; i++) {
            h->mapn1topos[i] = -1;
        }
    }
    return h;
}

void heap_insere(Heap* h, int prioridade, int n1, int n2) {
    if (h->pos < h->max) {
        h->itens[h->pos].prioridade = prioridade;
        h->itens[h->pos].n1 = n1;
        h->itens[h->pos].n2 = n2;
        if (h->mapn1topos) {
            h->mapn1topos[n1] = h->pos;
        }
        corrige_acima(h, h->pos);
        h->pos++;
    }
    else {
        printf("PrimHeap CHEIO!\n");
        exit(1);
    }
}

int heap_existe(Heap* h, int n1) {
    if (h->mapn1topos)
        return h->mapn1topos[n1] != -1;
    return 0;
}

void heap_dimprioridade(Heap* h, int prioridade, int n1, int n2) {
    if (h->mapn1topos == NULL) {
        printf("Heap: Mapeamento nao habilitado!\n");
        exit(1);
    }
    if (h->mapn1topos[n1] == -1) {
        printf("Heap: Elemento %d nao encontrado no heap!\n", n1);
        return;
    }
    assert(h->itens[h->mapn1topos[n1]].n1 == n1);
    if (prioridade < h->itens[h->mapn1topos[n1]].prioridade) {
        h->itens[h->mapn1topos[n1]].prioridade = prioridade;
        h->itens[h->mapn1topos[n1]].n2 = n2;
        corrige_acima(h, h->mapn1topos[n1]);
        corrige_abaixo(h, h->mapn1topos[n1]);
    }
}

int heap_remove(Heap* h, int* n1, int* n2) {
    int prio;
    if (h->pos > 0) {
        *n1 = h->itens[0].n1;
        *n2 = h->itens[0].n2;
        prio = h->itens[0].prioridade;
        h->itens[0] = h->itens[h->pos - 1];
        if (h->mapn1topos) {
            h->mapn1topos[*n1] = -1;
            if (h->pos > 0) {
                h->mapn1topos[h->itens[0].n1] = 0;
            }
        }
        h->pos--;
        corrige_abaixo(h, 0);
        return prio;
    }
    else {
        return -1;
    }
}

int heap_vazio(Heap* h) {
    return h->pos == 0;
}

void heap_libera(Heap* h) {
    if (h->mapn1topos) {
        free(h->mapn1topos);
    }
    free(h->itens);
    free(h);
}

void heap_debug_show(Heap* h, char* title) {
    int i;
    printf("%s = {", title);
    if (h->mapn1topos) {
        for (i = 0; i < (h->pos); i++)
            printf(" %d:%d-%d (%d),", h->itens[i].prioridade,
                h->itens[i].n1, h->itens[i].n2,
                h->mapn1topos[h->itens[i].n1]);
    }
    else {
        for (i = 0; i < (h->pos); i++)
            printf(" %d:%d-%d,", h->itens[i].prioridade,
                h->itens[i].n1, h->itens[i].n2);
    }
    printf("}\n");
}
