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
*     Toda lista é identificada por um ponteiro que representa sua cabeça.
*     Todo elemento da lista pode ser acessado por essa cabeça, um elemento é denominado como corrente.
*     Esse ponteiro é usado para todas as operações da lista.
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
*     Cria uma lista genérica circular vazia.
*     Os possíveis tipos são desconhecidos a priori.
*     A tipagem deles é implicita.
*
*  $EP Parâmetros
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para a cabeça da lista.
*
*     Esse ponteiro será usado para todas as outras funções do módulo.
*
*   Assertivas:
*       Retorna NULL caso haja um erro na alocação de memória.
***********************************************************************/
CIR_lstCircular *CIR_CriaLista();

/***********************************************************************
*
*  $FC Função: CIR  &DestroiLista
*
*  $ED Descrição da função
*     Percorre e libera todos os elementos de uma lista. 
*
*     A liberação dos dados contidos pela lista serão feitas pela função fornecida pelo cliente.
*
*
*  $EP Parâmetros
*     *pLista  - ponteiro para a lista.
*     *RemoveDado - Ponteiro para uma função encarregada de liberar o dado contido no elemento.
*  $FV Valor retornado
*     A função retorna CondRetOk em caso de sucesso
*
*   Assertivas:
*       pLista não pode ser NULL, caso seja a função retorna CondRetParametro.
***********************************************************************/
CIR_CondRetErro CIR_DestroiLista(CIR_lstCircular *pLista,void (*RemoveDado)(void*));

/***********************************************************************
*
*  $FC Função: CIR  &Conteudo
*
*  $ED Descrição da função
*     Retorna o dado contido pelo elemento corrente da lista.
*
*  $EP Parâmetros
*     *pLista  - Ponteiro para a lista.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para o dado contido no elemento corrente.
*
*
*   Assertivas:
*       pLista não pode ser NULL, caso seja a função retorna NULL.
*       pLista não pode ser vazia, caso seja retorna NULL.
***********************************************************************/
void *CIR_Conteudo(CIR_lstCircular *pLista);

/***********************************************************************
*
*  $FC Função: CIR  &InsereElemento
*
*  $ED Descrição da função
*     Insere um elemento na lista circular depois do elemento passsado como parâmetro.
*     O elemento corrente passa a ser o inserido.
*
*  $EP Parâmetros
*     *pLista  - Ponteiro para a lista.
      *pCont   - Ponteiro para o dado a ser contido no novo elemento.
*
*  $FV Valor retornado
*     Se executou corretamente retorna CondRetOk.
*
*   Assertivas:
*       pLista e pCont não podem ser NULL, caso seja a função CondRetParametro.
***********************************************************************/
CIR_CondRetErro CIR_InsereElemento(CIR_lstCircular *pLista,void *pCont);

/***********************************************************************
*
*  $FC Função: CIR  &RemoveElemento
*
*  $ED Descrição da função
*     Remove o elemento corrente da lista circular liberando-o e o dado contido nele.
*     O dado contido pelo elemento a ser removido será liberado utilizando a função fornecida pelo cliente.
*       
*
*  $EP Parâmetros
*     *pCont  - Ponteiro para a lista.
*     *RemoveDado - Ponteiro para a função encarregada de liberar o dado contido no elemento.
*  $FV Valor retornado
*     Retorna CondRetOk em caso de sucesso.
*
*   Assertivas:
*       pLista não pode ser NULL, caso seja a função retorna CondRetParametro.
*       A lista não pode ser vazia, caso seja retorna CondRetListaVazia.
***********************************************************************/
CIR_CondRetErro CIR_RemoveElemento(CIR_lstCircular *pLista,void (*RemoveDado)(void*));

/***********************************************************************
*
*  $FC Função: CIR  &ProximoElemento
*
*  $ED Descrição da função
*     Avança para o elemento corrente para o proximo elemento da lista circular.
*
*  $EP Parâmetros
*     *pLista  - Ponteiro para a lista.
*
*  $FV Valor retornado
*     Se executou corretamente retorna CondRetOk.
*
*   Assertivas:
*       pLista não pode ser NULL, caso seja a função retorna CondRetParametro.
*       A lista não pode ser vazia, caso seja a função retorna CondRetListaVazia.
***********************************************************************/
CIR_CondRetErro CIR_ProximoElemento(CIR_lstCircular *pLista);

/***********************************************************************
*
*  $FC Função: CIR  &PrecedenteElemento
*
*  $ED Descrição da função
*     Retorna o elemento corrente para seu precessor.
*
*  $EP Parâmetros
*     *pLista  - Ponteiro para a lista.
*
*  $FV Valor retornado
*     Se executou corretamente retorna CondRetOk.
*
*   Assertivas:
*       pLista não pode ser NULL, caso seja a função retorna CondRetParametro.
*       A lista não pode ser vazia, caso seja a função retorna CondRetListaVazia.
***********************************************************************/
CIR_CondRetErro CIR_PrecedenteElemento(CIR_lstCircular *pLista);

/***********************************************************************
*
*  $FC Função: CIR  &ProcuraElemento
*
*  $ED Descrição da função
*     Procura um elemento na lista circular contendo um dado passado como parâmetro.
*     Caso dois elementos possuam o mesmo conteúdo o retornado será um dos dois.
*     Avança o elemento corrente para o elemento encontrado.
*
*  $EP Parâmetros
*     *pLista  - Ponteiro para a lista.
*     *pCont  - Ponteiro com o dado a ser procurado.
*
*  $FV Valor retornado
*     Se encontrou corretamente retorna CondRetOk, caso contrário retorna CondRetNaoAchou.
*
*   Assertivas:
*       pLista e pCont não podem ser NULL, caso seja a função retorna CondRetParametro.
*       pLista não pode ser vazia, caso seja retorna CondRetListaVazia
***********************************************************************/
CIR_CondRetErro CIR_ProcuraElemento(CIR_lstCircular *pLista,void *pCont);

#endif
