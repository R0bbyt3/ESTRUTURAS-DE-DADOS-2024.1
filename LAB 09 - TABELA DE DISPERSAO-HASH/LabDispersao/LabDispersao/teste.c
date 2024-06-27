#include <stdio.h>
#include <stdlib.h>
#include "mapa.h"

int main(void) {
  Mapa *mapa = cria();
  mostra(mapa);

  mapa = insere(mapa, 11, 2*11);
  mostra(mapa);
  mapa = insere(mapa, 22, 2*22);
  mostra(mapa);
  mapa = insere(mapa, 33, 2*33);
  mostra(mapa);
  mapa = insere(mapa,  0, 2*0);
  mostra(mapa);
  mapa = insere(mapa,  1, 2*1);
  mostra(mapa);
  mapa = insere(mapa, 44, 2*44);
  mostra(mapa);
  mapa = insere(mapa, 49, 2*49);
  mostra(mapa);
  mapa = insere(mapa, 50, 2*50);
  mostra(mapa);
  mapa = insere(mapa, 55, 2*55);
  mostra(mapa);
  mapa = insere(mapa, 55, 2*55);

  int nchavesbusca = 7;
  int chavebuscas[] = { 0, 49, 44, 1, 4, 22, 66 };
  for (int i = 0; i < nchavesbusca; i++) {
    int posencontrada;
    int chave = chavebuscas[i];
    int dados = busca(mapa, chave, &posencontrada);
    printf("Busca: Resultado por %d: %d (pos %d)\n", chave, dados, posencontrada);
  }

  mapa = insere(mapa, 9, 2*9);
  mostra(mapa);
  mapa = insere(mapa, 10, 2*10);
  mostra(mapa);
  mapa = insere(mapa, 43, 2*43);
  mostra(mapa);
  mapa = insere(mapa, 64, 2*64);
  mostra(mapa);
  mapa = insere(mapa, 13, 2*13);
  mostra(mapa);
  mapa = insere(mapa, 34, 2*34);
  mostra(mapa);

  int nchavesrem = 9;
  int chaverems[] = { 55, 44, 43, 22, 1, 5, 7, 9, 64 };
  for (int i = 0; i < nchavesrem; i++) {
    int removeu = 0;
    int chave = chaverems[i];

    mapa = retira(mapa, chave, &removeu);
    if (removeu) {
      printf("chave %d removida\n", chave);
      mostra(mapa);
    }
    else {
      printf("chave %d nao encontrada\n", chave);
    }
  }
  mapa = insere(mapa, 10, 2*10);
  mapa = insere(mapa, 12, 2*12);
  mostra(mapa);
  destroi(mapa);
  return 0;
}
