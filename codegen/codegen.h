#pragma once
#ifndef CODEGEN_H
#define CODEGEN_H

#include <llvm-c/Core.h>
#include <stdlib.h>
#include <stddef.h>
#include "../parser.h"
#include "../symbol_table.h"


// Typed SSA value (NOT a pointer!)
typedef struct {
    LLVMValueRef val;
    LLVMTypeRef type;
    int is_ptr;  // 0=SSA value, 1=alloca pointer
} SSAValue;

typedef struct {
    LLVMModuleRef mod;
    LLVMBuilderRef b;
    LLVMValueRef cur_fn;
} CodegenContext;


// Typed SSA value (NOT a pointer!)


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

// Builder wrappers (LLVM encapsulation)
LLVMValueRef cb_add(CodegenContext* ctx, LLVMValueRef a, LLVMValueRef b);
LLVMValueRef cb_sub(CodegenContext* ctx, LLVMValueRef a, LLVMValueRef b);
LLVMValueRef cb_mul(CodegenContext* ctx, LLVMValueRef a, LLVMValueRef b);
LLVMValueRef cb_div(CodegenContext* ctx, LLVMValueRef a, LLVMValueRef b);
LLVMValueRef cb_fadd(CodegenContext* ctx, LLVMValueRef a, LLVMValueRef b);
LLVMValueRef cb_fsub(CodegenContext* ctx, LLVMValueRef a, LLVMValueRef b);
LLVMValueRef cb_fmul(CodegenContext* ctx, LLVMValueRef a, LLVMValueRef b);
LLVMValueRef cb_fdiv(CodegenContext* ctx, LLVMValueRef a, LLVMValueRef b);
LLVMValueRef cb_int_to_float(CodegenContext* ctx, LLVMValueRef v);
LLVMValueRef cb_global_string(CodegenContext* ctx, const char* str, const char* name);
LLVMValueRef cb_call_puts(CodegenContext* ctx, LLVMValueRef str);
LLVMValueRef cb_call_printf_int(CodegenContext* ctx, LLVMValueRef val);
LLVMValueRef cb_truth_test(CodegenContext* ctx, LLVMValueRef cond);
LLVMBasicBlockRef cb_append_block(CodegenContext* ctx, const char* name);
void cb_position_at_end(CodegenContext* ctx, LLVMBasicBlockRef bb);
void cb_build_br(CodegenContext* ctx, LLVMBasicBlockRef dest);
void cb_build_cond_br(CodegenContext* ctx, LLVMValueRef cond, LLVMBasicBlockRef then_bb, LLVMBasicBlockRef else_bb);
void cb_build_ret(CodegenContext* ctx, LLVMValueRef val);
int cb_block_has_terminator(CodegenContext* ctx);

LLVMValueRef cb_load(CodegenContext* ctx, LLVMTypeRef ty, LLVMValueRef ptr);
LLVMValueRef cb_store(CodegenContext* ctx, LLVMValueRef val, LLVMValueRef ptr);
LLVMValueRef cb_alloca(CodegenContext* ctx, LLVMTypeRef ty, const char* name);

LLVMValueRef cb_const_int(int64_t val);
LLVMValueRef cb_const_float(double val);
LLVMValueRef cb_const_bool(int val);
LLVMValueRef cb_const_zero(void);
LLVMTypeRef cb_type_i64(void);
LLVMTypeRef cb_type_f64(void);
LLVMTypeRef cb_type_bool(void);
LLVMTypeRef cb_type_text(void);
LLVMTypeRef cb_chaos_to_llvm_type(int ct);
