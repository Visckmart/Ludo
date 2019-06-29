/***************************************************************************
*  $MCI Módulo de implementação: JOG  Jogador
*
*  Arquivo gerado:              Jogador.c
*  Letras identificadoras:      JOG
*
*
*  Projeto: INF 1301 / Ludo
*  Autores: Victor Martins
*
*  $HA Histórico de evolução:
*     Versão  Autor            Data        Observações
*     1       Victor Martins   3/Maio/2019 inicio do desenvolvimento
*
***************************************************************************/
#include "Jogador.h"
#include <stdlib.h>
#include "LISTA.H"
#define num_jogadores 4
#define num_pecas 4

/***********************************************************************
*
*  $TC Tipo de dados: JOG Peça do jogador
*
***********************************************************************/
struct Peca {
    void * pos;
    JOG_tpCor cor;
};

/***********************************************************************
*
*  $TC Tipo de dados: JOG Jogador
*
***********************************************************************/
struct Jogador {
    LIS_tppLista pecas;
    JOG_tpCor cor;
};

static void JOG_LiberaPeca(void *);

/* * * * * * * * * *
 *
 *  Função: JOG Criar jogador
 *
 * * * * * * * * * */
JOG_CondRetErro JOG_Cria(JOG_tpCor corDasPecas,JOG_tpJogador **pResultado) {
    int i;
    // Aloca um espaço para o jogador
    if(pResultado==NULL) return JOG_CondRetParametro;
    *pResultado = (JOG_tpJogador *)malloc(sizeof(JOG_tpJogador));
    if ((*pResultado) == NULL) return JOG_CondRetMemoria;
    
    // Cria a primeira peça
    (*pResultado)->pecas = LIS_CriarLista(JOG_LiberaPeca);
    if ((*pResultado)->pecas == NULL) { free((*pResultado)); return JOG_CondRetMemoria; }
    // Cria elementos de uma lista encadeada que guarda peças
    for (i = 0; i < num_jogadores; i++) {
        JOG_tpPeca * p = (JOG_tpPeca *)malloc(sizeof(JOG_tpPeca));
        if (p == NULL) { JOG_Deleta((*pResultado)); return JOG_CondRetMemoria; }
        p->pos = NULL;
        p->cor = corDasPecas;
        LIS_InserirElementoApos((*pResultado)->pecas, p);
    }
    
    // Guarda a cor do jogador
    (*pResultado)->cor = corDasPecas;
    
    // Retorna o jogador criado
    return JOG_CondRetOk;
}

/* * * * * * * * * *
 *
 *  Função: JOG Deletar jogador
 *
 * * * * * * * * * */
JOG_CondRetErro JOG_Deleta(JOG_tpJogador * jog) {
    if (jog == NULL) { return JOG_CondRetParametro; }
    LIS_DestruirLista(jog->pecas);
    free(jog);
    return JOG_CondRetOk;
}

/***********************************************************************	
*	
*  $FC Função: JOG  &LiberaPeca
*	
*  $ED Descrição da função	
*     Libera a memória usada por uma determinada peça.
*
*  $EP Parâmetros	
*	  *peca - ponteiro para uma peça (do tipo void*)
*	
*   Assertivas:	
*     Checa se o ponteiro é válido.
*
***********************************************************************/	
static void JOG_LiberaPeca(void * pontPeca) {
	if (peca == NULL) { return NULL; }
	JOG_tpPeca * peca = (JOG_tpPeca *)pontPeca;
    free(peca);
}

/***********************************************************************	
*	
*  $FC Função: JOG  &RemovePeca
*	
*  $ED Descrição da função	
*     Remove uma peça da lista de peças do jogador.
*
*  $EP Parâmetros	
*	  *peca - ponteiro para uma peça
*	  *jog - ponteiro para um jogador
*	
*  $FV Valor retornado	
*     Retorna JOG_CondRetOk caso execute corretamente.
*     Retorna JOG_CondRetParametro caso um dos ponteiros recebidos
*     não seja válido ou se a peça não foi encontrada.
*
*   Assertivas:	
*     Checa se os ponteiros recebidos são válidos.
*
***********************************************************************/
JOG_CondRetErro JOG_RemovePeca(JOG_tpPeca *peca,JOG_tpJogador *jog)
{
    if(peca==NULL || jog==NULL) return JOG_CondRetParametro;
    LIS_IrInicioLista(jog->pecas);
    if(LIS_ProcurarValor(jog->pecas,peca)!=LIS_CondRetOK)
    {
        return JOG_CondRetParametro;
    }
    LIS_ExcluirElemento(jog->pecas);
    return JOG_CondRetOk;
}


