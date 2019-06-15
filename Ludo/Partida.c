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
static vJogadores[NUM_MAX_JOGADORES];
static turno = 0;

/*Funções estátivas emcapsuladas pelo módulo*/
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
        printf("Digite o numero de jogadores (de 2 a 4): ");
        scanf("%d", &numJogad);
    } while (numJogad < 2 || numJogad > 4);
    return numJogad;
}
    
