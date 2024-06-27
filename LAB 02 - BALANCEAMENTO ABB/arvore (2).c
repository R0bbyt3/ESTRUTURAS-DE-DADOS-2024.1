#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#include "arvore.h"

struct arvno {
  int info;
  ArvNo* esq;
  ArvNo* dir;
};

int info (ArvNo* p)
{
  if (p == NULL) return -1;
  return p->info;
}

ArvNo* criano (int v, ArvNo* esq, ArvNo* dir)
{
  ArvNo* p = (ArvNo*)malloc(sizeof(ArvNo));
  if (p != NULL) {
    p->info = v;
    p->esq = esq;
    p->dir = dir;
  }
  return p;
}

void imprime (ArvNo* r)
{
  printf("(");
  if (r != NULL) {
    printf("%d ", r->info);
    imprime(r->esq);
    printf(", ");
    imprime(r->dir);
  }
  printf(")");
}

void libera (ArvNo* r)
{
  if (r != NULL) {
    libera(r->esq);
    libera(r->dir);
    free(r);
  }
}

int num_nos (ArvNo* r)
{
  if (r == NULL) return 0;
  return num_nos(r->esq) + num_nos(r->dir) + 1;
}

ArvNo* busca (ArvNo* r, int v)
{
#if 1 // implementacao recursiva
  if (r == NULL) return NULL;
  else if (v < r->info) return busca(r->esq, v); 
  else if (v > r->info) return busca(r->dir, v); 
  else return r;
#else // implementacao iterativa  
  while (r != NULL) {
    if (v < r->info)
      r = r->esq;
    else if (v > r->info)
      r = r->dir;
    else
      return r;
  }
  return NULL;
#endif
}

ArvNo* insere (ArvNo* r, int v)
{
  if (r == NULL)
    return criano(v, NULL, NULL);
  else if (v < r->info)
    r->esq = insere(r->esq, v);
  else if (v > r->info)
    r->dir = insere(r->dir, v);
  // se for igual, nao sera adicionado
  return r;  
}

ArvNo* retira (ArvNo* r, int v)
{
  // COMPLETAR: codigo da aula passada 
  return r;
}

ArvNo* menor_no (ArvNo* r)
{
  // COMPLETAR caso opte por utilizar essa funcao auxiliar
}

ArvNo* maior_no (ArvNo* r)
{
  // COMPLETAR caso opte por utilizar essa funcao auxiliar
}

ArvNo* predecessor (ArvNo* r)
{
  // COMPLETAR caso opte por utilizar essa funcao auxiliar
}

ArvNo* sucessor (ArvNo* r)
{
  // COMPLETAR: codigo da aula passada (necessario para a funcao 'retira') 
  return r;
}

int altura (ArvNo* r)
{
  // COMPLETAR
  return -1;
}

int e_balanceada (ArvNo* r)
{
  // COMPLETAR
  return 0;
}

ArvNo* balancear (ArvNo* r)
{
  // COMPLETAR
  return r;
}