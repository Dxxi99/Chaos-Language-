struct Point
    num x
    num y
end struct

func double(n)
    return n * 2
end func

Point p = Point(3, 7)
print(p.x)
print(double(21))
