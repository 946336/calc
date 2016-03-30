/****************************************************************************/
/*                                  ast.c                                   */
/****************************************************************************/

#include "ast.h"

#include <stdlib.h>
#include <stdio.h>

#include <math.h>
#include <stdbool.h>

/****************************************************************************/

void label(const char *msg)
{
    static int count = 0;
    fprintf(stderr, "[%d]: %s\n", count++, msg);
}

/****************************************************************************/

struct AST_Node {
    AST_Node left;
    AST_Node right;
    TYPE type;
    double num;
};

AST_Node AST_new()
{
    AST_Node n = malloc(sizeof(*n));
    if (n == NULL) {
        perror("AST_new");
        exit(EXIT_FAILURE);
    }

    n->type = LITERAL;
    n->left = NULL;
    n->right = NULL;
    n->num = 0;

    return n;
}

void AST_free(AST_Node *n)
{
    if ((n == NULL) || (*n == NULL)) return;
    AST_Node t = *n;
    AST_free(&(t->left));
    AST_free(&(t->right));

    free(t);
    *n = NULL;
}

AST_Node AST_copy(AST_Node n)
{
    if (n == NULL) return NULL;
    AST_Node c = malloc(sizeof(*c));
    if (c == NULL) {
        perror("AST_copy");
        exit(EXIT_FAILURE);
    }

    c->type = n->type;
    c->num = n->num;
    c->left = AST_copy(n->left);
    c->right = AST_copy(n->right);

    return c;
}

AST_Node AST_settype(AST_Node n, TYPE type)
{
    if (n == NULL) return NULL;

    n->type = type;
    return n;
}

AST_Node AST_setright(AST_Node n, AST_Node r)
{
    if (n == NULL) return NULL;

    n->right = r;
    return n;
}

AST_Node AST_setleft(AST_Node n, AST_Node l)
{
    if (n == NULL) return NULL;

    n->left = l;
    return n;
}

AST_Node AST_setnum(AST_Node n, double num)
{
    if (n == NULL) return NULL;

    n->num = num;
    return n;
}

TYPE AST_gettype(AST_Node n)
{
    if (n == NULL) {
        fprintf(stderr, "%s\n", "AST_gettype: cannot extract type from NULL");
        exit(EXIT_FAILURE);
    } 
    return n->type;
}

AST_Node AST_getright(AST_Node n)
{
    if (n == NULL) {
        fprintf(stderr, "%s\n", "AST_getright: cannot extract right child "
                                "from NULL");
        exit(EXIT_FAILURE);
    } else if (n->type == LITERAL) {
        fprintf(stderr, "%s\n", "AST_getright: cannot extract right child "
                                "from [LITERAL] node");
        exit(EXIT_FAILURE);
    }
    return n->right;
}

AST_Node AST_getleft(AST_Node n)
{
    if (n == NULL) {
        fprintf(stderr, "%s\n", "AST_getleft: cannot extract left child "
                                "from NULL");
        exit(EXIT_FAILURE);
    } else if (n->type == LITERAL) {
        fprintf(stderr, "%s\n", "AST_getleft: cannot extract left child "
                                "from [LITERAL] node");
        exit(EXIT_FAILURE);
    }
    return n->left;
}

double AST_getnum(AST_Node n)
{
    if (n == NULL) {
        fprintf(stderr, "%s\n", "AST_getnum: cannot extract number from "
                                "NULL");
        exit(EXIT_FAILURE);
    } else if (n->type != LITERAL) {
        fprintf(stderr, "%s\n", "AST_getnum: cannot extract number from "
                                "non-literal node");
        exit(EXIT_FAILURE);
    }
    return n->num;
}

bool AST_wellformed(AST_Node n)
{
    if (n == NULL) return true;

    bool left;
    bool right;

    switch (n->type) {
        case LITERAL: return true;
        case PAREN:
            return (n->right == NULL) ? false : AST_wellformed(n->right);
        default:
            left = (n->left == NULL) ? false : AST_wellformed(n->left);
            right = (n->right == NULL) ? false : AST_wellformed(n->right);
            return left && right;
    }
}

bool AST_caninsertnum(AST_Node n)
{
    if (n == NULL) return true;

        if (n->type == LITERAL) return false;
        else return AST_caninsertnum(n->right);
}

AST_Node AST_rightmost(AST_Node root)
{
    if ((root == NULL) || (root->right == NULL)) return root;
    else return AST_rightmost(root->right);
}

AST_Node AST_insert(AST_Node n, AST_Node root)
{
    if (n == NULL) return root;
    if (root == NULL) return n;

    if ((n->type == LITERAL) || (n->type == PAREN)) {
        return AST_insertnum(n, root);
    } else return AST_insertoperator(n, root);
}

AST_Node AST_insertnum(AST_Node n, AST_Node root)
{
    if (n == NULL) return root;
    if (root == NULL) return n;

    if (root->type == LITERAL) {
        fprintf(stderr, "%s [%0.15f] %s\n", "AST_insertnum: cannot insert "
                                            "literal", n->num, "into filled "
                                            "tree");
        exit(EXIT_FAILURE);
    }
    if (root->right == NULL) {
        root->right = n;
        return root;
    } else {
        (void) AST_insertnum(n, root->right);
        return root; 
    }
}

