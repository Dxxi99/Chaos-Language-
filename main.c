#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "parser.h"
#include "codegen.h"

void print_help() {
    printf("Chaos Programming Language\n\n");
    printf("Usage:\n");
    printf("  chaos run <file.chs>     Compile and run\n");
    printf("  chaos build <file.chs>   Compile to executable\n");
    printf("  chaos install <package>  Install package\n");
    printf("  chaos help               Show this help\n");
}

void run_file(const char* path) {
    FILE* f = fopen(path, "r");
    if (!f) { fprintf(stderr, "Error: cannot open '%s'\n", path); exit(1); }
    fseek(f, 0, SEEK_END); long sz = ftell(f); fseek(f, 0, SEEK_SET);
    char* src = malloc(sz+1); fread(src, 1, sz, f); src[sz] = '\0'; fclose(f);
    
    lexer_init(src);
    AstNode* ast = parse_program();
    codegen_init("chaos_output");
    codegen_program(ast);
    codegen_finish();
    free(src);
    
    // Compile to native
    system("/opt/homebrew/Cellar/llvm@18/18.1.8/bin/llc chaos_output.ll -o chaos_output.s 2>/dev/null");
    system("clang chaos_output.s -o chaos_output 2>/dev/null");
    system("./chaos_output");
}

void build_file(const char* path, const char* output) {
    FILE* f = fopen(path, "r");
    if (!f) { fprintf(stderr, "Error: cannot open '%s'\n", path); exit(1); }
    fseek(f, 0, SEEK_END); long sz = ftell(f); fseek(f, 0, SEEK_SET);
    char* src = malloc(sz+1); fread(src, 1, sz, f); src[sz] = '\0'; fclose(f);
    
    lexer_init(src);
    AstNode* ast = parse_program();
    codegen_init(output);
    codegen_program(ast);
    codegen_finish();
    free(src);
    
    char cmd[512];
    snprintf(cmd, 512, "/opt/homebrew/Cellar/llvm@18/18.1.8/bin/llc %s.ll -o %s.s 2>/dev/null", output, output);
    system(cmd);
    snprintf(cmd, 512, "clang %s.s -o %s 2>/dev/null", output, output);
    system(cmd);
    printf("Built: %s\n", output);
}

void install_package(const char* name) {
    printf("Installing package: %s\n", name);
    printf("(Package manager coming soon)\n");
}

int main(int argc, char** argv) {
    if (argc < 2) {
        print_help();
        return 1;
    }
    
    if (strcmp(argv[1], "help") == 0) {
        print_help();
    } else if (strcmp(argv[1], "run") == 0 && argc >= 3) {
        run_file(argv[2]);
    } else if (strcmp(argv[1], "build") == 0 && argc >= 3) {
        char output[256];
        snprintf(output, 256, "%s", argv[2]);
        char* dot = strrchr(output, '.');
        if (dot) *dot = '\0';
        build_file(argv[2], output);
    } else if (strcmp(argv[1], "install") == 0 && argc >= 3) {
        install_package(argv[2]);
    } else {
        // Default: compile given file
        run_file(argv[1]);
    }
    
    return 0;
}
