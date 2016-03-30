/****************************************************************************/
/*                                 explist.h                                */
/****************************************************************************/

#ifndef CALC_EXPLIST_H
#define CALC_EXPLIST_H 

#include "ast.h"
#include "operator.h"

typedef struct Explist *Explist;

Explist Explist_new();
void    Explist_free(Explist *e);

void Explist_print(Explist e);

Explist Explist_prepend(Explist head, Explist rest);
Explist Explist_pop(Explist e);

Explist Explist_add(AST_Node n, Explist e);

AST_Node Explist_toAST(Explist e);
Explist  Explist_collapse(Explist e);

bool Explist_singleton(Explist e);

#endif

