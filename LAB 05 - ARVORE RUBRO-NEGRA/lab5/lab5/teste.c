#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include "arvrb.h"

int main(void) {
    ArvNoRb* a1 = NULL;
    int chave;
    while (1) {
        printf("chave a inserir em arvore rubro-negra (-111 para terminar): ");
        scanf("%d", &chave);

        if (chave == -111)
            break;

        a1 = insere(a1, chave);
        imprime(a1);
        printf("\n");
    }
    printf("Numero de nos pretos: %d\n", num_nos_pretos(a1));
    printf("Numero de nos vermelhos: %d\n", num_nos_vermelhos(a1));

    libera(a1);
    return 0;
}


