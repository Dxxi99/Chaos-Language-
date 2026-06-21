with open('codegen.c', 'r') as f:
    content = f.read()

# push 케이스를 완전히 새로 작성
old_start = content.find('case AST_FUNC_CALL:{if(strcmp(n->func_call.name,"push")')
old_end = content.find('break;}case AST_BLOCK', old_start)
old = content[old_start:old_end]

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
        LLVMValueRef idxs[]={len};
        LLVMValueRef gep=LLVMBuildGEP2(builder,LLVMInt64Type(),data,idxs,1,"idx");
        LLVMBuildStore(builder,val,gep);
        LLVMValueRef newlen=LLVMBuildAdd(builder,len,LLVMConstInt(LLVMInt64Type(),1,0),"newlen");
        LLVMBuildStore(builder,newlen,lenptr);
    }
}
'''

content = content[:old_start] + new + content[old_end:]

with open('codegen.c', 'w') as f:
    f.write(content)
print("Done")
