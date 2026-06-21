import "math"

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

print("=== 4. 구조체 ===")
Point p = Point(10, 20, "Home")
print(p.x)
print(p.name)

print("=== 5. concat ===")
text s1 = "Hello "
text s2 = "World"
print(concat(s1, s2))
print(s1 + s2)

print("=== 6. sqrt ===")
print(sqrt(16))

print("=== 7. abs ===")
print(abs(-99))

print("=== 8. factorial ===")
print(factorial(5))

print("=== 9. 파일 I/O ===")
writeFile("all100.txt", "OK!")
print(readFile("all100.txt"))

print("=== 전부 완료! ===")
