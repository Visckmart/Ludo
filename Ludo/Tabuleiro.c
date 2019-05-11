//
//  Tabuleiro.c
//  Ludo
//
#include <stdlib.h>
#include "Tabuleiro.h"
#include <stdlib.h>
#include "Jogador.h"
#include "Circular.h"
#include "LISTA.H"

typedef struct casa {
    JOG_tpPeca pecas[2];
    LIS_tppLista Bifurcacao;
    TAB_Cor Cor;
}TAB_tpCasa;


typedef struct tabuleiro {
    CIR_lstCircular *campoPrincipal;
	LIS_tppLista *retaFinal[4];
}TAB_tpTabuleiro;



/**********************************************
 *
 * Variável estática que guarda o tabuleiro
 *
 *********************************************/
static TAB_tpTabuleiro *Tabuleiro = NULL;

/*********************************************
 *
 * Protótipo das funções estáticas encapsuladas pelo módulo
 *
 ********************************************/
static TAB_tpCasa *TAB_CriaCasa(LIS_tppLista bifurcacao,TAB_Cor cor);
static TAB_CondRet TAB_InserePeca(TAB_tpCasa casa,JOG_tpPeca *peca);
static TAB_CondRet TAB_RemovePeca(TAB_tpCasa casa,int peca);
static JOG_enumCor TAB_Cor(TAB_tpCasa casa);
static TAB_tpCasa TAB_DestroiCasa(TAB_tpCasa casa);
static int TAB_NumPecas(TAB_tpCasa casa);
static TAB_CondRet TAB_AvancaPecaLDupla(LIS_tppLista Lista,int indPeca,int numCasas);
static TAB_CondRet TAB_AvancaPecaCircular(CIR_lstCircular *Lista,int indPeca,int numCasas);



/****************************************************************

Fun��o: TAB  &CriaCasa

****************************************************************/

TAB_tpCasa *TAB_CriaCasa(LIS_tppLista bifurcacao,TAB_Cor cor)
{
    TAB_tpCasa *nova;
    nova = (TAB_tpCasa) malloc(sizeof(TAB_tpCasa));
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
    TAB_tpTabuleiro * tab = (Tabuleiro *)malloc(sizeof(Tabuleiro));
    JOG_Cores Cores[4] = {Amarelo,Verde,Vermelho,Azul};
    TAB_tpCasa *casa;
    if (tab == NULL) {
        return NULL;
    }
    for(i=0;i<4;i++)
    {
		tab->retaFinal[i] = LIS_CriarLista(TAB_DestroiCasa);
		for(a=0;a<5;a++)
		{
			casa = TAB_CriaCasa(NULL,JOG_CorNeutra);
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
    		casa = TAB_CriaCasa(NULL,JOG_CorNeutra);
    	}
    	CIR_InsereElemento(tab->campoPrincipal,casa);
    }

    Tabuleiro = tab;
}


/****************************************************************

Fun��o: TAB  &InserePeca

****************************************************************/

TAB_CondRet TAB_InserePeca(TAB_tpCasa casa,JOG_tpPeca *peca)
{
    if(casa->pecas[0]==NULL) casa->pecas[0] = peca;
    else if(casa->pecas[1]==NULL) casa->pecas[1] = peca;
    else return TAB_CondRetSemEspaco;
    return TAB_CondRetOk;
}

TAB_CondRet TAB_RemovePeca(TAB_tpCasa casa,int peca)
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
	return condRetOk;
}

JOG_enumCor TAB_Cor(TAB_tpCasa casa)
{
    return casa->Cor;
}

TAB_tpCasa TAB_DestroiCasa(TAB_tpCasa casa)
{
    free(casa);
}

int TAB_NumPecas(TAB_tpCasa casa)
{
	if(casa->pecas[0]!=NULL)
	{
		if(casa->pecas[1]!=NULL) return 2;
		return 1;
	}
	return 0;
}


