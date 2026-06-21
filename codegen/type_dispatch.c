#include "codegen.h"
#include <string.h>

// ===========================
// ChaosType → LLVM Type Mapping
// ===========================
LLVMTypeRef chaos_to_llvm_type(CodegenContext* ctx, int chaos_type) {
    switch (chaos_type) {
        case TYPE_I64:  return LLVMInt64Type();
        case TYPE_F64:  return LLVMDoubleType();
        case TYPE_FLAG: return LLVMInt1Type();
        case TYPE_TEXT: return LLVMPointerType(LLVMInt8Type(), 0);
        case TYPE_VOID: return LLVMVoidType();
        default:        return LLVMInt64Type();
    }
}

// ===========================
// Type Inference from AST
// ===========================
int infer_chaos_type(CodegenContext* ctx, AstNode* n) {
    if (!n) return TYPE_VOID;
    
    switch (n->type) {
        case AST_NUMBER:
            return n->chaos_type;  // TYPE_I64 or TYPE_F64
            
        case AST_STRING:
            return TYPE_TEXT;
            
        case AST_BOOL:
            return TYPE_FLAG;
            
        case AST_IDENT: {
            extern Var vars[256];
            extern int vc;
            for (int i = 0; i < vc; i++) {
                if (strcmp(vars[i].n, n->ident.name) == 0)
                    return vars[i].ct;
            }
            return TYPE_I64;
        }
            
        case AST_BINARY: {
            int l = infer_chaos_type(ctx, n->binary.left);
            int r = infer_chaos_type(ctx, n->binary.right);
            // Numeric promotion: I64 + F64 → F64
            if (l == TYPE_F64 || r == TYPE_F64) return TYPE_F64;
            if (l == TYPE_TEXT && r == TYPE_TEXT) return TYPE_TEXT;
            if (l == TYPE_FLAG && r == TYPE_FLAG) return TYPE_FLAG;
            return TYPE_I64;
        }
            
        default:
            return TYPE_I64;
    }
}

// ===========================
// Coercion: cast value to target type
// ===========================
LLVMValueRef coerce_to(CodegenContext* ctx, LLVMValueRef val, int from_type, int to_type) {
    if (from_type == to_type) return val;
    
    // I64 → F64
    if (from_type == TYPE_I64 && to_type == TYPE_F64)
        return LLVMBuildSIToFP(ctx->b, val, LLVMDoubleType(), "promote");
    
    // F64 → I64 (truncate)
    if (from_type == TYPE_F64 && to_type == TYPE_I64)
        return LLVMBuildFPToSI(ctx->b, val, LLVMInt64Type(), "trunc");
    
    // FLAG → I64
    if (from_type == TYPE_FLAG && to_type == TYPE_I64)
        return LLVMBuildZExt(ctx->b, val, LLVMInt64Type(), "zext");
    
    return val;
}
