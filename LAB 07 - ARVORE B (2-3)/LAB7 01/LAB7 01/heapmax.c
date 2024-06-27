#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "heapmax.h"

struct heap {
    int max;         /* tamanho maximo do heap */
    int pos;         /* proxima posicao disponivel no vetor */
    int* prioridade; /* vetor das prioridades */
}; /* ignorando os dados! */

static void troca(int a, int b, int* v) {
    int f = v[a];
    v[a] = v[b];
    v[b] = f;
}

// corrigo o nó abaixo move o nó para maiores níveis
static void corrige_abaixo(int* prios, int atual, int tam) {
    int pai = atual;
    int filho_esq, filho_dir, filho;
    while (2 * pai + 1 < tam) {
        filho_esq = 2 * pai + 1;
        filho_dir = 2 * pai + 2;

        // se a posição do filho direito passar o tamanho atual do heap (numero de nos), faz com que seja igual ao filho esquerdo
        if (filho_dir >= tam)
            filho_dir = filho_esq;

        // decide qual filho ira ser escolhido, pegando o que tem a MAIOR prioridade (pois é um max heap)
        if (prios[filho_esq] > prios[filho_dir])
            filho = filho_esq;
        else
            filho = filho_dir;

        // se a frequencia do item corrente é MENOR que o filho escolhido, precisamos realizar a troca
        if (prios[pai] < prios[filho])
            troca(pai, filho, prios);
        else // caso contrario, termina o processo de correção
            break;

        // o item sendo corrigido agora tem o índice do filho (após ser feita a troca)
        pai = filho;
    }
}

static void heap_monta(Heap* heap, int n, int* prios) {
    int pri, i;
    if (n > heap->max) {
        printf("valores demais! \n");
        exit(1);
    }

    // Copiando os valores iniciais para o vetor do heap
    for (i = 0; i < n; i++) {
        heap->prioridade[i] = prios[i];
    }
    heap->pos = n; // Atualiza a posição para a próxima inserção

    // Inicia a correção do heap do último pai até a raiz
    for (i = (n / 2) - 1; i >= 0; i--) {
        corrige_abaixo(heap->prioridade, i, n);
    }
}


Heap* heap_cria(int max, int qtos, int* iniciais) {
    Heap* heap = (Heap*)malloc(sizeof(struct heap));
    heap->max = max;
    heap->pos = 0;
    heap->prioridade = (int*)malloc(max * sizeof(int));
    if (qtos > 0) {
        heap_monta(heap, qtos, iniciais);
    }
    return heap;
}

static void corrige_acima(Heap* heap, int pos) {
    int pai;
    while (pos > 0) {
        pai = (pos - 1) / 2;

        // se a frequencia do pai for MENOR que a do nó filho, quer dizer que precisamos realizar a troca
        if (heap->prioridade[pai] < heap->prioridade[pos])
            troca(pos, pai, heap->prioridade);
        else // caso contrário, nada mais a ser feito
            break;

        pos = pai;
    }
}

void heap_insere(Heap* heap, int prioridade) {
    if (heap->pos < heap->max) {
        heap->prioridade[heap->pos] = prioridade;
        corrige_acima(heap, heap->pos);
        heap->pos++;
    }
    else {
        printf("Heap CHEIO!\n");
    }
}

int heap_remove(Heap* heap) {
    if (heap->pos > 0) {
        int topo = heap->prioridade[0];
        heap->prioridade[0] = heap->prioridade[heap->pos - 1];
        heap->pos--;
        corrige_abaixo(heap->prioridade, 0, heap->pos);
        return topo;
    }
    else {
        printf("Heap VAZIO!");
        return -1;
    }
}

void heap_libera(Heap* h) {
    free(h->prioridade);
    free(h);
}

void heap_debug_show(Heap* h, char* title) {
    int i;
    printf("%s\n{", title);
    for (i = 0; i < (h->pos); i++)
        printf("%d,", h->prioridade[i]);
    printf("}\n");

}

int* cria_listaordenada(Heap* heap, int tam) {
    int* lista_ordenada = (int*)malloc(tam * sizeof(int));
    if (lista_ordenada == NULL) {
        printf("Falha ao alocar memória para a lista ordenada.\n");
        exit(1);
    }

    for (int i = 0; i < tam; i++) {
        lista_ordenada[i] = heap_remove(heap);  // Remover o maior elemento e adicionar ao vetor
    }

    return lista_ordenada;
}


int* heap_sort(int nums[], int tam) {
    Heap* heap = heap_cria(tam, tam, nums);
    int* novosnums = cria_listaordenada(heap, tam);
    heap_libera(heap);
    return novosnums;
}
