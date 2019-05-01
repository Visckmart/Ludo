/***************************************************************************
*  $MCI Módulo de implementação: LIS  Lista Circular
*
*  Arquivo gerado:              Circular.c
*  Letras identificadoras:      CIR
* 
*
*  Projeto: INF 1301 / Ludo
*
*
***************************************************************************/
#include <stdlib.h>
#include <assert.h>
#include "Circular.h"

/**************************************

$TC Tipo de dados: Elemento da lista Circualar

***************************************/
struct circular{
	void *pCont;
	struct circular *proximo;
	struct circular *anterior;
};


/***************************************************
*
*  Função: CIR  &CriaLista
*
*  *************************************************/
CIR_lstCircular *CIR_CriaLista(void *pCont) //Cria uma nova lista composta de um elemento que aponta para sí mesmo
{
	CIR_lstCircular *circ;
	circ = (CIR_lstCircular*) malloc(sizeof(CIR_lstCircular));
	
	assert(circ!=NULL && pCont!=NULL);
	
	
	circ ->proximo = circ;
	circ ->anterior = circ;
	circ ->pCont = pCont;
	return circ;
}

/***************************************************
*
*  Função: CIR  &DestroiLista
*
*  *************************************************/
void CIR_DestroiLista(CIR_lstCircular *pLista,void (*RemoveDado)(void*))
{
	CIR_lstCircular *proximo;
	pLista->anterior->proximo = NULL; //Define o final da lista circular
	while(pLista->proximo!=NULL){ //Deleta tudo ate chegar nesse final
		proximo = pLista->proximo;
        RemoveDado(pLista->pCont);
		free(pLista);
		pLista = proximo;
	}
}

/***************************************************
*
*  Função: CIR  &InsereElemento
*
*  *************************************************/
CIR_lstCircular *CIR_InsereElemento(CIR_lstCircular *pLista,void *pCont)
{
	CIR_lstCircular *novo,*prox = CIR_ProximoElemento(pLista);
	novo = (CIR_lstCircular*) malloc(sizeof(CIR_lstCircular));//Maloca e insere um elemento ajustando os ponteiros
	
	#ifdef _DEBUG
	assert(novo!=NULL && pCont!=NULL););
	#endif
	
	novo->pCont = pCont;
	novo->anterior = pLista;
	novo->proximo = prox;
	pLista->proximo = novo;
	prox->anterior = novo;
	
	#ifdef _DEBUG
	assert(novo->anterior->proximo == novo && novo->proximo->anterior == novo);
	#endif
	return novo;
}

/***************************************************
*
*  Função: CIR  &RemoveElemento
*
*  *************************************************/
CIR_lstCircular *CIR_RemoveElemento(CIR_lstCircular *pLista,void (*RemoveDado)(void*))
{
	CIR_lstCircular *ret = CIR_PrecedenteElemento(pLista);
	if(ret == pLista) ret = NULL;
	
	#ifdef _DEBUG
	assert(ret!=NULL && pLista!=NULL);
	#endif
	
	pLista->anterior->proximo = pLista->proximo;
	pLista->proximo->anterior = pLista->anterior;
    RemoveDado(pLista->pCont);
	free(pLista);
	
	return ret;
}

/***************************************************
*
*  Função: CIR  &ProximoElemento
*
*  *************************************************/
CIR_lstCircular *CIR_ProximoElemento(CIR_lstCircular *pLista)
{
	#ifdef _DEBUG
	assert(pLista!=NULL);
	#endif
	
	return pLista->proximo;
}

/***************************************************
*
*  Função: CIR  &PrecedenteElemento
*
*  *************************************************/
CIR_lstCircular *CIR_PrecedenteElemento(CIR_lstCircular *pLista)
{
	#ifdef _DEBUG
	assert(pLista!=NULL);
	#endif
	
	return pLista->anterior;
}

/***************************************************
*
*  Função: CIR  &Conteudo
*
*  *************************************************/
void *CIR_Conteudo(CIR_lstCircular *pLista)
{
	#ifdef _DEBUG
	assert(pLista!=NULL);
	#endif
	
	return pLista->pCont;
}

/***************************************************
*
*  Função: CIR  &ProcuraElemento
*
*  *************************************************/
CIR_lstCircular *CIR_ProcuraElemento(CIR_lstCircular *pLista,void *pCont)
{
	CIR_lstCircular *corrente = pLista->proximo;
	#ifdef _DEBUG
	assert(pLista!=NULL && pCont!=NULL&& corrente!=NULL);
	#endif
	
	while(corrente!=pLista) /*Marca o primeiro elemento e avança na lista circular ate encontrar ele novamente.*/
	{
		if(corrente->pCont==pCont) return corrente; /*Se encontrar no caminho para e retorna o endereço.*/
		corrente = corrente->proximo;
	}
	return NULL;
}