/* * * * * * * * * *
 *
 *  Função: JOG Atualizar posição de uma peça
 *
 * * * * * * * * * */
JOG_CondRetErro JOG_AtualizaPeca(JOG_tpPeca * peca, void * novaCasa) {
    if (peca == NULL) { return JOG_CondRetParametro; }
    // Atualiza a posição da peça
    peca->pos = novaCasa;
    return JOG_CondRetOk;
}

/* * * * * * * * * *
 *
 *  Função: JOG Checar se o jogador tem peças
 *
 * * * * * * * * * */
JOG_CondRetErro JOG_TemPecas(JOG_tpJogador * jog) {
    if (jog == NULL) { return JOG_CondRetParametro; }
    LIS_IrInicioLista(jog->pecas);
	if (LIS_ObterValor(jog->pecas) != NULL) {
		return JOG_CondRetTemPecas;
	}
	else { return JOG_CondRetNaoTemPecas; }
}

/* * * * * * * * * *
 *
 *  Função: JOG Obter posicao de uma peca peca
 *
 * * * * * * * * * */
void * JOG_ObterLocalPeca(JOG_tpPeca * IDPeca) {
    if (IDPeca == NULL) { return NULL; }
    return IDPeca->pos;
}

/* * * * * * * * * *
 *
 *  Função: JOG Obter cor da peca
 *
 * * * * * * * * * */
JOG_tpCor JOG_ObterCorPeca(JOG_tpPeca * IDPeca) {
	if(IDPeca==NULL) return -1;
    return IDPeca->cor;
}

/* * * * * * * * * *
 *
 *  Função: JOG Obter peca dado um índice
 *
 * * * * * * * * * */
JOG_tpPeca * JOG_ObterPecaNaPosicao(JOG_tpJogador * jog, int indexPeca) {
    int i;

    if(jog==NULL||indexPeca<0||indexPeca>num_pecas) return NULL;

    LIS_IrInicioLista(jog->pecas);
    // Procura o elemento que guarda a peça (anda 0 se o ID for 0, 1 se o ID for 1, ...)
    for (i = 0; i < indexPeca; i++) {
        LIS_AvancarElementoCorrente(jog->pecas, 1);
        if (LIS_ObterValor(jog->pecas) == NULL) { return NULL; }
    }
    return LIS_ObterValor(jog->pecas);
}

/* * * * * * * * * *
 *
 *  Função: JOG Retorna as posições das peças do jogador (se há alguma)
 *
 * * * * * * * * * */
JOG_CondRetErro JOG_ObterPosicoesDasPecas(JOG_tpJogador * jog, int * totalDePecas,void ***posicoes) {
    int tot = 0,i;

    if (jog == NULL || totalDePecas==NULL || posicoes==NULL) return JOG_CondRetParametro;

    LIS_IrInicioLista(jog->pecas);
    while (LIS_ObterValor(jog->pecas) != NULL) {

        tot++;
        if (LIS_AvancarElementoCorrente(jog->pecas, 1) == LIS_CondRetFimLista) break;
    }  
    (*posicoes) = (void**) malloc(sizeof(void*)*tot);
    if((*posicoes)==NULL) return JOG_CondRetMemoria;
    *totalDePecas = tot;

    LIS_IrInicioLista(jog->pecas);
    for(i=0;i<tot;i++)
    {
        (*posicoes)[i] = JOG_ObterLocalPeca(LIS_ObterValor(jog->pecas));
        LIS_AvancarElementoCorrente(jog->pecas,1);
    }
    return JOG_CondRetOk;
}
