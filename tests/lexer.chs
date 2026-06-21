struct Token
    num type
    text lexeme
    num line
    num col
end struct

func makeToken(typ, lex, ln, cl)
    Token t = Token(typ, lex, ln, cl)
    return t
end func

func isDigit(c)
    if c < 48
        return 0
    end if
    if c > 57
        return 0
    end if
    return 1
end func

func isAlpha(c)
    if c >= 65
        if c <= 90
            return 1
        end if
    end if
    if c >= 97
        if c <= 122
            return 1
        end if
    end if
    if c == 95
        return 1
    end if
    return 0
end func

func isAlphaNum(c)
    if isAlpha(c)
        return 1
    end if
    if isDigit(c)
        return 1
    end if
    return 0
end func

func isSpace(c)
    if c == 32
        return 1
    end if
    if c == 9
        return 1
    end if
    if c == 13
        return 1
    end if
    if c == 10
        return 1
    end if
    return 0
end func

// Token types
num TOK_EOF
num TOK_NUM
num TOK_IDENT
num TOK_STRING
num TOK_PLUS
num TOK_MINUS
num TOK_STAR
num TOK_SLASH
num TOK_LPAREN
num TOK_RPAREN
num TOK_LBRACKET
num TOK_RBRACKET
num TOK_EQ
num TOK_COMMA
num TOK_DOT

// Keywords
num KW_NUM
num KW_TEXT
num KW_FLAG
num KW_LIST
num KW_IF
num KW_ELSE
num KW_FOR
num KW_IN
num KW_WHILE
num KW_FUNC
num KW_STRUCT
num KW_RETURN
num KW_PRINT
num KW_END
num KW_TRUE
num KW_FALSE
num KW_AND
num KW_OR
num KW_NOT
num KW_IMPORT

main
    TOK_EOF = 0
    TOK_NUM = 1
    TOK_IDENT = 2
    TOK_STRING = 3
    TOK_PLUS = 4
    TOK_MINUS = 5
    TOK_STAR = 6
    TOK_SLASH = 7
    TOK_LPAREN = 8
    TOK_RPAREN = 9
    TOK_LBRACKET = 10
    TOK_RBRACKET = 11
    TOK_EQ = 12
    TOK_COMMA = 13
    TOK_DOT = 14

    KW_NUM = 100
    KW_TEXT = 101
    KW_FLAG = 102
    KW_LIST = 103
    KW_IF = 104
    KW_ELSE = 105
    KW_FOR = 106
    KW_IN = 107
    KW_WHILE = 108
    KW_FUNC = 109
    KW_STRUCT = 110
    KW_RETURN = 111
    KW_PRINT = 112
    KW_END = 113
    KW_TRUE = 114
    KW_FALSE = 115
    KW_AND = 116
    KW_OR = 117
    KW_NOT = 118
    KW_IMPORT = 119

    print(isAlphaNum(65))
    print(isAlphaNum(57))
    print(isAlphaNum(95))
    print(len("ChaosLanguage"))
end main
