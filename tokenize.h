/****************************************************************************/
/*                                tokenize.h                                */
/****************************************************************************/

#ifndef CALC_TOKENIZE_H
#define CALC_TOKENIZE_H 

#include "ast.h"
#include "operator.h"

typedef struct Token {
    char c;
    AST_Node n;
} Token;

static const char NULLCHAR = '\0';

Token next_token(char **str);

#endif

