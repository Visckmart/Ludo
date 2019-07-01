//Teste do Modulo Circular.h utilizando o arcabouco de testes
//Autor:THiago Lamenza

#include "GENERICO.h"
#include "TST_ESPC.H"
#include "LERPARM.h"
#include "Circular.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define DIM_VT_LISTA 5
#define DIM_VT_PONTEIROS 5
#define DIM_BUFFER 20
/*Vetor com as listas atuais*/
CIR_lstCircular *Listas[DIM_VT_LISTA];
void *vPonteiros[DIM_VT_PONTEIROS];

/*Condições de retorno de circular*/
 CIR_CondRetErro CondRet;

/*Função de validação de indice do vetor de listas*/
static int ValidaLista(int ind);

/*Função de liberação*/

static void LiberaDado(void *pDado);
    

// Funções aceitas para testar
static char DESTROI[] = "=destroi";
static char INICIA[] = "=inicia";
static char CRIALISTA[] = "=crialista";
static char INSERE[] = "=insere";
static char INSEREPONT[] = "=inserepont";
static char PROXIMO[] = "=proximo";
static char PRECEDENTE[] = "=precedente";
static char CONTEUDO[] = "=conteudo";
static char PROCURA[] = "=procura";
static char REMOVE[] = "=remove";


/***********************
Comandos disponíveis:
=destroi		indLista		ValorEsperado
=crialista		indLista		ValorEsperado
=insere 		StringDados		indLista	ValorEsperado
=inserepont     indLista        indPonteiro	ValorEsperado
=proximo	 	indLista		ValorEsperado
=precedente		indLista		ValorEsperado
=conteudo		indLista		StringDados		ValorEsperado
=procura 		indLista		StringDados		ValorEsperado
=remove			indLista		ValorEsperado
***********************/
TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
{
	int i=-1,indLista=-1,indPonteiro=-1,NumLidos=-1,ValorEsperado=-1,CondRet=-1;
	char StringDados[DIM_BUFFER];
	char *pDado;

	StringDados[0] = 0;

	//Reset teste
	if(strcmp(ComandoTeste,DESTROI)==0)
	{
		NumLidos = LER_LerParametros( "ii" , &indLista, &ValorEsperado ) ;
		if(!ValidaLista(indLista) || NumLidos!=2) return TST_CondRetParm;
		if(ValorEsperado == CIR_CondRetParametro)
		{
			CondRet = CIR_DestroiLista(NULL,LiberaDado);
		}
		else
		{
			CondRet = CIR_DestroiLista(Listas[indLista],LiberaDado);
			Listas[indLista] = NULL;
		}
		return TST_CompararInt(ValorEsperado,CondRet,"Condicao de retorno nao esperada.");
	}
	//Inicializa o teste
	else if(strcmp(ComandoTeste,INICIA)==0) 
	{
		for(i=0;i<DIM_VT_PONTEIROS;i++)
		{
			vPonteiros[i] = (void*)malloc(sizeof(char));
		}
		return TST_CondRetOK;
	}
	//Testar a funcao CriarLista
	else if(strcmp(ComandoTeste,CRIALISTA)==0) 
	{
		NumLidos = LER_LerParametros( "ii" , &indLista, &ValorEsperado ) ;
		if(ValidaLista(indLista) || NumLidos!=2) return TST_CondRetParm;
		if(ValorEsperado == CIR_CondRetParametro)
		{
			CondRet = CIR_CriaLista(NULL);
		}
		else
		{
			CondRet = CIR_CriaLista(&Listas[indLista]);
		}
		
		if(CondRet == CIR_CondRetMemoria) return TST_CondRetMemoria;
		
		return TST_CompararInt(ValorEsperado,CondRet,"Condicao de retorno nao esperada.");
	}
	
	//Testar a funcao insere com ponteiro
	else if(strcmp(ComandoTeste,INSEREPONT)==0) 
	{
		NumLidos = LER_LerParametros( "iii" , &indLista, &indPonteiro, &ValorEsperado ) ;
		if(!ValidaLista(indLista) || NumLidos!=3) return TST_CondRetParm;
		if(ValorEsperado == CIR_CondRetParametro)
		{
			CondRet = CIR_InsereElemento(NULL,NULL);
		}
		else
		{
			CondRet = CIR_InsereElemento(Listas[indLista],vPonteiros[indPonteiro]);
		}
		return TST_CompararInt(ValorEsperado,CondRet,"Condicao de retorno nao esperada.");
	}


	//Testar a funcao InsereElemento
	else if(strcmp(ComandoTeste,INSERE)==0)
	{
		NumLidos = LER_LerParametros("sii",StringDados, &indLista,&ValorEsperado);
		if(!ValidaLista(indLista) || NumLidos!=3) return TST_CondRetParm;
		
		pDado = malloc(strlen(StringDados)+1);

		strcpy(pDado,StringDados);

		if(ValorEsperado==CIR_CondRetParametro)
		{
			CondRet = CIR_InsereElemento(NULL,NULL);
			return TST_CompararInt(CondRet,ValorEsperado,"Deveria ter dado erro no parametro.");
		}
		else
		{
			CondRet = CIR_InsereElemento(Listas[indLista],pDado);
		}
		if(CondRet == CIR_CondRetMemoria) return TST_CondRetMemoria;
		
		return TST_CompararString((char*)CIR_ObterConteudo(Listas[indLista]),StringDados,"Elemento inserido incorretamente");
	}
	
	//Testar a funcao ProximoElemento
	else if(strcmp(ComandoTeste,PROXIMO)==0)
	{
		NumLidos = LER_LerParametros("ii",&indLista,&ValorEsperado);
		if(!ValidaLista(indLista)||NumLidos!=2) return TST_CondRetParm;
		if(ValorEsperado==CIR_CondRetParametro)
		{
			CondRet = CIR_ObterProximoElemento(NULL);
		}
		else
		{
			CondRet = CIR_ObterProximoElemento(Listas[indLista]);
		}
		return TST_CompararInt(CondRet,ValorEsperado,"Resultado nao e o esperado");
	}
	
	//Testar a funcao PrecedenteElemento
	else if(strcmp(ComandoTeste,PRECEDENTE)==0)
	{
		NumLidos = LER_LerParametros("ii",&indLista,&ValorEsperado);
		if(!ValidaLista(indLista)||NumLidos!=2) return TST_CondRetParm;

		if(ValorEsperado==CIR_CondRetParametro)
		{
			CondRet = CIR_ObterPrecedenteElemento(NULL);
		}
		else
		{
			CondRet = CIR_ObterPrecedenteElemento(Listas[indLista]);
		}
		return TST_CompararInt(CondRet,ValorEsperado,"Resultado nao e o esperado");
	}
	
	//Testar a funcao Conteudo
	else if(strcmp(ComandoTeste,CONTEUDO)==0)
	{
		NumLidos = LER_LerParametros("isi",&indLista,StringDados,&ValorEsperado);
		if(!ValidaLista(indLista)||NumLidos!=3) return TST_CondRetParm;

		pDado = CIR_ObterConteudo(Listas[indLista]);

		if(ValorEsperado==1){

			if(pDado==NULL) return TST_CompararPonteiroNulo(1,pDado,"Ponteiro nao deveria ser nulo");

			return TST_CompararString(pDado,StringDados,"Conteudo do elemento incorreto");
		}
		if(ValorEsperado==0)
			return TST_CompararPonteiroNulo(0,pDado,"Nao achou ponteiro nulo quando deveria");

	}
	
	//Testar a funcao RemoveElemento
	else if(strcmp(ComandoTeste,REMOVE)==0)
	{
		NumLidos = LER_LerParametros("ii",&indLista,&ValorEsperado);
		if(!ValidaLista(indLista)||NumLidos!=2) return TST_CondRetParm;

		if(ValorEsperado==CIR_CondRetParametro)
		{
			CondRet = CIR_RemoveElemento(NULL,LiberaDado);
		}
		else
		{
			CondRet = CIR_RemoveElemento(Listas[indLista],LiberaDado);
		}
		return TST_CompararInt(CondRet,ValorEsperado,"Resultado nao e o esperado.");
	}

	//Testar a funcao ProcuraElemento
	else if(strcmp(ComandoTeste,PROCURA)==0)
	{
		NumLidos = LER_LerParametros("iii",&indLista,&indPonteiro,&ValorEsperado);
		if(!ValidaLista(indLista)||NumLidos!=3) return TST_CondRetParm;

		if(ValorEsperado==CIR_CondRetParametro)
		{
			CondRet = CIR_ProcuraElemento(NULL,NULL);
		}
		else
		{
			CondRet = CIR_ProcuraElemento(Listas[indLista],vPonteiros[indPonteiro]);
		}
		return TST_CompararInt(CondRet,ValorEsperado,"Resultado nao e o esperado.");
	}
	
	return 0;
}


/******************************************
Função : Valida indice do vetor de Listas Circulares
******************************************/
int ValidaLista(int ind)
{
	if(ind>DIM_VT_LISTA || Listas[ind]==NULL) return 0;
	else return 1;
}

void LiberaDado(void *pDado)
{
	free(pDado);
}
