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
	/*Concluir corretamente*/

	TAB_CondRetParametro,
	/*Erro nos parametros*/

	TAB_CondRetNaoAndou,
	/*Não executou a jogada e a peça permanece no mesmo lugar*/

	TAB_CondRetSemEspaco,
	/*Não tem espaço para inserção*/

	TAB_CondRetCasaVazia
	/*Não existe nada para remover*/

}TAB_CondRet;

Tabuleiro * TAB_IniciaTabuleiro(void);
void TAB_ResetaTabuleiro(Tabuleiro *);
char TAB_ValidaJogada(void);
void TAB_FazJogada(void);
//TAB_JogadasPossiveis()
Casa * TAB_ListaPecas(Jogador *);


#endif /* Tabuleiro_h */
