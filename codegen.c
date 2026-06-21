// codegen.c - Chaos LLVM Code Generator (Clean)
#include "codegen.h"
#include "lexer.h"
#include <llvm-c/Core.h>
#include <llvm-c/BitWriter.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static LLVMModuleRef mod;
static LLVMBuilderRef b;
static LLVMValueRef cur_fn;
static LLVMValueRef main_fn;
static LLVMValueRef ret_v;
static LLVMBasicBlockRef loop_end, loop_cond;

// Function types
static LLVMTypeRef scanf_ty, strlen_ty, malloc_ty, strcpy_ty, strcat_ty;
static LLVMTypeRef fopen_ty, fread_ty, fclose_ty;
static LLVMTypeRef tm_args[2];

// Symbol tables
typedef struct { char* n; LLVMValueRef p; int s,f,l,flt,m; LLVMTypeRef t; } Var;
static Var vars[256]; static int vc;
typedef struct { char* n; char** fs; char** ft; int fc; } Struct;
static Struct st[32]; static int sc;
typedef struct { char* n; LLVMValueRef fn; LLVMTypeRef ty; int pc; } Func;
static Func fns[32]; static int fc;

#define I64 LLVMInt64Type()
#define I1 LLVMInt1Type()
#define I8P LLVMPointerType(LLVMInt8Type(),0)
#define I64P LLVMPointerType(I64,0)
static LLVMTypeRef list_ty() { LLVMTypeRef f[]={I64P,I64,I64}; return LLVMStructType(f,3,0); }

static LLVMValueRef call_builtin(AstNode* n);
static void declare_fn(AstNode* n);
static void define_fn(AstNode* n);
static void decl_var(AstNode* n);
static void print_stmt(AstNode* n);
static void if_stmt(AstNode* n);
static void while_stmt(AstNode* n);
static void for_stmt(AstNode* n);
static void for_in_list(AstNode* n);
static void stmt_call(AstNode* n);

void codegen_init(const char* fn) {
    mod=LLVMModuleCreateWithName(fn); b=LLVMCreateBuilder();
    LLVMTypeRef a1[]={I8P};
    scanf_ty=LLVMFunctionType(LLVMInt32Type(),a1,1,1); LLVMAddFunction(mod,"scanf",scanf_ty);
    strlen_ty=LLVMFunctionType(I64,a1,1,0); LLVMAddFunction(mod,"strlen",strlen_ty);
    LLVMTypeRef a2[]={I64}; malloc_ty=LLVMFunctionType(I8P,a2,1,0); LLVMAddFunction(mod,"malloc",malloc_ty);
    LLVMTypeRef a3[]={I8P,I8P}; strcpy_ty=LLVMFunctionType(I8P,a3,2,0); LLVMAddFunction(mod,"strcpy",strcpy_ty);
    strcat_ty=LLVMFunctionType(I8P,a3,2,0); LLVMAddFunction(mod,"strcat",strcat_ty);
    LLVMTypeRef a4[]={LLVMDoubleType(),LLVMDoubleType()}; LLVMAddFunction(mod,"llvm.pow.f64",LLVMFunctionType(LLVMDoubleType(),a4,2,0));LLVMTypeRef a7[]={LLVMDoubleType()};LLVMAddFunction(mod,"llvm.sqrt.f64",LLVMFunctionType(LLVMDoubleType(),a7,1,0));LLVMAddFunction(mod,"llvm.sin.f64",LLVMFunctionType(LLVMDoubleType(),a7,1,0));LLVMAddFunction(mod,"llvm.cos.f64",LLVMFunctionType(LLVMDoubleType(),a7,1,0));LLVMAddFunction(mod,"llvm.log.f64",LLVMFunctionType(LLVMDoubleType(),a7,1,0));
    fopen_ty=LLVMFunctionType(I8P,a3,2,0); LLVMAddFunction(mod,"fopen",fopen_ty);
    LLVMTypeRef a5[]={I8P,I64,I64,I8P}; fread_ty=LLVMFunctionType(I64,a5,4,0); LLVMAddFunction(mod,"fread",fread_ty);LLVMAddFunction(mod,"fwrite",fread_ty);
    LLVMTypeRef a6[]={I8P}; fclose_ty=LLVMFunctionType(LLVMInt32Type(),a6,1,0); LLVMAddFunction(mod,"fclose",fclose_ty);LLVMTypeRef tm_args[]={LLVMInt32Type(),I8P};tm_args[0]=LLVMInt32Type(); tm_args[1]=I8P; LLVMAddFunction(mod,"clock_gettime",LLVMFunctionType(LLVMInt32Type(),tm_args,2,0));
}

