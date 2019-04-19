//
//  Tabuleiro.h
//  Ludo
//

#ifndef Tabuleiro_h
#define Tabuleiro_h


#include <stdio.h>
#include "Casa.h"

typedef struct Tabuleiro Tabuleiro;

Tabuleiro * TAB_IniciaTabuleiro(void);
void TAB_ResetaTabuleiro(Tabuleiro *);
char TAB_ValidaJogada(void);
void TAB_FazJogada(void);
//TAB_JogadasPossiveis()
Casa * TAB_ListaPecas(void);


#endif /* Tabuleiro_h */
