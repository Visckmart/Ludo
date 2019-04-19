//
//  Casa.c
//  Ludo
//

#include "Casa.h"
#include <stdlib.h>

struct Casa {
    char pecas[2];
};

Casa * CAS_Cria() {
    Casa * c = (Casa *)malloc(sizeof(Casa));
    return c;
}

void CAS_Destroi(Casa * casa) {
    free(casa);
}
