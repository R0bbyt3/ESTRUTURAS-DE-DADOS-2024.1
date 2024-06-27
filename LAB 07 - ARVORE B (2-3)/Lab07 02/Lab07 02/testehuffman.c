#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"
#include "heaparvmin.h"

int main(void) {
  const char* arquivo_entrada = "entrada.txt";

  // calcula frequencias
  HuffFrequencias* f = freq_cria(arquivo_entrada);
  printf(">>>>> Tabela de Frequencias <<<<<\n");
  freq_imprime(f);
  printf("\n");
  
  // inicializa lista de frequencias e caracteres para o heap
  char* caracteres_iniciais = (char*)malloc(sizeof(char)*freq_tamanho(f));
  int* frequencia_iniciais = (int*)malloc(sizeof(int)*freq_tamanho(f));
  for (int i = 0; i < freq_tamanho(f); i++) {
    caracteres_iniciais[i]= freq_caractere(f, i);
    frequencia_iniciais[i]= freq_frequencia(f, i);
  }

  // cria heap
  HeapArvMin* h =  heaparvmin_cria(freq_tamanho(f), freq_tamanho(f), caracteres_iniciais, frequencia_iniciais);
  heaparvmin_debug_show(h, ">>>>> Heap minimo arvore <<<<<");
  printf("\n");

  // cria arvore de prefixos através do heap mínimo
  ArvNo* a = heaparvmin_criaarvorehuffman(h);
  HuffArvore* ha = arvh_cria(a); // passa a responsabilidade do ArvNo para o HuffArvore
  printf(">>>>> Arvore de Huffman <<<<<\n");
  arvh_imprime(ha);
  printf("\n");

  if (ha->raiz) { // se nao for uma arvore vazia
    // cria dicionario
    HuffDicionario* hd = dict_cria(f, ha);
    printf(">>>>> Dicionario de Simbolos <<<<<\n");
    dict_imprime(hd);
    printf("\n");
  
    // comprime e descomprime arquivo
    int n = huffman_comprime(hd, arquivo_entrada, "comprimido.txt");
    huffman_descomprime(ha, "comprimido.txt", "descomprimido.txt", n);
  
    dict_libera(hd);
  }

  arvh_libera(ha);
  heaparvmin_libera(h);
  free(frequencia_iniciais);
  free(caracteres_iniciais);
  freq_libera(f);
  return 0;
}