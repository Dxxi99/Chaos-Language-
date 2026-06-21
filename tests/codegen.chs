import "math"

// Codegen for Chaos - Self-hosting step 3

func emitAdd(a, b)
    return a + b
end func

func emitSub(a, b)
    return a - b
end func

func emitMul(a, b)
    return a * b
end func

func emitDiv(a, b)
    return a / b
end func

func codegen(node)
    return 0
end func

// Main
print(emitAdd(10, 20))
print(emitSub(50, 30))
print(emitMul(6, 7))
print(emitDiv(100, 4))
print(factorial(6))
