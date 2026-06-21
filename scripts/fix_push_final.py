with open('codegen.c', 'r') as f:
    content = f.read()

# 현재 stmt AST_FUNC_CALL 찾기
start = content.find('case AST_FUNC_CALL:{\nif(strcmp(n->func_call.name,"append")')
end = content.find('break;\n}', start)

old = content[start:end+7]

new = '''case AST_FUNC_CALL:{
if(strcmp(n->func_call.name,"push")==0||strcmp(n->func_call.name,"append")==0){
    Var* pv=get_var(n->func_call.args[0]->ident.name);
    if(pv&&pv->is_list){
        LLVMTypeRef lty=get_list_type();
        LLVMValueRef dptr=LLVMBuildStructGEP2(builder,lty,pv->ptr,0,"dptr");
        LLVMValueRef data=LLVMBuildLoad2(builder,LLVMPointerType(LLVMInt64Type(),0),dptr,"ldata");
        LLVMValueRef lenptr=LLVMBuildStructGEP2(builder,lty,pv->ptr,1,"lenptr");
        LLVMValueRef len=LLVMBuildLoad2(builder,LLVMInt64Type(),lenptr,"len");
        LLVMValueRef val=codegen_expr(n->func_call.args[1]);
        LLVMValueRef gep=LLVMBuildGEP2(builder,LLVMInt64Type(),data,&len,1,"idx");
        LLVMBuildStore(builder,val,gep);
        LLVMValueRef newlen=LLVMBuildAdd(builder,len,LLVMConstInt(LLVMInt64Type(),1,0),"newlen");
        LLVMBuildStore(builder,newlen,lenptr);
    }
}
break;}'''

content = content[:start] + new + content[end+7:]

with open('codegen.c', 'w') as f:
    f.write(content)
print("Done")
