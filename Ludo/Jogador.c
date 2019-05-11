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

Jogador * JOG_Cria(Cor corDasPecas) {
    // Aloca um espaço para o jogador
    Jogador * jog = (Jogador *)malloc(sizeof(Jogador));
    
    // Cria a primeira peça
    jog->pecas = LIS_CriarLista(JOG_Deleta);
    
    // Cria elementos de uma lista encadeada que guarda peças
    for (int i = 1; i < 4; i++) {
        JOG_tpPeca * p = (JOG_tpPeca *)malloc(sizeof(JOG_tpPeca));
        p->pos = NULL;
        p->cor = corDasPecas;
        jog->pecas = LIS_InserirElementoApos(j->pecas, p);
    }
    
    // Guarda a cor do jogador
    jog->cor = corDasPecas;
    
    // Retorna o jogador criado
    return jog;
}

void JOG_Deleta(Jogador * jog) {
    LIS_DestruirLista(jog->pecas);
    free(jog);
}

void JOG_AtualizaPeca(Jogador * jog, int IDPeca, void * novaCasa) {
    LIS_tppLista * pcs = jog->pecas;
    // Procura o elemento que guarda a peça (anda 0 se o ID for 0, 1 se o ID for 1, ...)
    for (int i = 0; i < IDPeca; i++) {
        pcs = LIS_AvancarElementoCorrente(pcs);
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

char JOG_TemPecas(Jogador * jog) {
    return jog->pecas != NULL;
}

void * JOG_LocalPeca(Jogador * jog, int IDpeca) {
    LIS_tppLista * pcs = jog->pecas;
    // Procura o elemento que guarda a peça (anda 0 se o ID for 0, 1 se o ID for 1, ...)
    for (int i = 0; i < IDPeca; i++) {
        pcs = LIS_AvancarElementoCorrente(pcs);
        if (pcs == NULL) {
            printf("Erro");
            return NULL;
        }
    }
    return LIS_ObterValor(pcs);
}
void * JOG_PosicoesDasPecas(Jogador * jog, int * totalDePecas) {
    int tot = 0;
    LIS_tppLista * l = jog->pecas;
    while (l != NULL) {
        tot ++;
        l = LIS_AvancarElementoCorrente(l);
    }
    if (tot == 0) return NULL;

    *totalDePecas = tot;
    void * posicoes = (int *)malloc(sizeof(char)*tot);
    if (posicoes == NULL) { return NULL; }
    
    l = jog->pecas;
    for (int i = 0; i < tot; i++) {
        posicoes[i] = LIS_ObterValor(l);
        l = LIS_AvancarElementoCorrente(l);
    }
    return posicoes;
}
