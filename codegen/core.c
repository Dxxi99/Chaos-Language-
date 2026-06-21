#include "codegen.h"
#include <stdio.h>
#include <string.h>

extern void stmt(CodegenContext* ctx, AstNode* n);

// Global printf type for consistency
LLVMTypeRef printf_type = NULL;

void codegen_init(CodegenContext* ctx, const char* name) {
    ctx->mod = LLVMModuleCreateWithName(name);
    ctx->b = LLVMCreateBuilder();
    ctx->cur_fn = NULL;
    
    // Declare printf ONCE with consistent type
    LLVMTypeRef printf_args[] = { LLVMPointerType(LLVMInt8Type(), 0) };
    printf_type = LLVMFunctionType(LLVMInt32Type(), printf_args, 1, 1);
    LLVMAddFunction(ctx->mod, "printf", printf_type);
}

void codegen_program(CodegenContext* ctx, AstNode* root) {
    LLVMTypeRef main_type = LLVMFunctionType(LLVMInt32Type(), NULL, 0, 0);
    LLVMValueRef main_fn = LLVMAddFunction(ctx->mod, "main", main_type);
    LLVMBasicBlockRef entry = LLVMAppendBasicBlock(main_fn, "entry");
    LLVMPositionBuilderAtEnd(ctx->b, entry);
    ctx->cur_fn = main_fn;
    
    fprintf(stderr, "DEBUG: before stmt, cur_fn=%p\n", (void*)ctx->cur_fn);
    stmt(ctx, root);
    fprintf(stderr, "DEBUG: after stmt, inserting ret\n");
    LLVMBuildRet(ctx->b, LLVMConstInt(LLVMInt32Type(), 0, 0));
}

void codegen_finish(CodegenContext* ctx) {
    // Dump module IR BEFORE printing
    LLVMDumpModule(ctx->mod);
    
    char* ir = LLVMPrintModuleToString(ctx->mod);
    FILE* f = fopen("chaos_output.ll", "w");
    if (f) {
        fprintf(f, "%s", ir);
        fclose(f);
    }
    LLVMDisposeMessage(ir);
}

// Export printf_type for stmt.c
extern LLVMTypeRef printf_type;
