//
//  Circular.c
//  Ludo
//
#include <stdlib.h>
#include "Circular.h"

/**************************************

Tipo de dados: Elemento da lista Circualar

***************************************/
struct circular{
	void *pCont;
	struct circular *proximo;
	struct circular *anterior;
};

CIR_lstCircular *CIR_CriaLista(void *pCont) //Cria uma nova lista composta de um elemento que aponta para sí mesmo
{
	CIR_lstCircular *circ = (CIR_lstCircular*) malloc(sizeof(CIR_lstCircular));
	if(circ==NULL) return NULL;
	circ ->proximo = circ;
	circ ->anterior = circ;
	circ ->pCont = pCont;
	return circ;
}
void CIR_DestroiLista(CIR_lstCircular *pCircular)
{
	CIR_lstCircular *proximo;
	pCircular->anterior->proximo = NULL; //Define o final da lista circular
	while(pCircular->proximo!=NULL){ //Deleta tudo ate chegar nesse final
		proximo = pCircular->proximo;
		free(pCircular);
		pCircular = proximo;
	}
}
CIR_lstCircular *CIR_InsereElemento(CIR_lstCircular *pLista,void *pCont)
{
	CIR_lstCircular *novo,*prox = CIR_ProximoElemento(pLista);
	
	novo = (CIR_lstCircular*) malloc(sizeof(CIR_lstCircular));//Maloca e insere um elemento ajustando os 
	if(novo==NULL) return NULL;
	
	novo->pCont = pCont;
	novo->anterior = pLista;
	novo->proximo = prox;
	pLista->proximo = novo;
	prox->anterior = novo;
	
	return novo;
}

CIR_lstCircular *CIR_RemoveElemento(CIR_lstCircular *pLista)
{
	CIR_lstCircular *ret = CIR_PrecedenteElemento(pLista);
	if(ret == pLista) ret = NULL;
	
	pLista->anterior->proximo = pLista->proximo;
	pLista->proximo->anterior = pLista->anterior;
	free(pLista);
	return ret;
}
CIR_lstCircular *CIR_ProximoElemento(CIR_lstCircular *pLista)
{
	return pLista->proximo;
}
CIR_lstCircular *CIR_PrecedenteElemento(CIR_lstCircular *pLista)
{
	return pLista->anterior;
}
void *CIR_Conteudo(CIR_lstCircular *pLista)
{
	return pLista->pCont;
}

CIR_lstCircular *CIR_ProcuraElemento(CIR_lstCircular *pLista,void *pCont)
{
	CIR_lstCircular *corrente = pLista;
	
	while(corrente->proximo!=pLista) //Marca o primeiro elemento e avança na lista circular ate encontrar ele novamente.
	{
		if(corrente->pCont==pCont) return corrente; //Se encontrar no caminho para e retorna o endereço.
		corrente = corrente->proximo;
	}
	return NULL; //Fazer um tipo enumerado com erros?
}