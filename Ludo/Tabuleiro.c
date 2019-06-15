/***************************************************************************
*  $MCI M�dulo de implementa��o: TAB  Tabuleiro
*
*  Arquivo gerado:              Tabuleiro.c
*  Letras identificadoras:      TAB
*
*
*  Projeto: INF 1301 / Ludo
*  Autores: Thiago Lamenza
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor            Data        Observa��es
*     1       Thiago Lamenza   11/mai/2019 inicio do desenvolvimento
*
***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "Tabuleiro.h"
#include "Jogador.h"
#include "Circular.h"
#include "LISTA.h"
#define NUM_RETASFINAIS 4 /*Numero de retas finais*/
#define NUM_CASASNARETAFINAL 5 /*Numero de casas na reta final*/
#define NUM_CASASNOTABULEIRO 52 /*Numero de casas na parte principal do tabuleiro*/
#define NUM_CASASEMTODOOTABULEIRO 72 /*Numero de casas na parte principal tal como em todas as retas finais*/
#define NUM_MAXJOGADORES 4 /*Numero maximo de jogadores*/
#define NUM_MAXPECASABRIGO 4 /*Numero maximo de peças no abrigo*/
#define NUM_MAXPECASPORJOGADOR 4 /*Número maximo de peças por jogador*/
#define NUM_PECAS (NUM_MAXJOGADORES*NUM_MAXPECASPORJOGADOR)

typedef struct casa
{
    JOG_tpPeca *pecas[2];
    LIS_tppLista Bifurcacao;
    JOG_tpCor Cor;
}TAB_tpCasa;


typedef struct tabuleiro
{
    CIR_lstCircular *campoPrincipal;
	LIS_tppLista retaFinal[4];
}TAB_tpTabuleiro;


/**********************************************
 *
 * Variável estática que guarda o tabuleiro
 *
 *********************************************/
static TAB_tpTabuleiro *Tabuleiro = NULL;


/************************************************
 *
 * Vetor de casas de entrada no tabuleiro ordenada por cor, é setada com a função IniciaTabuleiro.
 *
 * Ordem: Vermelho,Azul,Verde,Amarelo
 *
 ***********************************************/
static TAB_tpCasa *inicioPorCor[4];

/************************************************
 * 
 * Vetor que contém o número de casas em cada abrigo, inicia com NUM_MAX_ABRIGO para cada jogador
 * 
 * Ordem: Vermelho,Azul,Verde,Amarelo
 * 
 ***********************************************/
static int vNumPecasAbrigo[NUM_MAXJOGADORES] = {NUM_MAXPECASABRIGO,NUM_MAXPECASABRIGO,NUM_MAXPECASABRIGO,NUM_MAXPECASABRIGO};


/*********************************************
 *
 * Protótipo das funções estáticas encapsuladas pelo módulo
 *
 ********************************************/
static TAB_CondRet TAB_CriaCasa(LIS_tppLista bifurcacao,JOG_tpCor cor,TAB_tpCasa **novaCasa);
static TAB_CondRet TAB_InserePeca(TAB_tpCasa *casa,JOG_tpPeca *peca);
static TAB_CondRet TAB_RemovePeca(TAB_tpCasa *casa,int peca);
static void TAB_DestroiCasa(TAB_tpCasa *casa);
static void TAB_ComePecas(TAB_tpCasa *casa);
static int TAB_ObterNumPecas(TAB_tpCasa *casa);
static TAB_CondRet TAB_AvancaPecaLDupla(LIS_tppLista Lista,int indPeca,int numCasas);
static TAB_CondRet TAB_AvancaPecaCircular(CIR_lstCircular *Lista,int indPeca,int numCasas);
static void TAB_preparaVetoresDesenho(int * pVetorCasas[72][2], int * pVetorAbrigo[16]);
static void TAB_exibirTabuleiro(int ** v, int * u);


