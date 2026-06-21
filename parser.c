#include "parser.h"
#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern AstNode* import_file(const char* path);

static char* struct_names[32]; static int struct_name_count = 0;
static int is_struct_type(const char* name) { for (int i = 0; i < struct_name_count; i++) if (strcmp(struct_names[i], name) == 0) return 1; return 0; }

static void synchronize() {
    lexer_next();
    while (current_token.type != TOK_EOF) {
        if (current_token.type == TOK_NEWLINE || current_token.type == TOK_END) {
            lexer_next();
            return;
        }
        switch (current_token.type) {
            case TOK_IF: case TOK_WHILE: case TOK_FUNC: case TOK_STRUCT:
            case TOK_FOR: case TOK_DO: case TOK_PRINT: case TOK_RETURN:
                return;
            default:
                lexer_next();
        }
    }
}

static void expect(TokenType t) { if (current_token.type != t) { fprintf(stderr,"Error at line %d: expected %s but got '%s'\n",current_token.line, token_name(t), current_token.lexeme); synchronize(); return; } lexer_next(); }
static void skip_nl() { while (current_token.type == TOK_NEWLINE) lexer_next(); }
static AstNode* parse_expr();
static AstNode* parse_block();

static AstNode* parse_primary() {
    AstNode* n = calloc(1, sizeof(AstNode));
    switch (current_token.type) {
        case TOK_MINUS: lexer_next(); n->type = AST_BINARY; n->binary.op = TOK_MINUS; n->binary.left = calloc(1, sizeof(AstNode)); n->binary.left->type = AST_NUMBER; n->binary.left->number.int_val = 0; n->binary.right = parse_primary(); return n;
        case TOK_NOT: lexer_next(); n->type = AST_BINARY; n->binary.op = TOK_NOT; n->binary.left = parse_primary(); n->binary.right = NULL; return n;
        case TOK_NUM_INT: n->type = AST_NUMBER; n->number.is_float = 0; n->number.int_val = current_token.int_val; lexer_next(); return n;
        case TOK_NUM_FLOAT: n->type = AST_NUMBER; n->number.is_float = 1; n->number.float_val = current_token.float_val; lexer_next(); return n;
        case TOK_STRING: n->type = AST_STRING; n->string.value = strdup(current_token.str_val); lexer_next(); return n;
        case TOK_TRUE: n->type = AST_BOOL; n->boolean.value = 1; lexer_next(); return n;
        case TOK_FALSE: n->type = AST_BOOL; n->boolean.value = 0; lexer_next(); return n;
        case TOK_LBRACKET: { lexer_next(); n->type = AST_LIST; n->list.elements = NULL; n->list.count = 0; if (current_token.type != TOK_RBRACKET) { n->list.elements = malloc(sizeof(AstNode*)); n->list.elements[0] = parse_expr(); n->list.count = 1; while (current_token.type == TOK_COMMA) { lexer_next(); n->list.count++; n->list.elements = realloc(n->list.elements, sizeof(AstNode*)*n->list.count); n->list.elements[n->list.count-1] = parse_expr(); } } expect(TOK_RBRACKET); return n; }
        case TOK_IDENT: { char* name = strdup(current_token.lexeme); lexer_next(); if (current_token.type == TOK_LPAREN) { lexer_next(); AstNode** args = NULL; int argc = 0; if (current_token.type != TOK_RPAREN) { args = malloc(sizeof(AstNode*)); args[0] = parse_expr(); argc = 1; while (current_token.type == TOK_COMMA) { lexer_next(); argc++; args = realloc(args, sizeof(AstNode*)*argc); args[argc-1] = parse_expr(); } } if (current_token.type == TOK_RPAREN) lexer_next(); if (is_struct_type(name)) { n->type = AST_STRUCT_CREATE; n->struct_create.struct_name = name; n->struct_create.args = args; n->struct_create.arg_count = argc; } else { n->type = AST_FUNC_CALL; n->func_call.name = name; n->func_call.args = args; n->func_call.arg_count = argc; } return n; } if (current_token.type == TOK_DOT) { lexer_next(); n->type = AST_FIELD_ACCESS; n->field_access.object = calloc(1, sizeof(AstNode)); n->field_access.object->type = AST_IDENT; n->field_access.object->ident.name = name; n->field_access.field = strdup(current_token.lexeme); lexer_next(); return n; } if (current_token.type == TOK_INC) { lexer_next(); n = calloc(1, sizeof(AstNode)); n->type = AST_VAR_ASSIGN; n->var_assign.name = name; AstNode* one = calloc(1,sizeof(AstNode)); one->type=AST_NUMBER; one->number.int_val=1; AstNode* lhs = calloc(1,sizeof(AstNode)); lhs->type=AST_IDENT; lhs->ident.name=strdup(name); AstNode* bin = calloc(1,sizeof(AstNode)); bin->type=AST_BINARY; bin->binary.op=TOK_PLUS; bin->binary.left=lhs; bin->binary.right=one; n->var_assign.value=bin; return n; } if (current_token.type == TOK_DEC) { lexer_next(); n = calloc(1, sizeof(AstNode)); n->type = AST_VAR_ASSIGN; n->var_assign.name = name; AstNode* one = calloc(1,sizeof(AstNode)); one->type=AST_NUMBER; one->number.int_val=1; AstNode* lhs = calloc(1,sizeof(AstNode)); lhs->type=AST_IDENT; lhs->ident.name=strdup(name); AstNode* bin = calloc(1,sizeof(AstNode)); bin->type=AST_BINARY; bin->binary.op=TOK_MINUS; bin->binary.left=lhs; bin->binary.right=one; n->var_assign.value=bin; return n; } if (current_token.type == TOK_LBRACKET) { lexer_next(); n->type = AST_INDEX; n->index_expr.object = calloc(1, sizeof(AstNode)); n->index_expr.object->type = AST_IDENT; n->index_expr.object->ident.name = name; n->index_expr.index = parse_expr(); expect(TOK_RBRACKET); return n; } n->type = AST_IDENT; n->ident.name = name; return n; }
        case TOK_LPAREN: lexer_next(); n = parse_expr(); expect(TOK_RPAREN); return n;
        default: fprintf(stderr,"Error at line %d: unexpected %s\n",current_token.line,token_name(current_token.type)); exit(1);
    }
}

