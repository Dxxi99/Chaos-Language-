with open('codegen.c', 'r') as f:
    content = f.read()

old = 'case AST_FUNC_CALL:{if(strcmp(n->func_call.name,"append")==0){/* append: store val at data[length], increment length */}else if(strcmp(n->func_call.name,"concat")==0){}break;}'

new = '''case AST_FUNC_CALL:{
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

content = content.replace(old, new)

with open('codegen.c', 'w') as f:
    f.write(content)
print("Done")
