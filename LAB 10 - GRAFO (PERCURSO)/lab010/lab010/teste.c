#include <stdio.h>
#include "grafo.h"
 
int main()
{
  int noinicial;
  Grafo * g=grafoLe("grafo1.dat");
  grafoMostra("Grafo dado: ",g);
  while (1) {
    printf("Percurso em profundidade - no inicial (-1 para terminar): ");
    scanf ("%d", &noinicial);
    if (noinicial==-1) break;
    printf("recursivo: ");
    grafoPercorreProfundidadeRec(g, noinicial);
    printf("pilha: ");
    grafoPercorreProfundidade(g, noinicial);
    printf("\n");
  }

  while (1) {
    printf("Percurso em largura - no inicial (-1 para terminar): ");
    scanf ("%d", &noinicial);
    if (noinicial==-1) break;
    grafoPercorreLargura(g, noinicial);
    printf("\n");
  }

  g=grafoLe("grafo2.dat");
  grafoMostra("Grafo dado: ",g);
  while (1) {
    printf("Percurso em profundidade - no inicial (-1 para terminar): ");
    scanf ("%d", &noinicial);
    if (noinicial==-1) break;
    printf("recursivo: ");
    grafoPercorreProfundidadeRec(g, noinicial);
    printf("pilha: ");
    grafoPercorreProfundidade(g, noinicial);
    printf("\n");
  }

  while (1) {
    printf("Percurso em largura - no inicial (-1 para terminar): ");
    scanf ("%d", &noinicial);
    if (noinicial==-1) break;
    grafoPercorreLargura(g, noinicial);
    printf("\n");
  }

  return 0 ;
}
