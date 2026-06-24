#include <stdio.h>
#include "codegen.h"
#include <string.h>

// ===========================
// Arithmetic
// ===========================
LLVMValueRef cb_add(CodegenContext* ctx, LLVMValueRef a, LLVMValueRef b) {
    LLVMBasicBlockRef bb = LLVMGetInsertBlock(ctx->b);
    fprintf(stderr, "DEBUG cb_add: bb=%p, a=%p, b=%p\n", (void*)bb, (void*)a, (void*)b);
    if (!bb) { fprintf(stderr, "FATAL: no block in cb_add\n"); return NULL; }
    if (LLVMGetBasicBlockTerminator(bb)) { fprintf(stderr, "FATAL: dead block in cb_add, bb=%p\n", (void*)bb); return NULL; }
    if (LLVMGetBasicBlockParent(bb) != ctx->cur_fn) { 
        fprintf(stderr, "FATAL: block parent mismatch! bb_parent=%p, cur_fn=%p\n",
                (void*)LLVMGetBasicBlockParent(bb), (void*)ctx->cur_fn);
        return NULL;
    }
    // Manual add instruction for LLVM 18 opaque pointer
    LLVMValueRef args[] = { a, b };
    return LLVMBuildCall2(ctx->b, 
        LLVMFunctionType(LLVMInt64Type(), (LLVMTypeRef[]){LLVMInt64Type(), LLVMInt64Type()}, 2, 0),
        LLVMGetNamedFunction(ctx->mod, "llvm.add.i64") ? LLVMGetNamedFunction(ctx->mod, "llvm.add.i64") : LLVMAddFunction(ctx->mod, "add_tmp", LLVMFunctionType(LLVMInt64Type(), (LLVMTypeRef[]){LLVMInt64Type(), LLVMInt64Type()}, 2, 0)),
        args, 2, "add");
}
LLVMValueRef cb_sub(CodegenContext* ctx, LLVMValueRef a, LLVMValueRef b) {
    return LLVMBuildSub(ctx->b, a, b, "sub");
}
LLVMValueRef cb_mul(CodegenContext* ctx, LLVMValueRef a, LLVMValueRef b) {
    return LLVMBuildMul(ctx->b, a, b, "mul");
}
LLVMValueRef cb_div(CodegenContext* ctx, LLVMValueRef a, LLVMValueRef b) {
    return LLVMBuildSDiv(ctx->b, a, b, "div");
}

LLVMValueRef cb_fadd(CodegenContext* ctx, LLVMValueRef a, LLVMValueRef b) {
    return LLVMBuildFAdd(ctx->b, a, b, "fadd");
}
LLVMValueRef cb_fsub(CodegenContext* ctx, LLVMValueRef a, LLVMValueRef b) {
    return LLVMBuildFSub(ctx->b, a, b, "fsub");
}
LLVMValueRef cb_fmul(CodegenContext* ctx, LLVMValueRef a, LLVMValueRef b) {
    return LLVMBuildFMul(ctx->b, a, b, "fmul");
}
LLVMValueRef cb_fdiv(CodegenContext* ctx, LLVMValueRef a, LLVMValueRef b) {
    return LLVMBuildFDiv(ctx->b, a, b, "fdiv");
}

// ===========================
// Type conversion
// ===========================
LLVMValueRef cb_int_to_float(CodegenContext* ctx, LLVMValueRef v) {
    return LLVMBuildSIToFP(ctx->b, v, LLVMDoubleType(), "i2f");
}
LLVMValueRef cb_float_to_int(CodegenContext* ctx, LLVMValueRef v) {
    return LLVMBuildFPToSI(ctx->b, v, LLVMInt64Type(), "f2i");
}

// ===========================
// Comparison
// ===========================
LLVMValueRef cb_icmp(CodegenContext* ctx, int pred, LLVMValueRef a, LLVMValueRef b) {
    return LLVMBuildICmp(ctx->b, pred, a, b, "cmp");
}
LLVMValueRef cb_fcmp(CodegenContext* ctx, int pred, LLVMValueRef a, LLVMValueRef b) {
    return LLVMBuildFCmp(ctx->b, pred, a, b, "fcmp");
}

// ===========================
// Memory
// ===========================
LLVMValueRef cb_alloca(CodegenContext* ctx, LLVMTypeRef ty, const char* name) {
    return LLVMBuildAlloca(ctx->b, ty, name);
}
LLVMValueRef cb_store(CodegenContext* ctx, LLVMValueRef val, LLVMValueRef ptr) {
    return LLVMBuildStore(ctx->b, val, ptr);
}
LLVMValueRef cb_load(CodegenContext* ctx, LLVMTypeRef ty, LLVMValueRef ptr) {
    LLVMBasicBlockRef bb = LLVMGetInsertBlock(ctx->b);
    fprintf(stderr, "DEBUG cb_load: bb=%p, cur_fn=%p, ptr=%p, ty=%p, ty_kind=%d\n", 
            (void*)bb, (void*)ctx->cur_fn, (void*)ptr, (void*)ty,
            ty ? (int)LLVMGetTypeKind(ty) : -1);
    if (!bb) { fprintf(stderr, "FATAL: no insert block!\n"); return NULL; }
    if (LLVMGetBasicBlockTerminator(bb)) { fprintf(stderr, "FATAL: dead block in cb_load\n"); return NULL; }
    if (!ty) { fprintf(stderr, "FATAL: NULL type!\n"); return NULL; }
    LLVMValueRef result = LLVMBuildLoad2(ctx->b, ty, ptr, "load");
    // LLVM 18 opaque pointer: cast loaded value to the expected type
    if (ty && LLVMGetTypeKind(ty) == LLVMIntegerTypeKind) {
        result = LLVMBuildPtrToInt(ctx->b, result, ty, "load_cast");
    }
    return result;
}

