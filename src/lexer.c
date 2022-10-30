#include "../includes/lexer.h"

// Creates an instance of the lexer structure:
lexer_t *new_lexer(size_t ts_cap) {
	LASSERT(ts_cap, "Token stream capacity cannot be 0\n");

	lexer_t *lexer = calloc(1, sizeof(lexer_t));
	LASSERT(lexer, "Failure to allocate memory\n");

	lexer->ts_cap = ts_cap;
	lexer->token_stream = malloc(lexer->ts_cap * sizeof(token_t));
	LASSERT(lexer->token_stream, "Failure to allocate memory\n");

	return lexer;
}

// Inserts a token into the token stream:
void insert_token(lexer_t *lexer, token_t token) {
	LASSERT(lexer, "Lexer is NULL\n");

	if(lexer->ts_len == lexer->ts_cap) {
		lexer->ts_cap *= 2;
		lexer->token_stream = realloc(lexer->token_stream, lexer->ts_cap);

		LASSERT(lexer->token_stream, "Failed to extend token stream");
	}

	lexer->token_stream[lexer->ts_len++] = token;
}

// Binds a token type & value to a string and return it:
const char *bind_token(token_t token) {
	switch(token.type) {
		case INT: {
			static char digit_buff[44] = {0};
			sprintf(digit_buff, "(token: INT, lexeme: '%ld')", token.value);

			return digit_buff;
		}

		case ADD_OP:      return "(token: ADD_OP, lexeme: '+')";
		case SUB_OP:      return "(token: SUB_OP, lexeme: '-')";
		case MUL_OP:      return "(token: MUL_OP, lexeme: '*')";
		case DIV_OP:      return "(token: DIV_OP, lexeme: '/')";
		case POWER_OF:    return "(token: POWER_OF, lexeme: '^')";
		case LEFT_PAREN:  return "(token: LEFT_PAREN, lexeme: '(')";
		case RIGHT_PAREN: return "(token: RIGHT_PAREN, lexeme: ')')";
		case EOE: 	  return "(token: EOE, lexeme: None)";
		default:	  return NULL;
	}
}

// Dumps the entire token stream:
void dump_token_stream(lexer_t *lexer) {
	for(size_t i = 0; i < lexer->ts_len; ++i)
		printf("(index: %ld) %s\n", i, bind_token(lexer->token_stream[i]));
}

// Upon detection of a number we scan forward to load the entire number:
long scan_number(const char *src, int *size) {
	LASSERT(size, "Size variable isn't passed\n");

	char *end = NULL;
	long lexme = strtol(src, &end, 10);

	LASSERT(src != end, "Yeah dis broken\n");
	LASSERT(lexme <= MAX_NUM && lexme >= MIN_NUM, "Invalid long size\b");

	*size = end - src;

	src = end;
	return lexme;
}

// Lexical analysis function:
lexer_t *tokenize(const char *src) {
	LASSERT(src, "No expression given!\n");
	lexer_t *tokens = new_lexer(strlen(src));

	for(; *src; ++src) {
		switch(*src) {
			case '\n': continue;
			case ' ':  continue;
			case '+':  insert_token(tokens, (token_t) { .value = 0, .type = ADD_OP} );     break;
			case '-':  insert_token(tokens, (token_t) { .value = 0, .type = SUB_OP} );     break;
			case '*':  insert_token(tokens, (token_t) { .value = 0, .type = MUL_OP} );     break;
			case '/':  insert_token(tokens, (token_t) { .value = 0, .type = DIV_OP} );     break;
			case '^':  insert_token(tokens, (token_t) { .value = 0, .type = POWER_OF});    break;
			case '(':  insert_token(tokens, (token_t) { .value = 0, .type = LEFT_PAREN});  break;
			case ')':  insert_token(tokens, (token_t) { .value = 0, .type = RIGHT_PAREN}); break;
			case '0'...'9': {
				int size = 0;
				insert_token(tokens, (token_t) { .value = scan_number(src, &size), .type = INT });

				src += size - 1;
				break;
			}

			default: printf("{%c} is an invalid token!\n", *src); exit(0);
		}
	}

	insert_token(tokens, (token_t) { .value = 0, .type = EOE });
	return tokens;
}

// Destroys the allocated memory:
void destroy_lexer(lexer_t *lexer) {
	free(lexer->token_stream);
	free(lexer);
}
