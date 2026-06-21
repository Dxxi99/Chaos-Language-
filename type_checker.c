#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "type_checker.h"
#include "symbol_table.h"

static void type_error(const char* msg) {
    fprintf(stderr, "[Type Error] %s\n", msg);
    exit(1);
}

// External: get_v from symbol_table.c
extern Var* get_v(const char* name);
extern int vc;
extern Var vars[256];

// unify_types is defined in type.c
ChaosType infer_type(AstNode* node) {
    if (!node) return TYPE_UNKNOWN;
    
    switch (node->type) {
        case AST_NUMBER:
            return node->chaos_type;
        case AST_STRING:
            return TYPE_TEXT;
        case AST_BOOL:
            return TYPE_FLAG;
        case AST_IDENT: {
            Var* v = get_v(node->ident.name);
            if (!v) {
                fprintf(stderr, "[Type Error] Undefined variable '%s'\n", node->ident.name);
                exit(1);
            }
            return v->ct;
        }
        case AST_BINARY: {
            ChaosType l = infer_type(node->binary.left);
            ChaosType r = infer_type(node->binary.right);
            return unify_types(l, r);
        }
        default:
            return TYPE_UNKNOWN;
    }
}

static void walk(AstNode* node) {
    if (!node) return;
    
    switch (node->type) {
        case AST_VAR_DECL: {
            if (node->var_decl.value) {
                ChaosType init_type = infer_type(node->var_decl.value);
                // Store inferred type
                node->chaos_type = init_type;
            }
            break;
        }
        case AST_VAR_ASSIGN: {
            Var* v = get_v(node->var_assign.name);
            if (!v) {
                fprintf(stderr, "[Type Error] Undefined variable '%s'\n", node->var_assign.name);
                exit(1);
            }
            ChaosType rhs = infer_type(node->var_assign.value);
            if (v->ct != TYPE_UNKNOWN && v->ct != rhs) {
                fprintf(stderr, "[Type Error] Assignment type mismatch for '%s'\n", node->var_assign.name);
                exit(1);
            }
            break;
        }
        case AST_BINARY: {
            infer_type(node);  // Just validate
            break;
        }
        case AST_FUNC_CALL: {
            for (int i = 0; i < node->func_call.arg_count; i++) {
                infer_type(node->func_call.args[i]);
            }
            break;
        }
        default:
            break;
    }
    
    // Recurse into children
    if (node->type == AST_BINARY) {
        walk(node->binary.left);
        walk(node->binary.right);
    }
    if (node->type == AST_IF) {
        walk(node->if_stmt.cond);
        walk(node->if_stmt.then_body);
        walk(node->if_stmt.else_body);
    }
    if (node->type == AST_WHILE) {
        walk(node->while_stmt.cond);
        walk(node->while_stmt.body);
    }
    if (node->type == AST_FOR) {
        walk(node->for_stmt.start);
        walk(node->for_stmt.end);
        walk(node->for_stmt.body);
    }
    if (node->type == AST_FUNC_DEF) {
        walk(node->func_def.body);
    }
    if (node->type == AST_BLOCK) {
        for (int i = 0; i < node->block.count; i++) {
            walk(node->block.statements[i]);
        }
    }
    if (node->type == AST_RETURN) {
        infer_type(node->ret.value);
    }
    if (node->type == AST_PRINT) {
        for (int i = 0; i < node->print.arg_count; i++) {
            infer_type(node->print.args[i]);
        }
    }
}

void check_types(AstNode* root) {
    walk(root);
}
