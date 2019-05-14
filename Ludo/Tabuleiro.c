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

typedef struct casa
{
    JOG_tpPeca *pecas[2];
    LIS_tppLista Bifurcacao;
    JOG_tpCor Cor;
}TAB_tpCasa;


typedef struct tabuleiro
{
    CIR_lstCircular *campoPrincipal;
	LIS_tppLista retaFinal[4];
}TAB_tpTabuleiro;


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

Função: TAB  &CriaCasa

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

Função: TAB  &IniciaTabuleiro

****************************************************************/

TAB_CondRet TAB_IniciaTabuleiro() {
	int i,a;
    TAB_tpTabuleiro * tab;
    JOG_tpCor Cores[4] = {Amarelo,Verde,Vermelho,Azul};
    TAB_tpCasa *casa;

    if(Tabuleiro!=NULL) TAB_FinalizaTabuleiro();

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
    	if(casa==NULL) return TAB_CondRetMemoria;

    	if((i-2)%13==0) inicioPorCor[(i-2)/13] = casa; /*Se for uma das casas de inicio salva seu endereço no vetor de casas de inicio*/

    	CIR_InsereElemento(tab->campoPrincipal,casa);
    }

    Tabuleiro = tab;
    return TAB_CondRetOk;
}


/****************************************************************

Função: TAB  &InserePeca

****************************************************************/

TAB_CondRet TAB_InserePeca(TAB_tpCasa *casa,JOG_tpPeca *peca)
{
    if(casa->pecas[0]==NULL) casa->pecas[0] = peca;
    else if(casa->pecas[1]==NULL) casa->pecas[1] = peca;
    else return TAB_CondRetSemEspaco;
    return TAB_CondRetOk;
}


