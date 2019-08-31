
#include <stdio.h>
#include <stdlib.h>
#include "ponto.h"

typedef struct stack Stack;

//stack_create
//Cria e retorna uma pilha
Stack *stack_create();

//stack_free
//Destrói a pilha passada como parâmetro e libera da memória
void stack_free(Stack *st);

//stack_push
//Adiciona um elemento a pilha
int stack_push(Stack *st, Ponto p);

//stack_pop
//Deleta elemento do topo da pilha
int stack_pop(Stack *st);

//stack_top
//Retorna o elemento do topo da pilha
int stack_top(Stack *st, Ponto *p);

//stack_size
//Retorna a quantidade de elementos da pilha
int stack_size(Stack *st);

//stack_print
//imprime elementos da pilha
int stack_print(Stack *st);
