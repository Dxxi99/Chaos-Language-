#include "codegen.h"

// printf_type removed
static LLVMTypeRef puts_type = NULL;
#include <stdio.h>
#include <string.h>

// ===========================
// IF statement
// ===========================
// ===========================
// Safe LLVM function getters
// ===========================
// get_printf_fn removed - using print_i64
static LLVMValueRef get_puts_fn(CodegenContext* ctx) {
    LLVMValueRef fn = LLVMGetNamedFunction(ctx->mod, "puts");
    if (fn) return fn;
    LLVMTypeRef i8ptr = LLVMPointerType(LLVMInt8Type(), 0);
    LLVMTypeRef fn_ty = LLVMFunctionType(LLVMInt32Type(), &i8ptr, 1, 0);
    puts_type = fn_ty;
    return LLVMAddFunction(ctx->mod, "puts", fn_ty);
}

static void stmt_if(CodegenContext* ctx, AstNode* n) {
    ExprResult er = expr(ctx, n->if_stmt.cond);
    LLVMValueRef cond = er.val;
    cond = cb_truth_test(ctx, cond);
    
    LLVMBasicBlockRef then_bb = cb_append_block(ctx, "then");
    LLVMBasicBlockRef else_bb = n->if_stmt.else_body ? 
        cb_append_block(ctx, "else") : NULL;
    LLVMBasicBlockRef merge_bb = cb_append_block(ctx, "merge");
    
    if (else_bb)
        cb_build_cond_br(ctx, cond, then_bb, else_bb);
    else
        cb_build_cond_br(ctx, cond, then_bb, merge_bb);
    
    cb_position_at_end(ctx, then_bb);
    stmt(ctx, n->if_stmt.then_body);
    if (!cb_block_has_terminator(ctx))
        cb_build_br(ctx, merge_bb);
    
    if (else_bb) {
        cb_position_at_end(ctx, else_bb);
        stmt(ctx, n->if_stmt.else_body);
        if (!cb_block_has_terminator(ctx))
            cb_build_br(ctx, merge_bb);
    }
    
    cb_position_at_end(ctx, merge_bb);
}

// ===========================
// WHILE statement
// ===========================
static void stmt_while(CodegenContext* ctx, AstNode* n) {
    LLVMBasicBlockRef cond_bb = cb_append_block(ctx, "while_cond");
    LLVMBasicBlockRef body_bb = cb_append_block(ctx, "while_body");
    LLVMBasicBlockRef end_bb  = cb_append_block(ctx, "while_end");
    
    cb_build_br(ctx, cond_bb);
    
    cb_position_at_end(ctx, cond_bb);
    ExprResult er = expr(ctx, n->while_stmt.cond);
    LLVMValueRef cond = er.val;
    cond = cb_truth_test(ctx, cond);
    cb_build_cond_br(ctx, cond, body_bb, end_bb);
    
    cb_position_at_end(ctx, body_bb);
    stmt(ctx, n->while_stmt.body);
    cb_build_br(ctx, cond_bb);
    
    cb_position_at_end(ctx, end_bb);
}

// ===========================
// FOR statement
// ===========================
static void stmt_for(CodegenContext* ctx, AstNode* n) {
    LLVMBasicBlockRef cond_bb = cb_append_block(ctx, "for_cond");
    LLVMBasicBlockRef body_bb = cb_append_block(ctx, "for_body");
    LLVMBasicBlockRef end_bb  = cb_append_block(ctx, "for_end");
    
    cb_build_br(ctx, cond_bb);
    
    cb_position_at_end(ctx, cond_bb);
    ExprResult er = expr(ctx, n->for_stmt.end);
    LLVMValueRef cond = er.val;
    cond = LLVMBuildICmp(ctx->b, LLVMIntSLE, 
                         expr(ctx, n->for_stmt.start).val, cond, "");
    cb_build_cond_br(ctx, cond, body_bb, end_bb);
    
    cb_position_at_end(ctx, body_bb);
    stmt(ctx, n->for_stmt.body);
    cb_build_br(ctx, cond_bb);
    
    cb_position_at_end(ctx, end_bb);
}

