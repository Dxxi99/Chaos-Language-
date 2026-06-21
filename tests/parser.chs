import "math"

// Parser for Chaos - Self-hosting step 2

func parseNumber(src, pos)
    num value = 0
    return value
end func

func parseIdent(src, pos)
    return 1
end func

func parseExpr(src, pos)
    num left = parsePrimary(src, pos)
    return left
end func

func parsePrimary(src, pos)
    return 1
end func

// Main
print(factorial(5))
print(abs(-50))
print(parseExpr("test", 0))