static void clr() { vc=0; }
static void add_st(const char* n, char** fs, char** ft, int c) { st[sc].n=strdup(n);st[sc].fs=malloc(c*8);st[sc].ft=malloc(c*8);for(int i=0;i<c;i++){st[sc].fs[i]=strdup(fs[i]);st[sc].ft[i]=strdup(ft[i]);}st[sc].fc=c;sc++; }
static Struct* get_st(const char* n) { for(int i=0;i<sc;i++)if(strcmp(st[i].n,n)==0)return &st[i]; return 0; }
static Func* get_fn(const char* n) { for(int i=0;i<fc;i++)if(strcmp(fns[i].n,n)==0)return &fns[i]; return 0; }
static Var* get_v(const char* n) { for(int i=0;i<vc;i++)if(vars[i].n&&strcmp(vars[i].n,n)==0)return &vars[i]; return 0; }
static void set_v(const char* n, LLVMValueRef p, int s, int f, LLVMTypeRef t, int l, int flt, int m) { if(vc<256){vars[vc].n=strdup(n);vars[vc].p=p;vars[vc].s=s;vars[vc].f=f;vars[vc].t=t;vars[vc].l=l;vars[vc].flt=flt;vars[vc].m=m;vc++;} }
static LLVMTypeRef st_ty(const char* n) { Struct* si=get_st(n);if(!si)return 0;LLVMTypeRef* fs=malloc(8*si->fc);for(int i=0;i<si->fc;i++)fs[i]=strcmp(si->ft[i],"text")==0?I8P:I64;LLVMTypeRef r=LLVMStructType(fs,si->fc,0);free(fs);return r; }

