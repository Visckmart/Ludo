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

void PAR_Finaliza();
PAR_CondRet PAR_ExecutaRodada(int turno);
