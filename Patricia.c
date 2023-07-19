// TRABALHO PRÁTICO DE AEDS II

// Alunos: Gabriel Coimbra - 3044
// 				Maria Dalila Vieira - 3030
//				Naiara Cristine - 3005

// Fonte: Ziviani, Nívio. http://www2.dcc.ufmg.br/livros/algoritmos/implementacoes-05.php

#include "Patricia.h"

// Decide qual direção tomar
bool patriciaDirecao(int64_t *offset, char *item, char *pivo)
{
	return (item[*offset] > *pivo);
}

// Verifica se nó é externo
short patriciaEhExterno(nodePatricia **novo_no)
{
	assert(*novo_no != NULL);

	return ((*novo_no)->kind == Externo);
}

// Função encapsulada de pesquisa
void patriciaPesquisaAux(nodePatricia **no_atual, char *item,  int64_t *comparacoes, bool *sucesso)
{
	assert(item != NULL);
	assert(*no_atual != NULL);
	assert(sucesso != NULL);

	(*comparacoes)++;
	if (patriciaEhExterno(no_atual))
	{
		#ifdef VERBOSE
			printf("patriciaPesquisaAux(): %s %s\n", item,(*no_atual)->unionNode.item);
		#endif
		if (strcmp(item, (*no_atual)->unionNode.item) == 0)
		{
			#ifdef VERBOSE
			puts("patriciaPesquisa(): Elemento encontrado!");
			#endif
			*sucesso = true;
		}
		else
		{
			#ifdef VERBOSE
			puts("patriciaPesquisa(): Elemento não encontrado ");
			#endif

			*sucesso = false;
		}
		return;
	}
	if (!patriciaDirecao(&((*no_atual)->unionNode.insideNode.offset), item, &((*no_atual)->unionNode.insideNode.letra)))
		patriciaPesquisaAux(&(*no_atual)->unionNode.insideNode.esq, item, comparacoes, sucesso);
	else
		patriciaPesquisaAux(&(*no_atual)->unionNode.insideNode.dir, item, comparacoes, sucesso);
}

// Pesquisa na árvore por item
bool patriciaPesquisa(nodePatricia **raiz, char *item, int64_t *comparacoes)
{
	assert(item != NULL);
	if(*raiz == NULL)
		return 0;

	bool sucesso = false;
	//recebe um porque sempre compara a raiz com nulo
	*comparacoes = 0;

	patriciaPesquisaAux(raiz,item,comparacoes,&sucesso);
	// printf("patriciaPesquisa(): Numero de %zu comparacoes\n",comparacoes);
	return sucesso;
}

nodePatricia *patriciaCriaNoInterno(nodePatricia **esq,  nodePatricia **dir, int64_t offset, char letra)
{

	#ifdef VERBOSE
		printf("patriciaCriaNoInterno(): Criando no interno letra %c e offset %zu\n", letra,offset);
	#endif

	nodePatricia *novo_no;
	novo_no = (nodePatricia *) malloc(sizeof(nodePatricia));
	if(novo_no == NULL)
	{
		puts("patriciaCriaNoInterno(): ERRO FATAL impossível alocar espaço!");
		exit(-1);
	}
	novo_no->kind = Interno;
	novo_no->unionNode.insideNode.esq = *esq;
	novo_no->unionNode.insideNode.dir = *dir;
	novo_no->unionNode.insideNode.offset = offset;
	novo_no->unionNode.insideNode.letra = letra;

	return novo_no;
}


nodePatricia *patriciaCriaNoExterno(char *item)
{
	assert(item != NULL);

	nodePatricia *novo_no;
	novo_no = (nodePatricia *) malloc(sizeof(nodePatricia));
	if(novo_no == NULL)
	{
		puts("patriciaCriaNoExterno(): impossível alocar espaço!");
		exit(-1);
	}
	novo_no->kind = Externo;

  // Copia string para árvore
	strcpy(novo_no->unionNode.item,item);
	return novo_no;
}