static LLVMValueRef expr(AstNode* n) {
    if(!n)return LLVMConstInt(I64,0,0);
    switch(n->type){
        case AST_NUMBER:return n->number.is_float?LLVMConstReal(LLVMDoubleType(),n->number.float_val):LLVMConstInt(I64,n->number.int_val,0);
        case AST_IDENT:{Var* v=get_v(n->ident.name);if(!v)return LLVMConstInt(I64,0,0);if(v->t)return LLVMBuildLoad2(b,v->t,v->p,"sv");LLVMTypeRef ty=v->s?I8P:(v->f?I1:I64);return LLVMBuildLoad2(b,ty,v->p,"v");}
        case AST_BOOL:return LLVMConstInt(I1,n->boolean.value,0);
        case AST_STRING:return LLVMBuildGlobalStringPtr(b,n->string.value,"s");
        case AST_BINARY:{LLVMValueRef l=expr(n->binary.left),r=expr(n->binary.right);switch(n->binary.op){
            case TOK_PLUS:{LLVMValueRef a1=l,a2=r;if((n->binary.left->type==AST_IDENT&&get_v(n->binary.left->ident.name)&&get_v(n->binary.left->ident.name)->s)||(n->binary.right->type==AST_IDENT&&get_v(n->binary.right->ident.name)&&get_v(n->binary.right->ident.name)->s)||n->binary.left->type==AST_STRING||n->binary.right->type==AST_STRING){LLVMValueRef sl=LLVMGetNamedFunction(mod,"strlen");LLVMValueRef l1=LLVMBuildCall2(b,strlen_ty,sl,(LLVMValueRef[]){a1},1,""),l2=LLVMBuildCall2(b,strlen_ty,sl,(LLVMValueRef[]){a2},1,"");LLVMValueRef tot=LLVMBuildAdd(b,LLVMBuildAdd(b,l1,l2,""),LLVMConstInt(I64,1,0),"");LLVMValueRef buf=LLVMBuildCall2(b,malloc_ty,LLVMGetNamedFunction(mod,"malloc"),(LLVMValueRef[]){tot},1,"");LLVMBuildCall2(b,strcpy_ty,LLVMGetNamedFunction(mod,"strcpy"),(LLVMValueRef[]){buf,a1},2,"");LLVMBuildCall2(b,strcat_ty,LLVMGetNamedFunction(mod,"strcat"),(LLVMValueRef[]){buf,a2},2,"");return buf;}if(LLVMGetTypeKind(LLVMTypeOf(l))==LLVMDoubleTypeKind||LLVMGetTypeKind(LLVMTypeOf(r))==LLVMDoubleTypeKind){if(LLVMGetTypeKind(LLVMTypeOf(l))!=LLVMDoubleTypeKind)l=LLVMBuildSIToFP(b,l,LLVMDoubleType(),"");if(LLVMGetTypeKind(LLVMTypeOf(r))!=LLVMDoubleTypeKind)r=LLVMBuildSIToFP(b,r,LLVMDoubleType(),"");return LLVMBuildFAdd(b,l,r,"fadd");}return LLVMBuildAdd(b,l,r,"add");}
    if((n->binary.left->type==AST_STRING||n->binary.right->type==AST_STRING)||
       (n->binary.left->type==AST_IDENT&&get_v(n->binary.left->ident.name)&&get_v(n->binary.left->ident.name)->s)||
       (n->binary.right->type==AST_IDENT&&get_v(n->binary.right->ident.name)&&get_v(n->binary.right->ident.name)->s)){
        LLVMValueRef a1=expr(n->binary.left),a2=expr(n->binary.right);
        LLVMValueRef sl=LLVMGetNamedFunction(mod,"strlen");
        LLVMValueRef l1=LLVMBuildCall2(b,strlen_ty,sl,(LLVMValueRef[]){a1},1,""),l2=LLVMBuildCall2(b,strlen_ty,sl,(LLVMValueRef[]){a2},1,"");
        LLVMValueRef tot=LLVMBuildAdd(b,LLVMBuildAdd(b,l1,l2,""),LLVMConstInt(I64,1,0),"");
        LLVMValueRef buf=LLVMBuildCall2(b,malloc_ty,LLVMGetNamedFunction(mod,"malloc"),(LLVMValueRef[]){tot},1,"");
        LLVMBuildCall2(b,strcpy_ty,LLVMGetNamedFunction(mod,"strcpy"),(LLVMValueRef[]){buf,a1},2,"");
        LLVMBuildCall2(b,strcat_ty,LLVMGetNamedFunction(mod,"strcat"),(LLVMValueRef[]){buf,a2},2,"");
        return buf;
    }
    return LLVMBuildAdd(b,l,r,"add");case TOK_MINUS:if(LLVMGetTypeKind(LLVMTypeOf(l))==LLVMDoubleTypeKind||LLVMGetTypeKind(LLVMTypeOf(r))==LLVMDoubleTypeKind)return LLVMBuildFSub(b,l,r,"fsub");return LLVMBuildSub(b,l,r,"sub");
            case TOK_STAR:if(LLVMGetTypeKind(LLVMTypeOf(l))==LLVMDoubleTypeKind||LLVMGetTypeKind(LLVMTypeOf(r))==LLVMDoubleTypeKind)return LLVMBuildFMul(b,l,r,"fmul");return LLVMBuildMul(b,l,r,"mul");case TOK_SLASH:if(LLVMGetTypeKind(LLVMTypeOf(l))==LLVMDoubleTypeKind||LLVMGetTypeKind(LLVMTypeOf(r))==LLVMDoubleTypeKind)return LLVMBuildFDiv(b,l,r,"fdiv");return LLVMBuildSDiv(b,l,r,"div");
            case TOK_MOD:if(LLVMGetTypeKind(LLVMTypeOf(l))==LLVMDoubleTypeKind||LLVMGetTypeKind(LLVMTypeOf(r))==LLVMDoubleTypeKind){if(LLVMGetTypeKind(LLVMTypeOf(l))!=LLVMDoubleTypeKind)l=LLVMBuildSIToFP(b,l,LLVMDoubleType(),"");if(LLVMGetTypeKind(LLVMTypeOf(r))!=LLVMDoubleTypeKind)r=LLVMBuildSIToFP(b,r,LLVMDoubleType(),"");return LLVMBuildFRem(b,l,r,"fmod");}return LLVMBuildSRem(b,l,r,"mod");
            case TOK_POW:{LLVMValueRef dl=LLVMBuildSIToFP(b,l,LLVMDoubleType(),"");LLVMValueRef dr=LLVMBuildSIToFP(b,r,LLVMDoubleType(),"");LLVMValueRef pw=LLVMBuildCall2(b,LLVMFunctionType(LLVMDoubleType(),(LLVMTypeRef[]){LLVMDoubleType(),LLVMDoubleType()},2,0),LLVMGetNamedFunction(mod,"llvm.pow.f64"),(LLVMValueRef[]){dl,dr},2,"");if(LLVMGetTypeKind(LLVMTypeOf(l))!=LLVMDoubleTypeKind&&LLVMGetTypeKind(LLVMTypeOf(r))!=LLVMDoubleTypeKind)return LLVMBuildFPToSI(b,pw,I64,"");if(LLVMGetTypeKind(LLVMTypeOf(l))==LLVMDoubleTypeKind||LLVMGetTypeKind(LLVMTypeOf(r))==LLVMDoubleTypeKind)return pw;return LLVMBuildFPToSI(b,pw,I64,"");}
            case TOK_EQ_EQ:return LLVMBuildICmp(b,LLVMIntEQ,l,r,"e");case TOK_NOT_EQ:return LLVMBuildICmp(b,LLVMIntNE,l,r,"n");
            case TOK_LT:return LLVMBuildICmp(b,LLVMIntSLT,l,r,"l");case TOK_GT:return LLVMBuildICmp(b,LLVMIntSGT,l,r,"g");
            case TOK_LT_EQ:return LLVMBuildICmp(b,LLVMIntSLE,l,r,"le");case TOK_GT_EQ:return LLVMBuildICmp(b,LLVMIntSGE,l,r,"ge");
            case TOK_AND:{LLVMValueRef bl=LLVMBuildICmp(b,LLVMIntNE,l,LLVMConstInt(I64,0,0),"");LLVMValueRef br=LLVMBuildICmp(b,LLVMIntNE,r,LLVMConstInt(I64,0,0),"");return LLVMBuildZExt(b,LLVMBuildAnd(b,bl,br,""),I64,"");}
            case TOK_OR:{LLVMValueRef bl=LLVMBuildICmp(b,LLVMIntNE,l,LLVMConstInt(I64,0,0),"");LLVMValueRef br=LLVMBuildICmp(b,LLVMIntNE,r,LLVMConstInt(I64,0,0),"");return LLVMBuildZExt(b,LLVMBuildOr(b,bl,br,""),I64,"");}
            case TOK_NOT:{LLVMValueRef bl=LLVMBuildICmp(b,LLVMIntNE,l,LLVMConstInt(I64,0,0),"");return LLVMBuildZExt(b,LLVMBuildNot(b,bl,""),I64,"");}
            default:return l;
        }}
        case AST_FUNC_CALL:return call_builtin(n);
        case AST_STRUCT_CREATE:{Struct* si=get_st(n->struct_create.struct_name);if(!si)return LLVMConstInt(I64,0,0);LLVMTypeRef ty=st_ty(n->struct_create.struct_name);LLVMValueRef a=LLVMBuildAlloca(b,ty,"st");for(int i=0;i<si->fc&&i<n->struct_create.arg_count;i++){LLVMBuildStore(b,expr(n->struct_create.args[i]),LLVMBuildStructGEP2(b,ty,a,i,""));}return LLVMBuildLoad2(b,ty,a,"sv");}
        case AST_FIELD_ACCESS:{Var* v=get_v(n->field_access.object->ident.name);if(!v||!v->t)return LLVMConstInt(I64,0,0);int idx=0;Struct* si=0;for(int i=0;i<sc;i++)for(int j=0;j<st[i].fc;j++)if(strcmp(st[i].fs[j],n->field_access.field)==0){idx=j;si=&st[i];break;}LLVMValueRef gep=LLVMBuildStructGEP2(b,v->t,v->p,idx,"");if(si&&strcmp(si->ft[idx],"text")==0)return LLVMBuildLoad2(b,I8P,gep,"");return LLVMBuildLoad2(b,I64,gep,"");}
        case AST_LIST:{LLVMTypeRef ty=list_ty();LLVMValueRef lp=LLVMBuildAlloca(b,ty,"l");int cnt=n->list.count;LLVMValueRef d=LLVMBuildArrayAlloca(b,I64,LLVMConstInt(I64,100,0),"");for(int i=0;i<cnt;i++)LLVMBuildStore(b,expr(n->list.elements[i]),LLVMBuildStructGEP2(b,LLVMArrayType(I64,100),d,i,""));LLVMBuildStore(b,LLVMConstInt(I64,cnt,0),LLVMBuildStructGEP2(b,ty,lp,1,""));LLVMBuildStore(b,LLVMConstInt(I64,100,0),LLVMBuildStructGEP2(b,ty,lp,2,""));LLVMBuildStore(b,LLVMBuildBitCast(b,d,I64P,""),LLVMBuildStructGEP2(b,ty,lp,0,""));return lp;}
        case AST_INDEX:{Var* v=get_v(n->index_expr.object->ident.name);if(!v)return LLVMConstInt(I64,0,0);if(v->s){LLVMValueRef str=LLVMBuildLoad2(b,I8P,v->p,"");LLVMValueRef idx=expr(n->index_expr.index);return LLVMBuildZExt(b,LLVMBuildLoad2(b,LLVMInt8Type(),LLVMBuildGEP2(b,LLVMInt8Type(),str,&idx,1,""),""),I64,"");}if(!v->l)return LLVMConstInt(I64,0,0);LLVMTypeRef ty=list_ty();LLVMValueRef dp=LLVMBuildLoad2(b,I64P,LLVMBuildStructGEP2(b,ty,v->p,0,""),"");LLVMValueRef idx=expr(n->index_expr.index);return LLVMBuildLoad2(b,I64,LLVMBuildGEP2(b,I64,dp,&idx,1,""),"");}
        default:return LLVMConstInt(I64,0,0);
    }
}

