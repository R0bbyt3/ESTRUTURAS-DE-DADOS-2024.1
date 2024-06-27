#ifndef HUFFMAN_H
#define HUFFMAN_H

#define NUMERO_MAXIMO_DE_SIMBOLOS 128 // Tabela ascii padrao

////////////////////////////////////////////////////////////////////////
// Nos para o criacao da arvore
////////////////////////////////////////////////////////////////////////
typedef struct arvno ArvNo;
struct arvno {
  char info;
  int freq;
  ArvNo* esq;
  ArvNo* dir;
};

static char arvno_caractere (ArvNo* r) {
  return r->info;
}

static int arvno_frequencia (ArvNo* r) {
  return r->freq;
}

static ArvNo* arvno_esq (ArvNo* r) {
  return r->esq;
}

static ArvNo* arvno_dir (ArvNo* r) {
  return r->dir;
}

ArvNo* arv_criano (char info, int freq, ArvNo* esq, ArvNo* dir);
void arv_libera (ArvNo* r);
void arv_imprime (ArvNo* r);

////////////////////////////////////////////////////////////////////////
// Frequencias
////////////////////////////////////////////////////////////////////////
typedef struct hufffrequencias HuffFrequencias;
struct hufffrequencias {
  int n;
  int* f;
  char* c;
};

// Retorna o tamanho da tabela
HuffFrequencias* freq_cria (const char* arquivo_de_entrada);
// Retorna o tamanho da tabela
int freq_tamanho (HuffFrequencias* f);
// Retorna o caractere na posicao i, sendo i < freq_tamanho()
char freq_caractere (HuffFrequencias* f, int i);
// Retorna a ocorrencia do caractere na posicao i, sendo i < freq_tamanho()
int freq_frequencia (HuffFrequencias* f, int i);
// Imprime a tabela com printf
void freq_imprime (HuffFrequencias* f);
// Deleta a estrutura de frequencias
void freq_libera (HuffFrequencias* f);

////////////////////////////////////////////////////////////////////////
// Arvore
////////////////////////////////////////////////////////////////////////
typedef struct huffarvore HuffArvore;
struct huffarvore {
  ArvNo* raiz;
};

HuffArvore* arvh_cria (ArvNo* arv);
void arvh_imprime (HuffArvore* a);
void arvh_libera (HuffArvore* a);

////////////////////////////////////////////////////////////////////////
// Dicionario
////////////////////////////////////////////////////////////////////////
typedef struct huffsimbolo HuffSimbolo;
struct huffsimbolo {
  char simbolo;
  unsigned int codigo;
  unsigned int tamanho;
};

typedef struct huffdicionario HuffDicionario;
struct huffdicionario {
  int n; // numero de simbolos associados
  HuffSimbolo* simbolos;
};

HuffDicionario* dict_cria (HuffFrequencias* f, HuffArvore* a);
void dict_imprime (HuffDicionario* d);
void dict_libera (HuffDicionario* d);

////////////////////////////////////////////////////////////////////////
// Compressao e Descompressao
////////////////////////////////////////////////////////////////////////
int huffman_comprime (HuffDicionario* hd, const char* arquivo_de_entrada, const char* arquivo_de_saida);
void huffman_descomprime (HuffArvore* ha, const char* arquivo_de_entrada, const char* arquivo_de_saida, int numero_de_caracteres);

#endif