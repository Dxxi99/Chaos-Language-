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

main
    Token t = makeToken(1, "hello", 2, 3)
    print(t.type)
    print(t.line)
    print(t.col)
end main
