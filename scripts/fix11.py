with open('codegen.c', 'r') as f:
    content = f.read()

# append stmt 수정 - readFile/writeFile 추가
old = '''case AST_FUNC_CALL:{
if(strcmp(n->func_call.name,"append")==0){
    Var* v=get_var(n->func_call.args[0]->ident.name);
    if(v && v->is_list){
        LLVMTypeRef lty=get_list_type();
        LLVMValueRef dptr=LLVMBuildStructGEP2(builder,lty,v->ptr,0,"dptr");
        LLVMValueRef data=LLVMBuildLoad2(builder,LLVMPointerType(LLVMInt64Type(),0),dptr,"ldata");
        LLVMValueRef lenptr=LLVMBuildStructGEP2(builder,lty,v->ptr,1,"lenptr");
        LLVMValueRef len=LLVMBuildLoad2(builder,LLVMInt64Type(),lenptr,"len");
        LLVMValueRef val=codegen_expr(n->func_call.args[1]);
        LLVMValueRef gep=LLVMBuildGEP2(builder,LLVMInt64Type(),data,&len,1,"idx");
        LLVMBuildStore(builder,val,gep);
        LLVMValueRef newlen=LLVMBuildAdd(builder,len,LLVMConstInt(LLVMInt64Type(),1,0),"newlen");
        LLVMBuildStore(builder,newlen,lenptr);
    }
}
break;}'''

new = '''case AST_FUNC_CALL:{
if(strcmp(n->func_call.name,"readFile")==0){
    LLVMValueRef fp=LLVMGetNamedFunction(module,"fopen");
    LLVMValueRef fr=LLVMGetNamedFunction(module,"fread");
    if(!fp){LLVMTypeRef fa[]={LLVMPointerType(LLVMInt8Type(),0),LLVMPointerType(LLVMInt8Type(),0)};fp=LLVMAddFunction(module,"fopen",LLVMFunctionType(LLVMPointerType(LLVMInt8Type(),0),fa,2,0));}
    if(!fr){LLVMTypeRef fra[]={LLVMPointerType(LLVMInt8Type(),0),LLVMInt64Type(),LLVMInt64Type(),LLVMPointerType(LLVMInt8Type(),0)};fr=LLVMAddFunction(module,"fread",LLVMFunctionType(LLVMInt64Type(),fra,4,0));}
}
break;}'''

content = content.replace(old, new)

with open('codegen.c', 'w') as f:
    f.write(content)
print("Done")
