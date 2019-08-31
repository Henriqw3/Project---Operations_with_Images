#include "TADPilha.h"

typedef struct snode Snode;


struct stack
{
    Snode *head;
    int size;
};

struct snode
{
    Snode *next;
    Ponto data;
};


Stack *stack_create()
{
    Stack *st = NULL;
    st = malloc(sizeof(Stack));

    if(st != NULL)
    {
        st->head = NULL;
        st->size = 0;
    }
    return st;
}

void stack_free(Stack *st)
{
    Snode *aux = NULL;
    Snode *p = NULL;

    if(st != NULL)
    {
            if(st->size > 0)
            {
                aux = st->head;
                while(aux != NULL)
                {
                    p = aux;
                    aux = aux->next;
                    free(p);
                }
            }
    }

    free(st);
}

int stack_push(Stack *st, Ponto p)
{
    Snode *node = NULL;

    if(st == NULL)
        return 0;

    node = malloc(sizeof(Snode));
    if(node == NULL)
        return 0;

    node->data = p;
    node->next = NULL;

    if(st->size == 0)
    {
        st->head = node;
        st->size++;
        return 1;
    }
    else
    {
        node->next = st->head;
        st->head = node;
        st->size++;
        return 1;
    }
}

int stack_pop(Stack *st)
{
    Snode *aux = NULL;

    if(st == NULL)
        return 0;

    if(st->size <= 0)
        return 0;

    if(st->size == 1)
    {
        free(st->head);
        st->head = NULL;
        st->size--;
        return 1;
    }
    else
    {
        aux = st->head->next;


        free(st->head);
        st->head = aux;
        st->size--;
        return 1;
    }
}

int stack_top(Stack *st, Ponto *p)
{

    if(st == NULL)
        return 0;

    if(st->size == 0)
        return 0;

    *p = st->head->data;
    return 1;
}

int stack_size(Stack *st)
{
    if(st == NULL)
        return -1;

    return st->size;
}

int stack_print(Stack *st)
{
    Snode *aux = NULL;

    if(st == NULL)
        return 0;

    if(st->size == 0)
        return 0;

    aux = st->head;
    while(aux != NULL)
    {
        printf("\nX: %d", aux->data.x);
        printf("\nY: %d", aux->data.y);
        printf("\n=============================================================");
        aux = aux->next;
    }

    return 0;
}
