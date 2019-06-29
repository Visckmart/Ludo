/***************************************************************************
*  $MCI M�dulo de implementa��o: TAB  Partida
*
*  Arquivo gerado:              Partida.c
*  Letras identificadoras:      PAR
*
*
*  Projeto: INF 1301 / Ludo
*  Autores: Victor Martins,Thiago Lamenza, Guilherme Murad
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor            Data        Observa��es
*     1       Thiago Lamenza   14/jun/2019 inicio do desenvolvimento
*
***************************************************************************/
#define NUM_MAX_JOGADORES 4
#define NUM_MIN_JOGADORES 2
#define NUM_MAX_PECAS_POR_JOGADOR 4
#define NUM_CORES 4
#define MIN_DADO 1
#define MAX_DADO 6

#include "Partida.h"
#include "Jogador.h"
#include "Tabuleiro.h"
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

/* Variáveis estáticas do módulo */
static JOG_tpJogador *vJogadores[NUM_MAX_JOGADORES];

static char *cores[4] = {"Vermelho","Azul","Verde","Amarelo"};
static int numeroDeJogadores = 0;

/*Funções estáticas encapsuladas pelo módulo*/
static int PAR_RolaDado(void);
static PAR_CondRet PAR_EscolhePeca(int *indPeca, int totalPec);
static int PAR_obterNumJogadores();
static PAR_CondRet PAR_ExecutaRodada(int turno);
static void PAR_Finaliza();

	
PAR_CondRet PAR_Inicia()
{
    int i,turno=0;
    int numJog = PAR_obterNumJogadores();
    TAB_CondRet condRet;
    JOG_tpCor vCores[NUM_CORES] = {Vermelho,Azul,Verde,Amarelo};

    numeroDeJogadores = numJog;

    for(i=0;i<numJog;i++)
    {
        if(JOG_Cria(vCores[i],&vJogadores[i])==JOG_CondRetMemoria) 
            return PAR_CondRetMemoria;
    }
    if(TAB_IniciaTabuleiro()==TAB_CondRetMemoria)
        return PAR_CondRetMemoria;

    srand((unsigned int)time(NULL));
    
    do {
        condRet = PAR_ExecutaRodada(turno);
        turno = (turno + 1)%numeroDeJogadores;
    } while (condRet != PAR_CondRetTerminou);
    printf("Jogador %d (%s) venceu!!\n",turno,cores[turno]);
    PAR_Finaliza();
    
    return PAR_CondRetOk;
}

/***********************************************************************	
*	
*  $FC Função: PAR  &RolaDado
*	
*  $ED Descrição da função	
*     Gera um número aleatório entre MIN_DADO e MAX_DADO.
*	
*  $FV Valor retornado	
*     Um inteiro com o valor do dado.
*	
***********************************************************************/	
int PAR_RolaDado()
{
    return rand()%(MAX_DADO-MIN_DADO+1)+MIN_DADO; /*Equivale à um número de MIN_DADO até MAX_DADO*/
}

/***********************************************************************	
*	
*  $FC Função: PAR  &obterNumJogadores
*	
*  $ED Descrição da função	
*     Solicita o número de jogadores para a partida que iniciará.
*	
*  $FV Valor retornado	
*     Um inteiro com o número de jogadores que querem participar da partida.
*
***********************************************************************/	
int PAR_obterNumJogadores() {
    int numJogad;
    do {
        printf("Digite o numero de jogadores (de 2 a 4): ");
        scanf("%d", &numJogad);
    } while (numJogad < 2 || numJogad > 4);
    return numJogad;
}

/***********************************************************************	
*	
*  $FC Função: PAR  &EscolhePeca
*	
*  $ED Descrição da função	
*     Solicita ao jogador a escolha de uma peca.
*	
*  $EP Parâmetros	
*     *indPeca - ponteiro que receberá o índice da peça escolhida
*     totalPec - número total de peças
*
*  $FV Valor retornado	
*     Retorna PAR_CondRetOk caso execute corretamente.
*	
*   Assertivas:	
*     Caso o total de peças seja menor que 1, retorna PAR_CondRetParametro.
*
***********************************************************************/	
PAR_CondRet PAR_EscolhePeca(int *indPeca, int totalPec) {
    int pecaEscolhida;

    if (totalPec < 1) return PAR_CondRetParametro;
    if (totalPec == 1) {
        printf("Somente uma peca poderia ser escolhida, jogada feita automaticamente.\n");
        printf("Pressione enter para continuar: ");
        scanf("[ \n]");

        *indPeca = 0;
        return PAR_CondRetOk;
    }
    do {
        printf("Escolha a peca a ser jogada (entre 0 e %d): ", totalPec-1);
        scanf("%d", &pecaEscolhida);
    } while (pecaEscolhida < 0 || pecaEscolhida >= totalPec);
    *indPeca = pecaEscolhida;

    return PAR_CondRetOk;
}

