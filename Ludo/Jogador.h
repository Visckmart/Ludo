#if ! defined( JOGADOR_ )
    #define JOGADOR_


#include <stdio.h>

/***************************************************************************
 *
 *  $MCD Módulo de definição: JOG  Jogador
 *
 *  Arquivo gerado:              Jogador.h
 *  Letras identificadoras:      JOG
 *
 *
 *  Projeto: INF1301 / Ludo
 *  Autores: Victor Martins
 *
 *  $HA Histórico de evolução:
 *     Versão  Autor             Data         Observações
 *     1       Victor Martins    03/mai/2019  Desenvolvimento inicial
 *
 *
 *  $ED Descrição do módulo
 *     Implementa o jogador do jogo Ludo
 *
 *     O módulo é responsável por criar e alterar os dados de um jogador.
 *     O módulo é capaz de administrar mais de um jogador.
 *
 *     O jogador começa com 4 peças e uma cor.
 *     Cada peça está em uma casa e tem uma cor.
 
 *     As funções verificam se o ponteiro para jogador que foi recebido é válido,
 *     além de verificar (no caso de funções que alteram peças), se a peça
 *     existe antes de tentar alterá-la.
 *
 ***************************************************************************/

#include <stdio.h>

/***********************************************************************
*
*  $TC Tipo de dados: Cor
*
***********************************************************************/
typedef enum Cor {
    Nenhuma, Vermelho, Azul, Verde, Amarelo
} JOG_tpCor;

typedef struct Jogador JOG_tpJogador;
typedef struct Peca JOG_tpPeca;

/***********************************************************************
 *
 *  $TC Tipo de dados: JOG Condições de retorno
 *
 *
 *  $ED Descrição do tipo
 *     Condições de retorno das funções de Jogador
 *
 ***********************************************************************/
typedef enum {
    
    JOG_CondRetOk,
    /* Concluiu corretamente */
    
    JOG_CondRetParametro,
    /* Par�metro incorreto */
    
    JOG_CondRetFaltamPecas,
    /* Acabaram as pe�as a serem movidas */

} JOG_CondRetErro;

/***********************************************************************
 *
 *  $FC Função: JOG  &Cria
 *
 *  $ED Descrição da função
 *     Deve ser a primeira função executada no módulo.
 *     Cria um jogador com 4 peças e a cor recebida.
 *
 *  $EP Parâmetros
 *      A cor do jogador
 *
 *  $FV Valor retornado
 *     Se executou corretamente retorna um ponteiro válido.
 *
 *   Assertivas:
 *     Caso haja erro de memória retorna NULL.
 ***********************************************************************/
JOG_tpJogador * JOG_Cria(JOG_tpCor);

/***********************************************************************
 *
 *  $FC Função: JOG  &Deleta
 *
 *  $ED Descrição da função
 *     Deleta um jogador, deletando suas peças corretamente.
 *
 *  $EP Parâmetros
 *     Um ponteiro para um jogador.
 *
 *   Assertivas:
 *     Checa se o ponteiro recebido é válido.
 ***********************************************************************/
JOG_CondRetErro JOG_Deleta(JOG_tpJogador *);

void JOG_Remove(void *);

/***********************************************************************
 *
 *  $FC Função: JOG  &AtualizaPeca
 *
 *  $ED Descrição da função
 *     Atualiza a casa em que determinada peça do jogador está.
 *
 *  $EP Parâmetros
 *     Um ponteiro para uma peça e um ponteiro para a nova casa.
 *
 *  $FV Valor retornado
 *     Se executou corretamente, retorna JOG_CondRetOk.
 *     Se um dos ponteiros recebidos é nulo, retorna JOG_CondRetParametro.
 *
 *   Assertivas:
 *     Checa se os ponteiros recebidos são válidos.
 ***********************************************************************/
JOG_CondRetErro JOG_AtualizaPeca(JOG_tpPeca * peca, void * novaCasa);

/***********************************************************************
 *
 *  $FC Função: JOG  &TemPecas
 *
 *  $ED Descrição da função
 *     Checa se o jogador tem alguma peça.
 *
 *  $EP Parâmetros
 *     Um ponteiro para um jogador.
 *
 *  $FV Valor retornado
 *     Se o jogador tem ao menos uma peça, retorna 1.
 *     Se o jogador não tem nenhuma peça, retorna 0.
 *     Caso o ponteiro recebido não seja váludo, retorna -1.
 *
 *   Assertivas:
 *     Checa se o ponteiro recebido é válido.
 ***********************************************************************/
int JOG_TemPecas(JOG_tpJogador *);

/***********************************************************************
 *
 *  $FC Função: JOG  &LocalPeca
 *
 *  $ED Descrição da função
 *     Retorna a casa a qual a peça se encontra.
 *
 *  $EP Parâmetros
 *     Um ponteiro para uma peça.
 *
 *  $FV Valor retornado
 *     Um ponteiro para uma casa a qual a peça passada como argumento se
 *     ou NULL, caso o ponteiro recebido seja inválido.
 *
 *   Assertivas:
 *     Checa se o ponteiro recebido é válido.
 ***********************************************************************/
void * JOG_LocalPeca(JOG_tpPeca *);

/***********************************************************************
 *
 *  $FC Função: JOG  &CorPeca
 *
 *  $ED Descrição da função
 *     Retorna a cor da peça passada como argumento.
 *
 *  $EP Parâmetros
 *     Um ponteiro para uma peça. Esse ponteiro tem que ser válido e apontar
 *     para uma peça.
 *
 *  $FV Valor retornado
 *     A cor da peça.
 *     -1 caso o ponteiro seja NULL
 *
 *   Assertivas:
 *     Checa se o ponteiro recebido é válido.
 ***********************************************************************/
JOG_tpCor JOG_CorPeca(JOG_tpPeca *);

/***********************************************************************
 *
 *  $FC Função: JOG  &PecaNaPosicao
 *
 *  $ED Descrição da função
 *     Retorna a peça que está no indíce passado como argumento.
 *
 *  $EP Parâmetros
 *     Um ponteiro para um jogador e um inteiro com o índice da peça.
 *
 *  $FV Valor retornado
 *     Um ponteiro para uma peça ou NULL (se o ponteiro para jogador for nulo
 *     ou se não houver nenhuma peça).
 *
 *   Assertivas:
 *     Checa se o ponteiro recebido é válido.
 ***********************************************************************/
JOG_tpPeca * JOG_PecaNaPosicao(JOG_tpJogador * jog, int indexPeca);

/***********************************************************************
 *
 *  $FC Função: JOG  &PosicoesDasPecas
 *
 *  $ED Descrição da função
 *     Retorna uma lista com as casas que as peças do jogador passado se encontram.
 *
 *  $EP Parâmetros
 *     Um ponteiro para um jogador e um ponteiro para um inteiro, que receberá
 *     a quantidade de casas retornadas.
 *
 *  $FV Valor retornado
 *     Um vetor com as casas as quais as peças do jogador se encontram, ou NULL
 *     caso ponteiro para Jogador seja inválido ou ele não tenha nenhuma peça.
 *
 *   Assertivas:
 *     Checa se o ponteiro recebido é válido, se o número de peças é maior que
 *     zero e se a alocação de memória foi feita com sucesso.
 ***********************************************************************/
void * JOG_PosicoesDasPecas(JOG_tpJogador *, int *);


#endif /* JOGADOR_ */
