func abs(n)
    if n < 0
        return 0 - n
    end if
    return n
end func

func max(a, b)
    if a > b
        return a
    end if
    return b
end func

func min(a, b)
    if a < b
        return a
    end if
    return b
end func

func pow(base, exp)
    num result = 1
    num i = 0
    while i < exp
        result = result * base
        i = i + 1
    end while
    return result
end func

func factorial(n)
    if n <= 1
        return 1
    end if
    return n * factorial(n - 1)
end func
