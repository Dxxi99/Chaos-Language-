Chaos Programming Language
Chaos is a high-performance, statically-typed, compiled programming language built on LLVM. Designed for developers who require the raw speed of C with the clean, structured ergonomics of a modern language, Chaos offers a seamless bridge between low-level system control and high-level productivity.
Key Technical Features
LLVM-Powered Native Code Generation: Compiles directly to machine code via LLVM 18, ensuring execution performance comparable to C.
Unified num Type System: Simplifies numeric operations by integrating integer and floating-point logic, with the compiler handling type-specific LLVM instructions (ICmp/FCmp) automatically.
Robust CFG-Based Control Flow: Features stack-managed nested loops (break/continue) and blocks, ensuring stable and predictable execution paths in complex logic.
Extensible Interoperability: A built-in call_builtin system allows for native-speed access to C standard libraries (File I/O, Networking, etc.) without overhead.
Advanced Data Structure Support: Native support for struct and dynamic list types with efficient manual memory layout management.
Architecture Overview
The Chaos compiler is built with a clean, modular design:
Lexer: Tokenizes source code into a stream of meaningful symbols.
Parser: Constructs a robust Abstract Syntax Tree (AST) with error recovery capabilities (synchronize).
Codegen: Translates the AST into LLVM IR, handling symbol mapping and memory layout calculations.
Symbol Table: Manages variable scopes, function definitions, and type tracking for the entire lifecycle.
Getting Started
Prerequisites
LLVM 18
GCC or Clang (for final linking)
Build & Run
Bash
git clone https://github.com/Dxxi99/Chaos-Language-.git
cd Chaos-Language-
make
./chaos run examples/hello.chs
Language Philosophy
Chaos is built on the philosophy of "Write like Python, run like C." It avoids unnecessary verbosity (no curly braces, no semicolons) while maintaining strict static typing to ensure safety and performance.
