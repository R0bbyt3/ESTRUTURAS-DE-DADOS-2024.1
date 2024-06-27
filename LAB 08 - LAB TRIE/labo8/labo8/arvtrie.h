#include <stdbool.h>

#define M 26
#define KMAX 256
#define FIMDECHAVE '\0'

typedef struct arvtrie ArvTrie;

ArvTrie* cria (void);
void destroi (ArvTrie* t);

bool insere (ArvTrie* t, const char* chave);
bool retira (ArvTrie* t, const char* chave);

void imprime (ArvTrie* t);

void sugerir (ArvTrie* t, const char* prefixo);