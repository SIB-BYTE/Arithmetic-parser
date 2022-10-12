#ifndef AST_H
#define AST_H

#include <math.h>
#include "parser.h"

// AST functionalities:
void dump_ast(ast_t *);
void destroy_ast(ast_t *);
double evaluate_ast(ast_t *);

#endif

