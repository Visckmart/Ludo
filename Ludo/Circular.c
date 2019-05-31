/***************************************************************************
*  $MCI MÃ³dulo de implementação: LIS  Lista Circular
*
*  Arquivo gerado:              Circular.c
*  Letras identificadoras:      CIR
* 
*
*  Projeto: INF 1301 / Ludo
*  Autores: Thiago Lamenza
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor            Data        Observações
*     1       Thiago Lamenza   18/abr/2019 inicio do desenvolvimento
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


/**************************************

$TC Tipo de dados: Cabeça da lista Circular

***************************************/

struct circular{
	No *NoCorrente;
};

/***************************************************
*
*  Funcao: CIR  &CriaLista
*
*  *************************************************/
CIR_CondRetErro CIR_CriaLista(CIR_lstCircular *pResultado) //Cria uma nova lista composta de um elemento que aponta para si mesmo
{
	if(pResultado == NULL) return CIR_CondRetParametro;
	pResultado = (CIR_lstCircular*) malloc(sizeof(CIR_lstCircular));
	if(pResultado == NULL) return CIR_CondRetMemoria;

	pResultado->NoCorrente = NULL;
	return CIR_CondRetOk;
}

/***************************************************
*
*  Função: CIR  &DestroiLista
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
*  Função: CIR  &InsereElemento
*
*  *************************************************/
CIR_CondRetErro CIR_InsereElemento(CIR_lstCircular *pLista,void *pCont)
{
	No *novo,*prox;
	novo = (No*) malloc(sizeof(No));//Maloca e insere um elemento ajustando os ponteiros
	
	if (pLista==NULL || pCont== NULL) return CIR_CondRetParametro;

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
*  Função: CIR  &RemoveElemento
*
*  *************************************************/
CIR_CondRetErro CIR_RemoveElemento(CIR_lstCircular *pLista,void (*RemoveDado)(void*))
{
	No *Corrente,*Precursor;
    if(pLista==NULL) return CIR_CondRetParametro;
    if(pLista->NoCorrente==NULL) return CIR_CondRetListaVazia;

    Corrente = pLista->NoCorrente;
    Precursor = Corrente->anterior;

	Precursor->proximo = Corrente->proximo;
	Corrente->proximo->anterior = Precursor;
    RemoveDado(Corrente->pCont);
    
    if(Precursor == Corrente) pLista->NoCorrente = NULL; /*Se o elemento retirado foi o último o elemento corrente vira NULL */
    else {
    		pLista->NoCorrente = Precursor;
    }

	free(Corrente);

	return CIR_CondRetOk;
}

/***************************************************
*
*  Função: CIR  &ProximoElemento
*
*  *************************************************/
CIR_CondRetErro CIR_ObterProximoElemento(CIR_lstCircular *pLista)
{
	if (pLista == NULL) return CIR_CondRetParametro;
	if (pLista->NoCorrente==NULL) return CIR_CondRetListaVazia;
	pLista->NoCorrente = pLista->NoCorrente->proximo;
	return CIR_CondRetOk;
}

/***************************************************
*
*  Função: CIR  &PrecedenteElemento
*
*  *************************************************/
CIR_CondRetErro CIR_ObterPrecedenteElemento(CIR_lstCircular *pLista)
{
	if(pLista==NULL) return CIR_CondRetParametro;
	if (pLista->NoCorrente == NULL) return CIR_CondRetListaVazia;
	pLista->NoCorrente = pLista->NoCorrente->anterior;
	return CIR_CondRetOk;
}

/***************************************************
*
*  Função: CIR  &Conteudo
*
*  *************************************************/
void *CIR_ObterConteudo(CIR_lstCircular *pLista)
{
	if(pLista == NULL || pLista->NoCorrente==NULL) return NULL;
	
	return pLista->NoCorrente->pCont;
}

/***************************************************
*
*  Função: CIR  &ProcuraElemento
*
*  *************************************************/
CIR_CondRetErro CIR_ProcuraElemento(CIR_lstCircular *pLista,void *pCont)
{
	No *noCorrente,*inicio;
    
	if(pLista==NULL || pCont==NULL) return CIR_CondRetParametro;
	if(pLista->NoCorrente == NULL) return CIR_CondRetListaVazia;

	noCorrente = pLista->NoCorrente;
    inicio = pLista->NoCorrente;

	do
	{
		if(noCorrente->pCont == pCont)
		{
			pLista->NoCorrente = noCorrente;
			return CIR_CondRetOk;/*Se encontrar no caminho para e retorna o endereço.*/
		}

		noCorrente = noCorrente->proximo;
	}while(noCorrente!=inicio);
	return CIR_CondRetNaoAchou;
}
