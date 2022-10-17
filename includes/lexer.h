#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Debugging function:
#define LASSERT(condition, message, ...) \
    do \
    { \
        if(!(condition)) \
        { \
            fprintf(stderr, \
			"[*] Process terminated! LASSERT(); failed!\n" \
			"Condition\t: {%s}\n" \
			"Function\t: {%s}\n" \
			"Failed in file\t: {%s}\n" \
			"At line \t: {%d}\n", #condition, __func__, __FILE__, __LINE__);\
            fprintf(stderr, message, ##__VA_ARGS__); \
            exit(1); \
        } \
    } while(0) \

// Long type boundary defines
#define MAX_NUM 9223372036854775807L
#define MIN_NUM -MAX_NUM - 1L

// ANSI color clear escape code:
#define CLR "\x1b[0m"

// Token structure:
typedef struct _token {
	enum type {
		INT,
		ADD_OP,
		SUB_OP,
		MUL_OP,
		DIV_OP,
		POWER_OF,
		LEFT_PAREN,
		RIGHT_PAREN,

		EOE,
	} type;

	long value;
} token_t;

// Lexer setup:
typedef struct _lexer {
	size_t ts_cap, ts_len; // token stream capacity && length
	token_t *token_stream; // actual token stream
} lexer_t;

// Lexical analysis functions:
lexer_t *tokenize(const char *);

// Initialization & deinitialization:
lexer_t *new_lexer(size_t);
void destroy_lexer(lexer_t *);

// Helper functions:
void insert_token(lexer_t *, token_t);
long scan_number(const char *, int *);

// Misc:
int char_to_token(char);
const char *bind_token(token_t);
void dump_token_stream(lexer_t *);

#endif

