//
//  Jogador.c
//  Ludo
//

#include "Jogador.h"
#include <stdlib.h>

struct Jogador {
    int a;
};

Jogador * JOG_Cria() {
    Jogador * j = (Jogador *)malloc(sizeof(Jogador));
    j->a = 10;
    return j;
}

char JOG_TemPecas(Jogador * j) {
    return j->a;
}
