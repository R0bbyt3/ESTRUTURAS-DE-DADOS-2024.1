#include <stdio.h>
#include "avl.h"

int main(void) {
    AvlNo* a1 = NULL;
    int chave;
    while (1) {
        printf("chave a inserir (-111 para terminar): ");
        scanf("%d", &chave);

        if (chave == -111)
            break;

        a1 = insere_avl(a1, chave);
        imprime_avl(a1);
        printf("\n");
    }

    libera(a1);

    return 0;
}