typedef struct smapa Mapa;

Mapa* cria (void);
Mapa* insere (Mapa* m, int chave, int novodado);
int busca (Mapa *m, int chave, int* posencontrada);
Mapa* retira (Mapa *m, int chave, int* removeu);
void destroi (Mapa *m);

int iguais (Mapa* m1, Mapa* m2);
void mostra (Mapa *m);


