/****************************************************************************/
/*                                 explist.c                                */
/****************************************************************************/

#include "explist.h"

#include <stdlib.h>
#include <stdio.h>

struct Explist {
    AST_Node head;
    struct Explist *rest;
};

Explist Explist_new()
{
    Explist e = malloc(sizeof(*e));
    if (e == NULL) {
        perror("Explist_new");
        exit(EXIT_FAILURE);
    }

    e->head = NULL;
    e->rest = NULL;

    return e;
}

void Explist_free(Explist *e)
{
    while (*e != NULL) *e = Explist_pop(*e);
}

void Explist_print(Explist e)
{
    if (e == NULL) {
        fputc('\n', stdout);
        return;
    }
    AST_print(e->head);
    Explist_print(e->rest);
}

Explist Explist_prepend(Explist head, Explist rest)
{
    if (head == NULL) return rest;
    head->rest = rest;
    return head;
}

Explist Explist_pop(Explist e)
{
    if (e == NULL) return NULL;
    Explist t = e->rest;
    AST_free(&(e->head));
    free(e);
    return t;
}

Explist Explist_add(AST_Node n, Explist e)
{
    if (n == NULL) {
        return e;
    }
    if (e == NULL) {
        e = Explist_new();
        if (e == NULL) {
            perror("Explist_add");
            exit(EXIT_FAILURE);
        }
    }

    e->head = AST_insert(n, e->head);
    return e;
}

AST_Node Explist_toAST(Explist e)
{
    if (e == NULL) return NULL;
    return AST_copy(e->head);
}

Explist Explist_collapse(Explist e)
{
    if (e == NULL) return e;
    if (e->rest == NULL) return e;

    Explist prev = e->rest;
    AST_Node paren = AST_rightmost(prev->head);
    AST_Node this = e->head;

    AST_setright(paren, AST_copy(this));

    return Explist_pop(e);
}

