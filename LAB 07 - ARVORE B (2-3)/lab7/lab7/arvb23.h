typedef struct arvb23 ArvB23;

ArvB23* cria (void);
ArvB23* insere (ArvB23* b, int chave);
int existe (ArvB23* b, int chave);
void destroi (ArvB23* b);

void mostra (ArvB23* b);

int iguais (ArvB23* b1, ArvB23* b2);