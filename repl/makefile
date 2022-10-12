CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -O3 -g3 -lm -o
DEBUG_FLAGS = -Wall -Wextra -Wpedantic -O3 -g3 -fsanitize=address,undefined -lm -o

MAIN_SRC   = main.c
LEXER_SRC  = ../src/lexer.c
PARSER_SRC = ../src/parser.c
AST_SRC    = ../src/ast.c
STACK_SRC  = ../src/stack.c
REPL_SRC   = ../src/repl.c

BUILD_SET  = $(MAIN_SRC) $(LEXER_SRC) $(PARSER_SRC) $(AST_SRC) $(STACK_SRC) $(REPL_SRC)
MAIN_BIN   = main

build:
	$(CC) $(BUILD_SET) $(CFLAGS) $(MAIN_BIN)

build_debug:
	$(CC) $(BUILD_SET) $(DEBUG_FLAGS) $(MAIN_BIN)