/****************************************************************

Função: TAB  &CriaCasa

****************************************************************/

TAB_CondRet TAB_CriaCasa(LIS_tppLista bifurcacao,JOG_tpCor cor,TAB_tpCasa **novaCasa)
{
	if(novaCasa==NULL) return TAB_CondRetParametro;
    *novaCasa = (TAB_tpCasa*) malloc(sizeof(TAB_tpCasa));
    if(*novaCasa==NULL) return TAB_CondRetMemoria;
    (*novaCasa)->pecas[0] = NULL;
    (*novaCasa)->pecas[1] = NULL;
    (*novaCasa)->Cor = cor;
    (*novaCasa)->Bifurcacao = bifurcacao;
	return TAB_CondRetOk;
}

/****************************************************************

Função: TAB  &IniciaTabuleiro

****************************************************************/

TAB_CondRet TAB_IniciaTabuleiro() {
	int i,a;
    TAB_tpTabuleiro * tab;
    JOG_tpCor Cores[4] = {Vermelho,Azul,Verde,Amarelo};
    TAB_tpCasa *casa;
	TAB_CondRet CondRet;

    if(Tabuleiro!=NULL) TAB_FinalizaTabuleiro();

    tab = (TAB_tpTabuleiro*)malloc(sizeof(TAB_tpTabuleiro));

    if (tab == NULL) {
        return TAB_CondRetMemoria;
    }
    for(i=0;i<NUM_RETASFINAIS;i++)
    {
		tab->retaFinal[i] = LIS_CriarLista(TAB_DestroiCasa);
		for(a=0;a<NUM_CASASNARETAFINAL;a++)
		{
			CondRet = TAB_CriaCasa(NULL,Nenhuma,&casa);

			if(CondRet == TAB_CondRetMemoria) return TAB_CondRetMemoria;

			LIS_InserirElementoApos(tab->retaFinal[i],casa);
		}
    }

    if(CIR_CriaLista(&tab->campoPrincipal)==CIR_CondRetMemoria) return TAB_CondRetMemoria;
    a=0;
    for(i=0;i<NUM_CASASNOTABULEIRO;i++)
    {
    	if(i%(NUM_CASASNOTABULEIRO/4)==0)
    	{
    		CondRet = TAB_CriaCasa(tab->retaFinal[a],Cores[a],&casa);

    		a++;
    	}
    	else
    	{
    		CondRet = TAB_CriaCasa(NULL,Nenhuma,&casa);

    	}
    	if(CondRet==TAB_CondRetMemoria) return TAB_CondRetMemoria;

    	if((i-2)%(NUM_CASASNOTABULEIRO/4)==0) 
			inicioPorCor[(i-2)/(NUM_CASASNOTABULEIRO/4)] = casa; /*Se for uma das casas de inicio salva seu endereço no vetor de casas de inicio*/

    	CIR_InsereElemento(tab->campoPrincipal,casa);
    }

    Tabuleiro = tab;
    return TAB_CondRetOk;
}


/****************************************************************

Função: TAB  &InserePeca

****************************************************************/

TAB_CondRet TAB_InserePeca(TAB_tpCasa *casa,JOG_tpPeca *peca)
{
    if(casa->pecas[0]==NULL) casa->pecas[0] = peca;
    else if(casa->pecas[1]==NULL) casa->pecas[1] = peca;
    else return TAB_CondRetSemEspaco;
    return TAB_CondRetOk;
}


/****************************************************************

Função: TAB  &RemovePeca

****************************************************************/
TAB_CondRet TAB_RemovePeca(TAB_tpCasa *casa,int peca)
{
	if(casa->pecas[0]==NULL) return TAB_CondRetParametro;
	if(peca==0)
	{
		casa->pecas[0] = casa->pecas[1];
		casa->pecas[1] = NULL;
	}
	else
	{
		casa->pecas[1] = NULL;
	}
	return TAB_CondRetOk;
}

