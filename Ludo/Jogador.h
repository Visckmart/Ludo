//
//  Jogador.h
//  Ludo
//

#ifndef Jogador_h
#define Jogador_h


#include <stdio.h>
#include "Cor.h"

typedef struct Jogador Jogador;
typedef struct Peca JOG_tpPeca;

Jogador * JOG_Cria(Cor);
void JOG_Deleta(Jogador *);

void JOG_MovePeca(Jogador *, int);
void JOG_AvancaPeca(Jogador *, int);
char JOG_TemPecas(Jogador *);


#endif /* Jogador_h */
