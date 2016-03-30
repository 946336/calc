/****************************************************************************/
/*                                operator.h                                */
/****************************************************************************/

#ifndef CALC_OPERATOR_H
#define CALC_OPERATOR_H 

#include <stdbool.h>

typedef enum TYPE { LITERAL = 0,
                    PAREN,
                    EXP, LOG,
                    MOD, INT,
                    PROD, QUOT,
                    SUM, DIFF
                  } TYPE;

static const char delim[] = "()^|%\\*/+-";

/****************************************************************************/

#define LIT_CHAR    '$'
#define PAREN_CHAR  '&'
#define EXP_CHAR    '^'
#define LOG_CHAR    '|'
#define MOD_CHAR    '%'
#define INT_CHAR    '\\'
#define PROD_CHAR   '*'
#define QUOT_CHAR   '/'
#define SUM_CHAR    '+'
#define DIFF_CHAR   '-'

#define LPAREN '('
#define RPAREN ')'

/****************************************************************************/

TYPE  stringtoTYPE(char *str);
const char *TYPEtostring(TYPE type);

TYPE chartoTYPE(char c);
char TYPEtochar(TYPE type);

bool hasHigherPriorityThan(TYPE lhs, TYPE rhs);

#endif