/***********************************************************************	
*	
*  $FC Função: PAR  &ExecutaRodada
*	
*  $ED Descrição da função	
*     Executa a rodada. Solicita a escolha de uma peça, checa se a escolha foi válida,
*     executa o movimento e checa se a partida terminou.
*	
*  $EP Parâmetros	
*	  turno - índice do jogador que da rodada atual
*
*  $FV Valor retornado
*     Retorna PAR_CondRetOk caso execute corretamente.
*     PAR_CondRetSemEscolha caso não haja escolha para o jogador atual.
*	  PAR_CondRetParametro houve um problema ao localizar a peça do jogador.
*	
*   Assertivas:	
*   Checa se o tabuleiro retornou corretamente, checa se a peça andou,
*	checa se a peça do jogador foi obtida corretamente.
***********************************************************************/	
PAR_CondRet PAR_ExecutaRodada(int turno)
{
    int i,indPeca, dado, totalPec;
    void **casas;

    /*Vetor das escolhas feitas até o momento
    * No inicio é zerado pois nenhuma escolha foi feita
    * Se todas foram feitas não há jogada possível*/
    int vEscolhas[4] = {0,0,0,0}; 

    JOG_tpPeca *peca=NULL;
    TAB_CondRet condRetTab=0;
    printf("Jogador %d (%s), sua vez.\n",turno,cores[turno]);

    dado = PAR_RolaDado();
    printf("Voce rodou %d no dado.\n",dado);


    do
    {
        if(condRetTab == TAB_CondRetParametro)
        {
            printf("Erro nos parâmetros ao tentar andar.\n");
            return PAR_CondRetParametro;
        }
        
        if(condRetTab == TAB_CondRetNaoAndou)
        {
            printf("Essa peca nao pode se mover, escolha outra.\n");
        }
        JOG_ObterPosicoesDasPecas(vJogadores[turno], &totalPec,&casas);
        TAB_DesenhaTabuleiro(casas,totalPec);
        PAR_EscolhePeca(&indPeca, totalPec);
        /* Checa se há escolhas */
        for(i=0;i<totalPec;i++)
        {
            if(!vEscolhas[i]) /*Se houver ao menos uma escolha possível nota esse fato*/
            {
                i=-1;/*Seta i como um valor distinto para detectar que existe escolha possível*/
                break;
            }
        }
        if(i!=-1)
        {
            printf("Nao ha escolhas possiveis, passando turno...\n");
            TAB_DesenhaTabuleiro(NULL,0);
            return PAR_CondRetSemEscolha;
        }
        vEscolhas[indPeca] = 1;

        /*Checa se há alguma casa fora do abrigo*/
        for(i=0;i<totalPec;i++)
        {
            if(casas[i]!=NULL)/*Ao menos uma casa nao nula*/
            {
                i = -1;
                break;
            }
        }
        if(i!=-1 && dado!=6)/*Se todas as pecas estão no abrigo e o dado não é 6 não há escolha.*/
        {
            printf("Todas as pecas estao no abrigo e voce nao tirou 6, passando turno...\n");
            return PAR_CondRetSemEscolha;
        }
        peca = JOG_ObterPecaNaPosicao(vJogadores[turno],indPeca);
        if(peca==NULL) return PAR_CondRetParametro;
        /*Retorna CondRetParametro quando a peça não é encontrada*/

        if(JOG_ObterLocalPeca(peca)==NULL)
        {
            if(dado==6)
            {
                condRetTab = TAB_PoePecaNoJogo(peca);
            }
            else
            {
                printf("Deve tirar 6 para tirar a peca do abrigo.\n");
                condRetTab = TAB_CondRetNaoAndou;
            }
            
        }
        else
        {
            condRetTab = TAB_FazJogada(peca,dado);
        }
        
    }while(condRetTab != TAB_CondRetOk && condRetTab != TAB_CondRetChegouFinal && dado!=6);
    if(condRetTab == TAB_CondRetChegouFinal)
        {
            printf("Peca %d do jogador %s chegou no final.\n", indPeca, cores[turno]);
            JOG_RemovePeca(peca,vJogadores[turno]);
            if(JOG_TemPecas(vJogadores[turno])==JOG_CondRetNaoTemPecas)
            {
                TAB_DesenhaTabuleiro(NULL,0);
                return PAR_CondRetTerminou;
            }
        }
    
    TAB_DesenhaTabuleiro(NULL,0);
    printf("Fim da jogada.\n");
    return PAR_CondRetOk;
}

/***********************************************************************	
*	
*  $FC Função: PAR  &Finaliza
*	
*  $ED Descrição da função	
*     Finaliza a rodada. Chama a finalização do tabuleiro e deleta os jogadores.
*	
***********************************************************************/	
void PAR_Finaliza() {
    int i;
    TAB_FinalizaTabuleiro();
    for (i = 0; i < numeroDeJogadores; i++) {
        JOG_Deleta(vJogadores[i]);
    }
}
