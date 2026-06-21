#include "codegen.h"
#include "../lexer.h"
#include <string.h>

// ===========================
// build_cmp_num: integer/float comparison
// ===========================
LLVMValueRef build_cmp_num(CodegenContext* ctx, int tok, LLVMValueRef l, LLVMValueRef r) {
    LLVMTypeKind lk = LLVMGetTypeKind(LLVMTypeOf(l));
    LLVMTypeKind rk = LLVMGetTypeKind(LLVMTypeOf(r));
    int is_double = (lk == LLVMDoubleTypeKind || rk == LLVMDoubleTypeKind);
    
    if (is_double) {
        if (lk != LLVMDoubleTypeKind) l = LLVMBuildSIToFP(ctx->b, l, LLVMDoubleType(), "");
        if (rk != LLVMDoubleTypeKind) r = LLVMBuildSIToFP(ctx->b, r, LLVMDoubleType(), "");
        switch (tok) {
            case TOK_EQ_EQ: return LLVMBuildFCmp(ctx->b, LLVMRealOEQ, l, r, "e");
            case TOK_NOT_EQ: return LLVMBuildFCmp(ctx->b, LLVMRealONE, l, r, "n");
            case TOK_LT: return LLVMBuildFCmp(ctx->b, LLVMRealOLT, l, r, "l");
            case TOK_GT: return LLVMBuildFCmp(ctx->b, LLVMRealOGT, l, r, "g");
            case TOK_LT_EQ: return LLVMBuildFCmp(ctx->b, LLVMRealOLE, l, r, "le");
            case TOK_GT_EQ: return LLVMBuildFCmp(ctx->b, LLVMRealOGE, l, r, "ge");
            default: return NULL;
        }
    }
    
    // Integer path
    switch (tok) {
        case TOK_EQ_EQ: return LLVMBuildICmp(ctx->b, LLVMIntEQ, l, r, "e");
        case TOK_NOT_EQ: return LLVMBuildICmp(ctx->b, LLVMIntNE, l, r, "n");
        case TOK_LT: return LLVMBuildICmp(ctx->b, LLVMIntSLT, l, r, "l");
        case TOK_GT: return LLVMBuildICmp(ctx->b, LLVMIntSGT, l, r, "g");
        case TOK_LT_EQ: return LLVMBuildICmp(ctx->b, LLVMIntSLE, l, r, "le");
        case TOK_GT_EQ: return LLVMBuildICmp(ctx->b, LLVMIntSGE, l, r, "ge");
        default: return NULL;
    }
}

// ===========================
// build_cmp_text: string comparison via strcmp
// ===========================
LLVMValueRef build_cmp_text(CodegenContext* ctx, int tok, LLVMValueRef l, LLVMValueRef r) {
    LLVMTypeRef strcmp_args[] = {LLVMPointerType(LLVMInt8Type(), 0), LLVMPointerType(LLVMInt8Type(), 0)};
    LLVMTypeRef strcmp_ty = LLVMFunctionType(LLVMInt32Type(), strcmp_args, 2, 0);
    LLVMValueRef strcmp_fn = LLVMGetNamedFunction(ctx->mod, "strcmp");
    if (!strcmp_fn) strcmp_fn = LLVMAddFunction(ctx->mod, "strcmp", strcmp_ty);
    LLVMValueRef args[] = {l, r};
    LLVMValueRef cmp = LLVMBuildCall2(ctx->b, strcmp_ty, strcmp_fn, args, 2, "");
    
    switch (tok) {
        case TOK_EQ_EQ: return LLVMBuildICmp(ctx->b, LLVMIntEQ, cmp, LLVMConstInt(LLVMInt32Type(), 0, 0), "e");
        case TOK_NOT_EQ: return LLVMBuildICmp(ctx->b, LLVMIntNE, cmp, LLVMConstInt(LLVMInt32Type(), 0, 0), "n");
        case TOK_LT: return LLVMBuildICmp(ctx->b, LLVMIntSLT, cmp, LLVMConstInt(LLVMInt32Type(), 0, 0), "l");
        case TOK_GT: return LLVMBuildICmp(ctx->b, LLVMIntSGT, cmp, LLVMConstInt(LLVMInt32Type(), 0, 0), "g");
        case TOK_LT_EQ: return LLVMBuildICmp(ctx->b, LLVMIntSLE, cmp, LLVMConstInt(LLVMInt32Type(), 0, 0), "le");
        case TOK_GT_EQ: return LLVMBuildICmp(ctx->b, LLVMIntSGE, cmp, LLVMConstInt(LLVMInt32Type(), 0, 0), "ge");
        default: return NULL;
    }
}

