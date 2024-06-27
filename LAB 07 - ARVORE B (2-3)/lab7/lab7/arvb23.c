    #include <stdio.h>
    #include <stdlib.h>

    #include "arvb23.h"

    struct arvb23 {
        int k1, k2;
        ArvB23* pai;
        ArvB23* esq;
        ArvB23* meio;
        ArvB23* dir;
    };

    ArvB23* cria(void) {
        printf("Criando uma nova arvore vazia.\n");
        return NULL;
    }

    static ArvB23* novoNo(int chave) {
        ArvB23* b = (ArvB23*)malloc(sizeof(struct arvb23));
        if (b == NULL) {
            printf("Erro no malloc! Falha ao alocar memoria para novo no.\n");
            exit(1);
        }
        printf("Novo no criado com chave: %d\n", chave);
        b->pai = NULL;
        b->k1 = chave;
        b->k2 = -1;
        b->esq = b->meio = b->dir = NULL;
        return b;
    }

    static ArvB23* overflowQuebra(ArvB23* b, int* valorainserir, ArvB23* novofilho) {
        ArvB23* novo;

        novo = (ArvB23*)malloc(sizeof(struct arvb23));
        if (novo == NULL) {
            printf("erro em malloc! \n");
            exit(1);
        }

        if (*valorainserir < b->k1) {
            novo->esq = novofilho;
            if (novo->esq) {
                novo->esq->pai = novo;
            }
            novo->k1 = *valorainserir;
            novo->meio = b->esq;
            if (novo->meio) {
                novo->meio->pai = novo;
            }
            novo->k2 = -1;
            novo->dir = NULL;
            *valorainserir = b->k1;
            b->esq = b->meio;
            b->k1 = b->k2;
        }
        else if (*valorainserir < b->k2) {
            // O novo nó recebe o filho do meio e a nova chave promovida
            novo->esq = b->meio;
            novo->meio = novofilho;
            if (novo->esq) {
                novo->esq->pai = novo;
            }
            if (novo->meio) {
                novo->meio->pai = novo;
            }
            novo->k1 = *valorainserir;
            novo->k2 = -1;
            novo->dir = NULL;

            *valorainserir = b->k2;
        }
        // Caso a nova chave seja maior que todas as chaves do nó
        else {
            // O novo nó recebe o filho da direita e a segunda chave do nó original
            novo->esq = b->dir;
            novo->meio = novofilho;
            if (novo->esq) {
                novo->esq->pai = novo;
            }
            if (novo->meio) {
                novo->meio->pai = novo;
            }
            novo->k1 = b->k2;
            novo->k2 = -1;
            novo->dir = NULL;

            // A nova chave se torna o valor a ser inserido
            *valorainserir = b->k2; // Este valor deve ser o que sobe na árvore após a quebra.
        }

        b->meio = b->dir;
        b->k2 = -1;
        b->dir = NULL;
        return novo;
    }

    static int insere2(ArvB23* b, int chave, int* valorainserir, ArvB23** novofilho) {
        printf("Tentando inserir %d no no com chaves [%d, %d].\n", chave, b->k1, b->k2);
        // indica se deve inserir neste nó
        int inseriraqui = 0;

        if (b == NULL) {
            printf("erro! subárvore nula! \n");
            exit(1);
        }

        // não é folha, só insere neste nó se subir um valor
        if (b->esq != NULL) {
            if (chave < b->k1) {
                inseriraqui = insere2(b->esq, chave, valorainserir, novofilho);
            }
            // está entre as duas chaves ou só tem uma chave no nó
            else if (((b->k2 != -1) && (chave < b->k2)) || (b->k2 == -1)) {
                inseriraqui = insere2(b->meio, chave, valorainserir, novofilho);
            }
            else { // chave > b->k2
                inseriraqui = insere2(b->dir, chave, valorainserir, novofilho);
            }
        }
        // este nó é folha, tem que inserir nele
        else {
            printf("Insercao direta da chave %d em um no folha.\n", chave);
            *valorainserir = chave;
            inseriraqui = 1;
            *novofilho = NULL;
        }

        if (!inseriraqui) // se inserção já está completa
            return 0;

        // Agora devemos procurar um espaço no nó

        if (b->k2 == -1) { // tem espaço no nó
          // se nova chave for menor, empurra chave existente para a direita
            if (*valorainserir < b->k1) {
               b->k2 = b->k1;
                b->k1 = *valorainserir;
                b->dir = b->meio;
                b->meio = *novofilho;
                if (b->meio) b->meio->pai = b;
            }
            // é maior que a chave que já está lá
            else {
                b->k2 = *valorainserir;
                b->dir = b->meio;
                b->meio = *novofilho;
                if (b->meio) b->meio->pai = b;
            }
            // como havia espaço, não sobem valores a serem inseridos
            return 0;
        }

        *novofilho = overflowQuebra(b, valorainserir, *novofilho);

        // quando há quebra, sobe a mediana para nova inserção 
        return 1;
    }
    ArvB23* insere(ArvB23* b, int chave) {
        printf("Inserindo chave %d na arvore.\n", chave);
        int valorquesubiu;
        ArvB23* novofilho;
        ArvB23* novaraiz;

        if (b == NULL) {
            b = novoNo(chave);
            b->pai = novoNo(-1);  // Criação de uma raiz 'fictícia' para a nova raiz, isso pode ser discutível na implementação.
        }
        else {
            if (insere2(b, chave, &valorquesubiu, &novofilho)) {
                novaraiz = novoNo(valorquesubiu);
                novaraiz->pai = b->pai;
                novaraiz->esq = novofilho;
                novaraiz->esq->pai = novaraiz;
                novaraiz->meio = b;
                novaraiz->meio->pai = novaraiz;
                b = novaraiz;
            }
        }
        return b;
    }

    int existe(ArvB23* b, int chave) {
        int nivel = 0;
        while (b != NULL) {
            printf("Buscando chave %d no no com chaves [%d, %d] no nivel %d.\n", chave, b->k1, b->k2, nivel);
            if (chave == b->k1 || (b->k2 != -1 && chave == b->k2)) {
                printf("Chave %d encontrada no nivel %d.\n", chave, nivel);
                return nivel;
            }
            if (chave < b->k1) {
                b = b->esq;
            }
            else if (b->k2 == -1 || chave < b->k2) {
                b = b->meio;
            }
            else {
                b = b->dir;
            }
            nivel++;
        }
        printf("Chave %d nao encontrada na arvore.\n", chave);
        return -1;
    }

    void destroi(ArvB23* b) {
        if (b != NULL) {
            printf("Destruindo no com chaves [%d, %d].\n", b->k1, b->k2);
            destroi(b->esq);
            destroi(b->meio);
            destroi(b->dir);
            free(b);
        }
    }

    static void mostra_int(ArvB23* b, int nivel) {
        if (b != NULL) {
            // Indentação baseada no nível
            for (int i = 0; i < nivel; i++) {
                printf("   ");
            }
            printf("%d:%d->%d\n", b->k1, b->k2, b->pai ? b->pai->k1 : -1);
        
            mostra_int(b->esq, nivel + 1);
            mostra_int(b->meio, nivel + 1);
            if (b->k2 != -1) {
                mostra_int(b->dir, nivel + 1);
            }
        }
    }

    void mostra(ArvB23* b) {
        printf("Estrutura da Arvore:\n");
        mostra_int(b, 0);
    }

    int iguais(ArvB23* b1, ArvB23* b2) {
        if (b1 == NULL) return (b2 == NULL);
        if (b2 == NULL) return 0;
        return (b1->k1 == b2->k1) && (b1->k2 == b2->k2) && iguais(b1->esq, b2->esq) && iguais(b1->meio, b2->meio) && iguais(b1->dir, b2->dir) && (b1->pai->k1 == b2->pai->k1);
    }