static void pr(LLVMValueRef v, int s, int f, int flt) {
    LLVMTypeRef a[]={I8P};LLVMValueRef pf=LLVMGetNamedFunction(mod,"printf");
    if(!pf){LLVMTypeRef ft=LLVMFunctionType(LLVMInt32Type(),a,1,1);pf=LLVMAddFunction(mod,"printf",ft);}
    LLVMValueRef ca[2];if(s){ca[0]=LLVMBuildGlobalStringPtr(b,"%s\n","");ca[1]=v;}else if(f){ca[0]=LLVMBuildGlobalStringPtr(b,"%d\n","");ca[1]=LLVMBuildZExt(b,v,I64,"");}else{if(LLVMGetTypeKind(LLVMTypeOf(v))==LLVMDoubleTypeKind){ca[0]=LLVMBuildGlobalStringPtr(b,"%g\n","");}else{ca[0]=LLVMBuildGlobalStringPtr(b,"%d\n","");}ca[1]=v;}LLVMBuildCall2(b,LLVMFunctionType(LLVMInt32Type(),a,1,1),pf,ca,2,"");
}

static LLVMValueRef call_builtin(AstNode* n) {
    const char* nm=n->func_call.name;
    if(strcmp(nm,"input")==0){LLVMValueRef buf=LLVMBuildCall2(b,malloc_ty,LLVMGetNamedFunction(mod,"malloc"),(LLVMValueRef[]){LLVMConstInt(I64,256,0)},1,"");LLVMValueRef sf=LLVMGetNamedFunction(mod,"scanf");LLVMValueRef fmt=LLVMBuildGlobalStringPtr(b,"%s","");LLVMBuildCall2(b,scanf_ty,sf,(LLVMValueRef[]){fmt,buf},2,"");return buf;}
    if(strcmp(nm,"len")==0){if(n->func_call.args[0]->type==AST_IDENT){Var* v=get_v(n->func_call.args[0]->ident.name);if(v&&v->l)return LLVMBuildLoad2(b,I64,LLVMBuildStructGEP2(b,list_ty(),v->p,1,""),"");}LLVMValueRef sl=LLVMGetNamedFunction(mod,"strlen");return LLVMBuildCall2(b,strlen_ty,sl,(LLVMValueRef[]){expr(n->func_call.args[0])},1,"");}
    if(strcmp(nm,"concat")==0){LLVMValueRef a1=expr(n->func_call.args[0]),a2=expr(n->func_call.args[1]);LLVMValueRef sl=LLVMGetNamedFunction(mod,"strlen");LLVMValueRef l1=LLVMBuildCall2(b,strlen_ty,sl,(LLVMValueRef[]){a1},1,""),l2=LLVMBuildCall2(b,strlen_ty,sl,(LLVMValueRef[]){a2},1,"");LLVMValueRef tot=LLVMBuildAdd(b,LLVMBuildAdd(b,l1,l2,""),LLVMConstInt(I64,1,0),"");LLVMValueRef buf=LLVMBuildCall2(b,malloc_ty,LLVMGetNamedFunction(mod,"malloc"),(LLVMValueRef[]){tot},1,"");LLVMBuildCall2(b,strcpy_ty,LLVMGetNamedFunction(mod,"strcpy"),(LLVMValueRef[]){buf,a1},2,"");LLVMBuildCall2(b,strcat_ty,LLVMGetNamedFunction(mod,"strcat"),(LLVMValueRef[]){buf,a2},2,"");return buf;}
    if(strcmp(nm,"readFile")==0){LLVMValueRef p=expr(n->func_call.args[0]);LLVMValueRef m=LLVMBuildGlobalStringPtr(b,"r","");LLVMValueRef f=LLVMBuildCall2(b,fopen_ty,LLVMGetNamedFunction(mod,"fopen"),(LLVMValueRef[]){p,m},2,"");LLVMValueRef buf=LLVMBuildCall2(b,malloc_ty,LLVMGetNamedFunction(mod,"malloc"),(LLVMValueRef[]){LLVMConstInt(I64,4096,0)},1,"");LLVMBuildCall2(b,fread_ty,LLVMGetNamedFunction(mod,"fread"),(LLVMValueRef[]){buf,LLVMConstInt(I64,1,0),LLVMConstInt(I64,4096,0),f},4,"");LLVMBuildCall2(b,fclose_ty,LLVMGetNamedFunction(mod,"fclose"),(LLVMValueRef[]){f},1,"");return buf;}
if(strcmp(nm,"sqrt")==0){LLVMValueRef a=expr(n->func_call.args[0]);if(LLVMGetTypeKind(LLVMTypeOf(a))!=LLVMDoubleTypeKind)a=LLVMBuildSIToFP(b,a,LLVMDoubleType(),"");return LLVMBuildCall2(b,LLVMFunctionType(LLVMDoubleType(),(LLVMTypeRef[]){LLVMDoubleType()},1,0),LLVMGetNamedFunction(mod,"llvm.sqrt.f64"),(LLVMValueRef[]){a},1,"");}
    if(strcmp(nm,"writeFile")==0){LLVMValueRef p=expr(n->func_call.args[0]),c=expr(n->func_call.args[1]);LLVMValueRef m=LLVMBuildGlobalStringPtr(b,"w","");LLVMValueRef f=LLVMBuildCall2(b,fopen_ty,LLVMGetNamedFunction(mod,"fopen"),(LLVMValueRef[]){p,m},2,"");LLVMValueRef len=LLVMBuildCall2(b,strlen_ty,LLVMGetNamedFunction(mod,"strlen"),(LLVMValueRef[]){c},1,"");LLVMBuildCall2(b,fread_ty,LLVMGetNamedFunction(mod,"fwrite"),(LLVMValueRef[]){c,LLVMConstInt(I64,1,0),len,f},4,"");LLVMBuildCall2(b,fclose_ty,LLVMGetNamedFunction(mod,"fclose"),(LLVMValueRef[]){f},1,"");return LLVMConstInt(I64,1,0);}
    Func* fi=get_fn(nm);if(!fi)return LLVMConstInt(I64,0,0);LLVMValueRef* args=malloc(8*n->func_call.arg_count);for(int i=0;i<n->func_call.arg_count;i++)args[i]=expr(n->func_call.args[i]);LLVMValueRef call=LLVMBuildCall2(b,fi->ty,fi->fn,args,n->func_call.arg_count,"");free(args);return call;
}

