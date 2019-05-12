//Teste do Modulo Circular.h utilizando o arcabouco de testes

#include "GENERICO.h"
#include "TST_ESPC.H"
#include "LERPARM.h"
#include "Circular.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define DIM_VT_LISTA 5
#define DIM_BUFFER 20
/*Vetor com as listas atuais*/
CIR_lstCircular *Listas[DIM_VT_LISTA];

/*Condições de retorno de circular*/
 CIR_CondRetErro CondRet;

/*Função de validação de indice do vetor de listas*/
static int ValidaLista(int ind);

/*Função de liberação*/

static void LiberaDado(void *pDado);
    

// Funções aceitas para testar
static char RESETA[] = "=reseta";
static char CRIALISTA[] = "=crialista";
static char INSERE[] = "=insere";
static char PROXIMO[] = "=proximo";
static char PRECEDENTE[] = "=precedente";
static char CONTEUDO[] = "=conteudo";
static char REMOVE[] = "=remove";


/***********************
Comandos disponíveis:
=reseta
=crialista		indLista
=insere 		StringDados		indLista
=proximo	 	indLista		ValorEsperado
=precedente		indLista		ValorEsperado
=conteudo		indLista		StringDados		ValorEsperado
=remove			indLista		ValorEsperado
***********************/
TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
{
	int i,indLista=-1,NumLidos=-1,ValorEsperado=-1;
	char StringDados[DIM_BUFFER];
	char *pDado;

	StringDados[0] = 0;

	//Reset teste
	if(strcmp(ComandoTeste,RESETA)==0)
	{
		for(i=0;i<DIM_VT_LISTA;i++)
		{
			if(ValidaLista(i)) CIR_DestroiLista(Listas[i],LiberaDado);
			Listas[i] = NULL;
		}
		return TST_CondRetOK;
	}

	//Testar a funcao CriarLista
	else if(strcmp(ComandoTeste,CRIALISTA)==0) 
	{
		NumLidos = LER_LerParametros( "i" , &indLista ) ;
		if(ValidaLista(indLista) || NumLidos!=1) return TST_CondRetParm;
		Listas[indLista] = CIR_CriaLista();
		if(Listas[indLista] == NULL) return TST_CondRetMemoria;
		
		return TST_CondRetOK;
	}
	
	//Testar a funcao InsereElemento
	else if(strcmp(ComandoTeste,INSERE)==0)
	{
		NumLidos = LER_LerParametros("si",StringDados, &indLista);
		if(!ValidaLista(indLista) || NumLidos!=2) return TST_CondRetParm;
		
		pDado = malloc(strlen(StringDados)+1);

		strcpy(pDado,StringDados);

		CondRet = CIR_InsereElemento(Listas[indLista],pDado);
		if(CondRet == CIR_CondRetMemoria) return TST_CondRetMemoria;
		return TST_CompararString((char*)CIR_Conteudo(Listas[indLista]),StringDados,"Elemento inserido incorretamente");
	}
	
	//Testar a funcao ProximoElemento
	else if(strcmp(ComandoTeste,PROXIMO)==0)
	{
		NumLidos = LER_LerParametros("ii",&indLista,&ValorEsperado);
		if(!ValidaLista(indLista)||NumLidos!=2) return TST_CondRetParm;

		return TST_CompararInt(CIR_ProximoElemento(Listas[indLista]),ValorEsperado,"Resultado nao e o esperado");
	}
	
	//Testar a funcao PrecedenteElemento
	else if(strcmp(ComandoTeste,PRECEDENTE)==0)
	{
		NumLidos = LER_LerParametros("ii",&indLista,&ValorEsperado);
		if(!ValidaLista(indLista)||NumLidos!=2) return TST_CondRetParm;

		
		return TST_CompararInt(CIR_PrecedenteElemento(Listas[indLista]),ValorEsperado,"Resultado nao e o esperado");
	}
	
	//Testar a funcao Conteudo
	else if(strcmp(ComandoTeste,CONTEUDO)==0)
	{
		NumLidos = LER_LerParametros("isi",&indLista,StringDados,&ValorEsperado);
		if(!ValidaLista(indLista)||NumLidos!=3) return TST_CondRetParm;

		pDado = CIR_Conteudo(Listas[indLista]);

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

		return TST_CompararInt(CIR_RemoveElemento(Listas[indLista],LiberaDado),ValorEsperado,"Resultado nao e o esperado.");
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
