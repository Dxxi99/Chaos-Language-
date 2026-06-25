#include <stdio.h>
#include "codegen.h"
#include <string.h>

LLVMValueRef cb_add(CodegenContext* ctx, LLVMValueRef a, LLVMValueRef b) {
    if (!a || !b) return NULL;
    return LLVMBuildAdd(ctx->b, a, b, "add");
}
LLVMValueRef cb_sub(CodegenContext* ctx, LLVMValueRef a, LLVMValueRef b) { if (!a || !b) return NULL; return LLVMBuildSub(ctx->b, a, b, "sub"); }
LLVMValueRef cb_mul(CodegenContext* ctx, LLVMValueRef a, LLVMValueRef b) { if (!a || !b) return NULL; return LLVMBuildMul(ctx->b, a, b, "mul"); }
LLVMValueRef cb_div(CodegenContext* ctx, LLVMValueRef a, LLVMValueRef b) { if (!a || !b) return NULL; return LLVMBuildSDiv(ctx->b, a, b, "div"); }
LLVMValueRef cb_fadd(CodegenContext* ctx, LLVMValueRef a, LLVMValueRef b) { if (!a || !b) return NULL; return LLVMBuildFAdd(ctx->b, a, b, "fadd"); }
LLVMValueRef cb_fsub(CodegenContext* ctx, LLVMValueRef a, LLVMValueRef b) { if (!a || !b) return NULL; return LLVMBuildFSub(ctx->b, a, b, "fsub"); }
LLVMValueRef cb_fmul(CodegenContext* ctx, LLVMValueRef a, LLVMValueRef b) { if (!a || !b) return NULL; return LLVMBuildFMul(ctx->b, a, b, "fmul"); }
LLVMValueRef cb_fdiv(CodegenContext* ctx, LLVMValueRef a, LLVMValueRef b) { if (!a || !b) return NULL; return LLVMBuildFDiv(ctx->b, a, b, "fdiv"); }
LLVMValueRef cb_int_to_float(CodegenContext* ctx, LLVMValueRef v) { if (!v) return NULL; return LLVMBuildSIToFP(ctx->b, v, LLVMDoubleType(), "i2f"); }
LLVMValueRef cb_float_to_int(CodegenContext* ctx, LLVMValueRef v) { if (!v) return NULL; return LLVMBuildFPToSI(ctx->b, v, LLVMInt64Type(), "f2i"); }
LLVMValueRef cb_const_int(int64_t val) { return LLVMConstInt(LLVMInt64Type(), val, 0); }
LLVMValueRef cb_const_float(double val) { return LLVMConstReal(LLVMDoubleType(), val); }
LLVMValueRef cb_const_bool(int val) { return LLVMConstInt(LLVMInt1Type(), val, 0); }
LLVMValueRef cb_const_zero(void) { return LLVMConstInt(LLVMInt64Type(), 0, 0); }
LLVMTypeRef cb_type_i64(void) { return LLVMInt64Type(); }
LLVMTypeRef cb_type_f64(void) { return LLVMDoubleType(); }
LLVMTypeRef cb_type_bool(void) { return LLVMInt1Type(); }
LLVMTypeRef cb_type_text(void) { return LLVMPointerType(LLVMInt8Type(), 0); }
LLVMValueRef cb_alloca(CodegenContext* ctx, LLVMTypeRef ty, const char* name) { return LLVMBuildAlloca(ctx->b, ty, name); }
LLVMValueRef cb_store(CodegenContext* ctx, LLVMValueRef val, LLVMValueRef ptr) { if (!val || !ptr) return NULL; return LLVMBuildStore(ctx->b, val, ptr); }
LLVMValueRef cb_load(CodegenContext* ctx, LLVMTypeRef ty, LLVMValueRef ptr) { if (!ptr) return NULL; return LLVMBuildLoad2(ctx->b, ty, ptr, "load"); }
LLVMValueRef cb_global_string(CodegenContext* ctx, const char* str, const char* name) { return LLVMBuildGlobalStringPtr(ctx->b, str, name); }
int cb_block_has_terminator(CodegenContext* ctx) { LLVMBasicBlockRef bb = LLVMGetInsertBlock(ctx->b); return bb && LLVMGetBasicBlockTerminator(bb) != NULL; }
LLVMBasicBlockRef cb_append_block(CodegenContext* ctx, const char* name) { return LLVMAppendBasicBlock(ctx->cur_fn, name); }
void cb_position_at_end(CodegenContext* ctx, LLVMBasicBlockRef bb) { LLVMPositionBuilderAtEnd(ctx->b, bb); }
void cb_build_br(CodegenContext* ctx, LLVMBasicBlockRef dest) { LLVMBuildBr(ctx->b, dest); }
void cb_build_cond_br(CodegenContext* ctx, LLVMValueRef cond, LLVMBasicBlockRef then_bb, LLVMBasicBlockRef else_bb) { LLVMBuildCondBr(ctx->b, cond, then_bb, else_bb); }
void cb_build_ret(CodegenContext* ctx, LLVMValueRef val) { LLVMBuildRet(ctx->b, val); }
LLVMValueRef cb_truth_test(CodegenContext* ctx, LLVMValueRef cond) { return LLVMBuildICmp(ctx->b, LLVMIntNE, cond, LLVMConstInt(LLVMInt64Type(), 0, 0), "bool"); }
