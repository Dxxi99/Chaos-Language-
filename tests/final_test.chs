import "math"

print("== Chaos Test ==")
print(42)
print(true)

num x = 10 + 5
print(x)

if x > 10
    print(100)
else
    print(200)
end if

num count = 3
while count > 0
    print(count)
    count = count - 1
end while

list arr = [10, 20, 30]
for i in 0..2
    print(arr[i])
end for

text s = "Hi"
print(s)
print(len(s))

print(abs(-50))
print(factorial(5))
