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
    Jogador * jogadores;
}Tabuleiro;

Tabuleiro * TAB_IniciaTabuleiro() {
    Tabuleiro * tab = (Tabuleiro *)malloc(sizeof(Tabuleiro));
    if (tab == NULL) {
        /* Fazer algo que indique que ocorreu um problema */
        return NULL;
    }
    //Jogador ** jogadores, int numJogadores
//    for (int i = 0; i < numJogadores; i++) {
//        jogadores[i]
//    }
    return tab;
}

TAB_tpCasa TAB_CriaCasa(CIR_lstCircular bif,TAB_Cor cor)
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

void TAB_InserePeca(TAB_tpCasa casa,JOG_tpPeca *peca)
{
    if(casa->Pecas[0]==NULL) casa->Pecas[0] = peca;
    else if(casa->Pecas[1]==NULL) casa->Pecas[1] = peca;
    else return; /************************ADICIONAR CONDICAO DE ERRO**************************/
}

int TAB_Cor(TAB_tpCasa casa)
{
    return casa->Cor;
}

TAB_tpCasa TAB_DestroiCasa(TAB_tpCasa casa)
{
    free(casa);
}

/****************************************************************

Funco: TAB  &Avanca Peca Lista Dupla

CUIDADO: Pressupoe que o elemento atual da lista contém a peca desejada.

****************************************************************/
void TAB_AvancaPecaLDupla(LIS_tppLista Lista,int peca,int ncasas)
{
    TAB_tpCasa *CasaCorr = LIS_ObterValor(Lista);
    JOG_tpPeca *temp;
    temp = CasaCorr->pecas[peca];
    CasaCorr->pecas[peca] = NULL;

    while(ncasas>0 && LISAvancarElementoCorrente(Lista,1)!=LIS_CondRetFimLista) /*Avanca o maximo para frente poss�vel*/
    {
    	ncasas--;
    }
    LISAvancarElementoCorrente(Lista,-ncasas);/*Volta o restante*/
    CasaCorr = LIS_ObterValor(Lista);
    InserePeca(CasaCorr,temp);
}

void TAB_AvancaPecaCircular(CIR_lstCircular *Lista,TAB_tpCasa casa,int peca,int ncasas)
{
    TAB_Cor CorPeca;
    JOG_tpPeca *temp;
    TAB_tpCasa *CasaCorr;
    
    temp = casa->pecas[peca];
    casa->pecas[peca] = NULL;
    CorPeca = JOG_Cor(temp);
    
    Lista = (CIR_ProcuraElemento(Lista,casa));
    while(ncasas>0)
    {
        ncasas--;
        
        CasaCorr = CIR_Conteudo(Lista);
        if(TAB_Cor(CasaCorr)) == CorPeca) /*Se a casa tem cor igual a peça sendo movida ela é uma bifurcacao para ela, encaminha para a função apropriada*/
        {
            LIS_IrInicioLista(CasaCorr->Bifurcacao);
            CasaCorr = LIS_ObterValor(CasaCorr->Bifurcacao);
            TAB_InserePeca(CasaCorr,temp);
            TAB_AvancaPecaLDupla(CasaCorr->Bifucacao,ncasas);
            return;
        }
        else Lista = CIR_ProximoElemento(Lista);
    }
    CasaCorr = CIR_Conteudo(Lista);
    TAB_InserePeca(CasaCorr,temp);
    JOG_MovePeca(temp,CasaCorr);
}

