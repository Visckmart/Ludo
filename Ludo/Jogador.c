//
//  Jogador.c
//  Ludo
//

#include "Jogador.h"
#include <stdlib.h>
#include "Casa.h"
#include "Circular.h"

struct Peca {
    Casa * pos;
    Cor cor;
}

struct Jogador {
    LIS_tppLista * pecas;
    Cor cor;
};

Jogador * JOG_Cria(Cor corDasPecas) {
    // Aloca um espaço para o jogador
    Jogador * j = (Jogador *)malloc(sizeof(Jogador));
    
    // Cria a primeira peça
    j->pecas = LIS_CriarLista(JOG_Deleta);
    
    // Cria elementos de uma lista encadeada que guarda peças
    for (int i = 1; i < 4; i++) {
        JOG_tpPeca * p = (JOG_tpPeca *)malloc(sizeof(JOG_tpPeca));
        p->pos = -1;
        p->cor = corDasPecas;
        j->pecas = LIS_InserirElementoApos(j->pecas, p);
    }
    
    // Guarda a cor do jogador
    j->cor = corDasPecas;
    
    // Retorna o jogador criado
    return j;
}

void JOG_Deleta(Jogador * j) {
    LIS_DestruirLista(j->pecas);
    free(j);
}

void JOG_AtualizaPeca(Jogador * j, int IDPeca, Casa * novaCasa) {
    LIS_tppLista * pcs = j->pecas;
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
    p->pos = novaCasa;
}

char JOG_TemPecas(Jogador * j) {
    return j->pecas != NULL;
}

int * JOG_PosicoesDasPecas(Jogador * jogador, int * totalDePecas) {
    int tot = 0;
    LIS_tppLista * l = jogador->pecas;
    while (l != NULL) {
        tot ++;
        l = LIS_AvancarElementoCorrente(l);
    }
    if (tot == 0) return NULL;

    *totalDePecas = tot;
    int * posicoes = (int *)malloc(sizeof(int)*tot);
    if (posicoes == NULL) { return NULL; }
    
    l = jogador->pecas;
    for (int i = 0; i < tot; i++) {
        posicoes[i] = ((JOG_tpPeca *)LIS_ObterValor(l));
        l = LIS_AvancarElementoCorrente(l);
    }
    return posicoes;
}
