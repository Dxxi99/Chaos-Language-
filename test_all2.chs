func double(n)
    return n * 2
end func

struct Point
    num x
    num y
    text name
end struct

print("=== 1. 변수 ===")
num a = 42
text b = "Chaos"
flag c = true
list d = [1, 2, 3]
print(a)
print(b)
print(c)
print(d[0])

print("=== 2. 연산 ===")
print(10 + 5)
print(20 - 8)
print(6 * 7)
print(100 / 4)
print(25 % 7)
print(2 ** 10)

print("=== 3. 실수 ===")
num x = 3.14
num y = 2.5
num z = x + y
print(x)
print(y)
print(z)

print("=== 완료 ===")
