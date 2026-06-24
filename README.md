Chaos Programming Language
Write like Python, run like C. A meaning-centered, LLVM-based compiled language designed for maximum performance and readability.
Features
Python-like Syntax: Clean, expressive, and readable. No semicolons, no curly braces.
C-like Speed: Compiles directly to optimized native machine code via LLVM 18.
Unified num Type: Seamlessly handles integers and floats; the compiler handles the heavy lifting.
end-based Blocks: Explicit block termination for clear, structured control flow.
Advanced Pipeline: 2-pass compiler allows forward function references and optimized symbol resolution.
Batteries Included: Built-in support for File I/O, math, string manipulation, and dynamic lists.
Quick Start (macOS)
Bash
brew install llvm@18
git clone https://github.com/Dxxi99/Chaos-Language-.git
cd Chaos-Language-
make
./chaos run examples/hello.chs
Syntax Overview
Variables
Plaintext
num a = 42
num b = 3.14
text s = "hello"
flag f = true
list arr = [1, 2, 3]
Control Flow
Plaintext
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
Plaintext
func add(a, b)
    return a + b
end

struct Point
    num x
    num y
end
Architecture
Chaos is built on a modular pipeline designed for extensibility:
Lexer: Tokenization with multi-file import support.
Parser: AST generation with robust synchronize() error recovery.
Codegen: LLVM IR generation via codegen.c, utilizing GEP for complex structures.
Symbol Table: Scope-aware management for variables, functions, and structs.
Developed as a high-performance system programming tool.
