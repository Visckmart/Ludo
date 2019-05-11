//
//  Jogador.c
//  Ludo
//

#include "Jogador.h"
#include <stdlib.h>
#include "Circular.h"

struct Peca {
    void * pos;
    Cor cor;
}

struct Jogador {
    LIS_tppLista * pecas;
    Cor cor;
};

JOG_tpJogador * JOG_Cria(Cor corDasPecas) {
    // Aloca um espaço para o jogador
    JOG_tpJogador * jog = (JOG_tpJogador *)malloc(sizeof(Jogador));
    
    // Cria a primeira peça
    jog->pecas = LIS_CriarLista(JOG_Deleta);
    
    // Cria elementos de uma lista encadeada que guarda peças
    for (int i = 1; i < 4; i++) {
        JOG_tpPeca * p = (JOG_tpPeca *)malloc(sizeof(JOG_tpPeca));
        p->pos = NULL;
        p->cor = corDasPecas;
        LIS_InserirElementoApos(j->pecas, p);
    }
    
    // Guarda a cor do jogador
    jog->cor = corDasPecas;
    
    // Retorna o jogador criado
    return jog;
}

void JOG_Deleta(JOG_tpJogador * jog) {
    LIS_DestruirLista(jog->pecas);
    free(jog);
}

void JOG_AtualizaPeca(JOG_tpJogador * jog, int IDPeca, void * novaCasa) {
    IrInicioLista(jog->pecas);
    // Procura o elemento que guarda a peça (anda 0 se o ID for 0, 1 se o ID for 1, ...)
    for (int i = 0; i < IDPeca; i++) {
        LIS_AvancarElementoCorrente(pcs);
        if (pcs == NULL) {
            printf("Erro");
            return;
        }
    }
    // Pega a peça que está guardada no elemento
    JOG_tpPeca * p = (JOG_tpPeca *)LIS_ObterValor(pcs);
    // Atualiza a posição da peça
    jog->pos = novaCasa;
}

char JOG_TemPecas(JOG_tpJogador * jog) {
    return jog->pecas != NULL;
}

void * JOG_LocalPeca(JOG_tpJogador * jog, JOG_tpPeca IDpeca) {
    return IDPeca->pos;
}

Cor JOG_CorPeca(JOG_tpJogador * jog, JOG_tpPeca IDPeca) {
    return IDPeca->cor;
}

void * JOG_PosicoesDasPecas(JOG_tpJogador * jog, int * totalDePecas) {
    int tot = 0;
    IrInicioLista(jog->pecas);
    while (l != NULL) {
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
