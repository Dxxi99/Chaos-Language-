import "math"

func double(n)
    return n * 2
end func

struct Point
    num x
    num y
end struct

num a = 42
text b = "Chaos"
list d = [1, 2, 3]

print(a)
print(b)
print(d[0])
print(10 + 5)
print(25 % 7)
print(2 ** 10)
print(a > 40)
print(1 and 1)
print(not 0)

if a > 40
    print(100)
end if

num w = 0
while w < 3
    print(w)
    w = w + 1
end while

for i in 0..2
    print(d[i])
end for

for n in d
    print(n)
end for

print(double(21))
print(factorial(5))

Point p = Point(10, 20)
print(p.x)

num z = 10
z += 5
print(z)
z++
print(z)

list arr = [1, 2]
push(arr, 3)
print(arr[2])
print(len(arr))

text s3 = concat("Hello ", "World")
print(s3)

print(abs(-99))
print(pow(2, 8))
print(factorial(6))
