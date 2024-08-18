#include <stdio.h>
#include <stdlib.h>
#include "arvore_rb.h"
arvore no_null;

void inicializar(arvore *raiz){ //inicializa no nulo duplo preto e arvore_RB
    *raiz = NULL;
    no_null = (arvore) malloc(sizeof(struct no));
    no_null->cor = DUPLO_PRETO;
    no_null->dado = 0;
    no_null->esq = NULL;
    no_null->dir = NULL;
};

void ajustar(arvore *raiz, arvore elemento){

    //A �rvore est� desajustada se tanto o elemento quanto o seu pai estiverem com a cor vermelha
    //Utilizamos um while para continuar a verifica��o at� chegar a raiz, quando necess�rio

	while(cor(elemento->pai) == VERMELHO && cor(elemento) == VERMELHO) {
		//caso 1: Cor do tio � vermelha, desce o preto do av�
		if(cor(tio(elemento)) == VERMELHO) {
			tio(elemento)->cor = PRETO;
			elemento->pai->cor = PRETO;
			elemento->pai->pai->cor = VERMELHO;

			//Continua a verifica��o a partir do av�, que mudou para vermelho e pode ter
			//gerado uma sequ�ncia vermelho-vermelho

			elemento = elemento->pai->pai;
			continue;
		}

		//caso 2a: rota��o simples direita
		if(eh_filho_esquerdo(elemento) && eh_filho_esquerdo(elemento->pai)) {
            rotacao_simples_direita(raiz, elemento->pai->pai); //passa o v� para ser pivo
            elemento->pai->cor = PRETO;
            elemento->pai->dir->cor = VERMELHO;
            continue;
		}

		//caso 2b: rota��o simples esquerda
		if(!eh_filho_esquerdo(elemento) && !eh_filho_esquerdo(elemento->pai)){
            rotacao_simples_esquerda(raiz,elemento->pai->pai);
            elemento->pai->cor = PRETO;
            elemento->pai->esq->cor = VERMELHO;
            continue;
		}

		//caso 3a: rota��o dupla direita
		if(!eh_filho_esquerdo(elemento) && eh_filho_esquerdo(elemento->pai)) {
            rotacao_dupla_direita(raiz,elemento);

            //atualizacao de cores
            elemento->cor = PRETO;
            elemento->dir->cor = VERMELHO;
            continue;
		}
		//caso 3b: rota��o dupla esquerda
		if(eh_filho_esquerdo(elemento) && !eh_filho_esquerdo(elemento->pai)) {
            rotacao_dupla_esquerda(raiz,elemento);

            //atualizacao de cores
            elemento->cor = PRETO;
            elemento->esq->cor = VERMELHO;
            continue;
		}

	}

    //caso 0: toda raiz de arvore RB deve ser preta
	(*raiz)->cor = PRETO;
};


void adicionar (int valor, arvore *raiz){
    arvore posicao, pai, novo;
    //utiliza-se *raiz, por ser um ponteiro de ponteiro
	posicao = *raiz;
	pai = NULL;

    while(posicao != NULL) {
			pai = posicao;
			if(valor > posicao->dado)
					posicao = posicao->dir;
			else
					posicao = posicao->esq;
	}

    //Ap�s achar a posi��o, inicializa o novo elemento
	novo = (arvore) malloc(sizeof(struct no));
	novo->dado = valor;
	novo->esq = NULL;
	novo->dir = NULL;
	novo->pai = pai;
	novo->cor = VERMELHO;

    //Atualiza a raiz da �rvore, caso esteja inserindo o primeiro elemento
    //Observe novamente o uso do ponteiro de ponteiro
	if(eh_raiz(novo)){
        *raiz = novo;
	} else {
        //Se n�o for a raiz, � preciso realizar a liga��o do pai(direita ou esquerda) com o novo elemento
		if(valor > pai->dado){
			pai->dir = novo;
		}
		else{
			pai->esq = novo;
		}
	}

    //Ap�s inserir, verifica e ajusta a �rvore resultante
	ajustar(raiz, novo);
};

//ROTACOES

void rotacao_simples_direita(arvore *raiz, arvore pivo){
	arvore u, t2;
	u = pivo->esq;
    t2 = u->dir;

    /*Para fazer a liga��o da raiz da sub-�rvore resultante com o seu pai, � preciso saber se o pivo p era um filho esquerdo ou direito*/
	int posicao_pivo_esq = eh_filho_esquerdo(pivo);

	//Atualiza��o dos ponteiros
	pivo->esq = t2;

    if(t2 != NULL){
		t2->pai = pivo;
    }

	u->dir = pivo;

	u->pai = pivo->pai;
	pivo->pai = u;

    //Se n�o existir �rvore acima de u, u passa a ser a raiz da �rvore
	if(eh_raiz(u)){
        *raiz = u;
	}else {
        //Caso contr�rio (se existir) � preciso ligar o restante da �rvore a esta sub-�rvore, resultante da rota��o
        if(posicao_pivo_esq)
            u->pai->esq = u;
        else
            u->pai->dir = u;
	}
}

