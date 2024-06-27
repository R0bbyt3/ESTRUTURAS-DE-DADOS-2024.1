typedef struct heap Heap;

/* cria nova lista de prioridades, opcionalmente passando uma lista inicial de prios */
Heap* heap_cria(int max, int qtos, int* iniciais);

/* insere uma nova prioridade na lista */
void heap_insere(Heap* heap, int prioridade);

/* remove e retorna a maior prioridade */
int heap_remove(Heap* heap);

/* libera a lista de prioridades */
void heap_libera(Heap* heap);

/* enxerga representação interna */
void heap_debug_show(Heap* hp, char* title);

/* reordena valores utilizando heap */
int* heap_sort(int nums[], int tam);