static void stmt(AstNode* n) {
    if(!n)return;
    switch(n->type){
        case AST_STRUCT_DEF:add_st(n->struct_def.name,n->struct_def.field_names,n->struct_def.field_types,n->struct_def.field_count);break;
        case AST_FUNC_DEF:define_fn(n);break;
        case AST_RETURN:ret_v=n->ret.value?expr(n->ret.value):LLVMConstInt(I64,0,0);LLVMBuildRet(b,ret_v);break;
        case AST_VAR_ASSIGN:{Var* v=get_v(n->var_assign.name);if(v){if(!v->m){fprintf(stderr,"Error: Cannot reassign to immutable variable \"%s\"\n",n->var_assign.name);exit(1);}LLVMBuildStore(b,expr(n->var_assign.value),v->p);}break;}
        case AST_VAR_DECL:decl_var(n);break;
        case AST_PRINT:print_stmt(n);break;
        case AST_IF:if_stmt(n);break;
        case AST_WHILE:while_stmt(n);break;
        case AST_PROFILE:{LLVMValueRef ts=LLVMBuildAlloca(b,LLVMArrayType(I64,2),"ts");LLVMValueRef cv=LLVMConstInt(LLVMInt32Type(),0,0);LLVMValueRef ct=LLVMGetNamedFunction(mod,"clock_gettime");if(ct){LLVMBuildCall2(b,LLVMFunctionType(LLVMInt32Type(),tm_args,2,0),ct,(LLVMValueRef[]){cv,ts},2,"");}stmt(n->profile.body);if(ct){LLVMValueRef ts2=LLVMBuildAlloca(b,LLVMArrayType(I64,2),"ts2");LLVMBuildCall2(b,LLVMFunctionType(LLVMInt32Type(),tm_args,2,0),ct,(LLVMValueRef[]){cv,ts2},2,"");LLVMValueRef start=LLVMBuildLoad2(b,I64,LLVMBuildStructGEP2(b,LLVMArrayType(I64,2),ts,0,""),"");LLVMValueRef end=LLVMBuildLoad2(b,I64,LLVMBuildStructGEP2(b,LLVMArrayType(I64,2),ts2,0,""),"");LLVMValueRef diff=LLVMBuildSub(b,end,start,"");LLVMValueRef pf=LLVMGetNamedFunction(mod,"printf");LLVMValueRef fmt=LLVMBuildGlobalStringPtr(b,"Profile: %lld ns\n","");LLVMBuildCall2(b,LLVMFunctionType(LLVMInt32Type(),(LLVMTypeRef[]){I8P},1,1),pf,(LLVMValueRef[]){fmt,diff},2,"");}break;}case AST_FOR:for_stmt(n);break;
        case AST_FUNC_CALL:stmt_call(n);break;
        case AST_BLOCK:case AST_PROGRAM:for(int i=0;i<n->block.count;i++)stmt(n->block.statements[i]);break;
        case AST_BREAK:if(loop_end)LLVMBuildBr(b,loop_end);break;
        case AST_CONTINUE:if(loop_cond)LLVMBuildBr(b,loop_cond);break;
        default:break;
    }
}