static AstNode* parse_pow() { AstNode* l = parse_primary(); while (current_token.type == TOK_POW) { int op = current_token.type; lexer_next(); AstNode* r = parse_primary(); AstNode* b = calloc(1, sizeof(AstNode)); b->type = AST_BINARY; b->binary.op = op; b->binary.left = l; b->binary.right = r; l = b; } return l; }
static AstNode* parse_mul() { AstNode* l = parse_pow(); while (current_token.type == TOK_STAR || current_token.type == TOK_SLASH || current_token.type == TOK_MOD) { int op = current_token.type; lexer_next(); AstNode* r = parse_primary(); AstNode* b = calloc(1, sizeof(AstNode)); b->type = AST_BINARY; b->binary.op = op; b->binary.left = l; b->binary.right = r; l = b; } return l; }
static AstNode* parse_add() { AstNode* l = parse_mul(); while (current_token.type == TOK_PLUS || current_token.type == TOK_MINUS) { int op = current_token.type; lexer_next(); AstNode* r = parse_mul(); AstNode* b = calloc(1, sizeof(AstNode)); b->type = AST_BINARY; b->binary.op = op; b->binary.left = l; b->binary.right = r; l = b; } return l; }
static AstNode* parse_cmp() { AstNode* l = parse_add(); while (current_token.type >= TOK_EQ_EQ && current_token.type <= TOK_GT_EQ) { int op = current_token.type; lexer_next(); AstNode* r = parse_add(); AstNode* b = calloc(1, sizeof(AstNode)); b->type = AST_BINARY; b->binary.op = op; b->binary.left = l; b->binary.right = r; l = b; } return l; }
static AstNode* parse_and() { AstNode* l = parse_cmp(); while (current_token.type == TOK_AND) { int op = current_token.type; lexer_next(); AstNode* r = parse_cmp(); AstNode* b = calloc(1, sizeof(AstNode)); b->type = AST_BINARY; b->binary.op = op; b->binary.left = l; b->binary.right = r; l = b; } return l; }
static AstNode* parse_or() { AstNode* l = parse_and(); while (current_token.type == TOK_OR) { int op = current_token.type; lexer_next(); AstNode* r = parse_and(); AstNode* b = calloc(1, sizeof(AstNode)); b->type = AST_BINARY; b->binary.op = op; b->binary.left = l; b->binary.right = r; l = b; } return l; }
static AstNode* parse_expr() { return parse_or(); }

