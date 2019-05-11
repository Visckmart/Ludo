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

typedef enum {

	JOG_CondRetOk,
	/* Concluiu corretamente */

	JOG_CondRetParametro,
	/* Parâmetro nulo */

	JOG_CondRetFaltamPecas,
	/* Acabaram as peças a serem movidas */


} JOG_CondRetErro;


Jogador * JOG_Cria(Cor);
void JOG_Deleta(Jogador *);

void JOG_MovePeca(Jogador *, int);
void JOG_AvancaPeca(Jogador *, int);
char JOG_TemPecas(Jogador *);


#endif /* Jogador_h */
