with open('parser.c', 'r') as f:
    content = f.read()

# TOK_IDENT case에서 TOK_LPAREN일 때 parse_expr() 호출해서 AST_FUNC_CALL 반환
old = 'if (current_token.type == TOK_LPAREN) { lexer_next(); while (current_token.type != TOK_RPAREN) { parse_expr(); if (current_token.type == TOK_COMMA) lexer_next(); } expect(TOK_RPAREN); n = calloc(1, sizeof(AstNode)); n->type = AST_NUMBER; n->number.int_val = 0; free(name); return n; }'

new = 'if (current_token.type == TOK_LPAREN) { lexer_next(); AstNode** args = NULL; int argc = 0; if (current_token.type != TOK_RPAREN) { args = malloc(sizeof(AstNode*)); args[0] = parse_expr(); argc = 1; while (current_token.type == TOK_COMMA) { lexer_next(); argc++; args = realloc(args, sizeof(AstNode*)*argc); args[argc-1] = parse_expr(); } } if (current_token.type == TOK_RPAREN) lexer_next(); n = calloc(1, sizeof(AstNode)); n->type = AST_FUNC_CALL; n->func_call.name = name; n->func_call.args = args; n->func_call.arg_count = argc; return n; }'

content = content.replace(old, new)

with open('parser.c', 'w') as f:
    f.write(content)
print("Done")
