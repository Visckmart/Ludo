//Teste do Modulo Circular.h utilizando o arcabouco de testes

#include "GENERICO.h"
#include "LERPARM.h"
#include "Circular.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define DIM_VT_LISTA 5
#define DIM_BUFFER 20
// Ponteiro para as listas atuais e funcao de validacao de indice
CIR_lstCircular *Listas[DIM_VT_LISTA];
static int ValidaLista(int ind);


// Funções aceitas para testar
static char RESETA[] = "=reseta";
static char CRIALISTA[] = "=crialista";
static char INSERE[] = "=insere";
static char PROXIMO[] = "=proximo";
static char PRECEDENTE[] = "=precedente";
static char CONTEUDO[] = "=conteudo";
static char REMOVE[] = "=remove";
static char PROCURA[] = "=procura";



TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
{
	int i,indLista=-1,NumLidos=-1,ValorEsperado=-1;
	void *pDado;
	char StringDados[DIM_BUFFER];
	
	//Reset teste
	if(strcmp(ComandoTeste,RESETA)==0)
	{
		for(i=0;i<DIM_VT_LISTA;i++)
		{
			if(ValidaLista(i)) CIR_DestroiLista(Listas[i]);
			Listas[i] = NULL;
		}
		return TST_CondRetOK;
	}
	
	//Testar a funcao CriarLista
	else if(strcmp(ComandoTeste,CRIALISTA)==0) 
	{
		NumLidos = LER_LerParametros( "si" , StringDados , &indLista ) ;
		if(ValidaLista(indLista) || NumLidos!=2) return TST_CondRetParm;
		Listas[indLista] = CIR_CriaLista(StringDados);
		if(Listas[indLista] == NULL) return TST_CondRetMemoria;
		
		return TST_CompararString(CIR_Conteudo(Listas[indLista]),StringDados,"Conteudo do elemento incorreto.");
	}
	
	//Testar a funcao InsereElemento
	else if(strcmp(ComandoTeste,INSERE)==0)
	{
		NumLidos = LER_LerParametros("si",StringDados, &indLista);
		if(!ValidaLista(indLista) || NumLidos!=2) return TST_CondRetParm;
		
		Listas[indLista] = CIR_InsereElemento(Listas[indLista],StringDados);
		if(Listas[indLista]==NULL) return TST_CondRetMemoria;
		
		return TST_CompararString(CIR_Conteudo(Listas[indLista]),StringDados,"Elemento inserido incorretamente");
	}
	
	//Testar a funcao ProximoElemento
	else if(strcmp(ComandoTeste,PROXIMO)==0)
	{
		NumLidos = LER_LerParametros("i",&indLista);
		if(!ValidaLista(indLista)||NumLidos!=1) return TST_CondRetParm;
		
		Listas[indLista] = CIR_ProximoElemento(Listas[indLista]);
		return TST_CondRetOK;
	}
	
	//Testar a funcao PrecedenteElemento
	else if(strcmp(ComandoTeste,PRECEDENTE)==0)
	{
		NumLidos = LER_LerParametros("i",&indLista);
		if(!ValidaLista(indLista)||NumLidos!=1) return TST_CondRetParm;
		
		Listas[indLista] = CIR_ProximoElemento(Listas[indLista]);
		return TST_CondRetOK;
	}
	
	//Testar a funcao Conteudo
	else if(strcmp(ComandoTeste,CONTEUDO)==0)
	{
	NumLidos = LER_LerParametros("is",&indLista,StringDados);
	if(!ValidaLista(indLista)||NumLidos!=2) return TST_CondRetParm;	
	
	return TST_CompararString(CIR_Conteudo(Listas[indLista]),StringDados,"Conteudo do elemento incorreto");
	}
	
	//Testar a funcao RemoveElemento
	else if(strcmp(ComandoTeste,REMOVE)==0)
	{
	NumLidos = LER_LerParametros("i",&indLista);
	if(!ValidaLista(indLista)||NumLidos!=1) return TST_CondRetParm;
	
	Listas[indLista] = CIR_RemoveElemento(Listas[indLista]);
	printf("%c",CIR_Conteudo(Listas[indLista]));
	return TST_CondRetOK;
	}
	
	//Testar a funcao ProcuraElemento
	else if(strcmp(ComandoTeste,PROCURA)==0)
	{
		NumLidos = LER_LerParametros("sii",StringDados,&indLista,&ValorEsperado);
		if(!ValidaLista(indLista)||NumLidos!=2) return TST_CondRetParm;
		pDado = CIR_ProcuraElemento(Listas[indLista],StringDados);
		if(ValorEsperado == 0)
		{
			return TST_CompararPonteiroNulo(ValorEsperado,pDado,"Valor nao deveria existir");
		}
		else if(pDado==NULL)
		{
			return TST_CondRetErro;
		}
		return TST_CompararPonteiro(CIR_Conteudo(pDado),StringDados,"Elemento achado nao e o procurado.");
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
