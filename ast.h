/****************************************************************************/
/*                                  ast.h                                   */
/****************************************************************************/

#ifndef CALC_AST_H
#define CALC_AST_H 

#include "operator.h"

#include <stdbool.h>
#include <stdio.h>

#define VERBOSE false

typedef struct AST_Node *AST_Node;

AST_Node AST_new();
void     AST_free(AST_Node *n);
AST_Node AST_copy(AST_Node n);

AST_Node AST_settype(AST_Node n, TYPE type);
AST_Node AST_setright(AST_Node n, AST_Node r);
AST_Node AST_setleft(AST_Node n, AST_Node l);
AST_Node AST_setnum(AST_Node n, double num);

TYPE     AST_gettype(AST_Node n);
AST_Node AST_getright(AST_Node n);
AST_Node AST_getleft(AST_Node n);
double   AST_getnum(AST_Node n);

bool        AST_wellformed(AST_Node root);
bool        AST_caninsertnum(AST_Node root);
AST_Node    AST_rightmost(AST_Node root);

AST_Node AST_insert(AST_Node n, AST_Node root);
AST_Node AST_insertnum(AST_Node n, AST_Node root);
AST_Node AST_insertoperator(AST_Node n, AST_Node root);

bool bindsTighterThan(AST_Node lhs, AST_Node rhs);

void   AST_print(AST_Node root);
double AST_eval(AST_Node);

void label(const char *msg);

#endif

