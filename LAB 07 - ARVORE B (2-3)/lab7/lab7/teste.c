#include <stdio.h>
#include "arvb23.h"

int main(void) {
    ArvB23* b = cria();
    int chave;
    int nivel;

    // Inserção de chaves na árvore
    while (1) {
        printf("Chave a inserir (-111 para terminar): ");
        scanf("%d", &chave);
        if (chave == -111) break;

        b = insere(b, chave);
        printf("Arvore atual: \n");
        mostra(b);
    }

    // Consulta de chaves na árvore
    while (1) {
        printf("Chave a consultar (-111 para terminar): ");
        scanf("%d", &chave);
        if (chave == -111) break;

        nivel = existe(b, chave);
        if (nivel == -1) {
            printf("Chave %d nao encontrada.\n", chave);
        }
        else {
            printf("Chave %d encontrada no nivel %d.\n", chave, nivel);
        }
    }

    destroi(b);
    return 0;
}
