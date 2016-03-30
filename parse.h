/****************************************************************************/
/*                                 parse.h                                  */
/****************************************************************************/

#ifndef CALC_PARSE_H
#define CALC_PARSE_H 

#include "ast.h"
#include "explist.h"
#include "tokenize.h"
#include "operator.h"

// Errors resulting from a badly formed mathematical expression are identified
// in this function.
AST_Node parse(char *l);

#endif

