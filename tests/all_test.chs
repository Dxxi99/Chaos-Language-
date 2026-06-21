import "math"

// 함수 정의 먼저
func double(n)
    return n * 2
end func

struct Point
    num x
    num y
end struct

// ==========================================
//  Chaos 언어 - 전기능 최종 테스트
// ==========================================

print("=== 변수 ===")
num a = 42
text b = "Chaos"
flag c = true
list d = [1, 2, 3]
print(a)
print(b)
print(c)
print(len(b))

print("=== 연산 ===")
print(10 + 5)
print(20 - 8)
print(6 * 7)
print(100 / 4)
print(25 % 7)

print("=== 비교 ===")
print(a > 40)
print(a < 50)
print(a == 42)
print(a != 10)

print("=== 논리 ===")
print(1 and 1)
print(1 or 0)
print(not 0)

print("=== if/else ===")
if a > 40
    print(100)
else
    print(200)
end if

print("=== while ===")
num w = 3
while w > 0
    print(w)
    w = w - 1
end while

print("=== for ===")
for i in 0..2
    print(d[i])
end for

print("=== 함수 ===")
print(double(21))

print("=== 재귀 ===")
print(factorial(5))

print("=== 구조체 ===")
Point p = Point(10, 20)
print(p.x)
print(p.y)

print("=== 리스트 push ===")
list arr = [1, 2, 3]
push(arr, 4)
push(arr, 5)
print(arr[0])
print(arr[1])
print(arr[2])
print(arr[3])
print(arr[4])

print("=== concat ===")
text s1 = "Hello "
text s2 = "World"
text s3 = concat(s1, s2)
print(s3)

print("=== import ===")
print(abs(-99))
print(max(10, 30))
print(pow(2, 8))

print("=== 완료 ===")
