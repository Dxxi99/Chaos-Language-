#include "codegen.h"
#include <stdio.h>
#include <string.h>

// ===========================
// IF statement
// ===========================
// ===========================
// Safe LLVM function getters
// ===========================
static LLVMValueRef get_printf_fn(CodegenContext* ctx) {
    LLVMValueRef fn = LLVMGetNamedFunction(ctx->mod, "printf");
    if (fn) return fn;
    LLVMTypeRef i8ptr = LLVMPointerType(LLVMInt8Type(), 0);
    LLVMTypeRef fn_ty = LLVMFunctionType(LLVMInt32Type(), &i8ptr, 1, 1);
    return LLVMAddFunction(ctx->mod, "printf", fn_ty);
}

static LLVMValueRef get_puts_fn(CodegenContext* ctx) {
    LLVMValueRef fn = LLVMGetNamedFunction(ctx->mod, "puts");
    if (fn) return fn;
    LLVMTypeRef i8ptr = LLVMPointerType(LLVMInt8Type(), 0);
    LLVMTypeRef fn_ty = LLVMFunctionType(LLVMInt32Type(), &i8ptr, 1, 0);
    return LLVMAddFunction(ctx->mod, "puts", fn_ty);
}

static void stmt_if(CodegenContext* ctx, AstNode* n) {
    ExprResult er = expr(ctx, n->if_stmt.cond);
    LLVMValueRef cond = er.val;
    cond = LLVMBuildICmp(ctx->b, LLVMIntNE, cond,
                         LLVMConstInt(LLVMInt64Type(), 0, 0), "");
    
    LLVMBasicBlockRef then_bb = LLVMAppendBasicBlock(ctx->cur_fn, "then");
    LLVMBasicBlockRef else_bb = n->if_stmt.else_body ? 
        LLVMAppendBasicBlock(ctx->cur_fn, "else") : NULL;
    LLVMBasicBlockRef merge_bb = LLVMAppendBasicBlock(ctx->cur_fn, "merge");
    
    if (else_bb)
        LLVMBuildCondBr(ctx->b, cond, then_bb, else_bb);
    else
        LLVMBuildCondBr(ctx->b, cond, then_bb, merge_bb);
    
    LLVMPositionBuilderAtEnd(ctx->b, then_bb);
    stmt(ctx, n->if_stmt.then_body);
    if (!LLVMGetBasicBlockTerminator(LLVMGetInsertBlock(ctx->b)))
        LLVMBuildBr(ctx->b, merge_bb);
    
    if (else_bb) {
        LLVMPositionBuilderAtEnd(ctx->b, else_bb);
        stmt(ctx, n->if_stmt.else_body);
        if (!LLVMGetBasicBlockTerminator(LLVMGetInsertBlock(ctx->b)))
            LLVMBuildBr(ctx->b, merge_bb);
    }
    
    LLVMPositionBuilderAtEnd(ctx->b, merge_bb);
}

// ===========================
// WHILE statement
// ===========================
static void stmt_while(CodegenContext* ctx, AstNode* n) {
    LLVMBasicBlockRef cond_bb = LLVMAppendBasicBlock(ctx->cur_fn, "while_cond");
    LLVMBasicBlockRef body_bb = LLVMAppendBasicBlock(ctx->cur_fn, "while_body");
    LLVMBasicBlockRef end_bb  = LLVMAppendBasicBlock(ctx->cur_fn, "while_end");
    
    LLVMBuildBr(ctx->b, cond_bb);
    
    LLVMPositionBuilderAtEnd(ctx->b, cond_bb);
    ExprResult er = expr(ctx, n->while_stmt.cond);
    LLVMValueRef cond = er.val;
    cond = LLVMBuildICmp(ctx->b, LLVMIntNE, cond,
                         LLVMConstInt(LLVMInt64Type(), 0, 0), "");
    LLVMBuildCondBr(ctx->b, cond, body_bb, end_bb);
    
    LLVMPositionBuilderAtEnd(ctx->b, body_bb);
    stmt(ctx, n->while_stmt.body);
    LLVMBuildBr(ctx->b, cond_bb);
    
    LLVMPositionBuilderAtEnd(ctx->b, end_bb);
}

// ===========================
// FOR statement
// ===========================
static void stmt_for(CodegenContext* ctx, AstNode* n) {
    LLVMBasicBlockRef cond_bb = LLVMAppendBasicBlock(ctx->cur_fn, "for_cond");
    LLVMBasicBlockRef body_bb = LLVMAppendBasicBlock(ctx->cur_fn, "for_body");
    LLVMBasicBlockRef end_bb  = LLVMAppendBasicBlock(ctx->cur_fn, "for_end");
    
    LLVMBuildBr(ctx->b, cond_bb);
    
    LLVMPositionBuilderAtEnd(ctx->b, cond_bb);
    ExprResult er = expr(ctx, n->for_stmt.end);
    LLVMValueRef cond = er.val;
    cond = LLVMBuildICmp(ctx->b, LLVMIntSLE, 
                         expr(ctx, n->for_stmt.start).val, cond, "");
    LLVMBuildCondBr(ctx->b, cond, body_bb, end_bb);
    
    LLVMPositionBuilderAtEnd(ctx->b, body_bb);
    stmt(ctx, n->for_stmt.body);
    LLVMBuildBr(ctx->b, cond_bb);
    
    LLVMPositionBuilderAtEnd(ctx->b, end_bb);
}

// ===========================
// STMT entry point
// ===========================
void stmt(CodegenContext* ctx, AstNode* n) {
    if (!n) return;
    
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
            for (int i = 0; i < n->block.count; i++)
                stmt(ctx, n->block.statements[i]);
            break;
            
        case AST_RETURN: {
            ExprResult er = expr(ctx, n->ret.value);
            LLVMBuildRet(ctx->b, er.val);
            break;
        }
            
        case AST_VAR_DECL: {
            ExprResult er = expr(ctx, n->var_decl.value);
            (void)er;  // value is stored elsewhere
            break;
        }
            
        case AST_PRINT:
            for (int i = 0; i < n->print.arg_count; i++) {
                ExprResult r = expr(ctx, n->print.args[i]); fprintf(stderr, "DEBUG expr: type=%d val=%p\n", r.chaos_type, (void*)r.val);
                LLVMValueRef val = r.val;
                
                if (r.chaos_type == TYPE_TEXT) {
                    LLVMValueRef puts_fn = get_puts_fn(ctx); fprintf(stderr, "DEBUG puts_fn=%p\n", (void*)puts_fn);
                    LLVMValueRef args[] = { val };
                    LLVMTypeRef i8ptr = LLVMPointerType(LLVMInt8Type(), 0);
                    LLVMTypeRef _pty = LLVMFunctionType(LLVMInt32Type(), &i8ptr, 1, 0);
                    LLVMBuildCall2(ctx->b, _pty, puts_fn, args, 1, "");
                } else {
                    LLVMValueRef printf_fn = get_printf_fn(ctx);
                    LLVMValueRef fmt = LLVMBuildGlobalStringPtr(ctx->b, "%d\\n", "fmt");
                    LLVMValueRef args[] = { fmt, val };
                    LLVMTypeRef i8ptr2 = LLVMPointerType(LLVMInt8Type(), 0);
                    LLVMTypeRef _pfty = LLVMFunctionType(LLVMInt32Type(), &i8ptr2, 1, 1);
                    LLVMBuildCall2(ctx->b, _pfty, printf_fn, args, 2, "");
                }
            }
            break;
            
        default:
            // Expression statement
            { ExprResult er = expr(ctx, n); (void)er; }
            break;
    }
}