static void declare_fn(AstNode* n) {if(get_fn(n->func_def.name))return;LLVMTypeRef* ps=malloc(8*n->func_def.param_count);for(int i=0;i<n->func_def.param_count;i++)ps[i]=I64;LLVMTypeRef rty=I64;if(strncmp(n->func_def.name,"make",4)==0){Struct* si=get_st(n->func_def.name+4);if(si)rty=st_ty(n->func_def.name+4);}LLVMTypeRef fty=LLVMFunctionType(rty,ps,n->func_def.param_count,0);LLVMValueRef fn=LLVMAddFunction(mod,n->func_def.name,fty);fns[fc].n=strdup(n->func_def.name);fns[fc].fn=fn;fns[fc].ty=fty;fns[fc].pc=n->func_def.param_count;fc++;free(ps);}
static void define_fn(AstNode* n) {Func* fi=get_fn(n->func_def.name);if(!fi)return;LLVMValueRef old=cur_fn;Var ov[256];int oc=vc;memcpy(ov,vars,sizeof(vars));LLVMValueRef orv=ret_v;cur_fn=fi->fn;ret_v=0;clr();LLVMBasicBlockRef fe=LLVMAppendBasicBlock(cur_fn,"e");LLVMPositionBuilderAtEnd(b,fe);for(int j=0;j<n->func_def.param_count;j++){LLVMValueRef p=LLVMGetParam(fi->fn,j);LLVMValueRef a=LLVMBuildAlloca(b,I64,n->func_def.params[j]);LLVMBuildStore(b,p,a);set_v(n->func_def.params[j],a,0,0,0,0,0,1);}stmt(n->func_def.body);if(!ret_v)ret_v=LLVMConstInt(I64,0,0);if(!LLVMGetBasicBlockTerminator(LLVMGetInsertBlock(b)))LLVMBuildRet(b,ret_v);cur_fn=old;memcpy(vars,ov,sizeof(vars));vc=oc;ret_v=orv;LLVMPositionBuilderAtEnd(b,LLVMGetFirstBasicBlock(main_fn));}

static void decl_var(AstNode* n) {
    int s=0,f=0,l=0,st=0,flt=0;LLVMTypeRef ty=I64;LLVMValueRef init=0;Struct* si=0;
    if(n->var_decl.value&&n->var_decl.value->type==AST_STRUCT_CREATE){si=get_st(n->var_decl.value->struct_create.struct_name);if(si){ty=st_ty(n->var_decl.value->struct_create.struct_name);st=1;}}
if(n->var_decl.value&&n->var_decl.value->type==AST_FUNC_CALL){const char* nm=n->var_decl.value->func_call.name;if(strcmp(nm,"concat")==0||strcmp(nm,"readFile")==0||strcmp(nm,"input")==0){s=1;ty=I8P;}else if(strcmp(nm,"sqrt")==0){ty=LLVMDoubleType();flt=1;}else if(strncmp(nm,"make",4)==0){Struct* fsi=get_st(nm+4);if(fsi){ty=st_ty(nm+4);st=1;si=fsi;}}}
    if(st&&si){init=expr(n->var_decl.value);LLVMValueRef a=LLVMBuildAlloca(b,ty,n->var_decl.name);LLVMBuildStore(b,init,a);set_v(n->var_decl.name,a,0,0,ty,0,0,1);return;}
    if(n->var_decl.value&&n->var_decl.value->type==AST_LIST){ty=list_ty();l=1;init=expr(n->var_decl.value);}
    else if(n->var_decl.value&&n->var_decl.value->type==AST_STRING){ty=I8P;s=1;init=expr(n->var_decl.value);}
    else if(n->var_decl.value&&n->var_decl.value->type==AST_BOOL){ty=I1;f=1;init=expr(n->var_decl.value);}else if(n->var_decl.value&&n->var_decl.value->type==AST_BINARY){init=expr(n->var_decl.value);if(LLVMGetTypeKind(LLVMTypeOf(init))==LLVMDoubleTypeKind){ty=LLVMDoubleType();flt=1;}else if(LLVMGetTypeKind(LLVMTypeOf(init))==LLVMPointerTypeKind){ty=I8P;s=1;}}else if(n->var_decl.value&&n->var_decl.value->type==AST_NUMBER&&n->var_decl.value->number.is_float){ty=LLVMDoubleType();flt=1;init=expr(n->var_decl.value);}
    else init=n->var_decl.value?expr(n->var_decl.value):LLVMConstInt(I64,0,0);
    LLVMValueRef a=LLVMBuildAlloca(b,ty,n->var_decl.name);if(l)a=init;else LLVMBuildStore(b,init,a);
    set_v(n->var_decl.name,a,s,f,ty,l,flt,n->var_decl.is_mutable);
}

