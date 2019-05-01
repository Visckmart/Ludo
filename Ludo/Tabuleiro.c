//
//  Tabuleiro.c
//  Ludo
//

#include "Tabuleiro.h"
#include <stdlib.h>

struct Tabuleiro {
    Jogador * jogadores;
};

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

//Casa * TAB_ListaPecas(Jogador * jogador) {
//    int tot = 0;
//    while (jogador->pecas) {
//        <#statements#>
//    }
//}