// ===========================
// build_cmp_flag: boolean comparison
// ===========================
LLVMValueRef build_cmp_flag(CodegenContext* ctx, int tok, LLVMValueRef l, LLVMValueRef r) {
    if (LLVMGetTypeKind(LLVMTypeOf(l)) == LLVMIntegerTypeKind && LLVMGetIntTypeWidth(LLVMTypeOf(l)) == 1)
        l = LLVMBuildZExt(ctx->b, l, LLVMInt32Type(), "");
    if (LLVMGetTypeKind(LLVMTypeOf(r)) == LLVMIntegerTypeKind && LLVMGetIntTypeWidth(LLVMTypeOf(r)) == 1)
        r = LLVMBuildZExt(ctx->b, r, LLVMInt32Type(), "");
    switch (tok) {
        case TOK_EQ_EQ: return LLVMBuildICmp(ctx->b, LLVMIntEQ, l, r, "e");
        case TOK_NOT_EQ: return LLVMBuildICmp(ctx->b, LLVMIntNE, l, r, "n");
        default: return NULL;
    }
}

// ===========================
// build_cmp_default: integer fallback
// ===========================
LLVMValueRef build_cmp_default(CodegenContext* ctx, int tok, LLVMValueRef l, LLVMValueRef r) {
    switch (tok) {
        case TOK_EQ_EQ: return LLVMBuildICmp(ctx->b, LLVMIntEQ, l, r, "e");
        case TOK_NOT_EQ: return LLVMBuildICmp(ctx->b, LLVMIntNE, l, r, "n");
        case TOK_LT: return LLVMBuildICmp(ctx->b, LLVMIntSLT, l, r, "l");
        case TOK_GT: return LLVMBuildICmp(ctx->b, LLVMIntSGT, l, r, "g");
        case TOK_LT_EQ: return LLVMBuildICmp(ctx->b, LLVMIntSLE, l, r, "le");
        case TOK_GT_EQ: return LLVMBuildICmp(ctx->b, LLVMIntSGE, l, r, "ge");
        default: return NULL;
    }
}

// ===========================
// build_cmp: main dispatch
// ===========================
LLVMValueRef build_cmp(CodegenContext* ctx, int tok, LLVMValueRef l, LLVMValueRef r) {
    LLVMTypeKind lk = LLVMGetTypeKind(LLVMTypeOf(l));
    LLVMTypeKind rk = LLVMGetTypeKind(LLVMTypeOf(r));
    
    if (lk == LLVMDoubleTypeKind || rk == LLVMDoubleTypeKind)
        return build_cmp_num(ctx, tok, l, r);
    if (lk == LLVMIntegerTypeKind && LLVMGetIntTypeWidth(LLVMTypeOf(l)) == 1)
        return build_cmp_flag(ctx, tok, l, r);
    if (rk == LLVMIntegerTypeKind && LLVMGetIntTypeWidth(LLVMTypeOf(r)) == 1)
        return build_cmp_flag(ctx, tok, l, r);
    if (lk == LLVMPointerTypeKind && rk == LLVMPointerTypeKind) {
        LLVMTypeRef el = LLVMGetElementType(LLVMTypeOf(l));
        if (LLVMGetTypeKind(el) == LLVMIntegerTypeKind && LLVMGetIntTypeWidth(el) == 8)
            return build_cmp_text(ctx, tok, l, r);
    }
    return build_cmp_default(ctx, tok, l, r);
}
