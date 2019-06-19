typedef enum{

	PAR_CondRetOk,
	/*Concluiu corretamente*/

	PAR_CondRetParametro,
	/*Erro nos parametros*/

	PAR_CondRetMemoria,
	/*Erro de memoria*/
	
	PAR_CondRetSemEscolha
	/*Não existe uma escolha*/

}PAR_CondRet;