#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "arvtrie.h"

struct arvtrie {
  int n;           // informa a quantidade de ponteiros != NULL em 'nos'
  ArvTrie* nos[M]; // vetor contendo os ponteiros correspondentes a cada digito
  bool palavra;    // informa se o no corresponde ao final de uma palavra
};

static int transformaparaindice (char c) {
  if (c < 'a' || c > 'z') {
    printf(">>> digito desconhecido\n");
    exit(1);
  }
  int d = c - 'a';
  return d;
}

static char transformaparadigito (int d) {
  char c = d + 'a';
  if (c < 'a' || c > 'z') {
    printf(">>> digito desconhecido\n");
    exit(1);
  }
  return c;
}

static ArvTrie* criano (void) {
  ArvTrie* t = (ArvTrie*)malloc(sizeof(ArvTrie));
  t->n = 1;
  t->palavra = false;
  for (int i = 0; i < M; i++)
    t->nos[i] = NULL;
  return t;  
}

ArvTrie* cria (void) {
  return criano();
}

void destroi (ArvTrie* t) {
  for (int i = 0; i < M; i++) {
    if (t->nos[i]) {
      destroi(t->nos[i]);
    }
  }
  free(t);
}

bool insere(ArvTrie* t, const char* chave) {
    if (t == NULL) return false;

    int len = strlen(chave);
    ArvTrie* atual = t;

    for (int i = 0; i < len; i++) {
        int indice = transformaparaindice(chave[i]);
        if (atual->nos[indice] == NULL) {
            atual->nos[indice] = criano();
            atual->n++;
        }
        atual = atual->nos[indice];
    }

    if (atual->palavra) {
        printf("I: Chave \"%s\" nao inserida, pois ja existe\n", chave);
        return false;
    }

    atual->palavra = true;
    printf("I: Chave \"%s\" inserida\n", chave);
    return true;
}


bool retira(ArvTrie* t, const char* chave) {
    if (t == NULL) return false;

    int len = strlen(chave);
    ArvTrie* atual = t;
    ArvTrie* ult_valido = NULL;
    int ult_valido_indice = -1;

    // Percorre a árvore para encontrar o nó correspondente ao último caractere da chave
    for (int i = 0; i < len; i++) {
        int indice = transformaparaindice(chave[i]);
        if (atual->nos[indice] == NULL) {
            printf("R[]: Chave \"%s\" nao encontrada\n", chave);
            return false;
        }
        if (atual->n > 1 || atual->palavra) {
            ult_valido = atual;
            ult_valido_indice = indice;
        }
        atual = atual->nos[indice];
    }

    // Verifica se o nó final é realmente o fim de uma palavra
    if (!atual->palavra) {
        printf("R[]: Chave \"%s\" nao removida, pois nao e' uma palavra\n", chave);
        return false;
    }

    // Define que o nó final não é mais o fim de uma palavra
    atual->palavra = false;

    // Se o nó ainda tem filhos, simplesmente marca o fim da palavra como falso
    if (atual->n > 1) {
        printf("R[]: Chave \"%s\" removida (nó tem filhos)\n", chave);
        return true;
    }

    printf("R[");

    // Remoção de nós intermediários
    for (int i = len - 1; i >= 0; i--) {
        int indice = transformaparaindice(chave[i]);

        // Verifica se o nó atual é o final de outra palavra
        if (atual->palavra) {
            break;
        }
        
        // Verifica se o nó atual é tem mais de uma coisa inserida
        if (atual->n > 1) {
            printf("%c", chave[i]);

            atual->nos[indice] = NULL;
            atual->n--;

            break;
        }

        // Se não tem filhos e não é o final de outra palavra, remove o nó
        free(atual);

        if (i > 0) {
            // Atualiza o ponteiro do pai para NULL e decrementa o contador de filhos
            printf("%c", chave[i]);
            int pai_indice = transformaparaindice(chave[i - 1]);
            ArvTrie* pai = t;
            for (int j = 0; j < i - 1; j++) {
                pai = pai->nos[transformaparaindice(chave[j])];
            }
            pai->nos[indice] = NULL;
            pai->n--;
            atual = pai;
        }

    }
    
    printf("]: Chave \"%s\" removida (Com remoção de intermediários)\n", chave);
    return true;
}



static void imprimechaves (ArvTrie* t, char* chave) {
  if (t == NULL) return;

  // se for uma palavra, imprime o que foi acumulado
  if (t->palavra)
    printf("%s\n", chave);
  
  // se nao tiver nenhum proximo no, deve ser uma palavra, ou temos um erro 
  if (t->n == 0) {
    if (!t->palavra) {
      printf(">>> No folha e nao e' palavra, arvore contem algum erro\n");
      exit(1);
    }
  }
  else {
    // adiciona novo \0, em s+1, deixando a posicao s livre para o novo digito
    int s = strlen(chave);
    chave[s+1] = FIMDECHAVE;
    for (int d = 0; d < M; d++) {
      if (t->nos[d]) {
        // define digito na posicao s
        chave[s] = transformaparadigito(d);
        imprimechaves(t->nos[d], chave);
      }
    }
    // "reseta" o final da palavra
    chave[s] = FIMDECHAVE;
  }
}

void imprime (ArvTrie* t) {
  printf("Imprime chaves da arvore:\n");
  char chave[KMAX];
  chave[1] = FIMDECHAVE; 
  for (int d = 0; d < M; d++) {
    if (t->nos[d]) {
      chave[0] = transformaparadigito(d);
      imprimechaves(t->nos[d], chave);
    }
  }
}

static void sugerirchaves(ArvTrie* t, const char* prefixo) {
    if (t == NULL) return;

    int len = strlen(prefixo);
    ArvTrie* atual = t;

    for (int i = 0; i < len; i++) {
        int indice = transformaparaindice(prefixo[i]);
        if (atual->nos[indice] == NULL) {
            printf("prefixo nao encontrado");
            return;
        }
        atual = atual->nos[indice];
    }

    char pchave[KMAX];
    strcpy(pchave, prefixo);
    imprimechaves(atual, pchave);
}

void sugerir(ArvTrie* t, const char* prefixo) {
    printf("Sugerir completacoes para \"%s\": ", prefixo);
    sugerirchaves(t, prefixo);
    printf("\n");
}
