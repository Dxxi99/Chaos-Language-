#include <stdio.h>
#include "codegen.h"
#include "../symbol_table.h"
#include "../lexer.h"
#include <string.h>
#include <stdlib.h>

ExprResult expr(CodegenContext* ctx, AstNode* n) {
    ExprResult r = { NULL, TYPE_I64 };
    if (!n) return r;
    fprintf(stderr, "EXPR type=%d\n", n->type);
    LLVMBasicBlockRef _ebb = LLVMGetInsertBlock(ctx->b);
    if (_ebb && LLVMGetBasicBlockTerminator(_ebb)) return r;
    
    switch (n->type) {
        case AST_NUMBER: {
            SSAValue sv;
            if (n->number.is_float) {
                sv.val = cb_const_float(n->number.float_val);
                sv.type = cb_type_f64();
                sv.is_ptr = 0;
                r.val = sv.val;
                r.chaos_type = TYPE_F64;
            } else {
                sv.val = cb_const_int(n->number.int_val);
                sv.type = cb_type_i64();
                sv.is_ptr = 0;
                r.val = sv.val;
                r.chaos_type = TYPE_I64;
            }
            return r;
        }
            
        case AST_STRING:
            r.val = cb_global_string(ctx, n->string.value, "str");
            r.chaos_type = TYPE_TEXT;
            return r;
            
        case AST_BOOL:
            r.val = cb_const_bool(n->boolean.value);
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
                fprintf(stderr, "FATAL: undefined variable '%s'\n", n->ident.name);
                r.val = cb_const_zero();
                return r;
            }
            fprintf(stderr, "DEBUG IDENT: %s found, ct=%d, n=%p, v=%p\n", n->ident.name, v->ct, (void*)n, (void*)v);
            fprintf(stderr, "DEBUG IDENT load: v->p=%p, v->t=%p\n", (void*)v->p, (void*)v->t);
            if (v->t)
                r.val = cb_load(ctx, v->t, v->p);
            else {
                LLVMTypeRef ty = cb_type_i64();
                switch (v->ct) {
                    case TYPE_F64:  ty = cb_type_f64(); break;
                    case TYPE_TEXT: ty = cb_type_text(); break;
                    case TYPE_FLAG: ty = cb_type_bool(); break;
                    default: break;
                }
                r.val = cb_load(ctx, ty, v->p);
            }
            fprintf(stderr, "DEBUG IDENT after load: val=%p, val_type_kind=%d\n", 
                    (void*)r.val, r.val ? (int)LLVMGetTypeKind(LLVMTypeOf(r.val)) : -1);
            r.chaos_type = v->ct;
            return r;
        }
        break;
            
        case AST_FUNC_CALL: {
            LLVMValueRef fn = LLVMGetNamedFunction(ctx->mod, n->func_call.name);
            if (!fn) {
                r.val = cb_const_zero();
                return r;
            }
            int ac = n->func_call.arg_count;
            LLVMValueRef* args = ac > 0 ? malloc(sizeof(LLVMValueRef) * ac) : NULL;
            for (int i = 0; i < ac; i++) {
                ExprResult arg = expr(ctx, n->func_call.args[i]);
                args[i] = arg.val;
            }
            // Use registered function signature
            LLVMTypeRef fn_ty = lookup_func_sig(n->func_call.name);
            if (!fn_ty) {
                fprintf(stderr, "FATAL: function '%s' not registered\n", n->func_call.name);
                exit(1);
            }
                        
            r.val = LLVMBuildCall2(ctx->b, fn_ty, fn, args, ac, "");
            if (args) free(args);
            LLVMTypeRef ret_ty = LLVMGetReturnType(fn_ty);
            LLVMTypeKind rk = LLVMGetTypeKind(ret_ty);
            if (rk == LLVMIntegerTypeKind) r.chaos_type = TYPE_I64;
            else if (rk == LLVMDoubleTypeKind) r.chaos_type = TYPE_F64;
            else if (rk == LLVMPointerTypeKind) r.chaos_type = TYPE_TEXT;
            else r.chaos_type = TYPE_I64;
            return r;
        }
            
        case AST_BINARY: {
            fprintf(stderr, "BINARY op=%d left=%p right=%p\n",
                    n->binary.op, (void*)n->binary.left, (void*)n->binary.right);
            if (!n->binary.left || !n->binary.right) {
                fprintf(stderr, "FATAL: corrupted binary AST (left=%p, right=%p)\n",
                        (void*)n->binary.left, (void*)n->binary.right);
                r.val = cb_const_zero();
                return r;
            }
            ExprResult l = expr(ctx, n->binary.left);
            ExprResult r = expr(ctx, n->binary.right);
            if (!l.val || !r.val) {
                fprintf(stderr, "FATAL: NULL operand in binary op\n");
                r.val = cb_const_zero();
                return r;
            }
            
            // Float promotion
            if (l.chaos_type == TYPE_F64 || r.chaos_type == TYPE_F64) {
                if (l.chaos_type != TYPE_F64) l.val = cb_int_to_float(ctx, l.val);
                if (r.chaos_type != TYPE_F64) r.val = cb_int_to_float(ctx, r.val);
                
                switch (n->binary.op) {
                    case TOK_PLUS:  r.val = cb_fadd(ctx, l.val, r.val); break;
                    case TOK_MINUS: r.val = cb_fsub(ctx, l.val, r.val); break;
                    case TOK_STAR:  r.val = cb_fmul(ctx, l.val, r.val); break;
                    case TOK_SLASH: r.val = cb_fdiv(ctx, l.val, r.val); break;
                }
                r.chaos_type = TYPE_F64;
                return r;
            }
            
            // Integer ops
            switch (n->binary.op) {
                case TOK_PLUS: {
                
                SSAValue sb = {r.val, cb_type_i64(), 0};
                r.val = cb_add(ctx, l.val, r.val);
                break;
            }
                case TOK_MINUS: r.val = cb_sub(ctx, l.val, r.val); break;
                case TOK_STAR:  r.val = cb_mul(ctx, l.val, r.val); break;
                case TOK_SLASH: r.val = cb_div(ctx, l.val, r.val); break;
                default: r.val = l.val; break;
            }
            r.chaos_type = TYPE_I64;
            return r;
        }
            
        default:
            r.val = cb_const_zero();
            r.chaos_type = TYPE_I64;
            return r;
    }
}
