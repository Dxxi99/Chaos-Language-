func fib(n)
    if n <= 1
        return n
    end if
    return fib(n-1) + fib(n-2)
end func

for i in 0..10
    print(fib(i))
end for
