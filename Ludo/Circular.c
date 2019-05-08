/***************************************************************************
*  $MCI MÃ³dulo de implementaÃ§Ã£o: LIS  Lista Circular
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
#include <stdio.h>
/**************************************

$TC Tipo de dados: Elemento da lista Circular

***************************************/

typedef struct no{
	void *pCont;
	struct no *proximo;
	struct no *anterior;
}No;

struct circular{
	No *NoCorrente;
};

/***************************************************
*
*  Funcao: CIR  &CriaLista
*
*  *************************************************/
CIR_lstCircular *CIR_CriaLista() //Cria uma nova lista composta de um elemento que aponta para si mesmo
{
	CIR_lstCircular *circ;
	circ = (CIR_lstCircular*) malloc(sizeof(CIR_lstCircular));
	
	if(circ==NULL) return NULL;
	
	
	circ->NoCorrente = NULL;
	return circ;
}

/***************************************************
*
*  FunÃ§Ã£o: CIR  &DestroiLista
*
*  *************************************************/
CIR_CondRetErro CIR_DestroiLista(CIR_lstCircular *pLista,void (*RemoveDado)(void*))
{
	No *corrente,*proximo;
    if(pLista==NULL) return CIR_CondRetParametro;
    corrente = pLista->NoCorrente;
    if(corrente != NULL)
    {

		corrente->anterior->proximo = NULL; //Define o final da lista circular
		while(corrente->proximo!=NULL){ //Deleta tudo ate chegar nesse final
			proximo = corrente->proximo;
			RemoveDado(corrente->pCont);
			free(corrente);
			corrente = proximo;
		}
	}
	free(pLista);
	return CIR_CondRetOk;
}

/***************************************************
*
*  FunÃ§Ã£o: CIR  &InsereElemento
*
*  *************************************************/
CIR_CondRetErro CIR_InsereElemento(CIR_lstCircular *pLista,void *pCont)
{
	No *novo,*prox;
	novo = (No*) malloc(sizeof(No));//Maloca e insere um elemento ajustando os ponteiros
	
	if (pCont== NULL) return CIR_CondRetParametro;

	if (novo == NULL) return CIR_CondRetMemoria;

	novo->pCont = pCont;

	if(pLista->NoCorrente!=NULL)
	{
		prox = pLista->NoCorrente->proximo;
		novo->anterior = pLista->NoCorrente;
		novo->proximo = prox;
		pLista->NoCorrente->proximo = novo;
		prox->anterior = novo;
	}
	else
	{
		novo->proximo = novo;
		novo->anterior = novo;
	}
	pLista->NoCorrente = novo;
	return CIR_CondRetOk;
}

/***************************************************
*
*  FunÃ§Ã£o: CIR  &RemoveElemento
*
*  *************************************************/
CIR_CondRetErro CIR_RemoveElemento(CIR_lstCircular *pLista,void (*RemoveDado)(void*))
{
	No *Corr;
    if(pLista==NULL) return CIR_CondRetParametro;
    Corr = pLista->NoCorrente;

	Corr->anterior->proximo = Corr->proximo;
	Corr->proximo->anterior = Corr->anterior;
    RemoveDado(Corr->pCont);
    
    CIR_PrecedenteElemento(pLista);
	free(Corr);
	return CIR_CondRetOk;
}

/***************************************************
*
*  FunÃ§Ã£o: CIR  &ProximoElemento
*
*  *************************************************/
CIR_CondRetErro CIR_ProximoElemento(CIR_lstCircular *pLista)
{
	if (pLista == NULL) return CIR_CondRetParametro;
	if (pLista->NoCorrente==NULL) return CIR_CondRetListaVazia;
	pLista->NoCorrente = pLista->NoCorrente->proximo;
	return CIR_CondRetOk;
}

/***************************************************
*
*  FunÃ§Ã£o: CIR  &PrecedenteElemento
*
*  *************************************************/
CIR_CondRetErro CIR_PrecedenteElemento(CIR_lstCircular *pLista)
{
	if(pLista==NULL) return CIR_CondRetParametro;
	if (pLista->NoCorrente == NULL) return CIR_CondRetListaVazia;
	pLista->NoCorrente = pLista->NoCorrente->anterior;
	return CIR_CondRetOk;
}

/***************************************************
*
*  FunÃ§Ã£o: CIR  &Conteudo
*
*  *************************************************/
void *CIR_Conteudo(CIR_lstCircular *pLista)
{
	if(pLista->NoCorrente==NULL) return NULL;
	
	return pLista->NoCorrente->pCont;
}

/***************************************************
*
*  FunÃ§Ã£o: CIR  &ProcuraElemento
*
*  *************************************************/
CIR_CondRetErro CIR_ProcuraElemento(CIR_lstCircular *pLista,void *pCont)
{
	No *proc;
    
	if(pLista==NULL || pCont==NULL) return CIR_CondRetParametro;
	if(pLista->NoCorrente == NULL) return CIR_CondRetListaVazia;

    proc = pLista->NoCorrente;
	
	do
	{
		if(proc->pCont==pCont)
		{
			pLista->NoCorrente=proc; /*Se encontrar no caminho para e retorna o endereço.*/
			return CIR_CondRetOk;
		}
		proc = proc->proximo;
	}while(proc!=pLista->NoCorrente->anterior);
	return CIR_CondRetNaoAchou;
}
