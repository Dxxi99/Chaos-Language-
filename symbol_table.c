#include "symbol_table.h"
#include "type.h"
#include <stdlib.h>
#include <string.h>

Var vars[256]; int vc = 0;
Struct st[32]; int sc = 0;
Func fns[32]; int fc = 0;

void clr(void) { vc = 0; }

void add_st(const char* n, char** fs, char** ft, int c) {
    st[sc].n = strdup(n); st[sc].fs = malloc(c * sizeof(char*)); st[sc].ft = malloc(c * sizeof(char*));
    for (int i = 0; i < c; i++) { st[sc].fs[i] = strdup(fs[i]); st[sc].ft[i] = strdup(ft[i]); }
    st[sc].fc = c; sc++;
}

Struct* get_st(const char* n) { for (int i = 0; i < sc; i++) if (strcmp(st[i].n, n) == 0) return &st[i]; return NULL; }
Func* get_fn(const char* n) { for (int i = 0; i < fc; i++) if (strcmp(fns[i].n, n) == 0) return &fns[i]; return NULL; }
Var* get_v(const char* n) { for (int i = 0; i < vc; i++) if (vars[i].n && strcmp(vars[i].n, n) == 0) return &vars[i]; return NULL; }
void set_v(const char* n, LLVMValueRef p, int s, int f, LLVMTypeRef t, int l, int flt, int m, ChaosType ct) { if (vc < 256) { vars[vc].n = strdup(n); vars[vc].p = p; vars[vc].s = s; vars[vc].f = f; vars[vc].t = t; vars[vc].l = l; vars[vc].flt = flt; vars[vc].m = m; vars[vc].ct = ct; vc++; } }
LLVMTypeRef st_ty(const char* n) { Struct* si = get_st(n); if (!si) return NULL; LLVMTypeRef* fs = malloc(si->fc * sizeof(LLVMTypeRef)); for (int i = 0; i < si->fc; i++) fs[i] = strcmp(si->ft[i], "text") == 0 ? LLVMPointerType(LLVMInt8Type(), 0) : LLVMInt64Type(); LLVMTypeRef r = LLVMStructType(fs, si->fc, 0); free(fs); return r; }
LLVMTypeRef list_ty(void) { LLVMTypeRef f[] = { LLVMPointerType(LLVMInt64Type(), 0), LLVMInt64Type(), LLVMInt64Type() }; return LLVMStructType(f, 3, 0); }

// ===========================
// Function Signature Registry
// ===========================
static FuncSig func_sigs[64];
static int fs_count = 0;

void register_func_sig(const char* name, LLVMTypeRef fn_type, int pc) {
    LLVMTypeRef ret_ty = LLVMGetReturnType(fn_type);
    for (int i = 0; i < fs_count; i++) {
        if (strcmp(func_sigs[i].name, name) == 0) {
            func_sigs[i].fn_type = fn_type;
            func_sigs[i].return_type = ret_ty;
            func_sigs[i].param_count = pc;
            func_sigs[i].resolved = 1;
            return;
        }
    }
    if (fs_count < 64) {
        func_sigs[fs_count].name = strdup(name);
        func_sigs[fs_count].fn_type = fn_type;
        func_sigs[fs_count].return_type = ret_ty;
        func_sigs[fs_count].param_count = pc;
        func_sigs[fs_count].resolved = 1;
        fs_count++;
    }
}

LLVMTypeRef lookup_func_sig(const char* name) {
    for (int i = 0; i < fs_count; i++) {
        if (strcmp(func_sigs[i].name, name) == 0 && func_sigs[i].resolved)
            return func_sigs[i].fn_type;
    }
    return NULL;
}
