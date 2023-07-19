// TRABALHO PRÁTICO DE AEDS II

// Alunos: Gabriel Coimbra - 3044
// 				 Maria Dalila Vieira - 3030
//				 Naiara Cristine - 3005

// Fonte: Ziviani, Nívio.

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <sys/time.h>

#define MAX_PALAVRA 50
#define MAX_DICIONARIO 100000UL

#define VERBOSE
typedef enum
{
	Interno, Externo
} kindNode;

typedef struct nodePatricia nodePatricia;
typedef struct nodePatricia
{
	kindNode kind;
	union
	{
		struct
		{
			int64_t offset;
			char letra;
			nodePatricia *esq, *dir;
		} insideNode;
		char item[MAX_PALAVRA];
	} unionNode;
}nodePatricia;

short patriciaEhExterno(nodePatricia **novo_no);
bool patriciaDirecao(int64_t *offset, char *item, char *pivo);

nodePatricia *patriciaCriaNoInterno(nodePatricia **esq,  nodePatricia **dir, int64_t offset, char letra);
nodePatricia *patriciaCriaNoExterno(char *item);

void patriciaPesquisaAux(nodePatricia **no_atual, char *item,  int64_t *comparacoes, bool *sucesso);
bool patriciaPesquisa(nodePatricia **raiz, char *item, int64_t *comparacoes);

nodePatricia *patriciaInsereEntre(nodePatricia **no_atual, char *item,  int64_t offset, char letraNoInterno);
nodePatricia *patriciaInsere(nodePatricia **raiz, char *item);

void patriciaAlturaMaiorPalavraAux(nodePatricia **nodePatricia, int64_t *max_palavra_global, int64_t max_palavra);
int64_t patriciaAlturaMaiorPalavra(nodePatricia **nodePatricia);

void patriciaAlturaPalavraAux(nodePatricia **no_atual,char *palavra, int64_t *profundidade);
int64_t patriciaAlturaPalavra(nodePatricia **no_atual, char *palavra);

int64_t patriciaContaNos(nodePatricia **nodePatricia, char option);
