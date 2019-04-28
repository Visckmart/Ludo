//
//  Circular.h
//  Ludo
//

#ifndef Circular_h
#define Circular_h

#include <stdio.h>
/**************************************

Tipo de dados: Lista Circular

***************************************/
typedef struct circular CIR_lstCircular;

/**************************************

Função: CriaLista

Cria uma lista circular com um elemento.

Parâmetro: pCont -> Ponteiro para o conteudo do elemento da lista.

Retorno: Endereço da lista criada ou NULL caso ocorra erro de memoria.

***************************************/
CIR_lstCircular *CIR_CriaLista(void *pCont);

/**************************************

Função: DestroiLista

Percorre e destroi toda uma lista circular

Parâmetro: pCircular -> Ponteiro para uma lista circular.

***************************************/
void CIR_DestroiLista(CIR_lstCircular *pCircular);

/**************************************

Função: Conteudo

Retorna o conteudo de um elemento de uma lista circular.

Parâmetro: pLista -> Ponteiro pra uma lista circular.

Retorno: Conteúdo do elemento da lista circular.

***************************************/
void *CIR_Conteudo(CIR_lstCircular *pLista);

/**************************************

Função: InsereElemento

Insere um elemento apos o escolhido.

Parâmetros: pLista-> Ponteiro pra um elemento de uma lista, depois do qual será inserido o novo.
			pCont-> Ponteiro para o conteudo do novo elemento

Retorno: Endereço do novo elemento.

***************************************/
CIR_lstCircular *CIR_InsereElemento(CIR_lstCircular *pLista,void *pCont);

/**************************************

Função: RemoveElemento

Remove um elemento da lista circular.

Parâmetro: pLista -> Ponteiro para um elemento da lista circular a ser removido.

Retorno: Elemento anterior ao removido ou NULL caso seja o ultimo ou ocorra erro de memoria.

***************************************/
CIR_lstCircular *CIR_RemoveElemento(CIR_lstCircular *pLista);

/**************************************

Função: ProximoElemento

Retorna o endereço do elemento seguinte ao passado como parâmetro.

***************************************/
CIR_lstCircular *CIR_ProximoElemento(CIR_lstCircular *pLista);

/**************************************

Função: PrecedenteElemento

Retorna o endereço do elemento anterior ao passaco como parâmetro.

***************************************/
CIR_lstCircular *CIR_PrecedenteElemento(CIR_lstCircular *pLista);

/**************************************

Função: ProcuraElemento

Busca e retorna o endereço do elemento da lista circular com conteudo "pCont".

***************************************/
CIR_lstCircular *CIR_ProcuraElemento(CIR_lstCircular *pLista,void *pCont);

#endif /* Circular_h */
