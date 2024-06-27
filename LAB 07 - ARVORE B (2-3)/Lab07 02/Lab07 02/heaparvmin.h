#include "huffman.h"

typedef struct heaparvmin HeapArvMin;

/* cria nova lista de prioridades, opcionalmente passando uma lista inicial de prios */
HeapArvMin* heaparvmin_cria(int tamanho_max, int tamanho_inciais, char* caracteres_iniciais, int* frequencia_iniciais);

/* insere uma nova prioridade na lista */
void heaparvmin_insere(HeapArvMin* heap, ArvNo* r);

/* remove e retorna a maior prioridade */
ArvNo* heaparvmin_remove(HeapArvMin* h);

/* libera a lista de prioridades */
void heaparvmin_libera(HeapArvMin* heap);

/* enxerga representação interna */
void heaparvmin_debug_show(HeapArvMin* heap, char* title);

/* cria árvore de huffman a partir do heap min */
ArvNo* heaparvmin_criaarvorehuffman(HeapArvMin* heap);