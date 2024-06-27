#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mapa.h"

#define TAMINICIAL 11

typedef struct {
  int chave;
  int dados;
  int prox;
} ttabpos;

struct smapa {
  int tam;
  int ocupadas;
  ttabpos *tabpos;
};

static unsigned int hash (Mapa* m, int a) {
  return a % (m->tam);
}
  
Mapa* cria () {
  int i;
  Mapa* m = (Mapa*)malloc(sizeof(Mapa));
  if (m==NULL) {
    printf("erro na alocacao!\n");
    exit(1);
  }
  m->tabpos = (ttabpos*)malloc(TAMINICIAL*sizeof(ttabpos)); 
  if (m->tabpos==NULL) {
    printf("erro na alocacao!\n");
    exit(1);
  }
  m->tam = TAMINICIAL;
  m->ocupadas = 0;
  for (i=0;i<TAMINICIAL;i++) {
    m->tabpos[i].chave = -1;
    m->tabpos[i].prox = -1;
  }
  return m;
}

static void redimensiona (Mapa* m) {
#if 1
  int i;
  int tamanterior = m->tam;
  ttabpos* anterior = m->tabpos;

  /* aumenta o tamanho */
  printf ("Mapa: Inicia redimensiona... tamanho: %d-------\n", m->tam);
  m->tam = 1.947*m->tam;

  m->tabpos = (ttabpos*)malloc(m->tam*sizeof(ttabpos));

  /* 1. Inicializar nova tabela */
  for (i = 0; i < m->tam; i++) {
      m->tabpos[i].chave = -1;
      m->tabpos[i].dados = -1;
      m->tabpos[i].prox = -1;
  }

  m->ocupadas = 0;

  /* 2. Reinserir os elementos da tabela anterior para a nova tabela porque o tamanho mudou! */
  for (i = 0; i < tamanterior; i++) {
      if (anterior[i].chave != -1) {  // Apenas reinserir elementos válidos
          insere(m, anterior[i].chave, anterior[i].dados);
      }
  }

  free (anterior);

  printf("Mapa: Fim de Redimensiona... novo tamanho: %d-------\n", m->tam);
#endif
}

Mapa* insere (Mapa* m, int chave, int dados) {
    printf("Mapa: Inserir chave %d\n", chave);
    int posencontrada = -1;
    if (busca(m, chave, &posencontrada) != -1) {
        printf("Mapa: chave %d já inserida na tabela.\n", chave);
        return m; // Cancela a inserção se a chave já existir
    }

  printf("Mapa: tam %d | ocupadas %d\n",m->tam, m->ocupadas);
  if (m->ocupadas > 0.75*m->tam) redimensiona(m);

  if (m->ocupadas == m->tam) {
    printf ("Mapa: tabela cheia! Algo de errado nao esta certo!\n");
    exit(1);
  }

  int pos = hash(m, chave);
  /* esta vazia, apenas adiciona o valor, caso simples */
  if (m->tabpos[pos].chave == -1) {
    m->tabpos[pos].chave = chave;
    m->tabpos[pos].dados = dados;
    m->tabpos[pos].prox = -1;
  }
  /* conflito */
  else {
    /* primeiro, procuramos a proxima posicao livre */
    int poslivre = pos;
    do 
      poslivre = (poslivre+1) % (m->tam);
    while ((poslivre!=pos) && (m->tabpos[poslivre].chave!=-1));

    /* tabela cheia -- não deveria acontecer */
    if (poslivre==pos) {
      printf ("Mapa: tabela cheia! Algo de errado nao esta certo!\n");
      exit(1);
    }

    /* achou posicao livre  - verificar quem vai para ela */
    int hashocupadora = hash(m, m->tabpos[pos].chave);
    /* conflito primario: encadeia */
    if (hashocupadora == pos) { // Conflito primário
        printf("Mapa: Conflito primario %d %d...\n", hashocupadora, pos);

        int lastPos = pos; // Começa pela posição atual
        // Encontrar o último elemento na cadeia
        while (m->tabpos[lastPos].prox != -1) {
            lastPos = m->tabpos[lastPos].prox; // Siga para o próximo elemento na cadeia
        }
        // Agora, lastPos é o último elemento na cadeia de colisões

        m->tabpos[poslivre].chave = chave; // Inserir nova chave na posição livre encontrada
        m->tabpos[poslivre].dados = dados; // Dados da nova chave
        m->tabpos[poslivre].prox = -1; // Nova chave é agora o último elemento, sem próximo

        m->tabpos[lastPos].prox = poslivre; // Atualizar o último elemento anterior para apontar para o novo
    }

    else { // Conflito secundário
        printf("Mapa: Conflito secundario %d %d...\n", hashocupadora, pos);

        // Encontrar quem aponta para 'pos'
        int apontador = -1;
        for (int i = 0; i < m->tam; i++) {
            if (m->tabpos[i].prox == pos) {
                apontador = i;
                break;
            }
        }

        // Se alguém aponta para 'pos', atualize para apontar para 'poslivre'
        if (apontador != -1) {
            m->tabpos[apontador].prox = poslivre;
        }

        // Mova a chave em 'pos' para 'poslivre'
        m->tabpos[poslivre].chave = m->tabpos[pos].chave;
        m->tabpos[poslivre].dados = m->tabpos[pos].dados;
        m->tabpos[poslivre].prox = m->tabpos[pos].prox;

        // Insira a nova chave em 'pos'
        m->tabpos[pos].chave = chave;
        m->tabpos[pos].dados = dados;
        m->tabpos[pos].prox = -1;
    }

  }

  /* aumentou o numero de itens na tabela */
  (m->ocupadas)++; 
  return m;
}

