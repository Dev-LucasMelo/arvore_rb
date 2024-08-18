#include <stdio.h>
#include <stdlib.h>
#include "arvore_rb.h"

int main()
{
    arvore a;
    inicializar(&a); // ponteiro de ponteiro

    adicionar(20,&a);
    adicionar(30,&a);
    adicionar(25,&a);
    adicionar(40,&a);
    adicionar(35,&a);

    printf("\n\n __________arvore resultante_________ \n\n");
    pre_order(a);
    printf("\n\n");
    return 0;
}
