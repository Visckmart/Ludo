//
//  Casa.h
//  Ludo
//

#ifndef Casa_h
#define Casa_h

#include <stdio.h>

typedef struct Casa Casa;

Casa * CAS_Cria(void);
void CAS_Destroi(Casa *);

void CAS_AdicionaPeca(void);
void CAS_RemovePeca(void);

char CAS_TemObstrucao(Casa *);
char CAS_TemBifurcacao(Casa *);
char CAS_EhRetaFinal(Casa *);

#endif /* Casa_h */
