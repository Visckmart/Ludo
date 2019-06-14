#if ! defined( CIRCULAR_ )
    #define CIRCULAR_
/***************************************************************************
*
*  $MCD Módulo de definição: CIR  Lista Circular
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
*     Os ponteiros são copiados mas não os valores apontados pelos mesmos.
*
*     Toda lista é identificada por um ponteiro para sua cabeça.
*     Todo elemento da lista pode ser acessado pela cabeça.
*     Basta saber o ponteiro para a cabeça da lista para executar qualquer operação nela.
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
	/* Parâmetro nulo */

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
*	  A cabeça para a lista é colocada no ponteiro passado por referência.
*
*  $EP Parâmetros
*	  *pResultado - Ponteiro para o resultado passado por referência.
*  $FV Valor retornado
*     Se executou corretamente retorna CIR_CondRetOk.
*
*     Esse ponteiro será usado para todas as outras funções do módulo.
*
*   Assertivas:
*   Se pResultado passado for nulo retorna CIR_CondRetParametro.
*	Caso haja erro de alocação retorna CIR_CondRetMemoria.
***********************************************************************/
CIR_CondRetErro CIR_CriaLista(CIR_lstCircular **pResultado);


/***********************************************************************
*
*  $FC Função: CIR  &DestroiLista
*
*  $ED Descrição da função
*     Percorre e libera todos os elementos de uma lista e depois sua cabeça.
*
*     A liberação dos dados contidos pela lista serão feitas pela função fornecida pelo cliente.
*
*
*  $EP Parâmetros
*     *pLista  - ponteiro para a cabeça da lista.
*     *RemoveDado - Ponteiro para uma função encarregada de liberar o dado contido no elemento.
*
*  $FV Valor retornado
*     A função retorna CIR_CondRetOk caso execute corretamente.
*
*   Assertivas:
*       pLista não pode ser NULL, caso seja a função retorna CIR_CondRetParametro.
***********************************************************************/
CIR_CondRetErro CIR_DestroiLista(CIR_lstCircular *pLista,void (*RemoveDado)(void*));

/***********************************************************************
*
*  $FC Função: CIR  &Conteudo
*
*  $ED Descrição da função
*     Retorna o conteúdo do elemento corrente da lista.
*
*  $EP Parâmetros
*     *pLista  - Ponteiro para a cabeça da lista.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para o conteúdo.
*
*   Assertivas:
*       pLista não pode ser NULL, caso seja a função retorna NULL.
***********************************************************************/
void *CIR_ObterConteudo(CIR_lstCircular *pLista);

/***********************************************************************
*
*  $FC Função: CIR  &InsereElemento
*
*  $ED Descrição da função
*     Insere um elemento na lista circular depois do elemento corrente.
*
*  $EP Parâmetros
*     *pLista  - Ponteiro para a cabeça da lista.
      *pCont   - Ponteiro para o conteúdo do elemento a ser inserido.
*
*  $FV Valor retornado
*     Se executou corretamente retorna CIR_CondRetOk.
*
*   Assertivas:
*       pLista e pCont não podem ser NULL, caso seja a função retorna CIR_CondRetParametro.
*       Caso haja erro na alocaçao retorna CIR_CondRetMemoria.
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
*     *pCont  - Ponteiro para a cabeça da lista.
*     *RemoveDado - Ponteiro para a função encarregada de liberar o dado contido no elemento.
*  $FV Valor retornado
*     Retorna CIR_CondRetOk caso execute corretamente.
*
*   Assertivas:
*       pLista não pode ser NULL, caso seja a função retorna CIR_CondRetParametro.
*       Caso a lista pLista seja vazia retorna CIR_CondRetListaVazia.
***********************************************************************/
CIR_CondRetErro CIR_RemoveElemento(CIR_lstCircular *pLista,void (*RemoveDado)(void*));

/***********************************************************************
*
*  $FC Função: CIR  &ProximoElemento
*
*  $ED Descrição da função
*     Avança o elemento corrente para o proximo elemento da lista circular.
*
*  $EP Parâmetros
*     *pLista  - Ponteiro para a cabeça da lista.
*
*  $FV Valor retornado
*     Se executou corretamente retorna CIR_CondRetOk.
*
*   Assertivas:
*       pLista não pode ser NULL, caso seja a função retorna CIR_CondRetParametro
*       Se pLista é vazia retorna CIR_CondRetListaVazia
***********************************************************************/
CIR_CondRetErro CIR_ObterProximoElemento(CIR_lstCircular *pLista);

/***********************************************************************
*
*  $FC Função: CIR  &PrecedenteElemento
*
*  $ED Descrição da função
*     Volta o elemento corrente para o elemento precessor da lista.
*
*  $EP Parâmetros
*     *pLista  - Ponteiro para a cabeça da lista.
*
*  $FV Valor retornado
*     Se executou corretamente retorna CIR_CondRetOk.
*
*   Assertivas:
*       pLista não pode ser NULL, caso seja a função retorna CIR_CondRetParametro
*       Se pLista é vazia retorna CIR_CondRetListaVazia
***********************************************************************/
CIR_CondRetErro CIR_ObterPrecedenteElemento(CIR_lstCircular *pLista);

/***********************************************************************
*
*  $FC Função: CIR  &ProcuraElemento
*
*  $ED Descrição da função
*     Procura um elemento na lista circular contendo um dado passado como parâmetro.
*     Caso dois elementos possuam o mesmo conteúdo encontrado será um dos dois.
*     O elemento corrente passa a ser o elemento encontrado.
*
*  $EP Parâmetros
*     *pLista  - Ponteiro para a cabeça da lista.
*     *pCont  - Ponteiro com o dado a ser procurado.
*
*  $FV Valor retornado
*     Se achar corretamente retorna CIR_CondRetOk. Se não achar retorna CIR_CondRetNaoAchou.
*
*   Assertivas:
*       pLista e pCont não podem ser NULL, caso seja a função retorna CIR_CondRetParametro.
*       pLista não pode ser vazia, caso seja retorna CIR_CondRetListaVazia.
***********************************************************************/
CIR_CondRetErro CIR_ProcuraElemento(CIR_lstCircular *pLista,void *pCont);

#endif