void rotacao_simples_esquerda(arvore *raiz, arvore pivo){
    arvore u,t2;

    u = pivo->dir;
    t2 = u->esq;

    //verificando se pivo � filho esquerdo ou direito
    int posicao_pivo_esq = eh_filho_esquerdo(pivo);

    //atualizacao de ponteiros
    pivo->dir = t2;

    if(t2 != NULL){
        t2->pai = pivo;
    }

    u->esq = pivo;
    u->pai = pivo->pai;

    pivo->pai = u;

    //verificando se U vai ser raiz ou subarvore

    if(eh_raiz(u)){
        *raiz = u;
    }else{
        if(posicao_pivo_esq){
            u->pai->esq = u;
        }else{
            u->pai->dir = u;
        }
    }
};

void rotacao_dupla_direita(arvore *raiz, arvore elemento){
    rotacao_simples_esquerda(raiz,elemento->pai);
    // passa novamente elemento->pai como pivo, pois a primeira rotacao atualiza os ponteiros
    rotacao_simples_direita(raiz,elemento->pai);
};

void rotacao_dupla_esquerda(arvore *raiz, arvore elemento){
    printf("\n\n modulo rotacao dupla esquerda no elemento %d",elemento->dado);
    rotacao_simples_direita(raiz,elemento->pai);
    rotacao_simples_esquerda(raiz,elemento->pai);
};

// funcoes auxiliares
int altura(arvore raiz) {
	if(raiz == NULL) {
		return 0;
	}
	return 1 + maior(altura(raiz->dir), altura(raiz->esq));
}

int maior(int a, int b) {
	if(a > b)
		return a;
	else
		return b;
}

int maior_elemento(arvore raiz) {
	if(raiz == NULL)
			return -1;
	if(raiz->dir == NULL)
			return raiz->dado;
	else
			return maior_elemento(raiz->dir);
}

int menor_elemento(arvore raiz) {
	if(raiz == NULL)
			return -1;
	if(raiz->esq == NULL)
			return raiz->dado;
	else
			return maior_elemento(raiz->esq);
}

void pre_order(arvore raiz) {
	if(raiz != NULL) {
		imprimir_elemento(raiz);
		pre_order(raiz->esq);
		pre_order(raiz->dir);
	}
}

void pos_order(arvore raiz) {
	if(raiz != NULL) {
		pos_order(raiz->esq);
		pos_order(raiz->dir);
		imprimir_elemento(raiz);
	}
}

void in_order(arvore raiz) {
	if(raiz != NULL) {
		in_order(raiz->esq);
		imprimir_elemento(raiz);
		in_order(raiz->dir);
	}
}

void imprimir_elemento(arvore raiz) {

    if(raiz->pai != NULL){
        switch(raiz->cor){
            case PRETO:
                printf("\nNO: %d | pai: %d | cor: preto",raiz->dado,raiz->pai->dado);
			break;
            case VERMELHO:
                printf("\nNO: %d | pai: %d | cor: vermelho",raiz->dado,raiz->pai->dado);
            break;
            case DUPLO_PRETO:
                printf("\nNO: %d | pai: %d | cor: duplo_preto",raiz->dado,raiz->pai->dado);
			break;
        }
    }else{
        switch(raiz->cor){
            case PRETO:
                printf("\nNO: %d | pai: %d | cor: preto",raiz->dado,-1);
			break;
            case VERMELHO:
                printf("\nNO: %d | pai: %d | cor: vermelho",raiz->dado,-1);
            break;
            case DUPLO_PRETO:
                printf("\nNO: %d | pai: %d | cor: duplo_preto",raiz->dado,-1);
			break;
        }
    }
}

void imprimir(arvore raiz) {
	printf("(");
	if(raiz != NULL) {
		imprimir_elemento(raiz);
		imprimir(raiz->esq);
		imprimir(raiz->dir);
	}
	printf(")");
}

int eh_raiz(arvore elemento) {
	return (elemento->pai == NULL);
}

int eh_filho_esquerdo(arvore elemento) {
	return (elemento->pai != NULL && elemento == elemento->pai->esq);
}

arvore tio(arvore elemento) {
	return irmao(elemento->pai);
}

arvore irmao(arvore elemento) {
	if(eh_filho_esquerdo(elemento))
		return elemento->pai->dir;
	else
		return elemento->pai->esq;
}

arvore retornar_pai(arvore elemento){
    return elemento->pai;

}

enum cor cor(arvore elemento) {
	enum cor c;
	if(elemento==NULL || elemento->cor == PRETO)
		c = PRETO;
	else
		c = VERMELHO;
	return c;
}
