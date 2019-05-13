//
//  Jogador.c
//  Ludo
//

#include "Jogador.h"
#include <stdlib.h>
#include "LISTA.H"

/***********************************************************************
*
*  $TC Tipo de dados: JOG Peça do jogador
*
***********************************************************************/
struct Peca {
    void * pos;
    JOG_tpCor cor;
};

/***********************************************************************
*
*  $TC Tipo de dados: JOG Jogador
*
***********************************************************************/
struct Jogador {
    LIS_tppLista pecas;
    JOG_tpCor cor;
};



/* * * * * * * * * *
 *
 *  Função: JOG Criar jogador
 *
 * * * * * * * * * */
JOG_tpJogador * JOG_Cria(JOG_tpCor corDasPecas) {
    int i;
    // Aloca um espaço para o jogador
    JOG_tpJogador * jog = (JOG_tpJogador *)malloc(sizeof(JOG_tpJogador));
    if (jog == NULL) return NULL;
    
    // Cria a primeira peça
    jog->pecas = LIS_CriarLista(JOG_Remove);
    if (jog->pecas == NULL) { free(jog); return NULL; }
    // Cria elementos de uma lista encadeada que guarda peças
    for (i = 0; i < 4; i++) {
        JOG_tpPeca * p = (JOG_tpPeca *)malloc(sizeof(JOG_tpPeca));
        if (p == NULL) { JOG_Deleta(jog); return NULL; }
        p->pos = NULL;
        p->cor = corDasPecas;
        LIS_InserirElementoApos(jog->pecas, p);
    }
    
    // Guarda a cor do jogador
    jog->cor = corDasPecas;
    
    // Retorna o jogador criado
    return jog;
}

/* * * * * * * * * *
 *
 *  Função: JOG Deletar jogador
 *
 * * * * * * * * * */

JOG_CondRetErro JOG_Deleta(JOG_tpJogador * jog) {
    if (jog == NULL) { return JOG_CondRetParametro; }
    LIS_DestruirLista(jog->pecas);
    free(jog);
    return JOG_CondRetOk;
}

void JOG_Remove(void * possJog) {
    JOG_tpJogador * jog = (JOG_tpJogador *)possJog;
    if (possJog == NULL) return;
    LIS_DestruirLista(jog->pecas);
    free(jog);
}

/* * * * * * * * * *
 *
 *  Função: JOG Atualizar posição de uma peça
 *
 * * * * * * * * * */
JOG_CondRetErro JOG_AtualizaPeca(JOG_tpPeca * peca, void * novaCasa) {
    if (peca == NULL) { return JOG_CondRetParametro; }
    // Atualiza a posição da peça
    peca->pos = novaCasa;
    return JOG_CondRetOk;
}

/* * * * * * * * * *
 *
 *  Função: JOG Checar se o jogador tem peças
 *
 * * * * * * * * * */
int JOG_TemPecas(JOG_tpJogador * jog) {
    if (jog == NULL) { return -1; }
    IrInicioLista(jog->pecas);
    return LIS_ObterValor(jog->pecas) != NULL;
}

/* * * * * * * * * *
 *
 *  Função: JOG Obter posicao de uma peca peca
 *
 * * * * * * * * * */
void * JOG_LocalPeca(JOG_tpPeca * IDPeca) {
    if (IDPeca == NULL) { return NULL; }
    return IDPeca->pos;
}

/* * * * * * * * * *
 *
 *  Função: JOG Obter cor da peca
 *
 * * * * * * * * * */
JOG_tpCor JOG_CorPeca(JOG_tpPeca * IDPeca) {
    return IDPeca->cor;
}

/* * * * * * * * * *
 *
 *  Função: JOG Obter peca dado um índice
 *
 * * * * * * * * * */
JOG_tpPeca * JOG_PecaNaPosicao(JOG_tpJogador * jog, int indexPeca) {
    int i;

    if(jog==NULL||indexPeca<0||indexPeca>4) return NULL;

    IrInicioLista(jog->pecas);
    // Procura o elemento que guarda a peça (anda 0 se o ID for 0, 1 se o ID for 1, ...)
    for (i = 0; i < indexPeca; i++) {
        LIS_AvancarElementoCorrente(jog->pecas, 1);
        if (LIS_ObterValor(jog->pecas) == NULL) { return NULL; }
    }
    return LIS_ObterValor(jog->pecas);
}

/* * * * * * * * * *
 *
 *  Função: JOG Retorna as posições das peças do jogador (se há alguma)
 *
 * * * * * * * * * */
void * JOG_PosicoesDasPecas(JOG_tpJogador * jog, int * totalDePecas) {
    int tot = 0;
    int i = 0;
    JOG_tpPeca ** posicoes;
    if (jog == NULL) return NULL;
    IrInicioLista(jog->pecas);
    while (LIS_ObterValor(jog->pecas) != NULL) {
        tot ++;
        LIS_AvancarElementoCorrente(jog->pecas, 1);
    }
    if (tot == 0) return NULL;
    
    *totalDePecas = tot;
    posicoes = (JOG_tpPeca **)malloc(sizeof(JOG_tpPeca *)*tot);
    if (posicoes == NULL) { return NULL; }
    
    IrInicioLista(jog->pecas);
    for (i = 0; i < tot; i++) {
        posicoes[i] = (JOG_tpPeca *)LIS_ObterValor(jog->pecas);
        LIS_AvancarElementoCorrente(jog->pecas, 1);
    }
    return posicoes;
}