static void print_stmt(AstNode* n) {for(int i=0;i<n->print.arg_count;i++){AstNode* pe=n->print.args[i];if(pe->type==AST_STRING)pr(expr(pe),1,0,0);else if(pe->type==AST_FIELD_ACCESS){LLVMValueRef v=expr(pe);pr(v,LLVMGetTypeKind(LLVMTypeOf(v))==LLVMPointerTypeKind,0,0);}else if(pe->type==AST_IDENT){LLVMValueRef val=expr(pe);Var* v=get_v(pe->ident.name);pr(val,v?v->s:0,v?v->f:0,v?v->flt:0);}else if(pe->type==AST_FUNC_CALL){const char* nm=pe->func_call.name;pr(expr(pe),strcmp(nm,"concat")==0||strcmp(nm,"readFile")==0||strcmp(nm,"input")==0,0,(strcmp(nm,"sqrt")==0||strcmp(nm,"sin")==0||strcmp(nm,"cos")==0||strcmp(nm,"log")==0)?1:0);}else if(pe->type==AST_BINARY){LLVMValueRef v=expr(pe);pr(v,LLVMGetTypeKind(LLVMTypeOf(v))==LLVMPointerTypeKind,0,LLVMGetTypeKind(LLVMTypeOf(v))==LLVMDoubleTypeKind?1:0);}else pr(expr(pe),0,0,0);}}

static void if_stmt(AstNode* n) {
    LLVMValueRef raw=expr(n->if_stmt.cond);if(LLVMGetTypeKind(LLVMTypeOf(raw))==LLVMIntegerTypeKind)raw=LLVMBuildZExt(b,raw,I64,"");LLVMValueRef cond=LLVMBuildICmp(b,LLVMIntNE,raw,LLVMConstInt(I64,0,0),"");LLVMBasicBlockRef t=LLVMAppendBasicBlock(cur_fn,"t"),e=LLVMAppendBasicBlock(cur_fn,"e"),m=LLVMAppendBasicBlock(cur_fn,"m");LLVMBuildCondBr(b,cond,t,e);LLVMPositionBuilderAtEnd(b,t);stmt(n->if_stmt.then_body);if(!LLVMGetBasicBlockTerminator(LLVMGetInsertBlock(b)))LLVMBuildBr(b,m);LLVMPositionBuilderAtEnd(b,e);if(n->if_stmt.else_body)stmt(n->if_stmt.else_body);if(!LLVMGetBasicBlockTerminator(LLVMGetInsertBlock(b)))LLVMBuildBr(b,m);LLVMPositionBuilderAtEnd(b,m);
}

static void while_stmt(AstNode* n) {LLVMBasicBlockRef c=LLVMAppendBasicBlock(cur_fn,"wc"),b2=LLVMAppendBasicBlock(cur_fn,"wb"),e=LLVMAppendBasicBlock(cur_fn,"we");loop_end=e;loop_cond=c;LLVMBuildBr(b,c);LLVMPositionBuilderAtEnd(b,c);LLVMBuildCondBr(b,LLVMBuildICmp(b,LLVMIntNE,LLVMBuildZExt(b,expr(n->while_stmt.cond),I64,""),LLVMConstInt(I64,0,0),""),b2,e);LLVMPositionBuilderAtEnd(b,b2);stmt(n->while_stmt.body);if(!LLVMGetBasicBlockTerminator(LLVMGetInsertBlock(b)))LLVMBuildBr(b,c);LLVMPositionBuilderAtEnd(b,e);}

static void for_stmt(AstNode* n) {
    if(n->for_stmt.end==NULL){for_in_list(n);return;}
    LLVMValueRef s=expr(n->for_stmt.start),ed=expr(n->for_stmt.end);LLVMValueRef it=LLVMBuildAlloca(b,I64,"i");LLVMBuildStore(b,s,it);set_v(n->for_stmt.var,it,0,0,0,0,0,1);LLVMBasicBlockRef c=LLVMAppendBasicBlock(cur_fn,"fc"),b2=LLVMAppendBasicBlock(cur_fn,"fb"),i=LLVMAppendBasicBlock(cur_fn,"fi"),e=LLVMAppendBasicBlock(cur_fn,"fe");loop_end=e;loop_cond=c;LLVMBuildBr(b,c);LLVMPositionBuilderAtEnd(b,c);LLVMValueRef cur=LLVMBuildLoad2(b,I64,it,"");LLVMBuildCondBr(b,LLVMBuildICmp(b,LLVMIntSLE,cur,ed,""),b2,e);LLVMPositionBuilderAtEnd(b,b2);stmt(n->for_stmt.body);if(!LLVMGetBasicBlockTerminator(LLVMGetInsertBlock(b)))LLVMBuildBr(b,i);LLVMPositionBuilderAtEnd(b,i);LLVMBuildStore(b,LLVMBuildAdd(b,cur,LLVMConstInt(I64,1,0),""),it);LLVMBuildBr(b,c);LLVMPositionBuilderAtEnd(b,e);
}

