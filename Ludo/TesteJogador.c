//Teste do Modulo Jogador.h utilizando o arcabouco de testes
//Autor: Thiago Lamenza

#include "GENERICO.h"
#include "TST_ESPC.H"
#include "LERPARM.h"
#include "Jogador.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/*Dimensão dos vetores*/
#define DIM_VT_JOGADORES 4
#define DIM_VT_PONTEIROS 6


/* Vetor de peças a serem usadas nos testes*/
static JOG_tpJogador *vJogadores[DIM_VT_JOGADORES];
static void *vPonteiros[DIM_VT_PONTEIROS];


/*Funções aceitas para testar*/
static char RESETA[] = "=reseta";
static char INICIA[] = "=inicia";
static char CRIA[] = "=cria";
static char DELETA[] = "=deleta";
static char ATUALIZA[] = "=atualizapeca";
static char TEMPECA[] = "=tempeca";
static char LOCALPECA[] = "=localpeca";
static char CORPECA[] = "=corpeca";


/***********************
Comandos disponíveis:
=reseta
=inicia
=cria		    indJogador      Cor
=deleta		    indJogador
=atualizapeca   indJogador      indPeca         indPonteiro
=tempeca        indJogador      valorEsperado
=localpeca      indJogador      indPeca         indPonteiro		valorEsperado
=corpeca		indJogador		indPeca			valorEsperado
         
***********************/

TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
{
	int i,indJogador=-1,indPeca=-1,indPonteiro=-1,Cor=-1,numLidos=-1,valorEsperado=-1;
	JOG_tpPeca *peca;


	//Reset teste
	if(strcmp(ComandoTeste,RESETA)==0)
	{
		for(i=0;i<DIM_VT_JOGADORES;i++)
			JOG_Deleta(vJogadores[i]);
		vJogadores[i]=NULL;
		return TST_CondRetOK;
	}

	//Inicia o teste setando os vetores
	if(strcmp(ComandoTeste,INICIA)==0)
	{
		for(i=0;i<DIM_VT_PONTEIROS;i++)
			vPonteiros[i] = (void*) malloc(sizeof(void*));

		return TST_CondRetOK;
	}

	//Chama a função IniciaTabuleiro e cria os jogadores de teste além de criar o vetor de ponteiros teste.
	if(strcmp(ComandoTeste,CRIA)==0)
	{
		numLidos = LER_LerParametros("ii",&indJogador,&Cor);
		if(numLidos!=2 || indJogador<0 || indJogador>DIM_VT_JOGADORES
		   || Cor<0 || Cor>=5)
			return TST_CondRetParm;
		vJogadores[indJogador] = JOG_Cria(Cor);
		
		if(vJogadores[indJogador] == NULL) return TST_CondRetMemoria;
		return TST_CondRetOK;
	}

	//Testar a funcao FazJogada
	else if(strcmp(ComandoTeste,DELETA)==0)
	{
		numLidos = LER_LerParametros( "i" , &indJogador);
		if(indJogador<0|| indJogador>DIM_VT_JOGADORES || numLidos!=1)
			return TST_CondRetParm;
		if(vJogadores[indJogador]==NULL) return TST_CondRetParm;

		JOG_Deleta(vJogadores[indJogador]);
		vJogadores[indJogador] = NULL;
		return TST_CondRetOK;
	}

	//Testar a funcao PoePecaNoJogo
	else if(strcmp(ComandoTeste,ATUALIZA)==0)
	{
		numLidos = LER_LerParametros("iii",&indJogador,&indPeca,&indPonteiro);
		if(indJogador<0 || indJogador>DIM_VT_JOGADORES
		   || indPeca<0 || indPeca>3 
	       || indPonteiro<0 || indPonteiro>DIM_VT_PONTEIROS
		   || numLidos!=3)
			return TST_CondRetParm;
		if(vJogadores[indJogador]==NULL) return TST_CondRetParm;

		peca = JOG_ObterPecaNaPosicao(vJogadores[indJogador],indPeca);
		if(peca==NULL)return TST_CondRetParm;
		
		JOG_AtualizaPeca(peca,vPonteiros[indPonteiro]);

		
		return TST_CondRetOK;
	}

	//Testar a funcao TemPeca
	else if(strcmp(ComandoTeste,TEMPECA)==0)
	{
		numLidos = LER_LerParametros("ii",&indJogador,&valorEsperado);
		if(numLidos!=2) return TST_CondRetParm;

		return TST_CompararInt(JOG_TemPecas(vJogadores[indJogador]),valorEsperado,"Valor esperado não encontrado.");
	}

	else if(strcmp(ComandoTeste,LOCALPECA)==0)
	{
		numLidos = LER_LerParametros("iiii",&indJogador,&indPeca,&indPonteiro,&valorEsperado);
		if(indJogador<0 || indJogador>DIM_VT_JOGADORES
		   || indPeca<0 || indPeca>3
	       || indPonteiro<0 || indPonteiro>DIM_VT_PONTEIROS
		   || numLidos!=4)
			return TST_CondRetParm;
		if(vJogadores[indJogador]==NULL) return TST_CondRetParm;

		peca = JOG_ObterPecaNaPosicao(vJogadores[indJogador],indPeca);
		if(peca==NULL)return TST_CondRetErro;

		if(valorEsperado==0)
		{
			return TST_CompararPonteiroNulo(0,JOG_ObterLocalPeca(peca),"Ponteiro nao e nulo como deveria ser.");
		}
		return TST_CompararPonteiro(JOG_ObterLocalPeca(peca),vPonteiros[indPonteiro],"Ponteiro esperado não encontrado.");
	}

	else if(strcmp(ComandoTeste,LOCALPECA)==0)
	{
		numLidos = LER_LerParametros("iii",&indJogador,&indPeca,&valorEsperado);
		if(indJogador<0 || indJogador>DIM_VT_JOGADORES
		   || indPeca<0 || indPeca>3
		   || numLidos!=3)
			return TST_CondRetParm;
		if(vJogadores[indJogador]==NULL) return TST_CondRetParm;

		peca = JOG_ObterPecaNaPosicao(vJogadores[indJogador],indPeca);
		if(peca==NULL)return TST_CondRetErro;

		return TST_CompararInt(JOG_ObterCorPeca(peca),valorEsperado,"Cor esperada não encontrado.");
	}


	return 0;
}
