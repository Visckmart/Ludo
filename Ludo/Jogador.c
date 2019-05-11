//
//  Jogador.c
//  Ludo
//

#include "Jogador.h"
#include <stdlib.h>
#include "Lista.h"

/***********************************************************************
*
*  $TC Tipo de dados: Peça do jogador
*
***********************************************************************/
struct Peca {
    void * pos;
    Cor cor;
}

/***********************************************************************
*
*  $TC Tipo de dados: Jogador
*
***********************************************************************/
struct Jogador {
    LIS_tppLista * pecas;
    Cor cor;
};

/* * * * * * * * * *
 *
 *  Função: JOG Criar jogador
 *
 * * * * * * * * * */
JOG_tpJogador * JOG_Cria(Cor corDasPecas) {
    // Aloca um espaço para o jogador
    JOG_tpJogador * jog = (JOG_tpJogador *)malloc(sizeof(Jogador));
    if (jog == NULL) return NULL;
    
    // Cria a primeira peça
    jog->pecas = LIS_CriarLista(JOG_Deleta);
    if (jog->pecas == NULL) { free(jog); return NULL; }
    // Cria elementos de uma lista encadeada que guarda peças
    for (int i = 1; i < 4; i++) {
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

/* * * * * * * * * *
 *
 *  Função: JOG Atualizar posição de uma peça
 *
 * * * * * * * * * */
JOG_CondRetErro JOG_AtualizaPeca(JOG_tpJogador * jog, int IDPeca, void * novaCasa) {
    if (jog == NULL || IDPeca == NULL || novaCasa == NULL) { return JOG_CondRetParametro; }
    IrInicioLista(jog->pecas);
    // Procura o elemento que guarda a peça (anda 0 se o ID for 0, 1 se o ID for 1, ...)
    for (int i = 0; i < IDPeca; i++) {
        LIS_AvancarElementoCorrente(jog->pecas);
        if (LIS_ObterValor(jog->pecas) == NULL) {
            return JOG_CondRetFaltamPecas;
        }
    }
    // Pega a peça que está guardada no elemento
    JOG_tpPeca * p = (JOG_tpPeca *)LIS_ObterValor(pcs);
    // Atualiza a posição da peça
    jog->pos = novaCasa;
	return JOG_CondRetOk
}

/* * * * * * * * * *
 *
 *  Função: JOG Checar se o jogador tem peças
 *
 * * * * * * * * * */
char JOG_TemPecas(JOG_tpJogador * jog) {
    IrInicioLista(jog->pecas);
    return LIS_ObterValor(jog->pecas) != NULL;
}

/* * * * * * * * * *
 *
 *  Função: JOG Obter posicao de uma peca peca
 *
 * * * * * * * * * */
void * JOG_LocalPeca(JOG_tpPeca * IDpeca) {
    return IDPeca->pos;
}

/* * * * * * * * * *
 *
 *  Função: JOG Obter cor da peca
 *
 * * * * * * * * * */
Cor JOG_CorPeca(JOG_tpPeca * IDPeca) {
    return IDPeca->cor;
}

/* * * * * * * * * *
 *
 *  Função: JOG Retorna as posições das peças do jogador (se há alguma)
 *
 * * * * * * * * * */
void * JOG_PosicoesDasPecas(JOG_tpJogador * jog, int * totalDePecas) {
    int tot = 0;
    IrInicioLista(jog->pecas);
    while (LIS_ObterValor(jog->pecas) != NULL) {
        tot ++;
        LIS_AvancarElementoCorrente(l);
    }
    if (tot == 0) return NULL;

    *totalDePecas = tot;
    void * posicoes = (int *)malloc(sizeof(char)*tot);
    if (posicoes == NULL) { return NULL; }
    
    IrInicioLista(jog->pecas);
    for (int i = 0; i < tot; i++) {
        posicoes[i] = LIS_ObterValor(l);
        LIS_AvancarElementoCorrente(l);
    }
    return posicoes;
}