nodePatricia *patriciaInsereEntre(nodePatricia **no_atual, char *item,  int64_t offset, char letraNoInterno)
{
	assert(*no_atual != NULL);

	nodePatricia *novo_no;

  // Entra se achamos um nó interno ou estamos no offset certo
	if (patriciaEhExterno(no_atual) || offset < (*no_atual)->unionNode.insideNode.offset)
	{
		if(patriciaEhExterno(no_atual))
			if(!strcmp((*no_atual)->unionNode.item,item))
			{
				printf("patriciaInsereEntre(): ERRO Item %s já inserido!\n",item);
				return NULL;
			}

		// cria um novo no externo
		novo_no = patriciaCriaNoExterno(item);

    // Decide a direção tomada para criar o nó interno
		if (patriciaDirecao(&offset, item, &letraNoInterno))
			return (patriciaCriaNoInterno(no_atual, &novo_no, offset,letraNoInterno));
		else
			return (patriciaCriaNoInterno(&novo_no, no_atual, offset,letraNoInterno));
	}

  // Não se trata de um nó externo, percorre árvore
	else
	{
		if (patriciaDirecao(&(*no_atual)->unionNode.insideNode.offset, item, &(*no_atual)->unionNode.insideNode.letra))
		{
			nodePatricia *aux = (*no_atual)->unionNode.insideNode.dir;
			(*no_atual)->unionNode.insideNode.dir = patriciaInsereEntre(&(*no_atual)->unionNode.insideNode.dir,item,offset,letraNoInterno);

			// Se a palavra já foi inserida, precisamos verificar se o retorno é NULO e deixar o dir anterior
			if(!(*no_atual)->unionNode.insideNode.dir)
				(*no_atual)->unionNode.insideNode.dir = aux;
		}
		else
		{
			nodePatricia *aux = (*no_atual)->unionNode.insideNode.esq;
			(*no_atual)->unionNode.insideNode.esq = patriciaInsereEntre(&(*no_atual)->unionNode.insideNode.esq,item,offset,letraNoInterno);

			// Se a palavra já foi inserida, precisamos verificar se o retorno é NULO e deixar o esq anterior
			if(!(*no_atual)->unionNode.insideNode.esq)
				(*no_atual)->unionNode.insideNode.esq = aux;
		}
		return (*no_atual);
	}
}

nodePatricia *patriciaInsere(nodePatricia **raiz, char *item)
{
	assert(item != NULL);

	int64_t offset;
	char letraNoInterno;
	nodePatricia *novo_no;

	if (*raiz == NULL)
		return (patriciaCriaNoExterno(item));

	else
	{
		novo_no = *raiz;

		// Pecorre a árvore para achar ponto de inserção de forma iterativa
		while (!patriciaEhExterno(&novo_no))
			{
				if (patriciaDirecao(&(novo_no->unionNode.insideNode.offset), item, &(novo_no->unionNode.insideNode.letra)))
					novo_no = novo_no->unionNode.insideNode.dir;
				else
					novo_no = novo_no->unionNode.insideNode.esq;
			}

		// acha o primeiro char diferente
		offset = 0;
		while ((offset < MAX_PALAVRA) & (item[offset] ==  novo_no->unionNode.item[offset]))
			offset++;

		#ifdef VERBOSE
		printf("patriciaInsere(): item diferente:%c %c\n", item[offset], novo_no->unionNode.item[offset]);
		#endif

		if(novo_no->unionNode.item[offset] < item[offset])
			letraNoInterno = novo_no->unionNode.item[offset];
		else
			letraNoInterno = item[offset];

		#ifdef VERBOSE
		printf("patriciaInsere(): LETRA %c\n",letraNoInterno);
		#endif

		return (patriciaInsereEntre(raiz, item, offset, letraNoInterno));
	}
}

