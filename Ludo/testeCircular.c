//Teste do Modulo Circular.h utilizando o arcabouco de testes

#include "GENERICO.h"
#include "LERPARM.h"
#include "Circular.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define DIM_VT_LISTA 5
#define DIM_BUFFER 20
// Ponteiro para as listas atuais e funcao de validacao de indice
CIR_lstCircular *Listas[DIM_VT_LISTA];
static int ValidaLista(int ind);

//Parametros de testes
static char str0[] = "abcd"
static char str1[] = "efgh"
static char str2[] = "????"
static char str3[] = "12345abc"

// Funções aceitas para testar
static char CRIALISTA[] = "=CriaLista";
static char INSERE[] = "=Insere";


int i,*num1,indLista,NumLidos;
char *StringDados,CondRetEsperada;
char Buffer[DIM_BUFFER];
TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
{
	for(i=0;i<DIM_VT_LISTA;i++)
	{
		Listas[i] = NULL;
	}
	
	//Testar a funcao CriarLista
	if(strcmp(ComandoTeste,CRIALISTA)==0) 
	{
		NumLidos = LER_LerParametros( "si" , &StringDados , &indLista ) ;
		if(ValidaLista(indLista)) return TST_CondRetErro;
		Listas[indLista] = CIR_CriaLista(StringDados);
		if(Listas[indLista] == NULL) return TST_CondRetMemoria;
		
		printf("%c\n",(char*)CIR_Conteudo(Listas[indLista]));
		return TST_CondRetOK;
	}
	return 0;
	
	//Testar a funcao InsereElemento
	//if(strcmp(ComandoTeste,INSERE)==0)
	//{
	//	NumLidos = LER_LerParametros("si",&StringDados, &indLista);
	//	if(ValidaLista(indLista)
	//}
}


/******************************************
Função : Valida indice do vetor de Listas Circulares
******************************************/
int ValidaLista(int ind)
{
	if(Listas[ind]==NULL) return 0;
	else return 1;
}
