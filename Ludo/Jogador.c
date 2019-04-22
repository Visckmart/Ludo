//
//  Jogador.c
//  Ludo
//

#include "Jogador.h"
#include <stdlib.h>
#include "Casa.h"

struct Jogador {
    Casa * pecas;
    Cor cor;
};

Jogador * JOG_Cria(Cor corDasPecas) {
    Jogador * j = (Jogador *)malloc(sizeof(Jogador));
    j->pecas = (Casa *)malloc(sizeof(int) * 4);
    for (int i = 0; i < 4; i++) {
        j->pecas[i] = CAS_Cria();
    }
    j->cor = corDasPecas;
    return j;
}

char JOG_TemPecas(Jogador * j) {
    return j->pecas != NULL;
}
