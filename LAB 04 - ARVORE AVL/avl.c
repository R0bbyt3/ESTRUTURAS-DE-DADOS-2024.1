#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#include "avl.h"

struct avlno {
    int chave;
    int fb;
    AvlNo* esq;
    AvlNo* dir;
};

int info(AvlNo* p)
{
    if (p == NULL) return -1;
    return p->chave;
}

AvlNo* criano(int chave, AvlNo* esq, AvlNo* dir)
{
    AvlNo* p = (AvlNo*)malloc(sizeof(AvlNo));
    if (p != NULL) {
        p->chave = chave;
        p->fb = 0;
        p->esq = esq;
        p->dir = dir;
    }
    return p;
}

void libera(AvlNo* r)
{
    if (r != NULL) {
        libera(r->esq);
        libera(r->dir);
        free(r);
    }
}

AvlNo* retira(AvlNo* r, int chave)
{
    if (r == NULL) return NULL;
    if (chave < r->chave) r->esq = retira(r->esq, chave);
    else if (chave > r->chave) r->dir = retira(r->dir, chave);
    else { /* achou o nó a remover */
      /* nó sem filhos */
        if ((r->esq == NULL) && (r->dir == NULL)) {
            free(r);
            r = NULL;
        }
        /* nó com filho à direita */
        else if (r->esq == NULL) {
            AvlNo* t = r;
            r = r->dir;
            free(t);
        }
        /* nó com filho à esquerda */
        else if (r->dir == NULL) {
            AvlNo* t = r;
            r = r->esq;
            free(t);
        }
        /* nó tem dois filhos */
        else {
            AvlNo* s = sucessor(r);
            r->chave = s->chave;
            s->chave = chave;
            r->dir = retira(r->dir, chave);
        }
    }
    return r;
}

AvlNo* busca(AvlNo* r, int chave)
{
    if (r == NULL) return NULL;
    else if (chave < r->chave) return busca(r->esq, chave);
    else if (chave > r->chave) return busca(r->dir, chave);
    else return r;
}

AvlNo* menor_no(AvlNo* r)
{
    if (r == NULL) return NULL;
    while (r->esq) r = r->esq;
    return r;
}

AvlNo* sucessor(AvlNo* r)
{
    return menor_no(r->dir);
}

//    r         e
//  e   _ ->  a   r  
// a b           b
AvlNo* rotaciona_dir(AvlNo* r) {
    AvlNo* e = r->esq;
    r->esq = e->dir;
    e->dir = r;
    return e;
}


//   r           d
// _   d   ->  r   b  
//    a b       a  
AvlNo* rotaciona_esq(AvlNo* r) {
    AvlNo* d = r->dir;
    r->dir = d->esq;
    d->esq = r;
    return d;
}


void imprime_avl(AvlNo* r)
{
    printf("(");
    if (r != NULL) {
        printf("[%d,%d] ", r->chave, r->fb);
        imprime_avl(r->esq);
        printf(", ");
        imprime_avl(r->dir);
    }
    printf(")");
}

static AvlNo* corrige_esq(AvlNo* r) {
    /* se esq tem fb -1 rotaciono para a direita */
    if (r->esq->fb == -1) {
        /* altura da sad da raiz é h, e de sua sae ficou h+2 */
        /* movendo a raiz para a direita, suas duas sub-arvores ficam com altura h */
        /* movendo esq para posição de raiz, suas duas sub-arvores ficam com altura h+1 */
        r->fb = r->esq->fb = 0;
        return rotaciona_dir(r);
    }
    else/* if (r->esq->fb == 1) */ {
        /* será uma rotação dupla esq-dir */
        /* serão modificados os fb de r, de r->esq e de r->esq->dir */
        /* isso vai depender do fb de r->esq->dir */
        AvlNo* s = r->esq->dir;

        switch (s->fb) {
        case -1:
            r->fb = 1;
            r->esq->fb = s->fb = 0;
            break;
        case 0:
            r->fb = r->esq->fb = s->fb = 0;
            break;
        case 1:
            r->fb = s->fb = 0;
            r->esq->fb = -1;
            break;
        }

        // COMPLETAR com as rotações necessárias
        return NULL; /* só está aqui para compilar direito */
    }
}

static AvlNo* corrige_dir(AvlNo* r) {
    if (r->dir->fb == 1) {
        r->fb = r->dir->fb = 0;
        return rotaciona_esq(r);
    }
    else { // caso de rotação dupla direita-esquerda
        AvlNo* s = r->dir->esq;
        switch (s->fb) {
        case 1:
            r->fb = -1;
            r->dir->fb = s->fb = 0;
            break;
        case 0:
            r->fb = r->dir->fb = s->fb = 0;
            break;
        case -1:
            r->fb = s->fb = 0;
            r->dir->fb = 1;
            break;
        }
        r->dir = rotaciona_dir(r->dir);
        return rotaciona_esq(r);
    }
}


static AvlNo* insere2(AvlNo* r, int chave, int* cresceu) {
    if (r == NULL) {
        r = criano(chave, NULL, NULL);
        *cresceu = 1;
    }
    else if (chave < r->chave) {
        r->esq = insere2(r->esq, chave, cresceu);
        if (*cresceu) {
            switch (r->fb) {
            case 1: /* antes hd > he, depois hd = he pois he aumentou */
                r->fb = 0;
                *cresceu = 0;
                break;
            case 0: /* antes hd = he, agora he > hd, avisa para cima que cresceu */
                r->fb = -1;
                break;
            case -1: /* antes hd < he, depois hd-he = -2 pois he aumentou! */
                r = corrige_esq(r);
                *cresceu = 0;
                break;
            }
        }
    }
    else if (chave > r->chave) {
        r->dir = insere2(r->dir, chave, cresceu);
        if (*cresceu) {
            switch (r->fb) {
            case -1:
                r->fb = 0;
                *cresceu = 0;
                break;
            case 0:
                r->fb = 1;
                break;
            case 1:
                r = corrige_dir(r);
                *cresceu = 0;
                break;
            }
        }
    }

    return r;
}

AvlNo* insere_avl(AvlNo* r, int chave) {
    int cresceu = 0;
    return insere2(r, chave, &cresceu);
}