AST_Node AST_insertoperator(AST_Node n, AST_Node root)
{
    if (n == NULL) return root;
    if (root == NULL) return n;

    // If the node to insert binds tighter than the node we are inspecting,
    // check the next node down
    if (bindsTighterThan(n, root)) {
        // If our new node also binds tighter than the child node, then we need
        // to go deeper
        if (bindsTighterThan(n, root->right)) {
            (void) AST_insertoperator(n, root->right);
            return root;
        }
        // If new node is tighter than parent and looser than child, insert
        // new node in between them
        else {
            n->left = root->right;
            root->right = n;
            return root;
        }
    }
    // The new node is not tighter than the root
    else {
        // If the new node binds tighter than the root's child too, problems
        // unless the root is a paren group
        if (bindsTighterThan(n, root->right) && (root->type != PAREN)) {
            fprintf(stderr, "%s: [%s] %s [%s and %s]\n",
                            "AST_insertoperator: malformed tree. Operator "
                            "precedence violated", TYPEtostring(n->type),
                            "does not belong between", TYPEtostring(root->type),
                            TYPEtostring(root->right->type));
            exit(EXIT_FAILURE);
        }
        // If the new node is looser than both, then new node is new root
        else {
            n->left = root;
            return n;
        }
    }
    return root;
}

bool bindsTighterThan(AST_Node lhs, AST_Node rhs)
{
    if (lhs == NULL) return true;
    if (rhs == NULL) return false;
    return hasHigherPriorityThan(lhs->type, rhs->type);
}

void AST_print(AST_Node root)
{
    if (root == NULL) return;
    switch (root->type) {
        case LITERAL:
            fprintf(stdout, "%.15g ", root->num);
            break;
        case PAREN:
            fprintf(stdout, "( ");
            AST_print(root->right);
            fprintf(stdout, ") ");
            break;
        case EXP:
            if (VERBOSE) fprintf(stdout, "( ");
            AST_print(root->left);
            fprintf(stdout, "%c ", EXP_CHAR);
            AST_print(root->right);
            if (VERBOSE) fprintf(stdout, ") ");
            break;
        case LOG:
            if (VERBOSE) fprintf(stdout, "( ");
            AST_print(root->left);
            fprintf(stdout, "%c ", LOG_CHAR);
            AST_print(root->right);
            if (VERBOSE) fprintf(stdout, ") ");
            break;
        case MOD:
            if (VERBOSE) fprintf(stdout, "( ");
            AST_print(root->left);
            fprintf(stdout, "%c ", MOD_CHAR);
            AST_print(root->right);
            if (VERBOSE) fprintf(stdout, ") ");
            break;
        case INT:
            if (VERBOSE) fprintf(stdout, "( ");
            AST_print(root->left);
            fprintf(stdout, "%c ", INT_CHAR);
            AST_print(root->right);
            if (VERBOSE) fprintf(stdout, ") ");
            break;
        case PROD:
            if (VERBOSE) fprintf(stdout, "( ");
            AST_print(root->left);
            fprintf(stdout, "%c ", PROD_CHAR);
            AST_print(root->right);
            if (VERBOSE) fprintf(stdout, ") ");
            break;
        case QUOT:
            if (VERBOSE) fprintf(stdout, "( ");
            AST_print(root->left);
            fprintf(stdout, "%c ", QUOT_CHAR);
            AST_print(root->right);
            if (VERBOSE) fprintf(stdout, ") ");
            break;
        case SUM:
            if (VERBOSE) fprintf(stdout, "( ");
            AST_print(root->left);
            fprintf(stdout, "%c ", SUM_CHAR);
            AST_print(root->right);
            if (VERBOSE) fprintf(stdout, ") ");
            break;
        case DIFF:
            if (VERBOSE) fprintf(stdout, "( ");
            AST_print(root->left);
            fprintf(stdout, "%c ", DIFF_CHAR);
            AST_print(root->right);
            if (VERBOSE) fprintf(stdout, ") ");
            break;
    }
}

double AST_eval(AST_Node root)
{
    if (root == NULL) {
        fprintf(stderr, "%s\n", "AST_eval: malformed tree - cannot evaluate "
                                "incomplete tree");
        exit(EXIT_FAILURE);
    }

    switch (root->type) {
        case LITERAL: return root->num;
        case PAREN: return AST_eval(root->right);
        case EXP: return pow(AST_eval(root->left), AST_eval(root->right));
        case LOG: return log(AST_eval(root->left)) / log(AST_eval(root->right));
        case MOD: return fmod(AST_eval(root->left), AST_eval(root->right));
        case INT: return (int) (AST_eval(root->left) / AST_eval(root->right));
        case PROD: return AST_eval(root->left) * AST_eval(root->right);
        case QUOT: return AST_eval(root->left) / AST_eval(root->right);
        case SUM: return AST_eval(root->left) + AST_eval(root->right);
        case DIFF: return AST_eval(root->left) - AST_eval(root->right);
    }
    // Compiler dummy
    return 0;
}

