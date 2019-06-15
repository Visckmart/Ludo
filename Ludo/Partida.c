/***************************************************************************
*  $MCI M�dulo de implementa��o: TAB  Partida
*
*  Arquivo gerado:              Partida.c
*  Letras identificadoras:      PAR
*
*
*  Projeto: INF 1301 / Ludo
*  Autores: 
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor            Data        Observa��es
*     1       Thiago Lamenza   14/jun/2019 inicio do desenvolvimento
*
***************************************************************************/
#define NUM_MAX_JOGADORES 4
#define NUM_MIN_JOGADORES 2
#define MIN_DADO 1
#define MAX_DADO 6

#include "Partida.h"
#include "Jogador.h"
#include "Tabuleiro.h"
#include <math.h>
#include <time.h>
#include <stdlib.h>

/* Variáveis estáticas do módulo */
static JOG_tpJogador vJogadores[NUM_MAX_JOGADORES];

static int numeroDeJogadores = 0;

/* Funções estáticas encapsuladas pelo módulo */
static int PAR_rolaDado(void);




PAR_CondRet PAR_inicia(JOG_tpCor *vetCores)
{
    int i;
    int numJog = PAR_obterNumJogadores();
    if(numJog>NUM_MAX_JOGADORES || numJog<NUM_MIN_JOGADORES) return PAR_CondRetParametro;

    for(i=0;i<numJog;i++)
    {
        if(JOG_Cria(vetCores[i],vJogadores[i])==JOG_CondRetMemoria) 
            return PAR_CondRetMemoria;
    }
    if(TAB_IniciaTabuleiro()==TAB_CondRetMemoria)
        return PAR_CondRetMemoria;

    srand(time(0));

    return PAR_CondRetOk;
}

int PAR_rolaDado()
{
    return rand()%(MAX_DADO-MIN_DADO+1)+MIN_DADO; /*Equivale à um número de MIN_DADO até MAX_DADO*/
}

static int PAR_obterNumJogadores() {
    int numJogad;
    do {
        printf("Digite o numero de jogadores (de %d a %d): ", NUM_MIN_JOGADORES, NUM_MAX_JOGADORE);
        scanf("%d", &numJogad);
    } while (numJogad < NUM_MIN_JOGADORES || numJogad > NUM_MAX_JODORES);
    return numJogad;
}

static JOG_tpPeca * PAR_escolhePeca(JOG_tpJogador * jog) {
    int totalPec = JOG_NumPecas(jog);
    int pecaEscolhida;
    if (totalPec < 1) return NULL;
    if (totalPec == 1) {
        printf("Somente uma peça poderia ser escolhida, jogada feita automaticamente.")
        return 1;
    }
    do {
        printf("Escolha a peça a ser jogada (entre 1 e %d): ", totalPec-1);
        scanf("%d", &pecaEscolhida);
    } while (pecaEscolhida < 1 || pecaEscolhida >= totalPec);
    return JOG_ObterPecaNaPosicao(jog, pecaEscolhida);
}

void PAR_finaliza() {
    int i;
    TAB_FinalizaTabuleiro()
    for (i = 0; i < numeroDeJogadores; i++) {
        JOG_Deleta(vJogadores[i]);
    }
}
