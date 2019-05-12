/***************************************************************************
*  $MCI M�dulo de implementa��o: TAB  Tabuleiro
*
*  Arquivo gerado:              Tabuleiro.c
*  Letras identificadoras:      TAB
*
*
*  Projeto: INF 1301 / Ludo
*  Autores: Thiago Lamenza
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor            Data        Observa��es
*     1       Thiago Lamenza   11/mai/2019 inicio do desenvolvimento
*
***************************************************************************/

#include <stdlib.h>
#include "Tabuleiro.h"
#include "Jogador.h"
#include "Circular.h"
#include "LISTA.h"

struct casa
{
    JOG_tpPeca *pecas[2];
    LIS_tppLista Bifurcacao;
    JOG_tpCor Cor;
};


struct tabuleiro
{
    CIR_lstCircular *campoPrincipal;
	LIS_tppLista retaFinal[4];
};


/**********************************************
 *
 * Variável estática que guarda o tabuleiro
 *
 *********************************************/
static TAB_tpTabuleiro *Tabuleiro = NULL;


/************************************************
 *
 * Vetor de casas de entrada no tabuleiro ordenada por cor, é setada com a função IniciaTabuleiro.
 *
 * Ordem: Amarelo,Verde,Vermelho,Azul
 *
 ***********************************************/
static TAB_tpCasa *inicioPorCor[4];

/*********************************************
 *
 * Protótipo das funções estáticas encapsuladas pelo módulo
 *
 ********************************************/
static TAB_tpCasa* TAB_CriaCasa(LIS_tppLista bifurcacao,JOG_tpCor cor);
static TAB_CondRet TAB_InserePeca(TAB_tpCasa *casa,JOG_tpPeca *peca);
static TAB_CondRet TAB_RemovePeca(TAB_tpCasa *casa,int peca);
static void TAB_DestroiCasa(TAB_tpCasa *casa);
static void TAB_ComePecas(TAB_tpCasa *casa);
static int TAB_NumPecas(TAB_tpCasa *casa);
static TAB_CondRet TAB_AvancaPecaLDupla(LIS_tppLista Lista,int indPeca,int numCasas);
static TAB_CondRet TAB_AvancaPecaCircular(CIR_lstCircular *Lista,int indPeca,int numCasas);



/****************************************************************

Fun��o: TAB  &CriaCasa

****************************************************************/

TAB_tpCasa *TAB_CriaCasa(LIS_tppLista bifurcacao,JOG_tpCor cor)
{
    TAB_tpCasa *nova;
    nova = (TAB_tpCasa*) malloc(sizeof(TAB_tpCasa));
    if(nova==NULL) return NULL;

    nova->pecas[0] = NULL;
    nova->pecas[1] = NULL;
    nova->Cor = cor;
    nova->Bifurcacao = bifurcacao;

    return nova;
}

/****************************************************************

Fun��o: TAB  &IniciaTabuleiro

****************************************************************/

TAB_CondRet TAB_IniciaTabuleiro() {
	int i,a;
    TAB_tpTabuleiro * tab;
    JOG_tpCor Cores[4] = {Amarelo,Verde,Vermelho,Azul};
    TAB_tpCasa *casa;

    if(Tabuleiro!=NULL) TAB_DestroiTabuleiro();

    tab = (TAB_tpTabuleiro*)malloc(sizeof(TAB_tpTabuleiro));

    if (tab == NULL) {
        return TAB_CondRetMemoria;
    }
    for(i=0;i<4;i++)
    {
		tab->retaFinal[i] = LIS_CriarLista(TAB_DestroiCasa);
		for(a=0;a<5;a++)
		{
			casa = TAB_CriaCasa(NULL,Nenhuma);
			if(casa==NULL) return TAB_CondRetMemoria;

			LIS_InserirElementoApos(tab->retaFinal[i],casa);
		}
    }

    tab->campoPrincipal = CIR_CriaLista();
    a=0;
    for(i=0;i<52;i++)
    {
    	if(i%13==0)
    	{
    		casa = TAB_CriaCasa(tab->retaFinal[a],Cores[a]);

    		a++;
    	}
    	else
    	{
    		casa = TAB_CriaCasa(NULL,Nenhuma);
    	}
    	if((i-2)%13==0) inicioPorCor[i-2/13] = casa; /*Se for uma das casas de inicio salva seu endereço no vetor de casas de inicio*/

    	if(casa==NULL) return TAB_CondRetMemoria;
    	CIR_InsereElemento(tab->campoPrincipal,casa);
    }

    Tabuleiro = tab;
    return TAB_CondRetOk;
}


