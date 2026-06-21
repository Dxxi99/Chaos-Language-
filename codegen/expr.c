#include "codegen.h"
#include "../symbol_table.h"
#include "../lexer.h"
#include <string.h>

ExprResult expr(CodegenContext* ctx, AstNode* n) {
    ExprResult r = { NULL, TYPE_I64 };
    if (!n) return r;
    
    switch (n->type) {
        case AST_NUMBER:
            if (n->number.is_float) {
                r.val = LLVMConstReal(LLVMDoubleType(), n->number.float_val);
                r.chaos_type = TYPE_F64;
            } else {
                r.val = LLVMConstInt(LLVMInt64Type(), n->number.int_val, 0);
                r.chaos_type = TYPE_I64;
            }
            return r;
            
        case AST_STRING:
            r.val = LLVMBuildGlobalStringPtr(ctx->b, n->string.value, "str");
            r.chaos_type = TYPE_TEXT;
            return r;
            
        case AST_BOOL:
            r.val = LLVMConstInt(LLVMInt1Type(), n->boolean.value, 0);
            r.chaos_type = TYPE_FLAG;
            return r;
            
        case AST_IDENT: {
            extern Var vars[256];
            extern int vc;
            Var* v = NULL;
            for (int i = 0; i < vc; i++) {
                if (strcmp(vars[i].n, n->ident.name) == 0) {
                    v = &vars[i];
                    break;
                }
            }
            if (!v) {
                r.val = LLVMConstInt(LLVMInt64Type(), 0, 0);
                return r;
            }
            if (v->t) {
                r.val = LLVMBuildLoad2(ctx->b, v->t, v->p, "sv");
            } else {
                LLVMTypeRef ty;
                switch (v->ct) {
                    case TYPE_I64:  ty = LLVMInt64Type(); break;
                    case TYPE_F64:  ty = LLVMDoubleType(); break;
                    case TYPE_TEXT: ty = LLVMPointerType(LLVMInt8Type(), 0); break;
                    case TYPE_FLAG: ty = LLVMInt1Type(); break;
                    default: ty = LLVMInt64Type(); break;
                }
                r.val = LLVMBuildLoad2(ctx->b, ty, v->p, "v");
            }
            r.chaos_type = v->ct;
            return r;
        }
            
        case AST_BINARY: {
            ExprResult l = expr(ctx, n->binary.left);
            ExprResult r = expr(ctx, n->binary.right);
            
            // String concat
            if (l.chaos_type == TYPE_TEXT || r.chaos_type == TYPE_TEXT) {
                r.val = l.val;  // Simplified: just return left
                r.chaos_type = TYPE_TEXT;
                return r;
            }
            
            // Float promotion
            if (l.chaos_type == TYPE_F64 || r.chaos_type == TYPE_F64) {
                if (l.chaos_type != TYPE_F64) l.val = LLVMBuildSIToFP(ctx->b, l.val, LLVMDoubleType(), "");
                if (r.chaos_type != TYPE_F64) r.val = LLVMBuildSIToFP(ctx->b, r.val, LLVMDoubleType(), "");
                
                switch (n->binary.op) {
                    case TOK_PLUS:  r.val = LLVMBuildFAdd(ctx->b, l.val, r.val, "fadd"); break;
                    case TOK_MINUS: r.val = LLVMBuildFSub(ctx->b, l.val, r.val, "fsub"); break;
                    case TOK_STAR:  r.val = LLVMBuildFMul(ctx->b, l.val, r.val, "fmul"); break;
                    case TOK_SLASH: r.val = LLVMBuildFDiv(ctx->b, l.val, r.val, "fdiv"); break;
                }
                r.chaos_type = TYPE_F64;
                return r;
            }
            
            // Integer ops
            switch (n->binary.op) {
                case TOK_PLUS:  r.val = LLVMBuildAdd(ctx->b, l.val, r.val, "add"); break;
                case TOK_MINUS: r.val = LLVMBuildSub(ctx->b, l.val, r.val, "sub"); break;
                case TOK_STAR:  r.val = LLVMBuildMul(ctx->b, l.val, r.val, "mul"); break;
                case TOK_SLASH: r.val = LLVMBuildSDiv(ctx->b, l.val, r.val, "div"); break;
                default: r.val = l.val; break;
            }
            r.chaos_type = TYPE_I64;
            return r;
        }
            
        default:
            r.val = LLVMConstInt(LLVMInt64Type(), 0, 0);
            r.chaos_type = TYPE_I64;
            return r;
    }
}
