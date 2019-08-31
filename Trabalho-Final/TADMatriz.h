#ifndef TADMATRIZ_H_INCLUDED
#define TADMATRIZ_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

typedef struct matriz Matriz;

//m_create
//Cria e retorna uma TAD Matriz de acordo com as dimens�es de entrada
Matriz *m_create(int nlinha, int ncoluna);

//m_free
//Destr�i uma TAD Matriz passada como par�metro e libera mem�ria
int m_free(Matriz *n);

//m_push_int
//Adiciona um inteiro em uma posi��o espec�fica da matriz
int m_insert_int(Matriz *n, int i, int j, int val);

//m_select_int
//Seleciona elemento da lista
int m_select_int(Matriz *n, int i, int j, int* val);

//m_fill
//Preenche toda a matriz com valor inteiro passado por par�metro
int m_fill(Matriz *n, int val);

//m_get_lin_col
//Atribui a dimens�o da TAD Matriz m em nLin e nCol
int m_get_lin_col(Matriz *m, int *nLin, int *nCol);

//m_tad_print
//Imprime a tad de entrada na tela
int m_tad_print(Matriz *m);

#endif // TADMATRIZ_H_INCLUDED
