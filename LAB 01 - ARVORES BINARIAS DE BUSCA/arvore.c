#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#include "arvore.h"

struct arvno {
    int info;
    ArvNo* esq;
    ArvNo* dir;
};

ArvNo* cria_no(int v, ArvNo* esq, ArvNo* dir)
{
    ArvNo* p = (ArvNo*)malloc(sizeof(ArvNo));
    if (p != NULL) {
        p->info = v;
        p->esq = esq;
        p->dir = dir;
    }
    return p;
}

void imprime(ArvNo* r)
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

void libera(ArvNo* r)
{
    if (r != NULL) {
        libera(r->esq);
        libera(r->dir);
        free(r);
    }
}

int num_nos(ArvNo* r)
{
    int nm = 1;

    if (r != NULL)
    {
        nm += num_nos(r->esq);
    
        printf("%d\n", r->info);
  
        nm += num_nos(r->dir);

        return nm;
    }
    else
    {
        return 0;
    }

    
}

static int e_abb_preordem(ArvNo* r, int min, int max)
{
    // COMPLETAR: Escolha entre completar 'e_abb_preordem' OU 'e_abb_simetrica'
    return 0;
}

static int e_abb_simetrica(ArvNo* r, int* corrente)
{
    if (r == NULL)
        return 1; // Uma árvore vazia é uma ABB por definição

    int e = 1, d = 1;

    if (r->esq != NULL)
    {
        if (r->esq->info < r->info)
        {
            e = e_abb_simetrica(r->esq, r->info);
        }
        else
        {
            return 0;
        }
    }


    if (r->dir != NULL)
    {
        if (r->dir->info > r->info)
        {
            d = e_abb_simetrica(r->dir, r->info);

        }
        else
        {
            return 0;
        }
    }

    return e && d;

}

int e_abb(ArvNo* r)
{
# if 1 // Troque para 0 se optar por implementar a função e_abb_preordem
    int corrente = INT_MIN;
    return e_abb_simetrica(r, &corrente);
#else
    return e_abb_preordem(r, INT_MIN, INT_MAX);
#endif
}

int arvores_iguais(ArvNo* r1, ArvNo* r2)
{
    int e = 1, d = 1;

    if (r1 == NULL && r2 == NULL)
        return 1;

    if (r1 == NULL || r2 == NULL)
        return 0;

    if (r1->info == r2->info)
    {
        e = arvores_iguais(r1->esq, r2->esq);
        d = arvores_iguais(r1->dir, r2->dir);
    }
    else
    {
            return 0;
    }
    

    return e && d;
}

int num_maiores_que(ArvNo* r, int v)
{
    if (r == NULL) {
        return 0;
    }
    if (r->info > v) {
        return 1 + num_maiores_que(r->dir, v) + num_maiores_que(r->esq, v);
    }
    else {
        return num_maiores_que(r->dir, v);
    }
}

ArvNo* insere(ArvNo* r, int v)
{
    if (r == NULL)
        return cria_no(v, NULL, NULL);
    else if (v < r->info)
        r->esq = insere(r->esq, v);
    else // v > r->info
        r->dir = insere(r->dir, v);
    return r;
}
