typedef struct arvnorb ArvNoRb;

ArvNoRb* busca(ArvNoRb* r, int chave);
void libera(ArvNoRb* r);

ArvNoRb* insere(ArvNoRb* r, int chave);
void imprime(ArvNoRb* r);

int num_nos_pretos(ArvNoRb* r);
int num_nos_vermelhos(ArvNoRb* r);