static void for_in_list(AstNode* n) {
    Var* v=get_v(n->for_stmt.start->ident.name);if(!v||!v->l)return;
    LLVMTypeRef ty=list_ty();LLVMValueRef dp=LLVMBuildLoad2(b,I64P,LLVMBuildStructGEP2(b,ty,v->p,0,""),"");LLVMValueRef lenp=LLVMBuildStructGEP2(b,ty,v->p,1,"");LLVMValueRef len=LLVMBuildLoad2(b,I64,lenp,"");LLVMValueRef it=LLVMBuildAlloca(b,I64,"i");LLVMBuildStore(b,LLVMConstInt(I64,0,0),it);LLVMBasicBlockRef c=LLVMAppendBasicBlock(cur_fn,"fc"),b2=LLVMAppendBasicBlock(cur_fn,"fb"),e=LLVMAppendBasicBlock(cur_fn,"fe");loop_end=e;loop_cond=c;LLVMBuildBr(b,c);LLVMPositionBuilderAtEnd(b,c);LLVMValueRef idx=LLVMBuildLoad2(b,I64,it,"");LLVMBuildCondBr(b,LLVMBuildICmp(b,LLVMIntSLT,idx,len,""),b2,e);LLVMPositionBuilderAtEnd(b,b2);LLVMValueRef elem=LLVMBuildLoad2(b,I64,LLVMBuildGEP2(b,I64,dp,&idx,1,""),"");LLVMValueRef var=LLVMBuildAlloca(b,I64,"v");LLVMBuildStore(b,elem,var);set_v(n->for_stmt.var,var,0,0,0,0,0,1);stmt(n->for_stmt.body);if(!LLVMGetBasicBlockTerminator(LLVMGetInsertBlock(b))){LLVMBuildStore(b,LLVMBuildAdd(b,idx,LLVMConstInt(I64,1,0),""),it);LLVMBuildBr(b,c);}LLVMPositionBuilderAtEnd(b,e);
}

static void stmt_call(AstNode* n) {
    if(strcmp(n->func_call.name,"writeFile")==0){call_builtin(n);return;}if(strcmp(n->func_call.name,"push")==0||strcmp(n->func_call.name,"append")==0){Var* v=get_v(n->func_call.args[0]->ident.name);if(v&&v->l){LLVMTypeRef ty=list_ty();LLVMValueRef dp=LLVMBuildLoad2(b,I64P,LLVMBuildStructGEP2(b,ty,v->p,0,""),"");LLVMValueRef lenp=LLVMBuildStructGEP2(b,ty,v->p,1,"");LLVMValueRef len=LLVMBuildLoad2(b,I64,lenp,"");LLVMValueRef capp=LLVMBuildStructGEP2(b,ty,v->p,2,"");LLVMValueRef cap=LLVMBuildLoad2(b,I64,capp,"");LLVMValueRef val=expr(n->func_call.args[1]);LLVMBuildStore(b,val,LLVMBuildGEP2(b,I64,dp,&len,1,""));LLVMBuildStore(b,LLVMBuildAdd(b,len,LLVMConstInt(I64,1,0),""),lenp);}}
}

static void decl_all(AstNode*n){if(!n)return;if(n->type==AST_FUNC_DEF)declare_fn(n);if(n->type==AST_BLOCK||n->type==AST_PROGRAM)for(int i=0;i<n->block.count;i++)decl_all(n->block.statements[i]);}
void codegen_program(AstNode* prog) {
    for(int i=0;i<prog->block.count;i++)decl_all(prog->block.statements[i]);
    // Create main
    LLVMTypeRef mt=LLVMFunctionType(I64,0,0,0);main_fn=LLVMAddFunction(mod,"main",mt);cur_fn=main_fn;LLVMBasicBlockRef entry=LLVMAppendBasicBlock(cur_fn,"e");LLVMPositionBuilderAtEnd(b,entry);
    // Pass 2: generate
    for(int i=0;i<prog->block.count;i++){AstNode* n=prog->block.statements[i];if(n&&n->type==AST_FUNC_DEF)define_fn(n);else if(n)stmt(n);}
    LLVMBuildRet(b,LLVMConstInt(I64,0,0));
}

void codegen_finish() { /* TODO: RAII free tracking */ size_t len;char* ir=LLVMPrintModuleToString(mod);const char* id=LLVMGetModuleIdentifier(mod,&len);char fn[256];snprintf(fn,256,"%s.ll",id);FILE* f=fopen(fn,"w");fputs(ir,f);fclose(f);LLVMDisposeMessage(ir);LLVMDisposeBuilder(b);LLVMDisposeModule(mod);printf("Compiled: %s\n",fn); }