/****************************************************************

Função: TAB  &RemovePeca

****************************************************************/
TAB_CondRet TAB_RemovePeca(TAB_tpCasa *casa,int peca)
{
	if(casa->pecas[0]==NULL) return TAB_CondRetParametro;
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

/****************************************************************

Função: TAB  &ComePecas

****************************************************************/
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


/****************************************************************

Função: TAB  &DestroiCasa

****************************************************************/
void TAB_DestroiCasa(TAB_tpCasa *casa)
{
    free(casa);
}


/****************************************************************

Função: TAB  &NumPecas

****************************************************************/
int TAB_NumPecas(TAB_tpCasa *casa)
{
	if(casa==NULL) return -1;
	if(casa->pecas[0]!=NULL)
	{
		if(casa->pecas[1]!=NULL) return 2;
		return 1;
	}
	return 0;
}



/****************************************************************

Função: TAB  &FazJogada

****************************************************************/
TAB_CondRet TAB_FazJogada(void *peca,int dado)
{
	TAB_tpCasa *casa;
	int i,indPeca;
	TAB_CondRet CondRet = TAB_CondRetNaoAndou;

	if(peca==NULL || dado<1) return TAB_CondRetParametro;

	casa = JOG_LocalPeca(peca);
	if(casa == NULL) return TAB_CondRetParametro;

	if(casa->pecas[0]==peca) indPeca = 0;
	else if(casa->pecas[1]==peca) indPeca=1;
	else return TAB_CondRetParametro;


	if(CIR_ProcuraElemento(Tabuleiro->campoPrincipal,casa)!=CIR_CondRetNaoAchou)
	{
		CondRet = TAB_AvancaPecaCircular(Tabuleiro->campoPrincipal, indPeca, dado);
	}
	else
	{
		for(i=0;i<4;i++)
		{
			if(LIS_ProcurarValor(Tabuleiro->retaFinal[i],casa) != LIS_CondRetNaoAchou)
			{
				CondRet = TAB_AvancaPecaLDupla(Tabuleiro->retaFinal[i],indPeca, dado);
			}
		}
	}
	return CondRet;
}



/****************************************************************

Função: TAB  &PoePecaNoJogo

****************************************************************/
TAB_CondRet TAB_PoePecaNoJogo(void *peca)
{
	int indice;
	TAB_tpCasa *casa;
	JOG_tpCor Cor;
	TAB_CondRet CondRet;

	if(peca==NULL) return TAB_CondRetParametro;
	if(JOG_LocalPeca(peca)!=NULL) return TAB_CondRetParametro;

	Cor = JOG_CorPeca(peca);
	if(Cor == Amarelo) indice = 0;
	else if(Cor == Verde) indice = 1;
	else if(Cor == Vermelho) indice = 2;
	else if(Cor == Azul) indice = 3;
	else return TAB_CondRetParametro;

	casa = inicioPorCor[indice]; /*Seleciona a casa de inicio correta baseada na cor*/


	if(TAB_NumPecas(casa)>0 && JOG_CorPeca(casa->pecas[0])!= JOG_CorPeca(peca)) TAB_ComePecas(casa); /*Se houver uma peca inimiga come ela*/
	else if(TAB_NumPecas(casa)==2) return TAB_CondRetSemEspaco; /*Se a casa estiver cheia não executa a inserção*/

	CondRet = TAB_InserePeca(casa,peca);
	if(CondRet==TAB_CondRetOk) JOG_AtualizaPeca(peca,casa);
	return CondRet;
}


/****************************************************************

Função: TAB  &FinalizaTabuleiro

****************************************************************/
TAB_CondRet TAB_FinalizaTabuleiro()
{
	int i;
	if(Tabuleiro==NULL) return TAB_CondRetOk;
	CIR_DestroiLista(Tabuleiro->campoPrincipal,TAB_DestroiCasa);
	for(i=0;i<4;i++) LIS_DestruirLista(Tabuleiro->retaFinal[i]);

	free(Tabuleiro);
	return TAB_CondRetOk;
}

/****************************************************************

Função: TAB  &Avanca Peca Lista Dupla

CUIDADO: Pressupoe que o elemento atual da lista contém a peca desejada.

****************************************************************/
TAB_CondRet TAB_AvancaPecaLDupla(LIS_tppLista Lista,int indPeca,int numCasas)
{
	int res = numCasas;
    TAB_tpCasa *Proximo,*casaCorr,*casaInicial;
    JOG_tpPeca *temp;
    if(Lista==NULL || indPeca>1 || indPeca<0 || numCasas<0) return TAB_CondRetParametro;
    if(numCasas==0) return TAB_CondRetOk;

    casaInicial = casaCorr = LIS_ObterValor(Lista);
    if(casaCorr==NULL) return TAB_CondRetParametro;
    temp = casaCorr->pecas[indPeca];
    if(temp==NULL) return TAB_CondRetParametro;
    while(res>0 && LIS_AvancarElementoCorrente(Lista,1)!=LIS_CondRetFimLista) /*Avanca o maximo para frente possível*/
    {

    	Proximo = LIS_ObterValor(Lista);
    	if(TAB_NumPecas(Proximo)==2)  /*Se encontrar obstrução volta uma casa e termina a jogada*/
    	{
    		if(res==numCasas) return TAB_CondRetNaoAndou; /*Se a obstrução está na primeira casa andada então a jogada é inválida*/
    		res = 0;
    		break;
    	}
    	casaCorr = Proximo;
    	res--;
    }
    TAB_RemovePeca(casaInicial,indPeca); /*Evita que a peça rebata e fique presa numa obstruçao gerada por ela mesma*/
    res--; /*Bater no final do tabuleiro conta como "andar*/
    if(res==0)
    {
    	LIS_IrInicioLista(Lista);
    	JOG_AtualizaPeca(temp,NULL);
    	return TAB_CondRetChegouFinal;
    }

	while(res>0 && LIS_AvancarElementoCorrente(Lista,-1)!=LIS_CondRetFimLista)
	{
		Proximo = LIS_ObterValor(Lista);
		if(TAB_NumPecas(Proximo)==2)
		{
			res = 0;
			break;
		}
		casaCorr = Proximo;
		res--;
    }
    if(TAB_InserePeca(casaCorr,temp)!=TAB_CondRetOk)return TAB_CondRetNaoAndou;
    LIS_IrInicioLista(Lista);
    JOG_AtualizaPeca(temp,casaCorr);
    return TAB_CondRetOk;
}

/****************************************************************

Função: TAB  &Avanca Peca Lista Circular

CUIDADO: Pressupoe que o elemento atual da lista contém a peca desejada.

****************************************************************/
TAB_CondRet TAB_AvancaPecaCircular(CIR_lstCircular *Lista,int indPeca,int numCasas)
{
	int res=numCasas;
    JOG_tpCor CorPeca;
    JOG_tpPeca *temp;
    TAB_tpCasa *casaInicial,*casaCorr,*Proximo;
    if(Lista==NULL || indPeca>1 || indPeca<0 || numCasas<0) return TAB_CondRetParametro;
    if(numCasas==0) return TAB_CondRetOk;
    
    casaInicial = casaCorr = CIR_Conteudo(Lista);
    if(casaCorr==NULL || casaCorr->pecas[indPeca]==NULL) return TAB_CondRetParametro;
    temp = casaCorr->pecas[indPeca];
    if(temp==NULL) return TAB_CondRetParametro;
    CorPeca = JOG_CorPeca(temp);

    while(res>0)
    {
        CIR_ProximoElemento(Lista);
        Proximo = CIR_Conteudo(Lista);
        if(TAB_NumPecas(Proximo)==2 && res != 1)
        {
        	if(res == numCasas) return TAB_CondRetNaoAndou;
        	break;
        }
        if(casaCorr->Cor == CorPeca)
        /*Se a casa tem cor igual a pe�a sendo movida ela � uma bifurcacao para ela, encaminha para a função apropriada*/
        {
            LIS_IrInicioLista(casaCorr->Bifurcacao);
            Proximo = LIS_ObterValor(casaCorr->Bifurcacao);
            if(TAB_NumPecas(Proximo)==2)
            {
            	if(res==numCasas) return TAB_CondRetNaoAndou;
            	/*Se a obstrucao foi encontrada na primeira andada, a jogada não é válida*/

            	else break;
            	/*Se a primeira casa da lista está obstruida pare a peça onde está*/
            }


			if(TAB_InserePeca(Proximo,temp)==TAB_CondRetOk)
			{
				JOG_AtualizaPeca(temp,Proximo);
				TAB_RemovePeca(casaInicial,indPeca);
				return TAB_AvancaPecaLDupla(casaCorr->Bifurcacao,TAB_NumPecas(Proximo)-1,res-1);
			}
			else
				return TAB_CondRetNaoAndou;
        }

		casaCorr = Proximo;
		res--;
    }
    if(TAB_NumPecas(casaCorr)>0 && JOG_CorPeca(casaCorr->pecas[0])!=CorPeca) TAB_ComePecas(casaCorr);
    if(TAB_InserePeca(casaCorr,temp)!=TAB_CondRetOk) return TAB_CondRetNaoAndou;
    JOG_AtualizaPeca(temp,casaCorr);
    TAB_RemovePeca(casaInicial,indPeca);
    return TAB_CondRetOk;
}

