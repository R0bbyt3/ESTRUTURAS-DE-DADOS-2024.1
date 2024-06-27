#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "arvrb.h"

#define RED_NODE 1
#define BLACK_NODE 0

struct arvnorb {
  int chave;
  char vermelho;
  struct arvnorb* esq;
  struct arvnorb* dir;
};

typedef enum result {OK, RED, LEFTRED, RIGHTRED} Result;
static char *strstatus[] = {"ok", "red", "leftred", "rightred"};

ArvNoRb* busca (ArvNoRb* r, int chave) {
  if (r == NULL) {
    return NULL;
  }
  else if (r->chave == chave) {
    return r;
  }
  else if (chave < r->chave) {
  return busca(r->esq, chave);
  }
  else if (chave > r->chave) {
    return busca(r->dir, chave);
  }
  else {
    return NULL;
  }
}

void libera (ArvNoRb* r) {
  if (r != NULL) {
    libera(r->esq);
    libera(r->dir);
    free(r);
  }
}

static ArvNoRb* rotaciona_dir (ArvNoRb* r) {
  printf("\nRot_Dir, %d\n", r->chave);
  ArvNoRb* esq = r->esq;
  r->esq = esq->dir;
  esq->dir = r;
  return esq;
}

static ArvNoRb* rotaciona_esq (ArvNoRb* r) {
    printf("\nRot_Esq, %d\n", r->chave);
  ArvNoRb* dir = r->dir;
  r->dir = dir->esq;
  dir->esq = r;
  return dir;
}

static void troca_cores (ArvNoRb* r) {
    printf("\nCores, %d\n", r->chave);
  char corpai = r->vermelho; 
  r->vermelho = !corpai;     /* troca a cor do pai */
  r->esq->vermelho = corpai; /* os filhos recebem a cor inversa da do pai */
  r->dir->vermelho = corpai;
}

static ArvNoRb* cria_no (int c) {
  ArvNoRb* r = (ArvNoRb*)malloc(sizeof(ArvNoRb));
  if (r != NULL) {
    r->esq = r->dir = NULL;
    r->chave = c;
    r->vermelho = RED_NODE;
  }
  return r;
}

static ArvNoRb* corrige_esq (ArvNoRb* r, Result* status) {
  switch (*status) {
    case OK:  /* nada a corrigir */
       printf("\nCASE OK - %d\n", r->chave);
      break;
    case RED: /* filho vermelho */
      printf("\nCASE RED - %d\n", r->chave);
      if (r->vermelho) *status = LEFTRED;
      else *status = OK;
      break;
    case LEFTRED: /* LL */
        printf("\n\nCASE LEFTRED - %d\n\n", r->chave);
        if (!r->dir || !r->dir->vermelho) {  // LLb
            printf("\nLLb, %d\n", r->chave);
            r = rotaciona_dir(r);
            troca_cores(r);
            *status = OK;
       }
       else {  // LLr
            printf("\nLLr, %d\n", r->chave);
            troca_cores(r);  
            *status = RED;
       }
      break;
    case RIGHTRED: /* LR */
      printf("\n\nCASE RIGHTRED - %d\n\n", r->chave);
      if (!r->dir || !r->dir->vermelho) {  /* filho direito preto: LRb */
          printf("\nLRb, %d\n", r->chave);
        r->esq = rotaciona_esq(r->esq);
        r = rotaciona_dir(r);
        troca_cores(r);
        *status = OK;
      }
      else { /* filho direito vermelho -> LRr */
          printf("\nLRr, %d\n", r->chave);
          troca_cores(r);  
          *status = RED;
      }
      break;
  }
  return r;
}

static ArvNoRb* corrige_dir (ArvNoRb* r, Result* status) {
  switch (*status) {
    case OK: /* nada a corrigir */
        printf("\nCASE OK - %d\n", r->chave);
      break;
    case RED: /* filho vermelho */
        printf("\nCASE RED - %d\n", r->chave);
      if (r->vermelho) *status = RIGHTRED;
      else *status = OK;
      break;
    case RIGHTRED: /* RR */
      printf("\n\nCASE RIGHTRED - %d\n\n", r->chave);
      if (!r->esq || !r->esq->vermelho) { /* filho esquerdo preto: RRb */
          printf("\nRRb, %d\n", r->chave);
          r = rotaciona_esq(r);
          troca_cores(r);
          *status = OK;
      }
      else { /* filho esquerdo vermelho: RRr */
          printf("\nRRr, %d\n", r->chave);
          troca_cores(r);  
          *status = RED;
      }
      break;
    case LEFTRED: /* RL */
      printf("\n\nCASE LEFTRED - %d\n\n", r->chave);
      if (!r->esq || !r->esq->vermelho) { /* filho esquerdo preto: RLb */
          printf("\n\nRLb, %d\n\n", r->chave);
          r->dir = rotaciona_dir(r->dir);
          r = rotaciona_esq(r); 
          troca_cores(r);
          *status = OK;
      }
      else { /* filho esquerdo vermelho: RLr */
          printf("\n\nRLr, %d\n\n", r->chave);
          troca_cores(r);  
          *status = RED;
      }
      break;
  }
  return r;
}

static ArvNoRb* insere_rec (ArvNoRb* r, int chave, Result* status){
  if (r == NULL) {
    printf("\n\nCriando no vermelho com chave: %d\n\n", chave);
    r = cria_no(chave);
    *status = RED;
  }
  else if (chave < r->chave) {
    printf("\nInserindo %d a esquerda de %d\n", chave, r->chave);
    r->esq = insere_rec(r->esq, chave, status);
    if (*status == RED) printf("\n\nCorrecao a esquerda apos insercao de %d\n\n", chave);
    printf("\nR atual: %d\n", r->chave);
    r = corrige_esq(r, status);
   
  }
  else if (chave > r->chave) {
    printf("\n\nInserindo %d a direita de %d\n\n", chave, r->chave);
    r->dir = insere_rec(r->dir, chave, status);
    if (*status == RED) printf("\n\nCorrecao a direita apos insercao de %d\n\n", chave);
    printf("\nR atual: %d\n", r->chave);
    r = corrige_dir(r, status);
  }
  return r;
}

ArvNoRb* insere (ArvNoRb* r, int chave) {
  Result status;
  r = insere_rec(r, chave, &status);
  if (status == RED) r->vermelho = BLACK_NODE;
  else if (status != OK) {
    printf ("erro ao voltar para a raiz: status invalido %s !\n", strstatus[status]);
    printf("\n"); printf("\n");
    imprime(r);
    printf("\n"); printf("\n");
    exit(1);
  }
  return r;
}

void imprime (ArvNoRb* r) {
  printf("[");
  if (r != NULL) {
    printf("<%d - %c> ", r->chave,(r->vermelho) ?  'r' : 'b');
    imprime(r->esq);
    imprime(r->dir);
  }
  printf("] ");
}

int num_nos_pretos(ArvNoRb* r) {
    if (r == NULL) {
        return 0;
    }
    int count = (r->vermelho == BLACK_NODE) ? 1 : 0;
    return count + num_nos_pretos(r->esq) + num_nos_pretos(r->dir);
}


int num_nos_vermelhos(ArvNoRb* r) {
    if (r == NULL) {
        return 0;
    }
    int count = (r->vermelho == RED_NODE) ? 1 : 0;
    return count + num_nos_vermelhos(r->esq) + num_nos_vermelhos(r->dir);
}