TAB_CondRet TAB_FazJogada(JOG_tpPeca peca,int dado)
{
	void *casaImplicita = JOG_LocalPeca(peca);
	int indPeca,i;
	if(CIR_ProcuraElemento(Tabuleiro->campoPrincipal,casaImplicita)!=CIR_CondRetNaoAchou)
	{
		return TAB_AvancaPecaCircular(Tabuleiro->campoPrincipal, casaImplicita->pecas[0]==peca?0:1, dado);
	}

	for(i=0;i<4;i++)
	{
		if(LIS_ProcurarValor(Tabuleiro->retaFinal[i],casaImplicita) != LIS_CondRetNaoAchou)
		{
			return TAB_AvancaPecaLDupla(Tabuleiro->retafinal[i],casaImplicita->pecas[0]==peca?0:1, dado);
		}
	}
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

    while(res>0 && LISAvancarElementoCorrente(Lista,1)!=LIS_CondRetFimLista) /*Avanca o maximo para frente possível*/
    {
    	res--;
    	casaCorr = LIS_ObterValor(Lista);
    	if(TAB_NumPecas(casaCorr)==2)  /*Se encontrar obstrução volta uma casa e termina a jogada*/
    	{
    		if(res==numCasas-1) return TAB_CondRetNaoAndou; /*Se a obstrução está na primeira casa andada então a jogada é inválida*/
    		res = 0;
    		LISAvancarElementoCorrente(Lista,-1);
    		break;
    	}
    }
    res--; /*Bater no final do tabuleiro conta como "andar*/
    if(res==0)
    {
    	PAR_CompletaCircuito(temp);
    	return TAB_CondRetOk;
    }
    else if(res>0)
    	LISAvancarElementoCorrente(Lista,-res);/*Volta o restante*/

    casaCorr = LIS_ObterValor(Lista);
    if(TAB_InserePeca(casaCorr,temp)!=TAB_CondRetOk) return TAB_CondRetNaoAndou;

    TAB_RemovePeca(casaInicial,indPeca);
    JOG_MovePeca(temp,casaCorr);
    return TAB_CondRetOk;
}

/****************************************************************

Fun��o: TAB  &Avanca Peca Lista Circular

CUIDADO: Pressupoe que o elemento atual da lista contém a peca desejada.

****************************************************************/
TAB_CondRet TAB_AvancaPecaCircular(CIR_lstCircular *Lista,int indPeca,int numCasas)
{
	int res=numCasas;
    TAB_Cor CorPeca;
    JOG_tpPeca *temp;
    TAB_tpCasa *casaInicial,*casaCorr;

    if(Lista==NULL || indPeca>1 || indPeca<0 || numCasas<0) return TAB_CondRetParametro;
    
    casaInicial = casaCorr = CIR_Conteudo(Lista),*Proximo;
    temp = casaCorr->pecas[indPeca];
    CorPeca = JOG_Cor(temp);


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

        if(TAB_Cor(casaCorr) == CorPeca) /*Se a casa tem cor igual a pe�a sendo movida ela � uma bifurcacao para ela, encaminha para a função apropriada*/
        {
            LIS_IrInicioLista(casaCorr->Bifurcacao);
            if(TAB_NumPecas(LIS_ObterValor(casaCorr->Bifurcacao))==2) break; /*Se a primeira casa da lista está obstruida pare a peça onde está*/

			Proximo = LIS_ObterValor(casaCorr->Bifurcacao);
			if(TAB_AvancaPecaLDupla(casaCorr,TAB_NumPecas(casaCorr)-1,res==TAB_CondRetOk) return TAB_CondRetOk;

        }


		CIR_ProximoElemento(Lista);
		casaCorr = CIR_Conteudo(Lista);

    }
    if(TAB_NumCasas>0 && JOG_Cor(casaCorr->pecas[0])!=CorPeca) TAB_ComePecas(casaCorr);
    if(TAB_InserePeca(casaCorr,temp)!=TAB_CondRetOk)return TAB_CondRetNaoAndou;

    TAB_RemovePeca(casaInicial,indPeca);
    JOG_MovePeca(temp,casaCorr);
    return CondRetOk;
}

