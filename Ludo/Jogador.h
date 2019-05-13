//
//  Jogador.h
//  Ludo
//

#if ! defined( JOGADOR_ )
    #define JOGADOR_


#include <stdio.h>

/***********************************************************************
*
*  $TC Tipo de dados: Cor
*
***********************************************************************/
typedef enum Cor {
    Nenhuma, Vermelho, Azul, Verde, Amarelo
}JOG_tpCor;

typedef struct Jogador JOG_tpJogador;
typedef struct Peca JOG_tpPeca;

typedef enum {
    
    JOG_CondRetOk,
    /* Concluiu corretamente */
    
    JOG_CondRetParametro,
    /* Parâmetro nulo */
    
    JOG_CondRetFaltamPecas,
    /* Acabaram as peças a serem movidas */
    
    

} JOG_CondRetErro;

JOG_tpJogador * JOG_Cria(JOG_tpCor);
JOG_CondRetErro JOG_Deleta(JOG_tpJogador *);
void JOG_Remove(void *);

JOG_CondRetErro JOG_AtualizaPeca(JOG_tpPeca * peca, void * novaCasa);
char JOG_TemPecas(JOG_tpJogador *);
void * JOG_LocalPeca(JOG_tpPeca *);
void * JOG_PecaNaPosicao(JOG_tpJogador * jog, int indexPeca);
JOG_tpCor JOG_CorPeca(JOG_tpPeca *);
void * JOG_PosicoesDasPecas(JOG_tpJogador *, int *);


#endif /* Jogador_h */
