Chaos Language
Chaos is a high-performance, statically-typed, compiled programming language built on LLVM. Designed to bridge the gap between C-level performance and Python-like developer productivity, Chaos offers a robust framework for systems programming, data manipulation, and algorithmic tasks.
Key Technical Specifications
Native Execution: Compiles to optimized machine code via LLVM 18, delivering performance parity with C/C++.
Unified num System: A unified numeric type that handles both integers and floating-point logic, with the compiler automatically selecting optimal LLVM IR instructions (ICmp/FCmp).
Stack-Managed Control Flow: Advanced support for nested loops and conditional blocks using a dedicated stack-based management system, ensuring predictable break/continue semantics.
Zero-Overhead Interoperability: A native call_builtin interface enables seamless integration with C standard libraries (File I/O, Networking, Math) without performance penalties.
Memory & Structure: Native support for struct and dynamic list types with efficient layout management using LLVM's GEP (GetElementPtr) operations.
Architecture & Pipeline
Chaos employs a structured, modular compiler pipeline:
Lexical Analysis: Tokenizes source code, handling everything from numeric literals to keyword-based syntax.
Parser: Builds a robust Abstract Syntax Tree (AST). Includes built-in error recovery mechanisms (synchronize) to handle malformed input gracefully.
Code Generation: Translates the AST into LLVM IR, performing symbol table mapping and memory layout calculations for complex types.
Native Compilation: Triggers the LLVM toolchain (llc and clang) to produce optimized, hardware-specific binaries.
Getting Started
Build from Source
Bash
git clone https://github.com/Dxxi99/Chaos-Language-.git
cd Chaos-Language-
make
Basic Syntax Usage
Plaintext
# Example: Nested loop logic
func main()
    var count = 0
    while count < 3
        if count == 1
            count = count + 1
            continue
        end
        print(count)
        count = count + 1
    end
end
Project Philosophy
Chaos is built for those who value clarity in structure and uncompromised speed in execution. By adopting an end-based block structure and a clean type system, it eliminates unnecessary syntax noise while remaining strictly typed to ensure runtime safety and high performance.