/****************************************************************

Fun��o: TAB  &InserePeca

****************************************************************/

TAB_CondRet TAB_InserePeca(TAB_tpCasa *casa,JOG_tpPeca *peca)
{
    if(casa->pecas[0]==NULL) casa->pecas[0] = peca;
    else if(casa->pecas[1]==NULL) casa->pecas[1] = peca;
    else return TAB_CondRetSemEspaco;
    return TAB_CondRetOk;
}

TAB_CondRet TAB_RemovePeca(TAB_tpCasa *casa,int peca)
{
	if(casa->pecas[0]==NULL) return TAB_CondRetCasaVazia;
	if(peca==0)
	{
		casa->pecas[0] = casa->pecas[1];
		casa->pecas[1] = NULL;
	}
	else
	{
		casa->pecas[1] = NULL;
	}
	return TAB_CondRetOk;
}

void TAB_ComePecas(TAB_tpCasa *casa)
{
	if(casa->pecas[0]!=NULL)
	{
		JOG_AtualizaPeca(casa->pecas[0],NULL);
		casa->pecas[0]=NULL;
	}
	if(casa->pecas[1]!=NULL)
	{
		JOG_AtualizaPeca(casa->pecas[1],NULL);
		casa->pecas[1]=NULL;
	}
}


void TAB_DestroiCasa(TAB_tpCasa *casa)
{
    free(casa);
}

int TAB_NumPecas(TAB_tpCasa *casa)
{
	if(casa->pecas[0]!=NULL)
	{
		if(casa->pecas[1]!=NULL) return 2;
		return 1;
	}
	return 0;
}


TAB_CondRet TAB_FazJogada(void *peca,int dado)
{
	TAB_tpCasa *casa;
	int i;
	TAB_CondRet CondRet;

	if(peca==NULL || dado<1) return TAB_CondRetParametro;

	casa = JOG_LocalPeca(peca);
	if(casa == NULL) return TAB_CondRetNaoAndou;
	if(CIR_ProcuraElemento(Tabuleiro->campoPrincipal,casa)!=CIR_CondRetNaoAchou)
	{
		CondRet = TAB_AvancaPecaCircular(Tabuleiro->campoPrincipal, casa->pecas[0]==peca?0:1, dado);
		casa = CIR_Conteudo(Tabuleiro->campoPrincipal);
	}

	for(i=0;i<4;i++)
	{
		if(LIS_ProcurarValor(Tabuleiro->retaFinal[i],casa) != LIS_CondRetNaoAchou)
		{
			CondRet = TAB_AvancaPecaLDupla(Tabuleiro->retaFinal[i],casa->pecas[0]==peca?0:1, dado);
			casa = LIS_ObterValor(Tabuleiro->retaFinal[i]);
		}
	}
	JOG_AtualizaPeca(peca,casa);
	return TAB_CondRetOk;
}


TAB_CondRet TAB_PoePecaNoJogo(void *peca)
{
	int indice;
	TAB_tpCasa *casa;
	JOG_tpCor Cor;

	if(peca==NULL) return TAB_CondRetParametro;

	Cor = JOG_CorPeca(peca);
	if(Cor == Amarelo) indice = 0;
	else if(Cor == Verde) indice = 1;
	else if(Cor == Vermelho) indice = 2;
	else if(Cor == Azul) indice = 3;
	else return TAB_CondRetParametro;

	casa = inicioPorCor[indice]; /*Seleciona a casa de inicio correta baseada na cor*/

	if(TAB_NumPecas(casa)>0 && JOG_CorPeca(casa->pecas[0])!= JOG_CorPeca(peca)) TAB_ComePecas(casa);
	else if(TAB_NumPecas(casa)==2) return TAB_CondRetSemEspaco;

	return TAB_InserePeca(casa,peca);
}

TAB_CondRet TAB_DestroiTabuleiro()
{
	int i;
	if(Tabuleiro==NULL) return TAB_CondRetOk;
	CIR_DestroiLista(Tabuleiro->campoPrincipal,TAB_DestroiCasa);
	for(i=0;i<4;i++) LIS_DestruirLista(Tabuleiro->retaFinal[i]);

	free(Tabuleiro);
	return TAB_CondRetOk;
}

