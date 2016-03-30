/****************************************************************************/
/*                                tokenize.c                                */
/****************************************************************************/

#include "tokenize.h"
#include "operator.h"

#include <string.h>
#include <ctype.h>

#include <stdio.h>
#include <stdlib.h>

/****************************************************************************/

static char matchDelim(char c)
{
    for (const char *delim_ = delim; *delim_ != NULLCHAR; delim_++) {
        if (c == *delim_) return *delim_;
    }
    return NULLCHAR;
}

/****************************************************************************/

Token next_token(char **str)
{
    Token t = {'\0', NULL};
    char *s = *str;

    if ((str == NULL) || (*str == NULL) || (**str == NULLCHAR)) {
        return t;
    }

    // Eat whitespace
    while (isspace(*s)) ++s;

    // If we match a delimiter, we're done
    if (matchDelim(*s) != NULLCHAR) {
        t.n = AST_new();
        AST_settype(t.n, chartoTYPE(*s));
        t.c = *s;

        *str = ++s;
        return t;
    }
    char *jump = NULL;
    double literal = strtod(s, &jump);

    // If we matched a number, we're done
    if (s != jump) {
        t.n = AST_new();
        AST_settype(t.n, LITERAL);
        AST_setnum(t.n, literal);
        *str = jump;
        return t;
    }

    // If we don't know what to do with the string, print an error
    fprintf(stderr, "%s: [%s]\n", "Invalid expression", s);
    return t;
}

