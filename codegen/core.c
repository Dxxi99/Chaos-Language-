#include "codegen.h"

AstNode* root_ast = NULL;

#include <stdio.h>
#include <string.h>

extern void stmt(CodegenContext* ctx, AstNode* n);

LLVMTypeRef printf_type = NULL;

void codegen_init(CodegenContext* ctx, const char* name) {
    ctx->mod = LLVMModuleCreateWithName(name);
    ctx->b = LLVMCreateBuilder();
    ctx->cur_fn = NULL;
    
    LLVMTypeRef printf_args[] = { LLVMPointerType(LLVMInt8Type(), 0) };
    printf_type = LLVMFunctionType(LLVMInt32Type(), printf_args, 1, 1);
    LLVMAddFunction(ctx->mod, "printf", printf_type);
}

static void generate_func_body(CodegenContext* ctx, AstNode* n) {
    LLVMValueRef fn = LLVMGetNamedFunction(ctx->mod, n->func_def.name);
    if (!fn) return;
    
    LLVMValueRef prev_fn = ctx->cur_fn;
    LLVMBasicBlockRef prev_bb = LLVMGetInsertBlock(ctx->b);
    
    LLVMBasicBlockRef entry = LLVMAppendBasicBlock(fn, "entry");
    fprintf(stderr, "DEBUG gen_body: fn=%p, entry=%p, cur_fn=%p\n", (void*)fn, (void*)entry, (void*)ctx->cur_fn);
    LLVMPositionBuilderAtEnd(ctx->b, entry);
    ctx->cur_fn = fn;
    
    LLVMBasicBlockRef _chk = LLVMGetInsertBlock(ctx->b);
    fprintf(stderr, "DEBUG gen_body after position: bb=%p, term=%d\n", 
            (void*)_chk, _chk ? LLVMGetBasicBlockTerminator(_chk)!=NULL : -1);
    
    int pc = n->func_def.param_count;
    for (int i = 0; i < pc; i++) {
        LLVMValueRef param = LLVMGetParam(fn, i);
        // Store param directly as value (not alloca), using function parameter as value pointer
        extern void set_v(const char*, LLVMValueRef, int, int, LLVMTypeRef, int, int, int, ChaosType);
        set_v(n->func_def.params[i], param, 0, 0, NULL, 0, 0, 1, TYPE_I64);
    }
    
    if (n->func_def.body && n->func_def.body->type == AST_BLOCK) {
        for (int i = 0; i < n->func_def.body->block.count; i++) {
            LLVMBasicBlockRef bb = LLVMGetInsertBlock(ctx->b);
            if (!bb || LLVMGetBasicBlockTerminator(bb)) break;
            stmt(ctx, n->func_def.body->block.statements[i]);
        }
    }
    
    LLVMBasicBlockRef bb = LLVMGetInsertBlock(ctx->b);
    if (bb && !LLVMGetBasicBlockTerminator(bb))
        LLVMBuildRet(ctx->b, LLVMConstInt(LLVMInt64Type(), 0, 0));
    
    ctx->cur_fn = prev_fn;
}

void codegen_program(CodegenContext* ctx, AstNode* root) {
    root_ast = root;
    // Phase 1: declare all functions + create dummy for builder position
    LLVMTypeRef dummy_type = LLVMFunctionType(LLVMVoidType(), NULL, 0, 0);
    LLVMValueRef dummy_fn = LLVMAddFunction(ctx->mod, "__dummy", dummy_type);
    LLVMBasicBlockRef dummy_bb = LLVMAppendBasicBlock(dummy_fn, "entry");
    LLVMPositionBuilderAtEnd(ctx->b, dummy_bb);
    ctx->cur_fn = dummy_fn;
    
    for (int i = 0; i < root->block.count; i++) {
        AstNode* n = root->block.statements[i];
        if (n->type == AST_FUNC_DEF) {
            int pc = n->func_def.param_count;
            LLVMTypeRef* ptypes = pc > 0 ? malloc(sizeof(LLVMTypeRef) * pc) : NULL;
            for (int j = 0; j < pc; j++) ptypes[j] = LLVMInt64Type();
            LLVMTypeRef fn_type = LLVMFunctionType(LLVMInt64Type(), ptypes, pc, 0);
            LLVMAddFunction(ctx->mod, n->func_def.name, fn_type);
            register_func_sig(n->func_def.name, fn_type, pc);
            if (ptypes) free(ptypes);
        }
    }
    
    fprintf(stderr, "After Phase 1:\n");
    LLVMDumpModule(ctx->mod);
    
    // Phase 2: generate function bodies
    for (int i = 0; i < root->block.count; i++) {
        if (root->block.statements[i]->type == AST_FUNC_DEF)
            generate_func_body(ctx, root->block.statements[i]);
    }
    
    fprintf(stderr, "After Phase 2:\n");
    LLVMDumpModule(ctx->mod);
    
    // Phase 3: create main
    LLVMTypeRef main_type = LLVMFunctionType(LLVMInt64Type(), NULL, 0, 0);
    LLVMValueRef main_fn = LLVMAddFunction(ctx->mod, "main", main_type);
    LLVMBasicBlockRef main_entry = LLVMAppendBasicBlock(main_fn, "entry");
    LLVMPositionBuilderAtEnd(ctx->b, main_entry);
    ctx->cur_fn = main_fn;
    
    for (int i = 0; i < root->block.count; i++) {
        AstNode* n = root->block.statements[i];
        if (n->type != AST_FUNC_DEF)
            stmt(ctx, n);
    }
    
    LLVMBasicBlockRef bb = LLVMGetInsertBlock(ctx->b);
    if (bb && !LLVMGetBasicBlockTerminator(bb))
        LLVMBuildRet(ctx->b, LLVMConstInt(LLVMInt64Type(), 0, 0));
}

void codegen_finish(CodegenContext* ctx) {
    LLVMDumpModule(ctx->mod);
    char* ir = LLVMPrintModuleToString(ctx->mod);
    FILE* f = fopen("chaos_output.ll", "w");
    if (f) { fprintf(f, "%s", ir); fclose(f); }
    LLVMDisposeMessage(ir);
}