/****************************************************************

Fun��o: TAB  &Avanca Peca Lista Dupla

CUIDADO: Pressupoe que o elemento atual da lista contém a peca desejada.

****************************************************************/
TAB_CondRet TAB_AvancaPecaLDupla(LIS_tppLista Lista,int indPeca,int numCasas)
{
	int res = numCasas;
    TAB_tpCasa *casaCorr,*casaInicial;
    JOG_tpPeca *temp;

    if(Lista==NULL || indPeca>1 || indPeca<0 || numCasas<0) return TAB_CondRetParametro;

    casaInicial = casaCorr = LIS_ObterValor(Lista);
    temp = casaCorr->pecas[indPeca];

    while(res>0 && LIS_AvancarElementoCorrente(Lista,1)!=LIS_CondRetFimLista) /*Avanca o maximo para frente possível*/
    {
    	res--;
    	casaCorr = LIS_ObterValor(Lista);
    	if(TAB_NumPecas(casaCorr)==2)  /*Se encontrar obstrução volta uma casa e termina a jogada*/
    	{
    		if(res==numCasas-1) return TAB_CondRetNaoAndou; /*Se a obstrução está na primeira casa andada então a jogada é inválida*/
    		res = 0;
    		LIS_AvancarElementoCorrente(Lista,-1);
    		break;
    	}
    }
    res--; /*Bater no final do tabuleiro conta como "andar*/
    if(res==0)
    {
    	TAB_RemovePeca(casaInicial,indPeca);
    	return TAB_CondRetChegouFinal;
    }
    else if(res>0)
    	LIS_AvancarElementoCorrente(Lista,-res);/*Volta o restante*/

    casaCorr = LIS_ObterValor(Lista);
    if(TAB_InserePeca(casaCorr,temp)!=TAB_CondRetOk) return TAB_CondRetNaoAndou;

    TAB_RemovePeca(casaInicial,indPeca);
    return TAB_CondRetOk;
}

/****************************************************************

Fun��o: TAB  &Avanca Peca Lista Circular

CUIDADO: Pressupoe que o elemento atual da lista contém a peca desejada.

****************************************************************/
TAB_CondRet TAB_AvancaPecaCircular(CIR_lstCircular *Lista,int indPeca,int numCasas)
{
	int res=numCasas;
    JOG_tpCor CorPeca;
    JOG_tpPeca *temp;
    TAB_tpCasa *casaInicial,*casaCorr,*Proximo;

    if(Lista==NULL || indPeca>1 || indPeca<0 || numCasas<0) return TAB_CondRetParametro;
    
    casaInicial = casaCorr = CIR_Conteudo(Lista);
    temp = casaCorr->pecas[indPeca];
    CorPeca = JOG_CorPeca(temp);


    while(res>0)
    {
        res--;
        CIR_ProximoElemento(Lista);
        Proximo = CIR_Conteudo(Lista);
        
        if(TAB_NumPecas(Proximo)==2 && res != 0)
        {
        	if(res == numCasas-1) return TAB_CondRetNaoAndou;
        	break;
        }

        if(casaCorr->Cor == CorPeca) /*Se a casa tem cor igual a pe�a sendo movida ela � uma bifurcacao para ela, encaminha para a função apropriada*/
        {
            IrInicioLista(casaCorr->Bifurcacao);
            if(TAB_NumPecas(LIS_ObterValor(casaCorr->Bifurcacao))==2) break; /*Se a primeira casa da lista está obstruida pare a peça onde está*/

			Proximo = LIS_ObterValor(casaCorr->Bifurcacao);
			if(TAB_AvancaPecaLDupla(casaCorr->Bifurcacao,TAB_NumPecas(Proximo)-1,res)==TAB_CondRetOk) return TAB_CondRetOk;

        }


		CIR_ProximoElemento(Lista);
		casaCorr = CIR_Conteudo(Lista);

    }
    if(TAB_NumPecas>0 && JOG_CorPeca(casaCorr->pecas[0])!=CorPeca) TAB_ComePecas(casaCorr);
    if(TAB_InserePeca(casaCorr,temp)!=TAB_CondRetOk)return TAB_CondRetNaoAndou;

    TAB_RemovePeca(casaInicial,indPeca);
    return TAB_CondRetOk;
}

