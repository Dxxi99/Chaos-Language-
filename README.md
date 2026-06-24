# Chaos Programming Language

**Write like Python, run like C.**  
A meaning-centered, LLVM-based compiled language designed for maximum performance with clean, readable syntax.

---

## 🚀 Features

| Feature | Description |
|:--------|:------------|
| 🐍 **Python-like Syntax** | No semicolons, no curly braces — just clean code |
| ⚡ **C-like Speed** | Compiles directly to native code via LLVM 18 |
| 🔢 **Unified `num` Type** | Integers and floats handled automatically |
| 📐 **`end`-based Blocks** | Clear control flow without indentation conflicts |
| 🔄 **2-Pass Compiler** | Forward function references supported |
| 🧰 **Batteries Included** | File I/O, math, string, and list built-ins |

---

## 🛠 Quick Start (macOS)

```bash
# Install LLVM
brew install llvm@18

# Clone and build
git clone https://github.com/Dxxi99/Chaos-Language-.git
cd Chaos-Language-
make

# Run your first Chaos program
./chaos run examples/hello.chs
📝 Syntax Overview

## Variables

text
num a = 42          # Integer
num b = 3.14        # Float
text s = "hello"    # String
flag f = true       # Boolean
list arr = [1, 2, 3]  # List

## Operators

text
Arithmetic:  +  -  *  /  %  **
Comparison:  >  <  >=  <=  ==  !=
Logical:     and  or  not
Compound:    +=  -=  *=  /=  %=  **=
Increment:   ++  --

## Control Flow

text
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

## Functions & Structs

text
func add(a, b)
    return a + b
end

## struct Point
    num x
    num y
end

## 🏗 Architecture

text
chaos.chs → [Lexer] → [Parser] → [Codegen] → LLVM IR → Native Binary
                ↓           ↓           ↓
           lexer.c     parser.c    codegen.c
                           ↓
                    symbol_table.c

## Component	Description
Lexer	Multi-file import support, tokenization
Parser	AST generation with synchronize() error recovery
Codegen	LLVM IR generation via recursive AST traversal
Symbol Table	Scope-aware variable, function, and struct management

## 📂 Project Structure

text

## Chaos-Language-/
├── main.c              # Entry point, compile pipeline
├── lexer.c/h           # Lexical analysis
├── parser.c/h          # Syntax analysis, AST nodes
├── codegen.c/h         # LLVM IR code generation
├── symbol_table.c/h    # Symbol management
├── Makefile            # Build configuration
├── examples/           # Example Chaos programs
│   ├── hello.chs
│   └── math.chs
└── README.md

## 🔧 Current Version: v5.3

✅ if / elif / else recursive chains
✅ while loops with break / continue
✅ for loops (range and list iteration)
✅ Nested loop stack management
✅ Type system: num, text, flag, list
✅ Runtime library: math, string, I/O

##📜 License

MIT — feel free to use, modify, and distribute.

text

---

### ✨ 주요 개선 포인트
1. **표로 정리** — Features, Architecture를 표로 만들어 가독성 향상
2. **코드 블록 언어** — ` ``` ` 뒤에 언어 안 쓰고 순수 텍스트로 표시 (Chaos 언어는 아직 문법 하이라이팅이 없으므로)
3. **프로젝트 구조** — 디렉토리 트리와 컴포넌트 설명 추가
4. **현재 버전 정보** — v5.3까지 구현된 기능 체크리스트
5. **아키텍처 다이어그램** — ASCII 아트로 파이프라인 시각화

GitHub에서 `README.md` 파일 편집 모드로 들어가서 위 내용 전체를 붙여넣으면 됩니다. 커밋 메시지는 `"docs: polished README with architecture and v5.3 status"` 정도로 하면 좋겠네요
