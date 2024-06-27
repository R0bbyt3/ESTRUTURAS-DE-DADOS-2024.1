#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

void testeacm (const char* filename) {
  Grafo* original = grafoLe(filename);

  printf("Grafo \"%s\":\n", filename);
  grafoMostra(original);

  Grafo* parvore = primArvoreCustoMinimo(original, 0);
  printf("Arvore Geradora de Custo Minimo de Prim: \n");
  grafoMostra(parvore);

  Grafo* karvore = kruskalArvoreCustoMinimo(original);
  printf("Arvore Geradora de Custo Minimo de Kruskal: \n");
  grafoMostra(karvore);
}

int main (int argc, char** argv) {
  testeacm("grafo1.dat");
  testeacm("grafo2.dat");
  testeacm("grafo3.dat");
} 
