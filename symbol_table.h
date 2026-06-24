#pragma once
#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H
#include "parser.h"
#include "type.h"
#include <llvm-c/Core.h>

#ifndef VAR_T_DEFINED
#define VAR_T_DEFINED
typedef struct { char* n; LLVMValueRef p; int s,f,l,flt,m; LLVMTypeRef t; ChaosType ct; } Var;
#endif

#ifndef STRUCT_T_DEFINED
#define STRUCT_T_DEFINED
typedef struct { char* n; char** fs; char** ft; int fc; } Struct;
#endif

#ifndef FUNC_T_DEFINED
#define FUNC_T_DEFINED
typedef struct { char* n; LLVMValueRef fn; LLVMTypeRef ty; int pc; ChaosType params[16]; ChaosType ret; int resolved; } Func;
#endif

extern Var vars[256];
extern int vc;
extern Struct st[32];
extern int sc;
extern Func fns[32];
extern int fc;

void clr(void);
void add_st(const char* n, char** fs, char** ft, int c);
Struct* get_st(const char* n);
Func* get_fn(const char* n);
Var* get_v(const char* n);
void set_v(const char* n, LLVMValueRef p, int s, int f, LLVMTypeRef t, int l, int flt, int m, ChaosType ct);
LLVMTypeRef st_ty(const char* n);
LLVMTypeRef list_ty(void);
#endif

// Function signature for call resolution
typedef struct {
    char* name;
    LLVMTypeRef fn_type;
    LLVMTypeRef return_type;
    int param_count;
    LLVMTypeRef* param_types;
    int resolved;
} FuncSig;

void register_func_sig(const char* name, LLVMTypeRef fn_type, int pc);
LLVMTypeRef lookup_func_sig(const char* name);
