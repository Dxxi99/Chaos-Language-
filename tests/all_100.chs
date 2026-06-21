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
print(7.5 % 2.5)
print(2.5 ** 2)

print("=== 4. 비교/논리 ===")
print(a > 40)
print(a == 42)
print(1 and 1)
print(not 0)

print("=== 5. if/else if ===")
num score = 85
if score >= 90
    print(1)
else if score >= 80
    print(2)
else
    print(3)
end if

print("=== 6. while + break ===")
num w = 0
while w < 5
    print(w)
    if w == 2
        break
    end if
    w = w + 1
end while

print("=== 7. do-while + continue ===")
num dw = 0
do
    dw = dw + 1
    if dw == 3
        continue
    end if
    print(dw)
while dw < 5

print("=== 8. for range ===")
for i in 0..2
    print(d[i])
end for

print("=== 9. for in list + break ===")
for n in d
    if n == 2
        break
    end if
    print(n)
end for

print("=== 10. 함수 ===")
print(double(21))

print("=== 11. 재귀 ===")
print(factorial(5))

print("=== 12. 구조체 ===")
Point p = Point(10, 20, "Home")
print(p.x)
print(p.name)

print("=== 13. 리스트 ===")
list arr = [1, 2]
push(arr, 3)
push(arr, 4)
print(arr[0])
print(arr[3])
print(len(arr))

print("=== 14. concat + 문자열+ ===")
text s1 = "Hello "
text s2 = "World"
print(concat(s1, s2))
print(s1 + s2)

print("=== 15. sqrt ===")
print(sqrt(16))

print("=== 16. import ===")
print(abs(-99))
print(factorial(6))

print("=== 17. 파일 I/O ===")
writeFile("all100.txt", "OK!")
print(readFile("all100.txt"))

print("=== 전부 완료! ===")
