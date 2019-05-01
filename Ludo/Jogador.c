//
//  Jogador.c
//  Ludo
//

#include "Jogador.h"
#include <stdlib.h>
#include "Casa.h"
#include "Circular.h"

struct Jogador {
    CIR_lstCircular * pecas;
    Cor cor;
};

Jogador * JOG_Cria(Cor corDasPecas) {
    // Aloca um espaço para o jogador
    Jogador * j = (Jogador *)malloc(sizeof(Jogador));
    
    // Cria a primeira peça
    Casa * c = CAS_Cria();
    j->pecas = CIR_CriaLista(c);
    // Cria as peças adicionais
    for (int i = 1; i < 4; i++) {
        Casa * c = CAS_Cria();
        CIR_lstCircular * l = CIR_CriaLista(c);
        CIR_InsereElemento(l, j->pecas);
    }
    
    // Guarda a cor do jogador
    j->cor = corDasPecas;
    
    // Retorna o jogador criado
    return j;
}

char JOG_TemPecas(Jogador * j) {
    return j->pecas != NULL;
}
