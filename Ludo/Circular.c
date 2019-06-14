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

#ifdef _DEBUG
	#include "Conta.h"
#endif
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
CIR_CondRetErro CIR_CriaLista(CIR_lstCircular **pResultado) //Cria uma nova lista composta de um elemento que aponta para si mesmo
{
	if(pResultado==NULL) 
	{
		#ifdef _DEBUG
        	CNT_CONTAR( "CIR_CRIA_ASSERT_PARMNULO" );
      	#endif
		return CIR_CondRetParametro;
	}
		#ifdef _DEBUG
        	CNT_CONTAR( "CIR_CRIA_MALLOC" );
    	#endif
	*pResultado = (CIR_lstCircular*) malloc(sizeof(CIR_lstCircular));
	if(*pResultado == NULL) 
	{
		return CIR_CondRetMemoria;
	}
	(*pResultado)->NoCorrente = NULL;

	#ifdef _DEBUG
        	CNT_CONTAR( "CIR_CRIA_FIM" );
    #endif
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
    if(pLista==NULL) 
	{	
		#ifdef _DEBUG
        	CNT_CONTAR( "CIR_DESTROI_ASSERT_PARMNULO" );
      	#endif
		return CIR_CondRetParametro;
	}

	#ifdef _DEBUG
        	CNT_CONTAR( "CIR_DESTROI_PARMOK" );
    #endif

    corrente = pLista->NoCorrente;
    if(corrente != NULL)
    {
		#ifdef _DEBUG
        	CNT_CONTAR( "CIR_DESTROI_NOCORRENTE" );
   		#endif
		corrente->anterior->proximo = NULL; //Define o final da lista circular
		while(corrente->proximo!=NULL){ //Deleta tudo ate chegar nesse final
			proximo = corrente->proximo;
			RemoveDado(corrente->pCont);
			free(corrente);
			corrente = proximo;
		}
	}
	else
	{
		#ifdef _DEBUG
        	CNT_CONTAR( "CIR_DESTROI_VAZIONOCORRENTE" );
    	#endif
	}
	
	#ifdef _DEBUG
        CNT_CONTAR( "CIR_DESTROI_FIM" );
    #endif
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
	if (pLista==NULL || pCont== NULL) 
	{
		#ifdef _DEBUG
        	CNT_CONTAR( "CIR_INSERE_ASSERT_PARAMETRO" );
    	#endif

		return CIR_CondRetParametro;
	}
	if (novo == NULL) return CIR_CondRetMemoria;

	#ifdef _DEBUG
        CNT_CONTAR( "CIR_INSERE_PARMOK" );
    #endif

	novo->pCont = pCont;

	if(pLista->NoCorrente!=NULL)
	{
		#ifdef _DEBUG
        	CNT_CONTAR( "CIR_INSERE_LISTACHEIA" );
    	#endif
		prox = pLista->NoCorrente->proximo;
		novo->anterior = pLista->NoCorrente;
		novo->proximo = prox;
		pLista->NoCorrente->proximo = novo;
		prox->anterior = novo;
	}
	else
	{
		#ifdef _DEBUG
        	CNT_CONTAR( "CIR_INSERE_LISTAVAZIA" );
    	#endif
		novo->proximo = novo;
		novo->anterior = novo;
	}
	#ifdef _DEBUG
        CNT_CONTAR( "CIR_INSERE_FIM" );
    #endif
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
    if(pLista==NULL) 
	{
		#ifdef _DEBUG
        	CNT_CONTAR( "CIR_REMOVE_ASSERT_PARM" );
    	#endif

		return CIR_CondRetParametro;
	}

	#ifdef _DEBUG
        	CNT_CONTAR( "CIR_REMOVE_PARMOK" );
    #endif

    if(pLista->NoCorrente==NULL) 
	{
		#ifdef _DEBUG
        	CNT_CONTAR( "CIR_REMOVE_LISTAVAZIA" );
    	#endif

		return CIR_CondRetListaVazia;
	}
	#ifdef _DEBUG
        	CNT_CONTAR( "CIR_REMOVE_LISTAOK" );
    #endif

    Corrente = pLista->NoCorrente;
    Precursor = Corrente->anterior;

	Precursor->proximo = Corrente->proximo;
	Corrente->proximo->anterior = Precursor;
    RemoveDado(Corrente->pCont);
    
    if(Precursor == Corrente) 
	{
		#ifdef _DEBUG
        	CNT_CONTAR( "CIR_REMOVE_UMELEMENTO" );
    	#endif
		pLista->NoCorrente = NULL; /*Se o elemento retirado foi o último o elemento corrente vira NULL */
	}
    else 
	{
		#ifdef _DEBUG
        	CNT_CONTAR( "CIR_REMOVE_VARIOSELEMENTOS" );
    	#endif
    	pLista->NoCorrente = Precursor;
    }

	#ifdef _DEBUG
        CNT_CONTAR( "CIR_REMOVE_FIM" );
    #endif
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
	if (pLista == NULL) 
	{
		#ifdef _DEBUG
        	CNT_CONTAR( "CIR_PROXIMO_ASSERT_PARM" );
    	#endif

		return CIR_CondRetParametro;
	}
	else
	{
		#ifdef _DEBUG
        	CNT_CONTAR( "CIR_PROXIMO_PARMOK" );
    	#endif
	}
	
	
	if (pLista->NoCorrente==NULL) 
	{
		#ifdef _DEBUG
        	CNT_CONTAR( "CIR_PROXIMO_LISTAVAZIA" );
    	#endif

		return CIR_CondRetListaVazia;
	}
	else
	{
		#ifdef _DEBUG
        	CNT_CONTAR( "CIR_PROXIMO_LISTACHEIA" );
    	#endif
	}
	#ifdef _DEBUG
        	CNT_CONTAR( "CIR_PROXIMO_FIM" );
    #endif
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
	if(pLista==NULL) 
	{
		#ifdef _DEBUG
        	CNT_CONTAR( "CIR_PRECEDENTE_ASSERT_PARM" );
    	#endif

		return CIR_CondRetParametro;
	}
	else
	{
		#ifdef _DEBUG
			CNT_CONTAR( "CIR_PRECEDENTE_PARMOK" );
		#endif
	}

	if (pLista->NoCorrente == NULL) 
	{
		#ifdef _DEBUG
        	CNT_CONTAR( "CIR_PRECEDENTE_LISTAVAZIA" );
    	#endif
		return CIR_CondRetListaVazia;
	}
	else
	{
		#ifdef _DEBUG
        	CNT_CONTAR( "CIR_PRECEDENTE_LISTACHEIA" );
    	#endif
	}
	
	#ifdef _DEBUG
        	CNT_CONTAR( "CIR_PRECEDENTE_FIM" );
    #endif
	
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

#ifdef _DEBUG
	#undef _DEBUG
#endif