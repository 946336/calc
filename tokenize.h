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

// Error messages resulting from an invalid token (ie: not math, like "2+cake")
// originate come from here.
Token next_token(char **str);

#endif

