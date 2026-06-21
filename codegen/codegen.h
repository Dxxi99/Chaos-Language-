#ifndef CODEGEN_H
#define CODEGEN_H

#include <llvm-c/Core.h>
#include "../parser.h"
#include "../symbol_table.h"

typedef struct {
    LLVMModuleRef mod;
    LLVMBuilderRef b;
    LLVMValueRef cur_fn;
} CodegenContext;

typedef struct {
    LLVMValueRef val;
    int chaos_type;
} ExprResult;

ExprResult expr(CodegenContext* ctx, AstNode* n);
void stmt(CodegenContext* ctx, AstNode* n);
LLVMValueRef call_builtin(CodegenContext* ctx, AstNode* n);
LLVMValueRef build_cmp(CodegenContext* ctx, int tok, LLVMValueRef l, LLVMValueRef r);
LLVMTypeRef chaos_to_llvm_type(CodegenContext* ctx, int chaos_type);
LLVMValueRef list_create(CodegenContext* ctx, int capacity);
void codegen_init(CodegenContext* ctx, const char* module_name);
void codegen_program(CodegenContext* ctx, AstNode* program);
void codegen_finish(CodegenContext* ctx);

#endif
