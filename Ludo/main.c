//
//  main.c
//  Ludo
//

#include <stdio.h>
#include "Jogador.h"

int main(void) {
    Jogador * x = JOG_Cria(Vermelho);
    printf("%d\n", JOG_TemPecas(x));
    return 0;
}