//Funçao auxiliar que percorre a arvore de forma recursiva
void patriciaAlturaMaiorPalavraAux(nodePatricia **no_atual, int64_t *max_palavra_global, int64_t max_palavra)
{
	assert(max_palavra_global != NULL);

	if(*no_atual)
	{
		max_palavra++;

		if(!patriciaEhExterno(no_atual))
		{
			//Primeiro percorre a subarvore a esquerda
			patriciaAlturaMaiorPalavraAux(&(*no_atual)->unionNode.insideNode.esq,max_palavra_global,max_palavra);

			//Percorre a subarvore da direta
			patriciaAlturaMaiorPalavraAux(&(*no_atual)->unionNode.insideNode.dir,max_palavra_global,max_palavra);
		}
		else
		{
	      // Chegamos no nó externo, decide se temos um valor maior para a chave
			if(max_palavra > *max_palavra_global)
				*max_palavra_global = max_palavra - 1;
		}
	}
}

// Procura maior palavras todos nós. Função encapsulada
int64_t patriciaAlturaMaiorPalavra(nodePatricia **no_atual)
{
	assert(*no_atual != NULL);
	if(*no_atual == NULL)
		return 0;

	int64_t max_palavra_global = -1;
	patriciaAlturaMaiorPalavraAux(no_atual,&max_palavra_global,0);
	return max_palavra_global;
}

//Funçao auxiliar que percorre a arvore de forma recursiva
void patriciaAlturaPalavraAux(nodePatricia **no_atual,char *palavra, int64_t *profundidade)
{
	assert(palavra != NULL);

	if(*no_atual)
	{
		(*profundidade)++;
		if(patriciaEhExterno(no_atual))
		{
			(*profundidade)++;
			return;
		}
		else
		{
      // Não chegamos no nó especificado
			if (!patriciaDirecao(&((*no_atual)->unionNode.insideNode.offset), palavra, &((*no_atual)->unionNode.insideNode.letra)))
				patriciaAlturaPalavraAux(&(*no_atual)->unionNode.insideNode.esq,palavra,profundidade);
			else
				patriciaAlturaPalavraAux(&(*no_atual)->unionNode.insideNode.dir,palavra,profundidade);
		}
	}
}

// Procura palavra vê altura dela. Função encapsulada
int64_t patriciaAlturaPalavra(nodePatricia **no_atual, char *palavra)
{
	assert(*no_atual != NULL);
	assert(palavra != NULL);
	if(*no_atual == NULL)
		return 0;

	int64_t profundidade = 0;
	patriciaAlturaPalavraAux(no_atual,palavra,&profundidade);
	return profundidade;
}


void patriciaContaNosAux(nodePatricia **nodePatricia,int64_t *qtd_nos_internos,int64_t *qtd_nos_externos)
{
	assert(qtd_nos_internos != NULL);
	assert(qtd_nos_externos != NULL);

	if (*nodePatricia == NULL)
		return;

	if(patriciaEhExterno(nodePatricia))
	{
			(*qtd_nos_externos)++;
			return;
	}

	(*qtd_nos_internos)++;

  // Ainda precisamos percorrer na esquerda
	if(!patriciaEhExterno(&(*nodePatricia)->unionNode.insideNode.esq))
		patriciaContaNosAux(&(*nodePatricia)->unionNode.insideNode.esq,qtd_nos_internos,qtd_nos_externos);
	else
		(*qtd_nos_externos)++;

	// Ainda precisamos percorrer na direita
	if(!patriciaEhExterno(&(*nodePatricia)->unionNode.insideNode.dir))
		patriciaContaNosAux(&(*nodePatricia)->unionNode.insideNode.dir,qtd_nos_internos,qtd_nos_externos);
	else
		(*qtd_nos_externos)++;
}

int64_t patriciaContaNos(nodePatricia **nodePatricia, char option)
{
	assert(*nodePatricia != NULL);

	int64_t qtd_nos_externos = 0, qtd_nos_internos = 0;
	patriciaContaNosAux(nodePatricia, &qtd_nos_internos, &qtd_nos_externos);
	if(option == 'i')
		return qtd_nos_internos;
	if(option == 'e')
		return qtd_nos_externos;
}
