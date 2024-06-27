#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arvore.h"

ArvNo* preenche (ArvNo *a, int inicio, int fim)
{
  if (inicio > fim) return a;
  int meio = (fim + inicio) / 2;
  a = insere(a, meio);
  a = preenche(a, inicio, meio - 1);
  a = preenche(a, meio + 1, fim);
  return a;
}

int main (int argc, char **argv) {
  if (argc != 2) {
    printf ("Uso do programa: %s <num_nos>\n", argv[0]);
    exit(0);
  }
  int tam_arv = atoi(argv[1]);

  /* preenchendo sem balancear */
  ArvNo* a1 = NULL;
  for (int i = 0 ; i < tam_arv ; i++ )
    a1 = insere(a1, i);

  /* preenchendo balanceado */
  ArvNo* a2 = NULL;
  a2 = preenche(a2, 0, tam_arv-1);

  double total_criacao_sec_t = -1.0; // COMPLETAR: adicionar medicao de tempo para criacao das arvores
  printf("Tempo em segundos para criar arvores: %lf\n", total_criacao_sec_t);

  printf("Altura da arvore 1: %d\n", altura(a1));
  printf("Altura da arvore 2: %d\n", altura(a2));
  
  printf("Arvore 1 balanceada? %s\n", e_balanceada(a1) ? "Sim" : "Nao");
  printf("Arvore 2 balanceada? %s\n", e_balanceada(a2) ? "Sim" : "Nao");

  printf("Busca desbalanceada em arvore 1: ");
  for (int i = 0; i < tam_arv; i++) {
    busca(a1, i);
  }
  double total_busca_a1 = -1.0; // COMPLETAR: adicionar medicao de tempo para buscas
  printf("Tempo: %.10lf segundos\n", total_busca_a1);

  printf("Busca balanceada em arvore 2: ");
  for (int i = 0; i < tam_arv; i++) {
    busca(a2, i);
  }
  double total_busca_a2 = -1.0; // COMPLETAR: adicionar medicao de tempo para buscas
  printf("Tempo: %.10lf segundos\n", total_busca_a2);

  printf("Aplicando Balanceamento em arvore 1...\n");
  a1 = balancear(a1);
  
  printf("Altura da arvore 1 apos balanceamento: %d\n", altura(a1));
  printf("Arvore 1 balanceada? %s\n", e_balanceada(a1) ? "Sim" : "Nao");

  printf("Busca apos balanceamento de arvore 1: ");
  for (int i = 0; i < tam_arv; i++) {
    busca(a1, i);
  }
  double total_busca_a1_2 = -1.0; // COMPLETAR: adicionar medicao de tempo para buscas
  printf("Tempo: %.10lf segundos\n", total_busca_a1_2);

  libera(a1);
  libera(a2);

  return 0;
}