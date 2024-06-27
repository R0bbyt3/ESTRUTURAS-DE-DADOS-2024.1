
typedef struct avlno AvlNo;

int info(AvlNo* p);

AvlNo* criano(int chave, AvlNo* esq, AvlNo* dir);
void libera(AvlNo* r);

AvlNo* retira(AvlNo* r, int chave);
AvlNo* busca(AvlNo* r, int chave);
AvlNo* menor_no(AvlNo* r);
AvlNo* sucessor(AvlNo* r);

AvlNo* rotaciona_dir(AvlNo* r);
AvlNo* rotaciona_esq(AvlNo* r);

void imprime_avl(AvlNo* r);
AvlNo* insere_avl(AvlNo* r, int chave);

