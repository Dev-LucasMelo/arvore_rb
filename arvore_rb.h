#include <stdio.h>
#include <stdlib.h>
#ifndef ARVORE_RB_H_INCLUDED
#define ARVORE_RB_H_INCLUDED

enum cor { VERMELHO, PRETO, DUPLO_PRETO };

typedef struct no {
	int dado;
	enum cor cor;
	struct no *esq, *dir, *pai;
} no;

typedef no * arvore;

void inicializar(arvore *raiz); //OK
void adicionar (int valor, arvore *raiz); //OK
void remover (int valor, arvore *raiz);


// funcoes auxiliares

int altura(arvore raiz); //OK
int maior(int a, int b); //OK
int maior_elemento(arvore raiz); //OK
int menor_elemento(arvore raiz); //OK
void pre_order(arvore raiz); //OK
void pos_order(arvore raiz); //OK
void in_order(arvore raiz); //OK

void imprimir_elemento(arvore raiz); //OK
void imprimir(arvore raiz); //OK

enum cor cor(arvore elemento); //OK
void ajustar(arvore *raiz, arvore elemento); //OK //ajusta arvore resultante na operação de inserir
void reajustar(arvore *raiz, arvore elemento);
void rotacao_simples_direita(arvore *raiz, arvore pivo); //OK
void rotacao_simples_esquerda(arvore *raiz, arvore pivo); //OK
void rotacao_dupla_direita(arvore *raiz, arvore elemento); //OK
void rotacao_dupla_esquerda(arvore *raiz, arvore elemento); //OK

int eh_raiz(arvore elemento); //OK
int eh_filho_esquerdo(arvore elemento); //OK
arvore irmao(arvore elemento); //OK
arvore retornar_pai(arvore elemento); //OK
arvore tio(arvore elemento); //OK
void retira_duplo_preto(arvore *raiz, arvore elemento);

#endif // ARVORE_RB_H_INCLUDED
