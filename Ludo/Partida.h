#if ! defined( PARTIDA_ )
    #define PARTIDA_

/***************************************************************************
 *
 *  $MCD Módulo de definição: PAR  Partida
 *
 *  Arquivo gerado:              Partida.h
 *  Letras identificadoras:      PAR
 *
 *
 *  Projeto: INF1301 / Ludo
 *  Autores: Victor Martins,Thiago Lamenza, Guilherme Murad
 *
 *  $HA Histórico de evolução:
 *     Versão  Autor             Data         Observações
 *     1       Thiago Lamenza    14/jun/2019  Desenvolvimento inicial
 *
 *
 *  $ED Descrição do módulo
 *     Implementa o módulo controlador da partidaz de Ludo.
 *
 *     O módulo é responsável por iniciar, executar e finalizar uma partida de Ludo.
 *
 ***************************************************************************/

/***********************************************************************
*
*  $TC Tipo de dados: PAR Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções de Partida
*
***********************************************************************/
typedef enum{

	PAR_CondRetOk,
	/*Concluiu corretamente*/

	PAR_CondRetParametro,
	/*Erro nos parametros*/

	PAR_CondRetMemoria,
	/*Erro de memoria*/
	
	PAR_CondRetSemEscolha,
	/*Não existe uma escolha*/

	PAR_CondRetTerminou
	/*Partida terminou*/

}PAR_CondRet;

/***********************************************************************	
*	
*  $FC Função: PAR  &PAR_Inicia
*	
*  $ED Descrição da função	
*     Inicia e executa uma partida.
*     Essa é a única função exportada pelo módulo controlador, ela é capaz de iniciar, executar e finalizar uma partida inteira.
*
*  $FV Valor retornado	
*     Se executou corretamente retorna PAR_CondRetOk.

*   Assertivas:	
*   Retorna PAR_CondRetMemoria se houve um erro de memória na execução.
***********************************************************************/	
PAR_CondRet PAR_Inicia();

#endif /* PARTIDA_ */
