# Chaos Programming Language

**Write like Python, run like C.** A meaning-centered, LLVM-based compiled language designed for maximum performance with clean, readable syntax.

---

## 🚀 Features

| Feature | Description |
| :--- | :--- |
| 🐍 Python-like Syntax | No semicolons, no curly braces — just clean code |
| ⚡ C-like Speed | Compiles directly to native code via LLVM 18 |
| 🔢 Unified `num` Type | Integers and floats handled automatically |
| 📐 `end`-based Blocks | Clear control flow without indentation conflicts |
| 🔄 2-Pass Compiler | Forward function references supported |
| 🧰 Batteries Included | File I/O, math, string, and list built-ins |

---

## 🛠 Quick Start (macOS)

# Install LLVM
brew install llvm@18

# Clone and build
git clone https://github.com/Dxxi99/Chaos-Language-.git
cd Chaos-Language-
make

# Run your first Chaos program
./chaos run examples/hello.chs

---

## 📝 Syntax Overview

### Variables

num a = 42          # Integer
num b = 3.14        # Float
text s = "hello"    # String
flag f = true       # Boolean
list arr = [1, 2, 3]  # List

### Operations

Arithmetic:  +  -  * /  %  **
Comparison:  >  <  >=  <=  ==  !=
Logical:     and  or  not
Compound:    +=  -=  *=  /=  %=  **=
Increment:   ++  --

### Control Flow

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

for i = 0 to 10
    print(i)
end

for item in arr
    print(item)
end

### Functions & Structs

func add(a, b)
    return a + b
end

struct Point
    num x
    num y
end

---

## 🏗 Architecture



| Component | Description |
| :--- | :--- |
| Lexer | Multi-file import support, tokenization |
| Parser | AST generation with synchronize() error recovery |
| Codegen | LLVM IR generation via recursive AST traversal |
| Symbol Table | Scope-aware variable, function, and struct management |

---

## 📂 Project Structure

Chaos-Language-/
├── main.c              # Entry point, compile pipeline
├── lexer.c/h           # Lexical analysis
├── parser.c/h          # Syntax analysis, AST nodes
├── codegen.c/h         # LLVM IR code generation
├── symbol_table.c/h    # Symbol management
├── Makefile            # Build configuration
└── examples/           # Example Chaos programs
    ├── hello.chs
    └── math.chs

---

## 🔧 Current Version: v5.3

- [x] if / elif / else recursive chains
- [x] while loops with break / continue
- [x] for loops (range and list iteration)
- [x] Nested loop stack management
- [x] Type system: num, text, flag, list
- [x] Runtime library: math, string, I/O

---

## 📜 License

MIT — feel free to use, modify, and distribute.
