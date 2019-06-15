//Teste do Modulo Tabuleiro.h utilizando o arcabouco de testes
//Autor:THiago Lamenza

#include "GENERICO.h"
#include "TST_ESPC.H"
#include "LERPARM.h"
#include "Tabuleiro.h"
#include "Jogador.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define DIM_VT_JOGADORES 2

/* Vetor de peças a serem usadas nos testes*/
static JOG_tpJogador *vJogadores[2];



// Funções aceitas para testar
static char RESETA[] = "=reseta";
static char INICIA[] = "=inicia";
static char JOGADA[] = "=jogada";
static char NOVAPECA[] = "=novapeca";

/***********************
Comandos disponíveis:
=reseta
=inicia
=jogada		indJogador		indPeca		dado	ValorEsperado
=novapeca	indJogador		indPeca		ValorEsperado
***********************/
TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
{
	int indJogador=-1,indPeca=-1,dado=-1,NumLidos=-1,ValorEsperado=-1,CondRet=-1;
	JOG_tpPeca *peca;


	//Reset teste
	if(strcmp(ComandoTeste,RESETA)==0)
	{
		TAB_FinalizaTabuleiro();
		return TST_CondRetOK;
	}

	//Chama a função IniciaTabuleiro e cria os jogadores de teste
	if(strcmp(ComandoTeste,INICIA)==0)
	{
		CondRet = TAB_IniciaTabuleiro();
		JOG_Cria(Amarelo,&vJogadores[0]);
		JOG_Cria(Vermelho,&vJogadores[1]);
		if(CondRet == TAB_CondRetMemoria) return TST_CondRetMemoria;
		return TST_CondRetOK;
	}

	//Testar a funcao FazJogada
	else if(strcmp(ComandoTeste,JOGADA)==0)
	{
		NumLidos = LER_LerParametros( "iiii" , &indJogador,&indPeca,&dado,&ValorEsperado);
		if(indJogador<0|| indJogador>DIM_VT_JOGADORES || indPeca<0 || indPeca>3 || dado<0 || NumLidos!=4)
			return TST_CondRetParm;

		peca = JOG_ObterPecaNaPosicao(vJogadores[indJogador],indPeca);
		CondRet = TAB_FazJogada(peca,dado);


		return TST_CompararInt(CondRet, ValorEsperado,"Retorno diferente do esperado.");
	}

	//Testar a funcao PoePecaNoJogo
	else if(strcmp(ComandoTeste,NOVAPECA)==0)
	{
		NumLidos = LER_LerParametros("iii",&indJogador,&indPeca,&ValorEsperado);
		if(indJogador<0|| indJogador>DIM_VT_JOGADORES || indPeca<0 || indPeca>3 || NumLidos!=3)
			return TST_CondRetParm;

		peca = JOG_ObterPecaNaPosicao(vJogadores[indJogador],indPeca);
		CondRet = TAB_PoePecaNoJogo(peca);

		if(ValorEsperado==0)
		{
			if(CondRet==ValorEsperado)
				return TST_CompararPonteiroNulo(1,JOG_ObterLocalPeca(peca),"Peca deveria estar em jogo.");
		}
		if(ValorEsperado==4)
		{
			if(CondRet==ValorEsperado)
				return TST_CompararPonteiroNulo(0,JOG_ObterLocalPeca(peca),"Peca nao deveria estar em jogo.");
		}
		return TST_CompararInt(CondRet,ValorEsperado,"Valor encontrado diferente do esperado");
	}

	TAB_CondRet TAB_DesenhaTabuleiro();
	return 0;
}