// ===========================
// String
// ===========================
LLVMValueRef cb_global_string(CodegenContext* ctx, const char* str, const char* name) {
    return LLVMBuildGlobalStringPtr(ctx->b, str, name);
}

// ===========================
// Function calls (printf, puts)
// ===========================
LLVMValueRef cb_call_puts(CodegenContext* ctx, LLVMValueRef str) {
    LLVMValueRef fn = LLVMGetNamedFunction(ctx->mod, "puts");
    if (!fn) {
        LLVMTypeRef i8ptr = LLVMPointerType(LLVMInt8Type(), 0);
        LLVMTypeRef fn_ty = LLVMFunctionType(LLVMInt32Type(), &i8ptr, 1, 0);
        fn = LLVMAddFunction(ctx->mod, "puts", fn_ty);
    }
    LLVMValueRef args[] = { str };
    LLVMTypeRef fn_ty = LLVMFunctionType(LLVMInt32Type(), 
        (LLVMTypeRef[]){ LLVMPointerType(LLVMInt8Type(), 0) }, 1, 0);
    return LLVMBuildCall2(ctx->b, fn_ty, fn, args, 1, "");
}

LLVMValueRef cb_call_printf_int(CodegenContext* ctx, LLVMValueRef val) {
    LLVMValueRef fn = LLVMGetNamedFunction(ctx->mod, "printf");
    if (!fn) {
        LLVMTypeRef i8ptr = LLVMPointerType(LLVMInt8Type(), 0);
        LLVMTypeRef fn_ty = LLVMFunctionType(LLVMInt32Type(), &i8ptr, 1, 1);
        fn = LLVMAddFunction(ctx->mod, "printf", fn_ty);
    }
    LLVMValueRef fmt = LLVMBuildGlobalStringPtr(ctx->b, "%d\n", "fmt");
    LLVMValueRef args[] = { fmt, val };
    LLVMTypeRef fn_ty = LLVMFunctionType(LLVMInt32Type(), 
        (LLVMTypeRef[]){ LLVMPointerType(LLVMInt8Type(), 0) }, 1, 1);
    return LLVMBuildCall2(ctx->b, fn_ty, fn, args, 2, "");
}

// ===========================
// Control flow helpers
// ===========================
LLVMValueRef cb_truth_test(CodegenContext* ctx, LLVMValueRef cond) {
    return LLVMBuildICmp(ctx->b, LLVMIntNE, cond,
                         LLVMConstInt(LLVMInt64Type(), 0, 0), "bool");
}

LLVMBasicBlockRef cb_append_block(CodegenContext* ctx, const char* name) {
    return LLVMAppendBasicBlock(ctx->cur_fn, name);
}

void cb_position_at_end(CodegenContext* ctx, LLVMBasicBlockRef bb) {
    LLVMPositionBuilderAtEnd(ctx->b, bb);
}

void cb_build_br(CodegenContext* ctx, LLVMBasicBlockRef dest) {
    LLVMBuildBr(ctx->b, dest);
}

void cb_build_cond_br(CodegenContext* ctx, LLVMValueRef cond,
                       LLVMBasicBlockRef then_bb, LLVMBasicBlockRef else_bb) {
    LLVMBuildCondBr(ctx->b, cond, then_bb, else_bb);
}

void cb_build_ret(CodegenContext* ctx, LLVMValueRef val) {
    LLVMBuildRet(ctx->b, val);
}

int cb_block_has_terminator(CodegenContext* ctx) {
    return LLVMGetBasicBlockTerminator(LLVMGetInsertBlock(ctx->b)) != NULL;
}

// ===========================
// Constants
// ===========================
LLVMValueRef cb_const_int(int64_t val) {
    return LLVMConstInt(LLVMInt64Type(), val, 0);
}
LLVMValueRef cb_const_float(double val) {
    return LLVMConstReal(LLVMDoubleType(), val);
}
LLVMValueRef cb_const_bool(int val) {
    return LLVMConstInt(LLVMInt1Type(), val, 0);
}
LLVMValueRef cb_const_zero(void) {
    return LLVMConstInt(LLVMInt64Type(), 0, 0);
}

// ===========================
// Types
// ===========================
LLVMTypeRef cb_type_i64(void) { return LLVMInt64Type(); }
LLVMTypeRef cb_type_f64(void) { return LLVMDoubleType(); }
LLVMTypeRef cb_type_bool(void) { return LLVMInt1Type(); }
LLVMTypeRef cb_type_text(void) { return LLVMPointerType(LLVMInt8Type(), 0); }

LLVMTypeRef cb_chaos_to_llvm_type(int ct) {
    switch (ct) {
        case TYPE_I64:  return LLVMInt64Type();
        case TYPE_F64:  return LLVMDoubleType();
        case TYPE_FLAG: return LLVMInt1Type();
        case TYPE_TEXT: return LLVMPointerType(LLVMInt8Type(), 0);
        default:        return LLVMInt64Type();
    }
}
