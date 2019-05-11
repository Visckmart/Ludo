//
//  Tabuleiro.h
//  Ludo
//

#ifndef Tabuleiro_h
#define Tabuleiro_h


#include <stdio.h>
#include "Casa.h"
#include "Jogador.h"

typedef enum{

	TAB_CondRetOk,

	TAB_CondRetParametro,

	TAB_CondRetNaoAndou,

	TAB_CondRetSemEspaco,

	TAB_CondRetCasaVazia

}TAB_CondRet;

Tabuleiro * TAB_IniciaTabuleiro(void);
void TAB_ResetaTabuleiro(Tabuleiro *);
char TAB_ValidaJogada(void);
void TAB_FazJogada(void);
//TAB_JogadasPossiveis()
Casa * TAB_ListaPecas(Jogador *);


#endif /* Tabuleiro_h */
