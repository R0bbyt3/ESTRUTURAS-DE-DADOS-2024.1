#include <stdio.h>
#include <stdlib.h>
#include "mapa.h"

int main2(void) {

  int chavedada;

  Mapa *mapa1 = cria();

  mostra(mapa1);

  mapa1 = cria();
  while (1) {
    printf ("inserir em mapa1 (digite -111 para terminar): ");
    scanf ("%d", &chavedada);
    if (chavedada==-111) break;
    mapa1 = insere(mapa1, chavedada, 2*chavedada);
    mostra(mapa1);
  }
  while (1) {
    printf ("buscar em mapa1 (digite -111 para terminar): ");
    scanf ("%d", &chavedada);
    if (chavedada==-111) break;
    int posencontrada;
    int dados = busca(mapa1, chavedada, &posencontrada);
    printf("resultado da busca por %d: %d (pos %d)\n", chavedada, dados, posencontrada);
  }
  while (1) {
    printf ("retirar em mapa1 (digite -111 para terminar): ");
    scanf ("%d", &chavedada);
    if (chavedada==-111) break;
    int removeu;
    mapa1 = retira(mapa1, chavedada, &removeu);
    if (removeu) {
      printf("chave %d removida\n", chavedada);
      mostra(mapa1);
    }
    else {
      printf("chave %d nao encontrada\n", chavedada);
    }
  }
  destroi(mapa1);

  return 0;
}