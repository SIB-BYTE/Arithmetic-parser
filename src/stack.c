#include "../includes/stack.h"

stack_t *new_stack(size_t cap) {
	if(!cap)
		return puts("Invalid stack size!"), NULL;

	stack_t *stack = calloc(1, sizeof(stack_t));

	stack->stack_cap = cap;
	stack->stack = malloc(stack->stack_cap * sizeof(char));

	return stack;
}

void push(stack_t *stack, char paren) {
	if(!stack)
		return;

	if(stack->stack_cap == stack->stack_len) {
		stack->stack_cap *= 2;
		stack->stack = realloc(stack->stack, stack->stack_cap);
	}

	stack->stack[stack->sp++] = paren;
	stack->stack_len++;
}

void pop(stack_t *stack) {
	if(stack->sp <= 0 || !stack)
		return;

	stack->sp--;
}

bool scan_pair(token_t *token_stream, size_t ts_len) {
	if(!token_stream || !ts_len)
		return false;

	stack_t *stack = new_stack(5);

	for(size_t i = 0; i < ts_len; ++i) {
		if(token_stream[i].type == LEFT_PAREN)
			push(stack, '(');
		else if(token_stream[i].type == RIGHT_PAREN) {
			if(!stack->sp)
				return false;

			pop(stack);
		}
	}

	return !stack->sp;
}

