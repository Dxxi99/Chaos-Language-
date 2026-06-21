import "math"

func fib(n)
    if n <= 1
        return n
    end if
    return fib(n - 1) + fib(n - 2)
end func

func isPrime(n)
    if n <= 1
        return 0
    end if
    if n == 2
        return 1
    end if
    num i = 2
    while i < n
        if n % i == 0
            return 0
        end if
        i = i + 1
    end while
    return 1
end func

func gcd(a, b)
    while b != 0
        num t = b
        b = a % b
        a = t
    end while
    return a
end func

list arr = [1, 2, 3]
push(arr, 4)
push(arr, 5)
num sum = 0
for i in 0..4
    sum = sum + arr[i]
end for

print(fib(10))
print(isPrime(7))
print(isPrime(10))
print(gcd(48, 18))
print(sum)
print(factorial(8))
print(abs(-123))
