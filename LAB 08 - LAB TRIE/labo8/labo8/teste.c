#include <stdio.h>
#include <string.h>
#include "arvtrie.h"

int main (void) {
  ArvTrie* t = cria();
  insere(t, "algebra");   // compilador adiciona o '\0' em um const char* como "algebra\0"
  insere(t, "algoritmo"); 
  insere(t, "algoritmo"); 
  insere(t, "alcance");
  insere(t, "alto");
  insere(t, "altura");
  insere(t, "alternativa");
  insere(t, "alternancia");
  insere(t, "teste");
  insere(t, "testando");
  insere(t, "testamento");
  insere(t, "testemunha");
  insere(t, "tesoura");
  insere(t, "casa");
  insere(t, "canto");
  insere(t, "cantor");
  insere(t, "cantoria");
  insere(t, "cadeira");
  insere(t, "calibre");
  insere(t, "cascata");

  retira(t, "canto");
  retira(t, "cantr");
  retira(t, "cascata");
  retira(t, "testando");

  printf("\n");
  imprime(t);

  printf("\n");
  sugerir(t, "ca");
  sugerir(t, "ct");
  sugerir(t, "alt");
  sugerir(t, "al");
  sugerir(t, "tes");

  return 0;
}