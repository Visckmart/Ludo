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
    CIR_lstCircular *CampoPrincipal;
	LIS_tppLista *RetaFinal[4];
}Tabuleiro;

Tabuleiro * TAB_IniciaTabuleiro() {
	int i,a;
    Tabuleiro * tab = (Tabuleiro *)malloc(sizeof(Tabuleiro));
    if (tab == NULL) {
        return NULL;
    }
    for(i=0;i<4;i++)
    {
		tab->RetaFinal[i] = LIS_CriarLista();
		for(a=0;a<5;a++)
		{
			TAB_CriaCasa(NULL,)
		}

    }

    return tab;
}

TAB_tpCasa TAB_CriaCasa(LIS_tppLista bif,TAB_Cor cor)
{
    TAB_tpCasa *nova;
    nova = (TAB_tpCasa) malloc(sizeof(TAB_tpCasa));
    if(nova==NULL) return NULL;
    
    nova->pecas[0] = NULL;
    nova->pecas[1] = NULL;
    nova->Cor = cor;
    nova->Bifurcacao = bif;
    
    return bif;
}

TAB_CondRet TAB_InserePeca(JOG_tpPeca *peca,TAB_tpCasa casa)
{
    if(casa->pecas[0]==NULL) casa->pecas[0] = peca;
    else if(casa->pecas[1]==NULL) casa->pecas[1] = peca;
    else return TAB_CondRetSemEspaco;
    return TAB_CondRetOk;
}

int TAB_Cor(TAB_tpCasa casa)
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


/****************************************************************

Fun��o: TAB  &Avanca Peca Lista Dupla

CUIDADO: Pressupoe que o elemento atual da lista contém a peca desejada.

****************************************************************/
TAB_CondRet TAB_AvancaPecaLDupla(LIS_tppLista Lista,int peca,int ncasas)
{
	int res = ncasas;
    TAB_tpCasa *CasaCorr = LIS_ObterValor(Lista);
    JOG_tpPeca *temp;
    temp = CasaCorr->pecas[peca];
    CasaCorr->pecas[peca] = NULL;

    while(res>0 && LISAvancarElementoCorrente(Lista,1)!=LIS_CondRetFimLista) /*Avanca o maximo para frente possível*/
    {
    	res--;
    	CasaCorr = LIS_ObterValor(Lista);
    	if(TAB_NumPecas(CasaCorr)==2)  /*Se encontrar obstrução volta uma casa e termina a jogada*/
    	{
    		if(res==ncasas-1) return TAB_CondRetNaoAndou; /*Se a obstrução está na primeira casa andada então a jogada é inválida*/
    		res = 0;
    		LISAvancarElementoCorrente(Lista,-1);
    		break;
    	}
    }
    LISAvancarElementoCorrente(Lista,-res);/*Volta o restante*/
    CasaCorr = LIS_ObterValor(Lista);
    InserePeca(temp,CasaCorr);

    return TAB_CondRetOk;
}

/****************************************************************

Fun��o: TAB  &Avanca Peca Lista Circular

CUIDADO: Pressupoe que o elemento atual da lista contém a peca desejada.

****************************************************************/
TAB_CondRet TAB_AvancaPecaCircular(CIR_lstCircular *Lista,int peca,int ncasas)
{
	int res=ncasas;
    TAB_Cor CorPeca;
    JOG_tpPeca *temp;
    TAB_tpCasa *CasaCorr = CIR_Conteudo(Lista),*Proximo;
    
    temp = CasaCorr->pecas[peca];
    CasaCorr->pecas[peca] = NULL;
    CorPeca = JOG_Cor(temp);
    


    while(res>0)
    {
        res--;
        CIR_ProximoElemento(Lista);
        Proximo = CIR_Conteudo(Lista);
        
        if(TAB_NumPecas(Proximo)==2 && res != 0)
        {
        	if(res == ncasas-1) return TAB_CondRetNaoAndou;
        	break;
        }

        if(TAB_Cor(CasaCorr) == CorPeca) /*Se a casa tem cor igual a pe�a sendo movida ela � uma bifurcacao para ela, encaminha para a função apropriada*/
        {
            LIS_IrInicioLista(CasaCorr->Bifurcacao);
            if(TAB_NumPecas(LIS_ObterValor(CasaCorr->Bifurcacao))==2) break; /*Se a primeira casa da lista está obstruida pare a peça onde está*/

			Proximo = LIS_ObterValor(CasaCorr->Bifurcacao);
			if(TAB_AvancaPecaLDupla(CasaCorr,TAB_NumPecas(CasaCorr)-1,res==TAB_CondRetOk) return TAB_CondRetOk;

        }


		CIR_ProximoElemento(Lista);
		CasaCorr = CIR_Conteudo(Lista);

    }
    if(TAB_NumCasas==1 && JOG_Cor(CasaCorr->pecas[1])!=CorPeca) TAB_ComePecas(CasaCorr);
    TAB_InserePeca(CasaCorr,temp);
    JOG_MovePeca(temp,CasaCorr);
    return CondRetOk;
}

