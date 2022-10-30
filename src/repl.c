#include "../includes/ast.h"
#include "../includes/lexer.h"
#include "../includes/stack.h"
#include "../includes/parser.h"

void repl(void) {
    char buffer[128] = {0};

    for(;;) {
	printf("Enter an expression: ");
	LASSERT(fgets(buffer, sizeof(buffer), stdin), "Failed to read from stdin\n");

	lexer_t *tokens = tokenize(buffer);

	if(!scan_pair(tokens->token_stream, tokens->ts_len)) {
		puts("Unbalanced parentheses!");
		continue;
	}

	puts("\x1b[0;31mLexer output: ");
	dump_token_stream(tokens);
	puts(CLR);

	ast_t *ast_root = expr(tokens->token_stream);

	puts("\x1b[0;34mParsing result (AST-form): ");
	dump_ast(ast_root);
	puts(CLR);

	printf("Result of %s= %lf\n", buffer, evaluate_ast(ast_root));

	destroy_lexer(tokens);
	destroy_ast(ast_root);
    }
}

