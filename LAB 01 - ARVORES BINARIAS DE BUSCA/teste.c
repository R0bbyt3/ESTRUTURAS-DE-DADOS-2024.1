#include <stdio.h>
#include "arvore.h"

int main() {
  int n;
  ArvNo *a1 = cria_no(6, cria_no(2, cria_no(1, NULL, NULL),
                                    cria_no(4, NULL, NULL)),
                         cria_no(10, NULL,
                                     cria_no(15, NULL, NULL))
				     );
  ArvNo *a2 = cria_no(7, cria_no(3,  cria_no(2, NULL, NULL), 
                                     NULL),
                         cria_no(15, cria_no(12, NULL, NULL),
                                     cria_no(19, cria_no(18, NULL, NULL), 
									             NULL))
					 );

  ArvNo *a3 = cria_no(7, cria_no(3, cria_no(2, NULL, NULL), 
                                    NULL),
                         cria_no(15, cria_no(12, NULL, 
						                         cria_no(9, NULL, NULL)),
                                     cria_no(19, cria_no(20, NULL, NULL), 
 									             NULL))
                     );

  ArvNo *a4 = cria_no(7, cria_no(3, cria_no(2, NULL, NULL), 
                                    cria_no(1, NULL, NULL)),
                         cria_no(15, cria_no(12, NULL, 
						                         cria_no(9, NULL, NULL)),
                                     cria_no(19, cria_no(20, NULL, NULL), 
 									             NULL))
                     );
  /* Mostra a árvore 1 */
  printf("Arvore 1:\n");
  imprime(a1);
  printf("\n");
  printf("a1 num_nos: %d\n", num_nos(a1));
  printf("a1 e_abb? %s\n", e_abb(a1) ? "Sim" : "Nao");

  /* Mostra a árvore 2 */
  printf("Arvore 2:\n");
  imprime(a2);
  printf("\n");
  printf("a2 num_nos: %d\n", num_nos(a2));
  printf("a2 e_abb? %s\n", e_abb(a2) ? "Sim" : "Nao");

  /* Mostra a árvore 3 */
  printf("Arvore 3:\n");
  imprime(a3);
  printf("\n");
  printf("a3 num_nos: %d\n", num_nos(a3));
  printf("a3 e_abb? %s\n", e_abb(a3) ? "Sim" : "Nao");

  /* Mostra a árvore 4 */
  printf("Arvore 4:\n");
  imprime(a4);
  printf("\n");
  printf("a4 num_nos: %d\n", num_nos(a4));
  printf("a4 e_abb? %s\n", e_abb(a4) ? "Sim" : "Nao");

  printf("---------------------------\n");
  /* novas arvores com insere */
  ArvNo* a_igual1 = NULL;
  a_igual1 = insere(a_igual1, 6);
  a_igual1 = insere(a_igual1, 2);
  a_igual1 = insere(a_igual1, 1);
  a_igual1 = insere(a_igual1, 4);
  a_igual1 = insere(a_igual1, 10);
  a_igual1 = insere(a_igual1, 15);
  printf("Arvore aigual1:\n");
  imprime(a_igual1);
  printf("\n");
  printf("a1 e a_igual1 iguais?: %s\n", arvores_iguais(a1, a_igual1) ? "iguais" : "diferentes");
  
  ArvNo* a_igual2 = NULL;
  a_igual2 = insere(a_igual2, 7);
  a_igual2 = insere(a_igual2, 3);
  a_igual2 = insere(a_igual2, 2);
  a_igual2 = insere(a_igual2, 15);
  a_igual2 = insere(a_igual2, 12);
  a_igual2 = insere(a_igual2, 19);
  a_igual2 = insere(a_igual2, 18);
  printf("Arvore aigual2:\n");
  imprime(a_igual2);
  printf("\n");
  printf("a2 e a_igual2 iguais?: %s\n", arvores_iguais(a2, a_igual2) ? "iguais" : "diferentes");

  printf("---------------------------\n");
  /* Obtém o número de nós com chaves maiores que 3 */
  printf("Nos maiores que 3 em a1: %d\n", num_maiores_que(a1,3));
  printf("Nos maiores que 3 em a2: %d\n", num_maiores_que(a2,3));
  
  libera(a1);
  libera(a2);
  libera(a3);
  libera(a4);
  libera(a_igual1);
  libera(a_igual2);

  return 0;
}
  