/****************************************************************

Função: TAB  &ComePecas

****************************************************************/
void TAB_ComePecas(TAB_tpCasa *casa)
{
	if(casa->pecas[0]!=NULL)
	{
		JOG_AtualizaPeca(casa->pecas[0],NULL);
		casa->pecas[0]=NULL;

		vNumPecasAbrigo[JOG_ObterCorPeca(casa->pecas[0])-1] += 1; /*Coloca mais uma peça no abrigo do jogador */
	}
	if(casa->pecas[1]!=NULL)
	{
		JOG_AtualizaPeca(casa->pecas[1],NULL);
		casa->pecas[1]=NULL;

		vNumPecasAbrigo[JOG_ObterCorPeca(casa->pecas[0])-1] += 1; /*Coloca mais uma peça no abrigo do jogador */
	}
}


/****************************************************************

Função: TAB  &DestroiCasa

****************************************************************/
void TAB_DestroiCasa(TAB_tpCasa *casa)
{
    free(casa);
}


/****************************************************************

Função: TAB  &NumPecas

****************************************************************/
int TAB_ObterNumPecas(TAB_tpCasa *casa)
{
	if(casa==NULL) return -1;
	if(casa->pecas[0]!=NULL)
	{
		if(casa->pecas[1]!=NULL) return 2;
		return 1;
	}
	return 0;
}



/****************************************************************

Função: TAB  &FazJogada

****************************************************************/
TAB_CondRet TAB_FazJogada(void *peca,int dado)
{
	TAB_tpCasa *casa;
	int i,indPeca;
	TAB_CondRet CondRet = TAB_CondRetNaoAndou;

	if(peca==NULL || dado<1) return TAB_CondRetParametro;

	casa = JOG_ObterLocalPeca(peca);
	if(casa == NULL) return TAB_CondRetParametro;

	if(casa->pecas[0]==peca) indPeca = 0;
	else if(casa->pecas[1]==peca) indPeca=1;
	else return TAB_CondRetParametro;


	if(CIR_ProcuraElemento(Tabuleiro->campoPrincipal,casa)!=CIR_CondRetNaoAchou)
	{
		CondRet = TAB_AvancaPecaCircular(Tabuleiro->campoPrincipal, indPeca, dado);
	}
	else
	{
		for(i=0;i<NUM_RETASFINAIS;i++)
		{
			if(LIS_ProcurarValor(Tabuleiro->retaFinal[i],casa) != LIS_CondRetNaoAchou)
			{
				CondRet = TAB_AvancaPecaLDupla(Tabuleiro->retaFinal[i],indPeca, dado);
			}
		}
	}
	return CondRet;
}



/****************************************************************

Função: TAB  &PoePecaNoJogo

****************************************************************/
TAB_CondRet TAB_PoePecaNoJogo(void *peca)
{
	int indice;
	TAB_tpCasa *casa;
	JOG_tpCor Cor;
	TAB_CondRet CondRet;

	if(peca==NULL) return TAB_CondRetParametro;
	if(JOG_ObterLocalPeca(peca)!=NULL) return TAB_CondRetParametro;

	Cor = JOG_ObterCorPeca(peca);
	if(Cor == Amarelo) indice = 0;
	else if(Cor == Verde) indice = 1;
	else if(Cor == Vermelho) indice = 2;
	else if(Cor == Azul) indice = 3;
	else return TAB_CondRetParametro;

	casa = inicioPorCor[indice]; /*Seleciona a casa de inicio correta baseada na cor*/


	if(TAB_ObterNumPecas(casa)>0 && JOG_ObterCorPeca(casa->pecas[0])!= JOG_ObterCorPeca(peca)) TAB_ComePecas(casa); /*Se houver uma peca inimiga come ela*/
	else if(TAB_ObterNumPecas(casa)==2) return TAB_CondRetSemEspaco; /*Se a casa estiver cheia não executa a inserção*/

	CondRet = TAB_InserePeca(casa,peca);
	if(CondRet==TAB_CondRetOk) JOG_AtualizaPeca(peca,casa);

	vNumPecasAbrigo[JOG_ObterCorPeca(peca)-1] -= 1; /*Reduz o número de peças no abrigo do jogador, -1 pois o enum Cor inclui uma cor Neutra*/
	return CondRet;
}


