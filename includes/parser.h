#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

typedef struct _ast {
    token_t token;
    struct _ast *left, *right;
} ast_t;

/* Grammar definition:
<expr>     ::= <add_sub>
<add_sub>  ::= <mul_div>  ("+" | "-") <add_sub> | <mul_div>
<mul_div>  ::= <power_of> ("*" | "/") <mul_div> | <power_of>
<power_of> ::= <unary> "^" <power_of> | <unary>
<unary>    ::= "-" <unary> | <paren>
<paren>    ::= "(" <expr> ")" | <int>
<int>      ::= [0-9]+
*/

// Recursive descent parsing functions:
ast_t *expr(token_t *),
	  *add_sub(token_t **),
	  *mul_div(token_t **),
	  *power_of(token_t **),
	  *unary(token_t **),
	  *paren(token_t **),
	  *integer(token_t **);



#endif

