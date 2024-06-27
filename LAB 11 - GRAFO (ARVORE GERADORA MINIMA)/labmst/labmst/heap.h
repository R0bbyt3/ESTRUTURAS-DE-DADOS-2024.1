typedef struct _heap Heap;

/* cria nova lista de prioridades, onde o tamanho maximo e' o numero de vertices do grafo */
/* o segundo parametro consiste em um array que realiza o mapeamento do valor de n1 para a
   sua posicao corrente no heap, utilizado no algoritmo PRIM. */
Heap *heap_cria (int heap_max, int n1map_max);

/* insere um nova aresta na lista, definindo prioridade, no de saida (n1) e no de chegada (n2) */
void heap_insere (Heap* h, int prioridade, int n1, int n2); 

/* verifica se no esta' no heap */
int heap_existe (Heap* h, int n1); 

/* diminui o valor de prioridade de um item com um 'n1' especifico, caso o novo valor de 'prioridade'
   seja menor que o atual. Para que esse metodo ocorra, n1map_max deve ser inicializado com valor > 0
   ao inicializar o heap, para conseguir mapear um n1 na sua respectiva posicao no heap. */
void heap_dimprioridade (Heap* h, int prioridade, int n1, int n2); 

/* remove e retorna a maior prioridade e os dois nos associados a ela */
/* retorna -1 caso a lista esteja vazia */
int heap_remove (Heap* h, int* n1, int* n2);

/* retorna se o heap esta vazio */
int heap_vazio (Heap* h);

/* libera a lista de prioridades */
void heap_libera (Heap* h);

/* so para debug: enxerga representacao interna! */
void heap_debug_show (Heap* h, char* title);



