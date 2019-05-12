//
//  Jogador.h
//  Ludo
//

#if ! defined( JOGADOR_ )
#define JOGADOR_


/***********************************************************************
*
*  $TC Tipo de dados: Cor
*
***********************************************************************/
typedef enum {
    Nenhuma, Vermelho, Azul, Verde, Amarelo
}JOG_tpCor;

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

JOG_tpJogador *JOG_Cria(JOG_tpCor Cor);
JOG_CondRetErro JOG_Deleta(JOG_tpJogador *jog);
void JOG_Remove(void *possJog);

JOG_CondRetErro JOG_AtualizaPeca(JOG_tpPeca * peca, void * novaCasa);
char JOG_TemPecas(JOG_tpJogador *jog);
void * JOG_LocalPeca(JOG_tpPeca *IDPeca);
JOG_tpCor JOG_CorPeca(JOG_tpPeca *IDPeca);
void * JOG_PecaNaPosicao(JOG_tpJogador * jog, int indexPeca);
void * JOG_PosicoesDasPecas(JOG_tpJogador *jog, int *totalDePecas);


#endif /* Jogador_h */
