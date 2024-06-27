#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "heaparvmin.h"

struct heaparvmin {
  int max; /* tamanho maximo do heap */
  int pos; /* proxima posicao disponivel no vetor */ 
  ArvNo** prioridade; /* nos das prioridades */
}; 

static void troca (int a, int b, ArvNo** prioridade) {
  ArvNo* aux_no = prioridade[a];
  prioridade[a] = prioridade[b];
  prioridade[b] = aux_no;
}

static void corrige_abaixo (ArvNo** prioridade, int item_pos, int tam_heap) {
  int pai = item_pos;
  int filho_esq, filho_dir, filho;
  // Enquanto nao for um no folha (a partir do calculo do filho esquerdo)
  while (2*pai + 1 < tam_heap) {
    filho_esq = 2*pai + 1;
    filho_dir = 2*pai + 2;

    // se a posição do filho direito passar o tamanho atual do heap (numero de nos), faz com que seja igual ao filho esquerdo
    if (filho_dir >= tam_heap) filho_dir = filho_esq;
    
	  // decide qual filho ira ser escolhido, pegando o que tem a menor prioridade (a.k.a., frequencia)
    if (arvno_frequencia(prioridade[filho_esq]) < arvno_frequencia(prioridade[filho_dir]))
      filho = filho_esq;
    else
      filho = filho_dir;

    // se a frequencia do item corrente é maior que o filho escolhido, precisamos realizar a troca
    if (arvno_frequencia(prioridade[pai]) > arvno_frequencia(prioridade[filho]))
      troca(pai, filho, prioridade);
    else // caso contrario, termina o processo de correção
      break;

    // o item sendo corrigido agora tem o índice do filho (após ser feita a troca)
    pai = filho;
  }
}

static void heap_monta(HeapArvMin* heap, int tamanho_iniciais, char* caracteres_iniciais, int* frequencia_iniciais) {
    int i;
    if (tamanho_iniciais > heap->max) {
        printf("Valores demais!\n");
        exit(1);
    }

    for (i = 0; i < tamanho_iniciais; i++) {
        ArvNo* novo_no = arv_criano(caracteres_iniciais[i], frequencia_iniciais[i], NULL, NULL);
        heap->prioridade[i] = novo_no;
        heap->pos++;
    }

    // Ajusta o heap de baixo para cima
    for (i = (heap->pos - 1) / 2; i >= 0; i--) {
        corrige_abaixo(heap->prioridade, i, heap->pos);
    }
}


HeapArvMin* heaparvmin_cria (int tamanho_max, int tamanho_iniciais, char* caracteres_iniciais, int* frequencia_iniciais) {
  // cria heap para codificação de huffman
  HeapArvMin* heap = (HeapArvMin*)malloc(sizeof(HeapArvMin)); 
  heap->max = tamanho_max;
  heap->pos = 0;

  // cria vetor com os nos da arvore que sera criada
  heap->prioridade = (ArvNo**)malloc(tamanho_max * sizeof(ArvNo*)); 
  for (int i = 0; i < tamanho_max; i++) {
    heap->prioridade[i] = NULL;
  }
  
  // adiciona nos iniciais
  if (tamanho_iniciais > 0) {
    heap_monta(heap, tamanho_iniciais, caracteres_iniciais, frequencia_iniciais);
  }
  return heap;
}

static void corrige_acima(HeapArvMin* h, int item_pos) {
    int pos = item_pos;
    while (pos > 0) {
        int pai = (pos - 1) / 2;
        if (arvno_frequencia(h->prioridade[pos]) < arvno_frequencia(h->prioridade[pai])) {
            troca(pos, pai, h->prioridade);
            pos = pai;
        }
        else {
            break;
        }
    }
}


void heaparvmin_insere (HeapArvMin* h, ArvNo* r) {
  if (h->pos < h->max) {
    h->prioridade[h->pos] = r; 
    corrige_acima(h, h->pos); 
    h->pos++;
  } 
  else {
    printf("Heap CHEIO!\n"); 
  }
}

ArvNo* heaparvmin_remove (HeapArvMin* h) {
  if (h->pos > 0) {
    ArvNo* topo = h->prioridade[0];
    h->prioridade[0] = h->prioridade[h->pos - 1];
    h->pos--;
    corrige_abaixo(h->prioridade, 0, h->pos);
    return topo;
  }
  else {
    printf("Heap VAZIO!\n");
    return NULL;
  }
}

void heaparvmin_libera (HeapArvMin * h) {
  for (int i = 0; i < h->pos; i++) {
    free(h->prioridade[i]);
  }
  free(h->prioridade);
  free(h);
}

void heaparvmin_debug_show (HeapArvMin *h, char* title) {
	int i;
	printf("%s\n{", title);
	for (i = 0; i < h->pos; i++) {
		printf("[%c,%d],", arvno_caractere(h->prioridade[i]), arvno_frequencia(h->prioridade[i]));
  }
	printf("}\n");
}

ArvNo* heaparvmin_criaarvorehuffman(HeapArvMin* heap) {
    while (heap->pos > 1) {
        ArvNo* a = heaparvmin_remove(heap);
        ArvNo* b = heaparvmin_remove(heap);

        int nova_freq = arvno_frequencia(a) + arvno_frequencia(b);
        ArvNo* novo_no = arv_criano('\0', nova_freq, a, b);

        heaparvmin_insere(heap, novo_no);
    }

    return heaparvmin_remove(heap);
}
