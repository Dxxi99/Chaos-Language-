# Chaos Programming Language

**Write like Python, run like C.** A meaning-centered, LLVM-based compiled language.

---

## Features

- Python-like syntax - no semicolons, no curly braces
- C-like speed - compiles to native code via LLVM
- Unified `num` type - integers and floats, automatically
- `end`-based blocks - clear, readable, no indentation wars
- 2-pass compiler - functions can be called before they're defined
- Built-in functions: print, input, len, concat, sqrt, abs, push
- File I/O: readFile, writeFile
- Import system: import "math"

---

## Install (macOS)

    brew install llvm@18
    git clone https://github.com/Dxxi99/Chaos-Language-.git
    cd Chaos-Language-
    make

---

## Quick Start

    print("Hello World")

    num x = 10
    num y = 3.14
    print(x + y)

    text name = "Chaos"
    print("Hello " + name)

    list arr = [1, 2, 3]
    for n in arr
        print(n)
    end for

---

## Syntax

### Variables
    num a = 42
    num b = 3.14
    text s = "hello"
    flag f = true
    list arr = [1, 2, 3]

### Operations
    + - * / % **
    > < >= <= == !=
    and or not
    += -= *= /= %= **=
    ++ --

### Control Flow
    if x > 10
        print("big")
    elif x > 5
        print("mid")
    else
        print("small")
    end if

    while x > 0
        x = x - 1
    end while

    for i in 0..9
        print(i)
    end for

    for n in arr
        print(n)
    end for

    do
        print(x)
        x = x + 1
    while x < 5

### Functions
    func add(a, b)
        return a + b
    end func

    func factorial(n)
        if n <= 1
            return 1
        end if
        return n * factorial(n - 1)
    end func

### Structs
    struct Point
        num x
        num y
        text name
    end struct

    Point p = Point(10, 20, "Home")
    print(p.x)

### Built-in Functions
    print(x, y, z)
    num n = input()
    len(arr)
    concat(a, b)
    sqrt(x)
    abs(x)
    max(a, b)
    min(a, b)
    pow(base, exp)
    factorial(n)
    push(arr, val)
    readFile("file.txt")
    writeFile("file.txt", "data")

---

## Build & Run

    ./chaos run file.chs
    ./chaos build file.chs

---

## License

MIT License

## Author

**Dxxi99** - Created in 2024