int busca(Mapa* m, int chave, int* posencontrada) {
    if (m == NULL) {
        *posencontrada = -1;
        return -1;
    }

    int pos = hash(m, chave);

    //Loop que para quando a proxima posição for vazia (-1)

    while (pos != -1) {
        if (m->tabpos[pos].chave == chave) {
            *posencontrada = pos;
            return m->tabpos[pos].dados; // Retorna os dados associados se encontrar a chave
        }
        pos = m->tabpos[pos].prox; // Continua buscando na próxima posição
    }

    *posencontrada = -1;
    return -1; // Retorna -1 se não encontrar a chave
}



Mapa* retira(Mapa* m, int chave, int* removeu) {
    if (m == NULL) {
        *removeu = 0; //Não existe (não encontrada/ não removeu)
        return m;
    }

    int pos = hash(m, chave);
    int atual = pos;
    int anterior = -1;

    // Percorrer a cadeia de colisões
    while (atual != -1 && m->tabpos[atual].chave != -1) {
        if (m->tabpos[atual].chave == chave) {
            // Encontrou a chave, agora removê-la
            if (anterior == -1) { // Caso a. chave é a primeira do encadeamento
                if (m->tabpos[atual].prox != -1) { // Se houver um próximo
                    int prox_pos = m->tabpos[atual].prox;
                    m->tabpos[atual].chave = m->tabpos[prox_pos].chave;
                    m->tabpos[atual].dados = m->tabpos[prox_pos].dados;
                    m->tabpos[atual].prox = m->tabpos[prox_pos].prox;
                    m->tabpos[prox_pos].chave = -1; // Resetando a posição movida
                    m->tabpos[prox_pos].dados = 0;
                    m->tabpos[prox_pos].prox = -1;
                }
                else { // Não há próximo
                    m->tabpos[atual].chave = -1;
                    m->tabpos[atual].dados = 0;
                    m->tabpos[atual].prox = -1;
                }
            }
            else { // Caso b. chave está no meio ou no final do encadeamento
                m->tabpos[anterior].prox = m->tabpos[atual].prox;
                m->tabpos[atual].chave = -1;
                m->tabpos[atual].dados = 0;
                m->tabpos[atual].prox = -1;
            }
            *removeu = 1;
            /* diminuiu o numero de itens na tabela */
            (m->ocupadas)--;
            return m;
        }
        anterior = atual;
        atual = m->tabpos[atual].prox;
    }

    *removeu = 0; // Chave não encontrada
    return m;
}


void destroi (Mapa *m) {
  free(m->tabpos);
  free(m);
}

int iguais (Mapa* m1, Mapa* m2) {
  int i;

  if (m1==NULL || m2==NULL) return (m1==NULL && m2==NULL);
  if (m1->tam != m2->tam) return 0;
  ttabpos* tp1 = m1->tabpos;
  ttabpos* tp2 = m2->tabpos;
  for (i = 0; i < m1->tam; i++)
    if ((tp1[i].chave != tp2[i].chave) || (tp1[i].prox != tp2[i].prox))
      return 0;
  return 1;
}

void mostra (Mapa* m) {
  int i;
  for (i=0;i<m->tam;i++) 
    if (m->tabpos[i].chave!=-1) 
      printf("posicao %d, chave %d, proximo %d (hash %d): %d\n", i, m->tabpos[i].chave, m->tabpos[i].prox, hash(m, m->tabpos[i].chave), m->tabpos[i].dados);
}