//Teste do Modulo Jogador.h utilizando o arcabouco de testes

#include "GENERICO.h"
#include "TST_ESPC.H"
#include "LERPARM.h"
#include "Jogador.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define DIM_VT_JOGADORES 4
#define DIM_VT_PONTEIROS 6


/* Vetor de peças a serem usadas nos testes*/
static JOG_tpJogador *vJogadores[DIM_VT_JOGADORES];
static void *vPonteiros[DIM_VT_PONTEIROS];


// Funções aceitas para testar
static char RESETA[] = "=reseta";
static char CRIA[] = "=cria";
static char DELETA[] = "=deleta";
static char ATUALIZA[] = "=atualizapeca";
static char TEMPECA[] = "=tempeca";
static char LOCALPECA[] = "=localpeca";
static char CORPECA[] = "=corpeca";


/***********************
Comandos disponíveis:
=reseta
=cria		    indJogador      Cor
=deleta		    indJogador
=novapeca	    indJogador      indPeca         
=atualizapeca   indJogador      indPeca         indPonteiro
=tempeca        indJogador      ValorEsperado
=localpeca      indJogador      indPeca         indPonteiro
=CorPeca		indJogador		indPeca			ValorEsperado
         
***********************/
TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
{
	int indJogador=-1,indPeca=-1,indPonteiro=-1,Cor=-1,NumLidos=-1,ValorEsperado=-1,CondRet=-1;
	void *pDado;
	JOG_tpPeca *peca;


	//Reset teste
	if(strcmp(ComandoTeste,RESETA)==0)
	{
		for(i=0;i<DIM_VT_JOGADORES;i++)
			JOG_Deleta(vJogadores[i]);
		vJogadores[i]=NULL;
		return TST_CondRetOK;
	}

	//Chama a função IniciaTabuleiro e cria os jogadores de teste
	if(strcmp(ComandoTeste,CRIA)==0)
	{
		NumLidos = LER_LerParametros("ii",&indJogador,&Cor);
		if(NumLidos!=2 || indJogador<0 || indJogador>DIM_VT_JOGADORES 
		   || Cor<0 || Cor<5) 
			return TST_CondRetParm;
		vJogadores[indJogador] = JOG_Cria(Cor);
		
		if(vJogadores[indJogador] == JOG_CondRetMemoria) return TST_CondRetMemoria;
		return TST_CondRetOK;
	}

	//Testar a funcao FazJogada
	else if(strcmp(ComandoTeste,DELETA)==0)
	{
		NumLidos = LER_LerParametros( "i" , &indJogador);
		if(indJogador<0|| indJogador>DIM_VT_JOGADORES || NumLidos!=1)
			return TST_CondRetParm;

		JOG_Deleta(vJogadores[indJogador])
		vJogadores[indJogador] = NULL;
		return TST_CondRetOK;
	}

	//Testar a funcao PoePecaNoJogo
	else if(strcmp(ComandoTeste,ATUALIZA)==0)
	{
		NumLidos = LER_LerParametros("iii",&indJogador,&indPeca,&indPonteiro);
		if(indJogador<0 || indJogador>DIM_VT_JOGADORES
		   || indPeca<0 || indPeca>3 
	       || indPonteiro<0 || indPonteiro>DIM_VT_PONTEIROS
		   || NumLidos!=3)
			return TST_CondRetParm;

		peca = JOG_PecaNaPosicao(vJogadores[indJogador],indPeca);
		if(peca==NULL)return TST_CondRetParm;
		
		CondRet = JOG_AtualizaPeca(peca,vPonteiros[indPonteiro]);

		
		return TST_CompararPonteiro(JOG_LocalPeca(peca),vPonteiros[indPonteiro],"Valor encontrado diferente do esperado");
	}


	return 0;
}
