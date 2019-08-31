#include "TADMatriz.h"

struct matriz
{
    int *dados;
    int nlinhas;
    int ncolunas;
};


Matriz *m_create(int nlinha, int ncoluna)
{
    Matriz *n;

    n = malloc(sizeof(Matriz) );
    if(n == NULL)
    {
        return NULL;
    }
    else
    {
        n -> dados = malloc (nlinha * ncoluna * sizeof(int));
    }

    if(n -> dados == NULL)
    {
        return NULL;
    }
    else
    {
        n -> nlinhas = nlinha;
        n -> ncolunas = ncoluna;

        return n;
    }
}


int m_free(Matriz *n)
{
    if(n != NULL)
    {
        free(n -> dados);
        free(n);

        return 1;
    }
    else
    {
        return -1;
    }
}



int m_insert_int(Matriz *n, int i, int j, int val)
{

    if(n != NULL)
    {
        if(i > n->nlinhas || i < 0)
        return -1;

        if(j > n->ncolunas || j < 0)
        return -1;

        n -> dados[j * n -> nlinhas + i] = val;
        return 1;
    }
    else
    {
        return -1;
    }
}


int m_select_int(Matriz *n, int i, int j, int* val)
{

    if(n != NULL)
    {
        int a;

        if(i > n->nlinhas || i < 0)
        return -1;

        if(j > n->ncolunas || j < 0)
        return -1;

        a = n -> dados[j * n -> nlinhas + i];
        *val = a;
    }
    else
    {
        return -1;
    }

    return 1;
}




int m_fill(Matriz *n, int val)
{

    if(n != NULL)
    {

        for(int i = 0; i < n -> nlinhas; i++)
        {
            for(int j = 0; j < n -> ncolunas; j++)
            {
                n -> dados[j * n -> nlinhas + i] = val;
            }
        }

        return 1;
    }
    else
    {
        return -1;
    }
}

int m_get_lin_col(Matriz *m, int *nLin, int *nCol)
{
    *nLin = m->nlinhas;
    *nCol = m->ncolunas;

    return 1;
}


int m_tad_print(Matriz *m)
{
    int val;
    for(int i = 0; i < m->nlinhas; i++)
    {
        printf("\n");
        for(int j = 0; j < m->ncolunas; j++)
        {
            m_select_int(m, i, j, &val);
            printf("%d ", val);
        }
    }

    return 1;
}

