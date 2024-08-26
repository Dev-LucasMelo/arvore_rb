#include <stdio.h>
#include <stdlib.h>
#include "arvore_rb.h"

int main()
{
    arvore a;
    inicializar(&a); // ponteiro de ponteiro

    //inicializacao menu

    int option,valor;
    printf("___________________________________________________________________________\n");
    printf("ATIVIDADE AED2\n\n");
    printf("DISCENTE: LUCAS MESSIAS M. DE MELO\n");
    printf("ARVORE RB\n");
    printf("___________________________________________________________________________\n\n\n\n");

    printf("_________________________ESCOLHA UMA OPCAO__________________________________\n\n\n");


    printf("[1]INSERIR [2]REMOVER [3]PREORDER [4]SAIR\n\n");

    printf("Escolha uma opcao:");
    scanf("%d",&option);
    while(option != 4){

        switch(option){
            case 1:
                printf("Informe o valor a ser adicionado :");
                scanf("%d",&valor);

                adicionar(valor,&a);

                printf("\nValor inserido !");
            break;
            case 2:

                printf("\n[REMOVER EM DESENVOLVIMENTO]\n");
            break;
            case 3:
                printf("\n");
                pre_order(a);
                printf("\n");
            break;
        }


        printf("\n______________________");
        printf("\nEscolha uma opcao:");
        scanf("%d",&option);

    }

    printf("\nEncerrando programa...\n");
    return 0;
}