static AstNode* parse_stmt() {
    AstNode* n;
    switch (current_token.type) {
        case TOK_NUM: case TOK_TEXT: case TOK_FLAG: case TOK_LIST: case TOK_VAL: case TOK_VAR:;
            
int is_mut = 1; 
is_mut = (current_token.type == TOK_VAL) ? 0 : 1;
            lexer_next(); n = calloc(1, sizeof(AstNode)); n->type = AST_VAR_DECL; n->var_decl.name = strdup(current_token.lexeme); n->var_decl.is_mutable = is_mut; expect(TOK_IDENT);
            if (current_token.type == TOK_EQ) { lexer_next(); n->var_decl.value = parse_expr(); } return n;

            if (current_token.type == TOK_EQ) { lexer_next(); n->var_decl.value = parse_expr(); } return n;
        case TOK_IDENT: { char* name = strdup(current_token.lexeme);
            if (strcmp(name, "import") == 0) { lexer_next(); if (current_token.type == TOK_STRING) { char* path = strdup(current_token.str_val); lexer_next(); AstNode* imported = import_file(path); free(path); free(name); return imported; } }
int is_mut = 1; 
is_mut = (current_token.type == TOK_VAL) ? 0 : 1;
            if (is_struct_type(name)) { lexer_next(); n = calloc(1, sizeof(AstNode)); n->type = AST_VAR_DECL; n->var_decl.name = strdup(current_token.lexeme); n->var_decl.is_mutable = is_mut; expect(TOK_IDENT); if (current_token.type == TOK_LPAREN) { lexer_next(); AstNode** args = NULL; int argc = 0; if (current_token.type != TOK_RPAREN) { args = malloc(sizeof(AstNode*)); args[0] = parse_expr(); argc = 1; while (current_token.type == TOK_COMMA) { lexer_next(); argc++; args = realloc(args, sizeof(AstNode*)*argc); args[argc-1] = parse_expr(); } } if (current_token.type == TOK_RPAREN) lexer_next(); n = calloc(1, sizeof(AstNode)); n->type = AST_FUNC_CALL; n->func_call.name = name; n->func_call.args = args; n->func_call.arg_count = argc; return n; }
            if (current_token.type == TOK_EQ) { lexer_next(); n->var_decl.value = parse_expr(); } free(name); return n; }
            lexer_next(); if (strcmp(name, "main") == 0 && current_token.type != TOK_EQ && current_token.type != TOK_LPAREN && current_token.type != TOK_DOT) { skip_nl(); n = parse_block(); expect(TOK_END); expect(TOK_IDENT); return n; }
            if (current_token.type == TOK_LPAREN) { lexer_next(); AstNode** args = NULL; int argc = 0; if (current_token.type != TOK_RPAREN) { args = malloc(sizeof(AstNode*)); args[0] = parse_expr(); argc = 1; while (current_token.type == TOK_COMMA) { lexer_next(); argc++; args = realloc(args, sizeof(AstNode*)*argc); args[argc-1] = parse_expr(); } } if (current_token.type == TOK_RPAREN) lexer_next(); n = calloc(1, sizeof(AstNode)); n->type = AST_FUNC_CALL; n->func_call.name = name; n->func_call.args = args; n->func_call.arg_count = argc; return n; }

            if (current_token.type == TOK_LPAREN) { lexer_next(); AstNode** args = NULL; int argc = 0; if (current_token.type != TOK_RPAREN) { args = malloc(sizeof(AstNode*)); args[0] = parse_expr(); argc = 1; while (current_token.type == TOK_COMMA) { lexer_next(); argc++; args = realloc(args, sizeof(AstNode*)*argc); args[argc-1] = parse_expr(); } } if (current_token.type == TOK_RPAREN) lexer_next(); n = calloc(1, sizeof(AstNode)); n->type = AST_FUNC_CALL; n->func_call.name = name; n->func_call.args = args; n->func_call.arg_count = argc; return n; }
            if (current_token.type == TOK_INC) { lexer_next(); n = calloc(1, sizeof(AstNode)); n->type = AST_VAR_ASSIGN; n->var_assign.name = name; AstNode* one = calloc(1,sizeof(AstNode)); one->type=AST_NUMBER; one->number.int_val=1; AstNode* lhs = calloc(1,sizeof(AstNode)); lhs->type=AST_IDENT; lhs->ident.name=strdup(name); AstNode* bin = calloc(1,sizeof(AstNode)); bin->type=AST_BINARY; bin->binary.op=TOK_PLUS; bin->binary.left=lhs; bin->binary.right=one; n->var_assign.value=bin; return n; } if (current_token.type == TOK_DEC) { lexer_next(); n = calloc(1, sizeof(AstNode)); n->type = AST_VAR_ASSIGN; n->var_assign.name = name; AstNode* one = calloc(1,sizeof(AstNode)); one->type=AST_NUMBER; one->number.int_val=1; AstNode* lhs = calloc(1,sizeof(AstNode)); lhs->type=AST_IDENT; lhs->ident.name=strdup(name); AstNode* bin = calloc(1,sizeof(AstNode)); bin->type=AST_BINARY; bin->binary.op=TOK_MINUS; bin->binary.left=lhs; bin->binary.right=one; n->var_assign.value=bin; return n; } if (current_token.type == TOK_EQ || current_token.type == TOK_PLUS_EQ || current_token.type == TOK_MINUS_EQ || current_token.type == TOK_STAR_EQ || current_token.type == TOK_SLASH_EQ || current_token.type == TOK_MOD_EQ || current_token.type == TOK_POW_EQ) { int op = current_token.type; lexer_next(); n = calloc(1, sizeof(AstNode)); n->type = AST_VAR_ASSIGN; n->var_assign.name = name; if(op==TOK_EQ)n->var_assign.value = parse_expr(); else { AstNode* lhs = calloc(1,sizeof(AstNode)); lhs->type=AST_IDENT; lhs->ident.name=strdup(name); AstNode* rhs = parse_expr(); AstNode* bin = calloc(1,sizeof(AstNode)); bin->type=AST_BINARY; bin->binary.op=(op==TOK_PLUS_EQ?TOK_PLUS:op==TOK_MINUS_EQ?TOK_MINUS:op==TOK_STAR_EQ?TOK_STAR:op==TOK_SLASH_EQ?TOK_SLASH:TOK_MOD); bin->binary.left=lhs; bin->binary.right=rhs; n->var_assign.value=bin; } return n; }
            fprintf(stderr,"Error at line %d: expected '=' after '%s'\n",current_token.line,name); exit(1);
        }
        case TOK_PRINT: { lexer_next(); expect(TOK_LPAREN); n = calloc(1, sizeof(AstNode)); n->type = AST_PRINT; n->print.args = malloc(sizeof(AstNode*)); n->print.args[0] = parse_expr(); n->print.arg_count = 1; while (current_token.type == TOK_COMMA) { lexer_next(); n->print.arg_count++; n->print.args = realloc(n->print.args, sizeof(AstNode*)*n->print.arg_count); n->print.args[n->print.arg_count-1] = parse_expr(); } expect(TOK_RPAREN); return n; }
        case TOK_IF: lexer_next(); n = calloc(1, sizeof(AstNode)); n->type = AST_IF; n->if_stmt.cond = parse_expr(); skip_nl(); n->if_stmt.then_body = parse_block(); if (current_token.type == TOK_ELSE) { lexer_next(); skip_nl(); n->if_stmt.else_body = parse_block(); } expect(TOK_END); expect(TOK_IF); return n;
        case TOK_FOR: { lexer_next(); n = calloc(1, sizeof(AstNode)); n->type = AST_FOR; n->for_stmt.var = strdup(current_token.lexeme); expect(TOK_IDENT); expect(TOK_IN); n->for_stmt.start = parse_expr(); if (current_token.type == TOK_DOT_DOT) { lexer_next(); n->for_stmt.end = parse_expr(); } else if (current_token.type == TOK_DOT) { lexer_next(); expect(TOK_DOT); n->for_stmt.end = parse_expr(); } else { n->for_stmt.end = NULL; } skip_nl(); AstNode* body = calloc(1, sizeof(AstNode)); body->type = AST_BLOCK; body->block.statements = NULL; body->block.count = 0; while (current_token.type != TOK_END) { AstNode* s = parse_stmt(); body->block.count++; body->block.statements = realloc(body->block.statements, sizeof(AstNode*)*body->block.count); body->block.statements[body->block.count-1] = s; skip_nl(); } n->for_stmt.body = body; expect(TOK_END); expect(TOK_FOR); return n; }
        case TOK_DO: { lexer_next(); skip_nl(); AstNode* body = calloc(1, sizeof(AstNode)); body->type = AST_BLOCK; body->block.statements = NULL; body->block.count = 0; while (current_token.type != TOK_WHILE) { AstNode* s = parse_stmt(); body->block.count++; body->block.statements = realloc(body->block.statements, sizeof(AstNode*)*body->block.count); body->block.statements[body->block.count-1] = s; skip_nl(); } lexer_next(); n = calloc(1, sizeof(AstNode)); n->type = AST_WHILE; n->while_stmt.cond = parse_expr(); n->while_stmt.body = body; return n; }
        case TOK_PROFILE: { lexer_next(); skip_nl(); n = calloc(1, sizeof(AstNode)); n->type = AST_PROFILE; n->profile.body = parse_block(); expect(TOK_END); expect(TOK_END); return n; }
        case TOK_WHILE: { lexer_next(); n = calloc(1, sizeof(AstNode)); n->type = AST_WHILE; n->while_stmt.cond = parse_expr(); skip_nl(); AstNode* body = calloc(1, sizeof(AstNode)); body->type = AST_BLOCK; body->block.statements = NULL; body->block.count = 0; while (current_token.type != TOK_END) { AstNode* s = parse_stmt(); body->block.count++; body->block.statements = realloc(body->block.statements, sizeof(AstNode*)*body->block.count); body->block.statements[body->block.count-1] = s; skip_nl(); } n->while_stmt.body = body; expect(TOK_END); expect(TOK_WHILE); return n; }
        case TOK_FUNC: lexer_next(); n = calloc(1, sizeof(AstNode)); n->type = AST_FUNC_DEF; n->func_def.name = strdup(current_token.lexeme); lexer_next(); if (current_token.type == TOK_LPAREN) { lexer_next(); n->func_def.param_count = 0; n->func_def.params = NULL; if (current_token.type == TOK_IDENT) { n->func_def.param_count++; n->func_def.params = malloc(sizeof(char*)); n->func_def.params[0] = strdup(current_token.lexeme); lexer_next(); while (current_token.type == TOK_COMMA) { lexer_next(); n->func_def.param_count++; n->func_def.params = realloc(n->func_def.params, sizeof(char*)*n->func_def.param_count); n->func_def.params[n->func_def.param_count-1] = strdup(current_token.lexeme); lexer_next(); } } expect(TOK_RPAREN); } skip_nl(); n->func_def.body = parse_block(); expect(TOK_END); expect(TOK_FUNC); return n;
        case TOK_STRUCT: lexer_next(); n = calloc(1, sizeof(AstNode)); n->type = AST_STRUCT_DEF; n->struct_def.name = strdup(current_token.lexeme); struct_names[struct_name_count++] = strdup(n->struct_def.name); expect(TOK_IDENT); skip_nl(); n->struct_def.field_count = 0; n->struct_def.field_names = NULL; n->struct_def.field_types = NULL; while (current_token.type != TOK_END) { char* ft = strdup(current_token.lexeme); lexer_next(); char* fn = strdup(current_token.lexeme); expect(TOK_IDENT); skip_nl(); n->struct_def.field_count++; n->struct_def.field_names = realloc(n->struct_def.field_names, sizeof(char*)*n->struct_def.field_count); n->struct_def.field_types = realloc(n->struct_def.field_types, sizeof(char*)*n->struct_def.field_count); n->struct_def.field_names[n->struct_def.field_count-1] = fn; n->struct_def.field_types[n->struct_def.field_count-1] = ft; } expect(TOK_END); expect(TOK_STRUCT); return n;
        case TOK_RETURN: lexer_next(); n = calloc(1, sizeof(AstNode)); n->type = AST_RETURN; if (current_token.type != TOK_NEWLINE && current_token.type != TOK_END) n->ret.value = parse_expr(); return n;
        case TOK_BREAK: lexer_next(); n = calloc(1, sizeof(AstNode)); n->type = AST_BREAK; return n;
        case TOK_CONTINUE: lexer_next(); n = calloc(1, sizeof(AstNode)); n->type = AST_CONTINUE; return n;
        default: return parse_expr();
    }
}
static AstNode* parse_block() { AstNode* n = calloc(1, sizeof(AstNode)); n->type = AST_BLOCK; skip_nl(); while (current_token.type != TOK_END && current_token.type != TOK_ELSE && current_token.type != TOK_EOF) { AstNode* s = parse_stmt(); n->block.count++; n->block.statements = realloc(n->block.statements, sizeof(AstNode*)*n->block.count); n->block.statements[n->block.count-1] = s; skip_nl(); } return n; }
AstNode* parse_program() { AstNode* p = calloc(1, sizeof(AstNode)); p->type = AST_PROGRAM; skip_nl(); while (current_token.type != TOK_EOF) { AstNode* s = parse_stmt(); p->block.count++; p->block.statements = realloc(p->block.statements, sizeof(AstNode*)*p->block.count); p->block.statements[p->block.count-1] = s; skip_nl(); } return p; }
