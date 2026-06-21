#include "parser.h"
#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
Token current_token;
char* source;
int pos, line = 1, col = 1;
static struct { char* keyword; TokenType type; } keywords[] = {
    {"num",TOK_NUM},{"text",TOK_TEXT},{"flag",TOK_FLAG},{"list",TOK_LIST},{"val",TOK_VAL},{"var",TOK_VAR},{"profile",TOK_PROFILE},
    {"if",TOK_IF},{"else",TOK_ELSE},{"elif",TOK_ELSE_IF},{"for",TOK_FOR},{"in",TOK_IN},
    {"while",TOK_WHILE},{"func",TOK_FUNC},{"struct",TOK_STRUCT},
    {"return",TOK_RETURN},{"print",TOK_PRINT},{"end",TOK_END},
    {"main",TOK_IDENT},
    {"true",TOK_TRUE},{"false",TOK_FALSE},{"and",TOK_AND},{"or",TOK_OR},{"not",TOK_NOT},{"break",TOK_BREAK},{"continue",TOK_CONTINUE},{"do",TOK_DO},
    {NULL,TOK_EOF}
};
void lexer_init(char* src) { source = src; pos = 0; line = 1; col = 1; lexer_next(); }
static char peek() { return source[pos]; }
static char peek2() { return source[pos+1]; }
static char advance() { col++; return source[pos++]; }
static void skip_whitespace() {
    while (1) {
        char c = peek();
        if (c == ' ' || c == '\t' || c == '\r') advance();
        else if (c == '/' && peek2() == '/') { while (peek() && peek() != '\n') advance(); }
        else break;
    }
}
static Token make_token(TokenType t, char* s, int l) {
    Token tok = {t, strndup(s,l), .line=line, .col=col-l}; return tok;
}
static Token parse_number() {
    char* s = &source[pos]; int flt = 0;
    while (isdigit(peek())) advance();
    if (peek() == '.') { if (peek2() != '.') { flt = 1; advance(); while (isdigit(peek())) advance(); } }
    int len = &source[pos] - s;
    Token tok = {flt ? TOK_NUM_FLOAT : TOK_NUM_INT, strndup(s,len), .line=line, .col=col-len};
    if (flt) tok.float_val = atof(tok.lexeme); else tok.int_val = atol(tok.lexeme);
    return tok;
}
static Token parse_string() {
    advance(); char* s = &source[pos];
    while (peek() && peek() != '"') advance();
    int len = &source[pos] - s;
    if (peek() == '"') advance();
    Token tok = {TOK_STRING, strndup(s,len), .str_val=strndup(s,len), .line=line, .col=col-len-1};
    return tok;
}
static Token parse_ident() {
    char* s = &source[pos];
    while (isalnum(peek()) || peek() == '_') advance();
    int len = &source[pos] - s;
    char* id = strndup(s,len);
    for (int i = 0; keywords[i].keyword; i++)
        if (strcmp(id, keywords[i].keyword) == 0) { free(id); return make_token(keywords[i].type, keywords[i].keyword, strlen(keywords[i].keyword)); }
    Token tok = {TOK_IDENT, id, .line=line, .col=col-len}; return tok;
}
void lexer_next() {
    skip_whitespace();
    char c = peek();
    if (c == '\0') { current_token = make_token(TOK_EOF, "EOF", 3); return; }
    if (c == '\n') { advance(); line++; col = 1; current_token = make_token(TOK_NEWLINE, "\\n", 1); return; }
    if (isdigit(c)) { current_token = parse_number(); return; }
    if (c == '"') { current_token = parse_string(); return; }
    if (isalpha(c) || c == '_') { current_token = parse_ident(); return; }
    switch (c) {
                                                
        case '(': advance(); current_token = make_token(TOK_LPAREN,"(",1); return;
        case ')': advance(); current_token = make_token(TOK_RPAREN,")",1); return;
        case '[': advance(); current_token = make_token(TOK_LBRACKET,"[",1); return;
        case ']': advance(); current_token = make_token(TOK_RBRACKET,"]",1); return;
        case ',': advance(); current_token = make_token(TOK_COMMA,",",1); return;
        case '=': advance(); if (peek()=='=') { advance(); current_token = make_token(TOK_EQ_EQ,"==",2); } else current_token = make_token(TOK_EQ,"=",1); return;
        case '+': advance(); if(peek()=='='){advance(); current_token = make_token(TOK_PLUS_EQ,"+=",2);} else if(peek()=='+'){advance(); current_token = make_token(TOK_INC,"++",2);} else current_token = make_token(TOK_PLUS,"+",1); return;
        case '-': advance(); if(peek()=='='){advance(); current_token = make_token(TOK_MINUS_EQ,"-=",2);} else if(peek()=='-'){advance(); current_token = make_token(TOK_DEC,"--",2);} else current_token = make_token(TOK_MINUS,"-",1); return;
        case '*': advance(); if(peek()=='='){advance(); current_token = make_token(TOK_STAR_EQ,"*=",2);} else if(peek()=='*'){advance(); current_token = make_token(TOK_POW,"**",2);} else current_token = make_token(TOK_STAR,"*",1); return;
        case '/': advance(); if(peek()=='='){advance(); current_token = make_token(TOK_SLASH_EQ,"/=",2);} else current_token = make_token(TOK_SLASH,"/",1); return;
        case '%': advance(); if(peek()=='='){advance(); current_token = make_token(TOK_MOD_EQ,"%=",2);} else current_token = make_token(TOK_MOD,"%",1); return;
        case '!': advance(); if (peek()=='=') { advance(); current_token = make_token(TOK_NOT_EQ,"!=",2); } return;
        case '<': advance(); if (peek()=='=') { advance(); current_token = make_token(TOK_LT_EQ,"<=",2); } else current_token = make_token(TOK_LT,"<",1); return;
        case '>': advance(); if (peek()=='=') { advance(); current_token = make_token(TOK_GT_EQ,">=",2); } else current_token = make_token(TOK_GT,">",1); return;
        case '.': advance(); if (peek()=='.') { advance(); current_token = make_token(TOK_DOT_DOT,"..",2); } else current_token = make_token(TOK_DOT,".",1); return;
    }
    fprintf(stderr,"Lexer error at line %d: Unknown character '%c'\n", line, c); exit(1);
}
const char* token_name(TokenType t) {
    switch(t) {
        case TOK_EOF: return "end of file";
        case TOK_NUM_INT: return "integer";
        case TOK_NUM_FLOAT: return "float";
        case TOK_STRING: return "string";
        case TOK_IDENT: return "identifier";
        case TOK_NUM: return "'num'"; case TOK_TEXT: return "'text'"; case TOK_FLAG: return "'flag'"; case TOK_LIST: return "'list'";
        case TOK_IF: return "'if'"; case TOK_ELSE: return "'else'"; case TOK_FOR: return "'for'"; case TOK_IN: return "'in'"; case TOK_WHILE: return "'while'";
        case TOK_FUNC: return "'func'"; case TOK_STRUCT: return "'struct'"; case TOK_RETURN: return "'return'"; case TOK_PRINT: return "'print'"; case TOK_END: return "'end'";
        case TOK_TRUE: return "'true'"; case TOK_FALSE: return "'false'";
        case TOK_PLUS: return "'+'"; case TOK_MINUS: return "'-'"; case TOK_STAR: return "'*'"; case TOK_SLASH: return "'/'";
        case TOK_EQ: return "'='"; case TOK_EQ_EQ: return "'=='"; case TOK_NOT_EQ: return "'!='";
        case TOK_LT: return "'<'"; case TOK_GT: return "'>'"; case TOK_LT_EQ: return "'<='"; case TOK_GT_EQ: return "'>='";
        case TOK_AND: return "'and'"; case TOK_OR: return "'or'"; case TOK_NOT: return "'not'";
        case TOK_LPAREN: return "'('"; case TOK_RPAREN: return "')'"; case TOK_LBRACKET: return "'['"; case TOK_RBRACKET: return "']'";
        case TOK_DOT: return "'.'"; case TOK_DOT_DOT: return "'..'"; case TOK_COMMA: return "','"; case TOK_NEWLINE: return "newline";
        default: return "unknown";
    }
}
// Import helper: parse external file
AstNode* import_file(const char* path) {
    FILE* f = fopen(path, "r");
    if (!f) { char fn[256]; snprintf(fn, 256, "%s.chs", path); f = fopen(fn, "r"); }
    if (!f) { fprintf(stderr, "Error: cannot import '%s'\n", path); exit(1); }
    fseek(f, 0, SEEK_END); long sz = ftell(f); fseek(f, 0, SEEK_SET);
    char* src = malloc(sz+1); fread(src, 1, sz, f); src[sz] = '\0'; fclose(f);
    
    // Save lexer state
    char* saved_src = source; int saved_pos = pos, saved_line = line, saved_col = col;
    Token saved_tok = current_token;
    
    // Parse imported file
    lexer_init(src);
    AstNode* imported = parse_program();
    
    // Restore lexer state
    source = saved_src; pos = saved_pos; line = saved_line; col = saved_col;
    current_token = saved_tok;
    free(src);
    
    // Skip newlines that might have been added
    while (current_token.type == TOK_NEWLINE) lexer_next();
    
    return imported;
}
