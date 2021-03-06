/****************************************************************************/
/*                                 parse.h                                  */
/****************************************************************************/

#include <stdlib.h>
#include <stdio.h>

#include "parse.h"
#include "operator.h"

#include "ast.h"

AST_Node parse(char *l)
{
    Explist e = Explist_new();
    Explist e_;
    Token t;
    Token last = {'\0', NULL};
    AST_Node root = NULL;

    bool done = false;

    while (!done) {
        t = next_token(&l);

        if (t.n == NULL) {
            done = true;
            continue;
        }

        TYPE type = AST_gettype(t.n);

        // Closing paren followed by opening paren or literal
        if ((last.c == RPAREN) && ((type == LITERAL) || (t.c == LPAREN))) {
            AST_Node mul = AST_settype(AST_new(), PROD);
            e = Explist_add(mul, e);
        }
        // Literal followed by opening paren
        else if ((last.n != NULL) &&
                 (AST_gettype(last.n) == LITERAL) && (t.c == LPAREN)) {
            AST_Node mul = AST_settype(AST_new(), PROD);
            e = Explist_add(mul, e);
        }

        if (t.c == LPAREN) {
            e = Explist_add(t.n, e);
            e = Explist_prepend(Explist_new(), e);
    
            AST_free(&last.n);
            last.c = t.c;
            last.n = AST_copy(t.n);
            continue;
        }
        if (t.c == RPAREN) {
            e_ = Explist_collapse(e);
            if (e == e_) {
                fprintf(stderr, "%s\n", "Unexpected right parenthesis");
                Explist_free(&e_);
                AST_free(&t.n);
                AST_free(&last.n);
                return NULL;
            }
            e= e_;
            
            AST_free(&t.n);
            AST_free(&last.n);
            last.c = t.c;
            last.n = AST_copy(t.n);
            continue;
        }

        // Literal followed by literal
        if ((AST_gettype(t.n) == LITERAL) &&
            ((last.n != NULL) && (AST_gettype(last.n) == LITERAL))) {
            fprintf(stderr, "%s %.15g and %.15g\n", "Missing operator "
                            "between", AST_getnum(last.n), AST_getnum(t.n));
            Explist_free(&e);
            AST_free(&t.n);
            AST_free(&last.n);
            return NULL;
        }

        e = Explist_add(t.n, e);
        AST_free(&last.n);
        last.c = t.c;
        last.n = AST_copy(t.n);
    }

    if (!Explist_singleton(e)) {
        fprintf(stderr, "%s\n", "Unclosed parenthesis");
        Explist_free(&e);
    } else {
        root = Explist_toAST(e);
    }

    if (!AST_wellformed(root)) {
        fprintf(stderr, "%s\n", "Incomplete expression - Missing operand "
                                "to an operator");
        AST_free(&root);
    }

    Explist_free(&e);
    AST_free(&last.n);
    return root;
}

