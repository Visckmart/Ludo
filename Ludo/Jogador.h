//
//  Jogador.h
//  Ludo
//

#ifndef Jogador_h
#define Jogador_h


#include <stdio.h>
#include "Cor.h"

typedef struct Jogador JOG_tpJogador;
typedef struct Peca JOG_tpPeca;

typedef enum {
    
    JOG_CondRetOk,
    /* Concluiu corretamente */
    
    JOG_CondRetParametro,
    /* Par�metro nulo */
    
    JOG_CondRetFaltamPecas,
    /* Acabaram as pe�as a serem movidas */
    
    
} JOG_CondRetErro;

JOG_tpJogador * JOG_Cria(Cor);
JOG_CondRetErro JOG_Deleta(JOG_tpJogador *);
void JOG_Remove(void *);

JOG_CondRetErro JOG_AtualizaPeca(JOG_tpJogador *, int, void *);
char JOG_TemPecas(JOG_tpJogador *);
void * JOG_LocalPeca(JOG_tpPeca *);
Cor JOG_CorPeca(JOG_tpPeca *);
void * JOG_PosicoesDasPecas(JOG_tpJogador *, int *);


#endif /* Jogador_h */
