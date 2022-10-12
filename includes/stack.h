#ifndef STACK_H
#define STACK_H

#include "lexer.h"
#include <stdbool.h>

// Stack structure:
typedef struct _stack {
	ssize_t sp;
	char *stack;
	size_t stack_len, stack_cap;
} stack_t;

// Initialization & deinitialization:
stack_t *new_stack(size_t);
void destroy_stack(stack_t *);

// Stack functionalities:
void push(stack_t *, char),
	 pop(stack_t *);

// Bracket balancing:
bool scan_pair(token_t *, size_t);

#endif

