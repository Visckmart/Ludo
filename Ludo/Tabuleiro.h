#if ! defined( TABULEIRO_ )
#define TABULEIRO_
/***************************************************************************
*
*  $MCD Módulo de definição: TAB  Tabuleiro
*
*  Arquivo gerado:              Tabuleiro.h
*  Letras identificadoras:      TAB
*
*
*  Projeto: INF 1301 / Ludo
*  Autores: Thiago de Souza Lamenza
*
*  $HA Histórico de evolução:
*     Versão  Autor             Data        Observações
*     1       Thiago Lamenza   03/mai/2019  Desenvolvimento inicial
*
*
*  $ED Descrição do módulo
*     Implementa o tabuleiro do jogo Ludo
*
*     O módulo cria e administra uma copia do tabuleiro.
*     O módulo não é capaz de administrar mais de um tabuleiro.
*
*     O tabuleiro tem 52 casas no campo de jogo principal e 4 retas finais com 5 casas cada.
*     Os jogadores não são armazenados em tabuleiro, apenas peças.
*
*     As funções do tabuleiro validam a jogada antes de faze-la e não executa se a jogada não for válida.
***************************************************************************/

/***********************************************************************
*
*  $TC Tipo de dados: TAB Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções de Tabuleiro
*
***********************************************************************/
typedef enum{

	TAB_CondRetOk,
	/*Concluir corretamente*/

	TAB_CondRetParametro,
	/*Erro nos parametros*/

	TAB_CondRetMemoria,
	/*Erro de memoria*/

	TAB_CondRetNaoAndou,
	/*Não executou a jogada e a peça permanece no mesmo lugar*/

	TAB_CondRetSemEspaco,
	/*Não tem espaço para inserção*/

	TAB_CondRetCasaVazia,
	/*Não existe nada para remover*/

	TAB_CondRetChegouFinal
	/*Peca chegou ao final do tabuleiro*/

}TAB_CondRet;

/**************************************
*
* $TC Tipo de dados: TAB Casa
*
***************************************/
typedef struct casa TAB_tpCasa;

/**************************************
*
* $TC Tipo de dados: TAB Tabuleiro
*
***************************************/
typedef struct tabuleiro TAB_tpTabuleiro;

/***********************************************************************
*
*  $FC Função: TAB  &IniciaTabuleiro
*
*  $ED Descrição da função
*     Deve ser a primeira função executada no módulo.
*     Inicia o tabuleiro de Ludo com todas suas casas.
*     Caso já exista um ele será destruido.
*
*  $EP Parâmetros
*
*  $FV Valor retornado
*     Se executou corretamente retorna TAB_CondRetOk.
*
*   Assertivas:
*      Caso haja erro de memódia retorna TAB_CondRetMemoria.
***********************************************************************/
TAB_CondRet TAB_IniciaTabuleiro();


/***********************************************************************
*
*  $FC Função: TAB  &FazJogada
*
*  $ED Descrição da função
*     Avalia e executa uma jogada, andando com uma peça e comendo peças inimigas se necessário.
*     Caso a jogada não seja válida a peça permanece no mesmo lugar.
*
*  $EP Parâmetros
*	  peca - Ponteiro para a peça a ser movida.
*	  dado - Valor inteiro tirado no dado.
*  $FV Valor retornado
*     Se executou corretamente retorna TAB_CondRetOk.
*     Se a peça chegou ao final do tabuleiro retorna TAB_CondRetChegouFinal.
*
*   Assertivas:
*      Caso a jogada seja invalida retorna TAB_CondRetNaoAndou.
*      Caso peca seja NULL ou dado seja menor que 1 retorna TAB_CondRetParametro.
***********************************************************************/
TAB_CondRet TAB_FazJogada(void *peca,int dado);


/***********************************************************************
*
*  $FC Função: TAB  &PoePecaNoJogo
*
*  $ED Descrição da função
*     Adiciona uma nova peca no tabuleiro.
*     A peça é adicinado no local de inicio correspondente a sua cor.
*     Pode acontecer de comer uma peca inimiga caso esteja no caminho.
*     A peça não é inserida caso haja obstrução na casa de inserção.
*
*  $EP Parâmetros
*	  peca - Ponteiro para a peça a ser inserida.
*  $FV Valor retornado
*     Se executou corretamente retorna TAB_CondRetOk.
*
*   Assertivas:
*      Caso a casa de inserção esteja obstruida retorna TAB_CondRetSemEspaco.
*      Caso peca seja NULL retorna TAB_CondRetParametro.
***********************************************************************/
TAB_CondRet TAB_PoePecaNoJogo(void *peca);

/***********************************************************************
*
*  $FC Função: TAB  &DestroiTabuleiro
*
*  $ED Descrição da função
*     Destroi completamente o tabuleiro.
*     Não libera as peças contidas no tabuleiro, somente o tabuleiro em sí.
*
*  $EP Parâmetros

*  $FV Valor retornado
*     Se executou corretamente retorna TAB_CondRetOk.
*
*   Assertivas:
*      Caso Tabuleiro não exista, somente retorna TAB_CondRetOk.
***********************************************************************/
TAB_CondRet TAB_DestroiTabuleiro();


#endif /* Tabuleiro_h */
