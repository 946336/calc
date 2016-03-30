/****************************************************************************/
/*                                 parse.h                                  */
/****************************************************************************/

#ifndef CALC_PARSE_H
#define CALC_PARSE_H 

#include "ast.h"
#include "explist.h"
#include "tokenize.h"
#include "operator.h"

AST_Node parse(char *l);

#endif

