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

static int numeroDeJogadores = 0;

/*Funções estátivas emcapsuladas pelo módulo*/
static int PAR_rolaDado(void);




PAR_CondRet PAR_inicia(JOG_tpCor *vetCores)
{
    int i;
    int numJog = PAR_obterNumJogadores();
    if(numJog>NUM_MAX_JOGADORES || numJog<NUM_MIN_JOGADORES) return PAR_CondRetParametro;

    numeroDeJogadores = numJog;

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

static PAR_CondRet PAR_escolhePeca(JOG_tpJogador * jog,int *indPeca,int *vEscolhidas) {
    int i,totalPec;
    int pecaEscolhida;
    void * casas = JOG_ObterPosicoesDasPecas(jog, &totalPec);
    
    for(i=0;i<totalPec;i++)
    {
        if(!vEscolhidas[i]) /*Se houver ao menos uma escolha possível nota esse fato*/
        {
            i=-1;/*Seta i como um valor distinto para detectar que existe escolha possível*/
            break;
        }
    }
    if(i!=-1)
    {
        printf("Nao ha escolhas possiveis, finalizando turno...\n");
        return PAR_CondRetSemEscolha;
    }

    if (totalPec < 1) return PAR_CondRetParametro;
    if (totalPec == 1) {
        printf("Somente uma peça poderia ser escolhida, jogada feita automaticamente.");
        indPeca = 1;
        return PAR_CondRetOk;
    }
    TAB_DesenhaTabuleiro(casas,totalPec);
    do {
        printf("Escolha a peça a ser jogada (entre 1 e %d): ", totalPec-1);
        scanf("%d", &pecaEscolhida);
    } while (pecaEscolhida < 1 || pecaEscolhida >= totalPec);
    *indPeca = pecaEscolhida;
    vEscolhidas[*indPeca] = 1;

    return PAR_CondRetOk;
}

PAR_CondRet PAR_executaRodada(int turno)
{
    int indPeca,dado;

    /*Vetor das escolhas feitas até o momento
    * No inicio é zerado pois nenhuma escolha foi feita
    * Se todas foram feitas não há jogada possível*/
    int vEscolhas[4] = {0,0,0,0}; 

    JOG_tpPeca *peca;
    TAB_CondRet condRetTab;
    char *cores[4] = {"Vermelho","Azul","Verde","Amarelo"};
    printf("Jogador %s, sua vez.\n",cores[turno]);

    dado = PAR_rolaDado();
    printf("Voce rodou %d no dado.\n",dado);


    do
    {
        if(PAR_escolhePeca(vJogadores[turno],&indPeca,vEscolhas)==PAR_CondRetSemEscolha)
        {
            TAB_DesenhaTabuleiro;
            return PAR_CondRetSemEscolha;
        }

        peca = JOG_ObterPecaNaPosicao(vJogadores[turno],indPeca);
        if(peca==NULL) return PAR_CondRetParametro; 
        /*Retorna CondRetParametro quando a peça não é encontrada*/

        if(condRetTab == TAB_CondRetChegouFinal)
        {
            /*Condição quando a peça chega no final*/
            return PAR_CondRetOk;
        }

        if(condRetTab == TAB_CondRetNaoAndou)
        {
            printf("Essa peca nao pode se mover, escolha outra.\n");
        }
    }while(condRetTab = TAB_FazJogada(peca,dado) != TAB_CondRetOk);
    
    TAB_DesenhaTabuleiro(NULL,0);
    printf("Fim da jogada.\n");
    return PAR_CondRetOk;
}

void PAR_finaliza() {
    int i;
    TAB_FinalizaTabuleiro();
    for (i = 0; i < numeroDeJogadores; i++) {
        JOG_Deleta(vJogadores[i]);
    }
}