// ===========================
// STMT entry point
// ===========================
void stmt(CodegenContext* ctx, AstNode* n) {
    if (!n) return;
    LLVMBasicBlockRef _bb = LLVMGetInsertBlock(ctx->b);
    if (!_bb || LLVMGetBasicBlockTerminator(_bb)) return;
    
    switch (n->type) {
        case AST_IF:
            stmt_if(ctx, n);
            break;
            
        case AST_WHILE:
            stmt_while(ctx, n);
            break;
            
        case AST_FOR:
            stmt_for(ctx, n);
            break;
            
        case AST_BLOCK:
        case AST_PROGRAM:
            if (n->block.statements) {
                for (int i = 0; i < n->block.count; i++) {
                    LLVMBasicBlockRef _bb2 = LLVMGetInsertBlock(ctx->b);
                    if (!_bb2 || LLVMGetBasicBlockTerminator(_bb2)) break;
                    stmt(ctx, n->block.statements[i]);
                }
            }
            break;
            
        case AST_RETURN: {
            ExprResult er = expr(ctx, n->ret.value);
            cb_build_ret(ctx, er.val);
            break;
        }
            
        case AST_VAR_DECL: {
            LLVMBasicBlockRef _bb = LLVMGetInsertBlock(ctx->b);
            if (!_bb || LLVMGetBasicBlockTerminator(_bb)) break;
            ExprResult er = expr(ctx, n->var_decl.value);
            LLVMValueRef alloca = LLVMBuildAlloca(ctx->b, LLVMInt64Type(), n->var_decl.name);
            LLVMBuildStore(ctx->b, er.val, alloca);
            extern void set_v(const char*, LLVMValueRef, int, int, LLVMTypeRef, int, int, int, ChaosType);
            set_v(n->var_decl.name, alloca, 0, 0, NULL, 0, 0, 1, er.chaos_type);
            break;
        }
            
        case AST_FUNC_DEF: {
            LLVMValueRef fn = LLVMGetNamedFunction(ctx->mod, n->func_def.name);
            if (!fn) break;
            
            LLVMValueRef prev_fn = ctx->cur_fn;
            LLVMBasicBlockRef prev_bb = LLVMGetInsertBlock(ctx->b);
            ctx->cur_fn = fn;
            LLVMBasicBlockRef entry = LLVMAppendBasicBlock(fn, "entry");
            LLVMPositionBuilderAtEnd(ctx->b, entry);
            
            // Allocate parameters
            int pc = n->func_def.param_count;
            for (int i = 0; i < pc; i++) {
                LLVMValueRef param = LLVMGetParam(fn, i);
                LLVMValueRef alloca = LLVMBuildAlloca(ctx->b, LLVMInt64Type(), n->func_def.params[i]);
                LLVMBuildStore(ctx->b, param, alloca);
                extern void set_v(const char*, LLVMValueRef, int, int, LLVMTypeRef, int, int, int, ChaosType);
                set_v(n->func_def.params[i], alloca, 0, 0, NULL, 0, 0, 1, TYPE_I64);
            }
            
            stmt(ctx, n->func_def.body);
            
            LLVMBasicBlockRef bb = LLVMGetInsertBlock(ctx->b);
            if (bb && !LLVMGetBasicBlockTerminator(bb))
                LLVMBuildRet(ctx->b, LLVMConstInt(LLVMInt64Type(), 0, 0));
            
            ctx->cur_fn = prev_fn;
            if (prev_bb) LLVMPositionBuilderAtEnd(ctx->b, prev_bb);
            break;
        }
            
        case AST_PRINT:
            for (int i = 0; i < n->print.arg_count; i++) {
                ExprResult r = expr(ctx, n->print.args[i]);
                LLVMValueRef val = r.val;
                
                if (r.chaos_type == TYPE_TEXT) {
                    LLVMValueRef puts_fn = get_puts_fn(ctx);
                    LLVMValueRef args[] = { val };
                    LLVMBuildCall2(ctx->b, puts_type, puts_fn, args, 1, "");
                } else {
                    LLVMValueRef printf_fn = LLVMGetNamedFunction(ctx->mod, "printf");
                    if (!printf_fn) {
                        LLVMTypeRef i8ptr = LLVMPointerType(LLVMInt8Type(), 0);
                        LLVMTypeRef pt = LLVMFunctionType(LLVMInt32Type(), &i8ptr, 1, 1);
                        printf_fn = LLVMAddFunction(ctx->mod, "printf", pt);
                    }
                    LLVMValueRef val32 = val;
                    if (LLVMTypeOf(val) != LLVMInt32Type())
                        val32 = LLVMBuildIntCast(ctx->b, val, LLVMInt32Type(), "cast");
                    LLVMValueRef fmt = LLVMBuildGlobalStringPtr(ctx->b, "%d\n", "fmt");
                    LLVMValueRef args[] = { fmt, val32 };
                    LLVMTypeRef ft = LLVMTypeOf(printf_fn);
                    LLVMBuildCall2(ctx->b, ft, printf_fn, args, 2, "");
                }
            }
            break;
            
        default:
            // Expression statement
            { ExprResult er = expr(ctx, n); (void)er; }
            break;
    }
}
