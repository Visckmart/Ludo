//
//  Jogador.h
//  Ludo
//

#ifndef Jogador_h
#define Jogador_h


#include <stdio.h>

typedef struct Jogador Jogador;

Jogador * JOG_Cria(void);
void JOG_Deleta(Jogador *);

void JOG_MovePeca(Jogador *, int);
void JOG_AvancaPeca(Jogador *, int);
char JOG_TemPecas(Jogador *);


#endif /* Jogador_h */
