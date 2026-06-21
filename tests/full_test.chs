func factorial(n)
    if n <= 1
        return 1
    end if
    return n * factorial(n - 1)
end func

func double(n)
    return n * 2
end func

print("== Full Test ==")
print(42)
print("Hello")
print(true)
print(10 + 5)
print(25 % 7)
print(2 ** 10)

num x = 10
x += 5
print(x)
x++
print(x)

if x > 10
    print(100)
end if

num w = 0
while w < 3
    print(w)
    w = w + 1
end while

list arr = [1, 2, 3]
for i in 0..2
    print(arr[i])
end for

for n in arr
    print(n)
end for

push(arr, 4)
print(arr[3])
print(len(arr))

text s = concat("Hello ", "World")
print(s)

print(double(21))
print(factorial(5))

writeFile("fulltest.txt", "OK")
print(readFile("fulltest.txt"))