/****************************************************************

Função: TAB  &FinalizaTabuleiro

****************************************************************/
TAB_CondRet TAB_FinalizaTabuleiro()
{
	int i;
	if(Tabuleiro==NULL) return TAB_CondRetOk;
	CIR_DestroiLista(Tabuleiro->campoPrincipal,TAB_DestroiCasa);
	for(i=0;i<NUM_RETASFINAIS;i++) LIS_DestruirLista(Tabuleiro->retaFinal[i]);

	free(Tabuleiro);
	return TAB_CondRetOk;
}

/****************************************************************

Função: TAB  &Avanca Peca Lista Dupla

CUIDADO: Pressupoe que o elemento atual da lista contém a peca desejada.

****************************************************************/
TAB_CondRet TAB_AvancaPecaLDupla(LIS_tppLista Lista,int indPeca,int numCasas)
{
	int res = numCasas;
    TAB_tpCasa *Proximo,*casaCorr,*casaInicial;
    JOG_tpPeca *temp;
    if(Lista==NULL || indPeca>1 || indPeca<0 || numCasas<0) return TAB_CondRetParametro;
    if(numCasas==0) return TAB_CondRetOk;

    casaInicial = casaCorr = LIS_ObterValor(Lista);
    if(casaCorr==NULL) return TAB_CondRetParametro;
    temp = casaCorr->pecas[indPeca];
    if(temp==NULL) return TAB_CondRetParametro;
    while(res>0 && LIS_AvancarElementoCorrente(Lista,1)!=LIS_CondRetFimLista) /*Avanca o maximo para frente possível*/
    {

    	Proximo = LIS_ObterValor(Lista);
    	if(TAB_ObterNumPecas(Proximo)==2)  /*Se encontrar obstrução volta uma casa e termina a jogada*/
    	{
    		if(res==numCasas) return TAB_CondRetNaoAndou; /*Se a obstrução está na primeira casa andada então a jogada é inválida*/
    		res = 0;
    		break;
    	}
    	casaCorr = Proximo;
    	res--;
    }
    TAB_RemovePeca(casaInicial,indPeca); /*Evita que a peça rebata e fique presa numa obstruçao gerada por ela mesma*/
    res--; /*Bater no final do tabuleiro conta como "andar*/
    if(res==0)
    {
    	LIS_IrInicioLista(Lista);
    	JOG_AtualizaPeca(temp,NULL);
    	return TAB_CondRetChegouFinal;
    }

	while(res>0 && LIS_AvancarElementoCorrente(Lista,-1)!=LIS_CondRetFimLista)
	{
		Proximo = LIS_ObterValor(Lista);
		if(TAB_ObterNumPecas(Proximo)==2)
		{
			res = 0;
			break;
		}
		casaCorr = Proximo;
		res--;
    }
    if(TAB_InserePeca(casaCorr,temp)!=TAB_CondRetOk)return TAB_CondRetNaoAndou;
    LIS_IrInicioLista(Lista);
    JOG_AtualizaPeca(temp,casaCorr);
    return TAB_CondRetOk;
}

