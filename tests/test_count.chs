func isSpace(c)
    if c == 32
        return 1
    end if
    return 0
end func

func countTokens(source)
    num count = 1
    num i = 0
    num ln = len(source)
    
    while i < ln
        num c = source[i]
        num sp = isSpace(c)
        count = count + sp
        i = i + 1
    end while
    
    return count
end func

print(isSpace(32))
print(countTokens("x = 42"))
