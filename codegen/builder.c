#include "codegen.h"
#include <stdlib.h>

// ===========================
// Internal helper
// ===========================
static LLVMBuilderRef builder(CodegenContext* ctx) {
    return ctx->b;
}

// ===========================
// Type-safe wrappers (핵심)
// ===========================
LLVMValueRef cb_add(CodegenContext* ctx, LLVMValueRef a, LLVMValueRef b) {
    return LLVMBuildAdd(builder(ctx), a, b, "addtmp");
}
LLVMValueRef cb_sub(CodegenContext* ctx, LLVMValueRef a, LLVMValueRef b) {
    return LLVMBuildSub(builder(ctx), a, b, "subtmp");
}
LLVMValueRef cb_mul(CodegenContext* ctx, LLVMValueRef a, LLVMValueRef b) {
    return LLVMBuildMul(builder(ctx), a, b, "multmp");
}
LLVMValueRef cb_div(CodegenContext* ctx, LLVMValueRef a, LLVMValueRef b) {
    return LLVMBuildSDiv(builder(ctx), a, b, "divtmp");
}

// Float versions
LLVMValueRef cb_fadd(CodegenContext* ctx, LLVMValueRef a, LLVMValueRef b) {
    return LLVMBuildFAdd(builder(ctx), a, b, "faddtmp");
}
LLVMValueRef cb_fsub(CodegenContext* ctx, LLVMValueRef a, LLVMValueRef b) {
    return LLVMBuildFSub(builder(ctx), a, b, "fsubtmp");
}
LLVMValueRef cb_fmul(CodegenContext* ctx, LLVMValueRef a, LLVMValueRef b) {
    return LLVMBuildFMul(builder(ctx), a, b, "fmultmp");
}
LLVMValueRef cb_fdiv(CodegenContext* ctx, LLVMValueRef a, LLVMValueRef b) {
    return LLVMBuildFDiv(builder(ctx), a, b, "fdivtmp");
}

// ===========================
// Memory helpers
// ===========================
LLVMValueRef cb_alloca(CodegenContext* ctx, LLVMTypeRef ty, const char* name) {
    return LLVMBuildAlloca(builder(ctx), ty, name);
}
LLVMValueRef cb_store(CodegenContext* ctx, LLVMValueRef val, LLVMValueRef ptr) {
    return LLVMBuildStore(builder(ctx), val, ptr);
}
LLVMValueRef cb_load(CodegenContext* ctx, LLVMTypeRef ty, LLVMValueRef ptr) {
    return LLVMBuildLoad2(builder(ctx), ty, ptr, "loadtmp");
}
