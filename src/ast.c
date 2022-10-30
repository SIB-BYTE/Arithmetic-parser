#include "../includes/ast.h"

// Recursive post-order display function:
void dump_ast(ast_t *root) {
    if(!root)
        return;

    printf("%s\n", bind_token(root->token));
    dump_ast(root->left);
    dump_ast(root->right);
 }

// Recusively evaluates the abstract syntax tree:
double evaluate_ast(ast_t *ast) {
    if(!ast)
        return 0;

    double left = evaluate_ast(ast->left),
 	  right = evaluate_ast(ast->right);

    switch(ast->token.type) {
        case INT:      return ast->token.value;
        case ADD_OP:   return left + right;
        case SUB_OP:   return left - right;
        case MUL_OP:   return left * right;
        case DIV_OP:   return left / right;
 	case POWER_OF: return pow(right, left);
	default:       return -1;
    }
}

// Postorder destruction function:
void destroy_ast(ast_t *root) {
    if(!root)
        return;

    destroy_ast(root->left);
    destroy_ast(root->right);
    free(root);
}

