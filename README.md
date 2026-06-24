# Chaos Programming Language

**Write like Python, run like C.** A meaning-centered, LLVM-based compiled language designed for maximum performance.

---

## Features

- **Python-like syntax:** No semicolons, no curly braces.
- **C-like speed:** Compiles directly to native code via LLVM.
- **Unified `num` type:** Integers and floats handled automatically.
- **`end`-based blocks:** Clear, readable control flow without indentation wars.
- **2-pass compiler:** Allows forward function references.
- **Batteries included:** Built-in support for File I/O, math, string, and lists.

---

## Quick Start (macOS)

```bash
brew install llvm@18
git clone [https://github.com/Dxxi99/Chaos-Language-.git](https://github.com/Dxxi99/Chaos-Language-.git)
cd Chaos-Language-
make
./chaos run examples/hello.chs

Syntax Overview
Variables
num a = 42
num b = 3.14
text s = "hello"
flag f = true
list arr = [1, 2, 3]

Operations
+ - * / % **
> < >= <= == !=
and or not
+= -= *= /= %= **=
++ --

Control Flow
if x > 10
    print("big")
elif x > 5
    print("mid")
else
    print("small")
end

while x > 0
    x = x - 1
end

for n in arr
    print(n)
end

Functions & Structs
func add(a, b)
    return a + b
end

struct Point
    num x
    num y
end

Architecture
Lexer: Multi-file import support.
Parser: AST generation with synchronize() error recovery.
Codegen: LLVM IR generation via codegen.c.
Symbol Table: Scope-aware variable and function management.
