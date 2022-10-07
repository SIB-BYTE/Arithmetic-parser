# Arithmetic-parser
A basic arithmetic parser which uses a basic LL parsing algorithm aka recursive descent parsing.

# Preface:
This is a basic arithmetic parser written in C, it utilizes recursive descent parsing which is an LL(1) parsing algorithm.

# What is recursive descent parsing?
Recursive descent parsing is a parsing algorithm that parses LL-based grammars via converting non-terminals into procedures that handle the terminal sequences in the grammar. It allows for backtracking which is seen as inefficient but we can perform certain translations to a given context-free grammar to make backtracking more avoidable, a translation / resolution technique you can do is left-factoring of a given grammar. It simply eliminates a starting terminal in a given non-terminal production rule to avoid backtracking but it's not needed.

# What's the issues of recursive descent parsing?
Recursive descent parsing has some issues, the main issue of it is a lack of efficiency in performance and it not being able to handle left recursion. The issue with that is, is it can cause infinite recursion if not handled properly; an example of that would look like such:
```bnf
<expr> ::= <add_or_sub>
<add_or_sub> ::= <add_or_sub> ("+" | "-") <mul_or_div> | <mul_or_div>
<mul_or_div> ::= <mul_or_div> ("*" | "/") <int> | <int>
<int> ::= [0-9]+
```
This grammar is deterministic and non-ambiguous but it cannot be parsed by a recursive descent parser because the code would look like such:
```c
typedef struct _ast_node_t {
  token_t token;
  struct _ast_node_t *left,
                     *right;
} ast_node_t;

ast_node_t *new_ast_node(token_t token, ast_node_t *left, ast_node_t *right) {
  ast_node_t *ast_node = malloc(sizeof(ast_node_t));
  ast_node->token = token;
  ast_node->left  = left;
  ast_node->right = right;

  return ast_node;
}

ast_node_t *expr(token_t *token_stream) {
   token_t *tmp_stream = token_stream;
   return add_or_sub(&tmp_stream);
}

ast_node_t *add_or_sub(token_t **token_stream) {
  ast_node_t *result = add_or_sub(token_stream); // endless recursion
  
  if((*token_stream)->type == '+' || *(token_stream)->type == '-' {
    token_t token = *(*token_stream)++;
    result = new_ast_node(token, result, add_or_sub(token, token_stream));
  }
  
  return result;
}

// You get the idea
```

# Better algorithms:

# Resources for learning:
