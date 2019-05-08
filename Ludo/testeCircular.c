//Teste do Modulo Circular.h utilizando o arcabouco de testes

#include "GENERICO.h"
#include "LERPARM.h"
#include "Circular.h"
#include <string.h>
#include <stdio.h>

#define DIM_VT_LISTA 5
#define DIM_BUFFER 20
/*Vetor com as listas atuais*/
CIR_lstCircular *Listas[DIM_VT_LISTA];

/*Condições de retorno de circular*/
 CIR_CondRetErro CondRet;

/*Função de validação de indice do vetor de listas*/
static int ValidaLista(int ind);

/*Função dummy de liberação*/
/*Como as strings são compartilhadas entre as listas elas não podem ser liberadas ao remover elementos*/
static void LiberaDado(void *pDado);
    

// Funções aceitas para testar
static char RESETA[] = "=reseta";
static char CRIALISTA[] = "=crialista";
static char INSERE[] = "=insere";
static char PROXIMO[] = "=proximo";
static char PRECEDENTE[] = "=precedente";
static char CONTEUDO[] = "=conteudo";
static char REMOVE[] = "=remove";
static char PROCURA[] = "=procura";


/***********************
Comandos disponíveis:
=reseta
=crialista		StringDados		indLista
=insere 		StringDados		indLista
=proximo	 	indLista
=precedente		indLista
=conteudo		indLista		StringDados
=remove			indLista
=procura		StringDados		indLista	ValorEsperado
***********************/
TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
{
	int i,indLista=-1,NumLidos=-1,ValorEsperado=-1;
	char StringDados[DIM_BUFFER];
	
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
		
		CondRet = CIR_InsereElemento(Listas[indLista],StringDados);
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

		if(ValorEsperado==1)
			return TST_CompararString(CIR_Conteudo(Listas[indLista]),StringDados,"Conteudo do elemento incorreto");

		if(ValorEsperado==0)
			return TST_CompararPonteiroNulo(0,CIR_Conteudo(Listas[indLista]),"Nao achou ponteiro nulo quando deveria");
	}
	
	//Testar a funcao RemoveElemento
	else if(strcmp(ComandoTeste,REMOVE)==0)
	{
		NumLidos = LER_LerParametros("i",&indLista);
		if(!ValidaLista(indLista)||NumLidos!=1) return TST_CondRetParm;

		CIR_RemoveElemento(Listas[indLista],LiberaDado);
		return TST_CondRetOK;
	}
	
	//Testar a funcao ProcuraElemento
	else if(strcmp(ComandoTeste,PROCURA)==0)
	{
		NumLidos = LER_LerParametros("sii",StringDados,&indLista,&ValorEsperado);
		if(!ValidaLista(indLista)||NumLidos!=3) return TST_CondRetParm;
		CondRet = CIR_ProcuraElemento(Listas[indLista],StringDados);

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
    return;
}
