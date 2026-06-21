#ifndef CHAOS_LEXER_H
#define CHAOS_LEXER_H

typedef enum {
    TOK_EOF = 0, TOK_NUM_INT, TOK_NUM_FLOAT, TOK_STRING, TOK_IDENT,
    TOK_NUM, TOK_TEXT, TOK_FLAG, TOK_LIST, TOK_VAL, TOK_VAR, TOK_PROFILE,
    TOK_IF, TOK_ELSE, TOK_ELSE_IF, TOK_FOR, TOK_IN, TOK_WHILE,
    TOK_FUNC, TOK_STRUCT, TOK_RETURN, TOK_PRINT, TOK_END,
    TOK_TRUE, TOK_FALSE,
    TOK_PLUS, TOK_MINUS, TOK_STAR, TOK_SLASH, TOK_MOD, TOK_POW, TOK_PLUS_EQ, TOK_MINUS_EQ, TOK_STAR_EQ, TOK_SLASH_EQ, TOK_MOD_EQ, TOK_INC, TOK_DEC, TOK_POW_EQ,
    TOK_EQ, TOK_EQ_EQ, TOK_NOT_EQ, TOK_LT, TOK_GT, TOK_LT_EQ, TOK_GT_EQ,
    TOK_AND, TOK_OR, TOK_NOT, TOK_BREAK, TOK_CONTINUE, TOK_DO,
    TOK_LPAREN, TOK_RPAREN, TOK_LBRACKET, TOK_RBRACKET,
    TOK_DOT, TOK_DOT_DOT, TOK_COMMA, TOK_NEWLINE, TOK_ERROR
} TokenType;

typedef struct {
    TokenType type;
    char* lexeme;
    union { long int_val; double float_val; char* str_val; };
    int line, col;
} Token;

extern Token current_token;
void lexer_init(char* source);
void lexer_next();
const char* token_name(TokenType t);
#endif
