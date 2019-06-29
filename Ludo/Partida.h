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
*     Inicia
*
*  $FV Valor retornado	
*     Se executou corretamente retorna PAR_CondRetOk.
*     Pode retornar PAR_CondRetMemoria, caso não alguma alocação não pôde ser concluída.
*
***********************************************************************/	
PAR_CondRet PAR_Inicia();