/****************************************************************

Função: TAB  &Avanca Peca Lista Circular

CUIDADO: Pressupoe que o elemento atual da lista contém a peca desejada.

****************************************************************/
TAB_CondRet TAB_AvancaPecaCircular(CIR_lstCircular *Lista,int indPeca,int numCasas)
{
	int res=numCasas;
    JOG_tpCor CorPeca;
    JOG_tpPeca *temp;
    TAB_tpCasa *casaInicial,*casaCorr,*Proximo;
    if(Lista==NULL || indPeca>1 || indPeca<0 || numCasas<0) return TAB_CondRetParametro;
    if(numCasas==0) return TAB_CondRetOk;
    
    casaInicial = casaCorr = CIR_ObterConteudo(Lista);
    if(casaCorr==NULL || casaCorr->pecas[indPeca]==NULL) return TAB_CondRetParametro;
    temp = casaCorr->pecas[indPeca];
    if(temp==NULL) return TAB_CondRetParametro;
    CorPeca = JOG_ObterCorPeca(temp);

    while(res>0)
    {
        CIR_ObterProximoElemento(Lista);
        Proximo = CIR_ObterConteudo(Lista);
        if(TAB_ObterNumPecas(Proximo)==2 && res != 1)
        {
        	if(res == numCasas) return TAB_CondRetNaoAndou;
        	break;
        }
        if(casaCorr->Cor == CorPeca)
        /*Se a casa tem cor igual a pe�a sendo movida ela � uma bifurcacao para ela, encaminha para a função apropriada*/
        {
            LIS_IrInicioLista(casaCorr->Bifurcacao);
            Proximo = LIS_ObterValor(casaCorr->Bifurcacao);
            if(TAB_ObterNumPecas(Proximo)==2)
            {
            	if(res==numCasas) return TAB_CondRetNaoAndou;
            	/*Se a obstrucao foi encontrada na primeira andada, a jogada não é válida*/

            	else break;
            	/*Se a primeira casa da lista está obstruida pare a peça onde está*/
            }


			if(TAB_InserePeca(Proximo,temp)==TAB_CondRetOk)
			{
				JOG_AtualizaPeca(temp,Proximo);
				TAB_RemovePeca(casaInicial,indPeca);
				return TAB_AvancaPecaLDupla(casaCorr->Bifurcacao,TAB_ObterNumPecas(Proximo)-1,res-1);
			}
			else
				return TAB_CondRetNaoAndou;
        }

		casaCorr = Proximo;
		res--;
    }
    if(TAB_ObterNumPecas(casaCorr)>0 && JOG_ObterCorPeca(casaCorr->pecas[0])!=CorPeca) TAB_ComePecas(casaCorr);
    if(TAB_InserePeca(casaCorr,temp)!=TAB_CondRetOk) return TAB_CondRetNaoAndou;
    JOG_AtualizaPeca(temp,casaCorr);
    TAB_RemovePeca(casaInicial,indPeca);
    return TAB_CondRetOk;
}

/****************************************************************

Função: TAB  &DesenhaTabuleiro

****************************************************************/

TAB_CondRet TAB_DesenhaTabuleiro()
{
	CIR_CondRetErro condRet;

	int v[72][2];
	int u[16];

	if (Tabuleiro == NULL) {
		return TAB_CondRetParametro;
	}

	condRet = CIR_ProcuraElemento(Tabuleiro->campoPrincipal, inicioPorCor[0]);
	if (condRet != CIR_CondRetOk) {
		return TAB_CondRetNaoDesenhou;
	}

	TAB_preparaVetoresDesenho(&v,&u);

	TAB_exibirTabuleiro(v,u);

	return TAB_CondRetOk;
}

