#ifndef CHAOS_PARSER_H
#define CHAOS_PARSER_H

typedef enum {
    AST_PROGRAM, AST_VAR_DECL, AST_VAR_ASSIGN, AST_PRINT,
    AST_IF, AST_FOR, AST_WHILE, AST_FUNC_DEF, AST_STRUCT_DEF,
    AST_STRUCT_CREATE, AST_FIELD_ACCESS, AST_FUNC_CALL,
    AST_LIST, AST_INDEX,
    AST_RETURN, AST_BREAK, AST_CONTINUE, AST_BLOCK, AST_BINARY, AST_NUMBER, AST_STRING, AST_BOOL, AST_IDENT
} AstNodeType;

typedef struct AstNode {
    AstNodeType type;
    union {
        struct { char* name; struct AstNode* value; } var_decl;
        struct { char* name; struct AstNode* value; } var_assign;
        struct { struct AstNode** args; int arg_count; } print;
        struct { struct AstNode *cond, *then_body, *else_body; } if_stmt;
        struct { char* var; struct AstNode *start, *end, *body; } for_stmt;
        struct { struct AstNode *cond, *body; } while_stmt;
        struct { char* name; char** params; int param_count; struct AstNode* body; } func_def;
        struct { char* name; char** field_names; char** field_types; int field_count; } struct_def;
        struct { char* struct_name; struct AstNode** args; int arg_count; } struct_create;
        struct { struct AstNode* object; char* field; } field_access;
        struct { char* name; struct AstNode** args; int arg_count; } func_call;
        struct { struct AstNode** elements; int count; } list;
        struct { struct AstNode* object; struct AstNode* index; } index_expr;
        struct { struct AstNode* value; } ret;
        struct { struct AstNode** statements; int count; } block;
        struct { int op; struct AstNode *left, *right; } binary;
        struct { int is_float; union { long int_val; double float_val; }; } number;
        struct { char* value; } string;
        struct { int value; } boolean;
        struct { char* name; } ident;
    };
} AstNode;

AstNode* parse_program();
#endif
