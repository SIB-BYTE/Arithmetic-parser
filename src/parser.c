#include "../includes/parser.h"

/* Grammar definition:
<expr>     ::= <add_sub>
<add_sub>  ::= <mul_div>  ("+" | "-") <add_sub> | <mul_div>
<mul_div>  ::= <power_of> ("*" | "/") <mul_div> | <power_of>
<power_of> ::= <unary> "^" <power_of> | <unary>
<unary>    ::= "-" <unary> | <paren>
<paren>    ::= "(" <expr> ")" | <int>
<int>      ::= [0-9]+
*/

// This is for error displaying, but it's not good at fucking all:
void validate(token_t *token_stream, unsigned int type) {
	/*
	 * Yes I can use LASSERT, but this is mean't to be expanded on. Like for example multiple errors
	 * should be added into an error list with an enumeration indicating the syntax error but I'm too lazy
	*/

	if((++token_stream)->type == type) {
		fprintf(stderr, "[Parser error]: Invalid expression\n");
		exit(0);
	}
}

// Creates an instance of an AST node:
ast_t *new_ast_node(token_t token, ast_t *left, ast_t *right) {
    ast_t *ast_node = malloc(sizeof(ast_t));
    LASSERT(ast_node, "[Parser error]: Failure to allocate memory\n");

    ast_node->token = token;
    ast_node->left  = left;
    ast_node->right = right;

    return ast_node;
}

// <expr>     ::= <add_sub>
ast_t *expr(token_t *token_stream) {
    token_t *saved_token_stream = token_stream;
	return add_sub(&saved_token_stream);
}

// <add_sub>  ::= <mul_div>  ("+" | "-") <add_sub> | <mul_div>
ast_t *add_sub(token_t **token_stream) {
	ast_t *result = mul_div(token_stream);

    if((*token_stream)->type == ADD_OP || (*token_stream)->type == SUB_OP) {
	validate(*token_stream, EOE);

	token_t token = *(*token_stream)++;
        result = new_ast_node(token, result, add_sub(token_stream));
    }

    return result;
}

// <mul_div>  ::= <power_of> ("*" | "/") <mul_div> | <power_of>
ast_t *mul_div(token_t **token_stream) {
    ast_t *result = power_of(token_stream);

    if((*token_stream)->type == MUL_OP || (*token_stream)->type == DIV_OP) {
	validate(*token_stream, EOE);

	token_t token = *(*token_stream)++;
        result = new_ast_node(token, result, mul_div(token_stream));
    }

    return result;
}

// <power_of> ::= <unary> "^" <power_of> | <unary>
ast_t *power_of(token_t **token_stream) {
	ast_t *result = unary(token_stream);

	if((*token_stream)->type == POWER_OF) {
		validate(*token_stream, EOE);

		token_t token = *(*token_stream)++;
		result = new_ast_node(token, power_of(token_stream), result);
	}

	return result;
}

// <unary>    ::= "-" <unary> | <paren>
ast_t *unary(token_t **token_stream) {
	if((*token_stream)->type == SUB_OP) {
		validate(*token_stream, EOE);

		token_t token = *(*token_stream)++;
		return new_ast_node(token, NULL, unary(token_stream));
	}

	return paren(token_stream);
}

// <paren>    ::= "(" <expr> ")" | <int>
ast_t *paren(token_t **token_stream) {
	ast_t *result = NULL;
	if((*token_stream)->type == LEFT_PAREN) {
		(*token_stream)++;

		result = add_sub(token_stream);
		(*token_stream)++;

		return result;
	}

	else if((*token_stream)->type == INT)
		return integer(token_stream);

	return NULL; // unreachable
}

// <int>      ::= [0-9]+
ast_t *integer(token_t **token_stream) {
    validate(*token_stream, INT);

    token_t token = *(*token_stream)++;
    return new_ast_node(token, NULL, NULL);
}