void TAB_preparaVetoresDesenho(int * pVetorCasas[72][2], int * pVetorAbrigo[16]) {
	int a, i, j, index, indexcoratual, indexpeca;
	int counts[] = { 0, 0, 0, 0 };
	int posicaoDasPecas[NUM_PECAS];
	JOG_tpCor corAtual;
	TAB_tpCasa *casaAtual;
	int * u;
	int ** v;
	v = *pVetorCasas;
	u = *pVetorAbrigo;

	char cores[] = { 'r','b','g','y' };

	for (i = 0; i < NUM_PECAS; i++) {	//Preenche todas as posições do vetor com -1
		posicaoDasPecas[i] = -1;
	}

	for (i = 0; i < NUM_CASASNOTABULEIRO; i++) {	//Coloca em um vetor as posições de todas as peças que estão no campo principal
		casaAtual = CIR_ObterConteudo(Tabuleiro->campoPrincipal);
		if (TAB_ObterNumPecas(casaAtual) > 0) {
			corAtual = JOG_ObterCorPeca(casaAtual->pecas[0]);
			indexcoratual = corAtual - 1;
			indexpeca = indexcoratual * 4 + counts[indexcoratual];
			posicaoDasPecas[indexpeca] = i;
			counts[indexcoratual]++;
		}
		CIR_ObterProximoElemento(Tabuleiro->campoPrincipal);
	}
	for (i = 0; i < NUM_RETASFINAIS; i++) {			//Coloca no mesmo vetor as posições de todas as peças nas retas finais
		for (j = 0; j < NUM_CASASNARETAFINAL; j++) {
			casaAtual = CIR_ObterConteudo(Tabuleiro->retaFinal[i]);
			if (TAB_ObterNumPecas(casaAtual) > 0) {
				corAtual = JOG_ObterCorPeca(casaAtual->pecas[0]);
				indexcoratual = corAtual - 1;
				indexpeca = indexcoratual * 4 + counts[indexcoratual];
				posicaoDasPecas[indexpeca] = NUM_CASASNOTABULEIRO + i * NUM_RETASFINAIS + j;
				counts[indexcoratual]++;
			}
			CIR_ObterProximoElemento(Tabuleiro->campoPrincipal);
		}
	}

	for (i = 0; i < NUM_CASASEMTODOOTABULEIRO; i++) {	//Preenche o vetor de casas com espaços vazios
		v[i][0] = ' ';
		v[i][1] = ' ';
	}

	for (i = 0; i < NUM_MAXPECASABRIGO * NUM_MAXJOGADORES; i++) {	//Preenche o vetor de abrigos com espaços vazios
		u[i] = ' ';
	}

	for (i = 0; i < NUM_MAXJOGADORES; i++) {	//Preenche o vetor de casas com as peças de cada uma
		for (j = 0; j < NUM_MAXPECASPORJOGADOR; j++) {
			index = 4 * i + j;
			if (posicaoDasPecas[index] != -1) {
				if (v[posicaoDasPecas[index]][0] != ' ') {
					v[posicaoDasPecas[index]][1] = cores[i];
				}
				else {
					v[posicaoDasPecas[index]][0] = cores[i];
				}
			}
		}

		for (j = 0; j < vNumPecasAbrigo[i]; j++) {	//preenche o vetor de abrigos com as peças de cada uma
			u[i * 4 + j] = cores[i];
		}

	}
}

