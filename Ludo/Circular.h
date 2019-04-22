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

Cria e retorna uma lista circular com um elemento de conteúdo "pCont".

***************************************/
CIR_lstCircular *CIR_CriaLista(void *pCont);

/**************************************

Função: DestroiLista

Percorre e destroi toda uma lista circular

***************************************/
void CIR_DestroiLista(CIR_lstCircular *pCircular);

/**************************************

Função: Conteudo

Retorna o conteudo de um elemento(pLista) da lista circular.

***************************************/
void *CIR_Conteudo(CIR_lstCircular *pLista);

/**************************************

Função: Insereelemento

Insere um elemento apos o no passado como parâmetro e retorna o endereço do elemento inserido.

***************************************/
CIR_lstCircular *CIR_InsereElemento(CIR_lstCircular *pLista,void *pCont);

/**************************************

Função: RemoveElemento

Remove um elemento da lista circular.

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
