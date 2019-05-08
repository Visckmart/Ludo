#if ! defined( LISTA_ )
    #define LISTA_
/***************************************************************************
*
*  $MCD Módulo de definição: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              Circular.h
*  Letras identificadoras:      CIR
*
*
*  Projeto: INF 1301 / Ludo
*  Autores: Thiago de Souza Lamenza
*
*  $HA Histórico de evolução:
*     Versão  Autor             Data        Observações
*     1       Thiago Lamenza   18/abr/2019  Desenvolvimento inicial
*     
*
*  $ED Descrição do módulo
*     Implementa listas genericas circulares. 
*
*     Cada lista é homogênea quanto ao tipo dos dados que armazena.
*     Cada elemento da lista referencia o valor que contém.
*
*     Os ponteiros para os dados são copiados para elementos da lista.
*     Não é copiado o valor apontado por estes ponteiros.
*
*     Toda lista é identificada por um ponteiro pra um elemento dela.
*     Todo elemento da lista identifica ela igualmente.
*     Basta saber o ponteiro para um elemento da lista para executar qualquer operação nela.
***************************************************************************/


/**************************************

Tipo de dados: Lista Circular

***************************************/
typedef struct circular CIR_lstCircular;

/***********************************************************************
*
*  $TC Tipo de dados: CIR Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções de Lista Circular
*
***********************************************************************/


typedef enum { 

	CIR_CondRetOk,
	/* Concluiu corretamente */

	CIR_CondRetMemoria,
	/* Faltou memória ao tentar criar um elemento de lista */

	CIR_CondRetParametro,
	/* Parâmetro nulo*/

	CIR_CondRetListaVazia,
	/* A lista não contém elementos */

	CIR_CondRetNaoAchou
	/* Não encontrou o elemento procurado */

} CIR_CondRetErro;


/***********************************************************************
*
*  $FC Função: CIR  &Crialista
*
*  $ED Descrição da função
*     Cria uma lista genérica circular contendo um elemento.
*     Os possíveis tipos são desconhecidos a priori.
*     A tipagem deles é implicita.
*
*  $EP Parâmetros
*     *pCont  - ponteiro para o elemento a ser contido na lista.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para a lista.
*
*     Esse ponteiro será usado para todas as outras funções do módulo.
*
*   Assertivas:
*       pCont não pode ser NULL, caso seja a função retorna NULLL.
***********************************************************************/
CIR_lstCircular *CIR_CriaLista();

/***********************************************************************
*
*  $FC Função: CIR  &DestroiLista
*
*  $ED Descrição da função
*     Percorre e libera todos os elementos de uma lista. 
*
*     A liberação dos ponteiros que a lista contém serão feitas pela função fornecida pelo cliente.
*
*
*  $EP Parâmetros
*     *pLista  - ponteiro para um elemento da lista a ser destruida.
*     *RemoveDado - Ponteiro para uma função encarregada de liberar o dado contido no elemento.
*  $FV Valor retornado
*     A função não retorna nenhum valor.
*
*   Assertivas:
*       pLista não pode ser NULL, caso seja a função retorna NULLL.
***********************************************************************/
CIR_CondRetErro CIR_DestroiLista(CIR_lstCircular *pLista,void (*RemoveDado)(void*));

/***********************************************************************
*
*  $FC Função: CIR  &Conteudo
*
*  $ED Descrição da função
*     Retorna o conteúdo na forma de ponteiro do elemento passado como parâmetro.
*
*  $EP Parâmetros
*     *pLista  - Ponteiro para o elemento com o conteúdo desejado.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para a lista.
*
*     Esse ponteiro será usado para todas as outras funções do módulo.
*
*   Assertivas:
*       pLista não pode ser NULL, caso seja a função retorna NULLL.
***********************************************************************/
void *CIR_Conteudo(CIR_lstCircular *pLista);

/***********************************************************************
*
*  $FC Função: CIR  &InsereElemento
*
*  $ED Descrição da função
*     Insere um elemento na lista circular depois do elemento passsado como parâmetro.
*
*  $EP Parâmetros
*     *pLista  - Ponteiro para o elemento depois do qual deve ser inserido o novo.
      *pCont   - Ponteiro para o conteúdo do elemento a ser inserido.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para o novo elemento da lista.
*
*   Assertivas:
*       pLista e pCont não podem ser NULL, caso seja a função retorna NULLL.
***********************************************************************/
CIR_CondRetErro CIR_InsereElemento(CIR_lstCircular *pLista,void *pCont);

/***********************************************************************
*
*  $FC Função: CIR  &RemoveElemento
*
*  $ED Descrição da função
*     Remove um elemento da lista circular liberando-o e o dado contido nele.
*     O dado contido pelo elemento a ser removido será liberado utilizando a função fornecida pelo cliente.
*       
*
*  $EP Parâmetros
*     *pCont  - Ponteiro para o elemento a ser contido na lista.
*     *RemoveDado - Ponteiro para a função encarregada de liberar o dado contido no elemento.
*  $FV Valor retornado
*     Retorna o ponteiro para o elemento anterior ao removido, caso o removido seja o último retorna NULL.
*
*   Assertivas:
*       pLista não pode ser NULL, caso seja a função retorna NULLL.
***********************************************************************/
CIR_CondRetErro CIR_RemoveElemento(CIR_lstCircular *pLista,void (*RemoveDado)(void*));

/***********************************************************************
*
*  $FC Função: CIR  &ProximoElemento
*
*  $ED Descrição da função
*     Avança para o proximo elemento da lista circular.
*
*  $EP Parâmetros
*     *pLista  - Ponteiro para o elemento anterior ao desejado.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para o proximo elemento da lista.
*
*   Assertivas:
*       pLista não pode ser NULL, caso seja a função retorna NULLL.
***********************************************************************/
CIR_CondRetErro CIR_ProximoElemento(CIR_lstCircular *pLista);

/***********************************************************************
*
*  $FC Função: CIR  &PrecedenteElemento
*
*  $ED Descrição da função
*     Retorna para o elemento anterior da lista circular.
*
*  $EP Parâmetros
*     *pLista  - Ponteiro para o elemento posterior ao desejado.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para o elemento anterior da lista.
*
*   Assertivas:
*       pLista não pode ser NULL, caso seja a função retorna NULLL.
***********************************************************************/
CIR_CondRetErro CIR_PrecedenteElemento(CIR_lstCircular *pLista);

/***********************************************************************
*
*  $FC Função: CIR  &ProcuraElemento
*
*  $ED Descrição da função
*     Procura um elemento na lista circular contendo um dado passado como parâmetro.
*     Caso dois elementos possuam o mesmo conteúdo o retornado será um dos dois.
*
*  $EP Parâmetros
*     *pLista  - Ponteiro para o elemento anterior ao desejado.
*     *pCont  - Ponteiro com o dado a ser procurado.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para o elemento encontrado.
*
*   Assertivas:
*       pLista e pCont não podem ser NULL, caso seja a função retorna NULLL.
***********************************************************************/
CIR_CondRetErro CIR_ProcuraElemento(CIR_lstCircular *pLista,void *pCont);

#endif