void TAB_exibirTabuleiro(int ** v, int * u) {
	printf(".--------------------------------------------.\n");
	printf("|                 |%c%c|%c%c|%c%c|                 |\n", v[49][0], v[49][1], v[50][0], v[50][1], v[51][0], v[51][1]);
	printf("|                 .--.--.--.                 |\n");
	printf("|                 |%c%c|%c%c|%c%c|                 |\n", v[48][0], v[48][1], v[52][0], v[52][1], v[0][0], v[0][1]);
	printf("|                 .--.--.--.                 |\n");
	printf("|                 |%c%c|%c%c|%c%c|                 |\n", v[47][0], v[47][1], v[53][0], v[53][1], v[1][0], v[1][1]);
	printf("|      %c%c%c%c       .--.--.--.       %c%c%c%c      |\n", u[0], u[1], u[2], u[3], u[4], u[5], u[6], u[7]);
	printf("|                 |%c%c|%c%c|%c%c|                 |\n", v[46][0], v[46][1], v[54][0], v[54][1], v[2][0], v[2][1]);
	printf("|                 .--.--.--.                 |\n");
	printf("|                 |%c%c|%c%c|%c%c|                 |\n", v[45][0], v[45][1], v[55][0], v[55][1], v[3][0], v[3][1]);
	printf("|                 .--.--.--.                 |\n");
	printf("|                 |%c%c|%c%c|%c%c|                 |\n", v[44][0], v[44][1], v[56][0], v[56][1], v[4][0], v[4][1]);
	printf(".--.--.--.--.--.--.--.--.--.--.--.--.--.--.--.\n");
	printf("|%c%c|%c%c|%c%c|%c%c|%c%c|%c%c|        |%c%c|%c%c|%c%c|%c%c|%c%c|%c%c|\n", v[38][0], v[38][1], v[39][0], v[39][1], v[40][0], v[40][1], v[41][0], v[41][1], v[42][0], v[42][1], v[43][0], v[43][1], v[5][0], v[5][1], v[6][0], v[6][1], v[7][0], v[7][1], v[8][0], v[8][1], v[9][0], v[9][1], v[10][0], v[10][1]);
	printf(".--.--.--.--.--.--.        .--.--.--.--.--.--.\n");
	printf("|%c%c|%c%c|%c%c|%c%c|%c%c|%c%c|        |%c%c|%c%c|%c%c|%c%c|%c%c|%c%c|\n", v[37][0], v[37][1], v[67][0], v[67][1], v[68][0], v[68][1], v[69][0], v[69][1], v[70][0], v[70][1], v[71][0], v[71][1], v[61][0], v[61][1], v[60][0], v[60][1], v[59][0], v[59][1], v[58][0], v[58][1], v[57][0], v[57][1], v[11][0], v[11][1]);
	printf(".--.--.--.--.--.--.        .--.--.--.--.--.--.\n");
	printf("|%c%c|%c%c|%c%c|%c%c|%c%c|%c%c|        |%c%c|%c%c|%c%c|%c%c|%c%c|%c%c|\n", v[36][0], v[36][1], v[35][0], v[35][1], v[34][0], v[34][1], v[33][0], v[33][1], v[32][0], v[32][1], v[31][0], v[31][1], v[17][0], v[17][1], v[16][0], v[16][1], v[15][0], v[15][1], v[14][0], v[14][1], v[13][0], v[13][1], v[12][0], v[12][1]);
	printf(".--.--.--.--.--.--.--.--.--.--.--.--.--.--.--.\n");
	printf("|                 |%c%c|%c%c|%c%c|                 |\n", v[30][0], v[30][1], v[66][0], v[66][1], v[18][0], v[18][1]);
	printf("|                 .--.--.--.                 |\n");
	printf("|                 |%c%c|%c%c|%c%c|                 |\n", v[29][0], v[29][1], v[65][0], v[65][1], v[19][0], v[19][1]);
	printf("|                 .--.--.--.                 |\n");
	printf("|                 |%c%c|%c%c|%c%c|                 |\n", v[28][0], v[28][1], v[64][0], v[64][1], v[20][0], v[20][1]);
	printf("|      %c%c%c%c       .--.--.--.       %c%c%c%c      |\n", u[8], u[9], u[10], u[11], u[12], u[13], u[14], u[15]);
	printf("|                 |%c%c|%c%c|%c%c|                 |\n", v[27][0], v[27][1], v[63][0], v[63][1], v[21][0], v[21][1]);
	printf("|                 .--.--.--.                 |\n");
	printf("|                 |%c%c|%c%c|%c%c|                 |\n", v[26][0], v[26][1], v[62][0], v[62][1], v[22][0], v[22][1]);
	printf("|                 .--.--.--.                 |\n");
	printf("|                 |%c%c|%c%c|%c%c|                 |\n", v[25][0], v[25][1], v[24][0], v[24][1], v[23][0], v[23][1]);
	printf(".-----------------.--.--.--.-----------------.\n");
}