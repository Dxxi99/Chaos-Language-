with open('codegen.c', 'r') as f:
    content = f.read()

old = 'Var* pv=get_var(n->func_call.args[0]->ident.name);if(pv&&pv->is_list){'
new = 'Var* pv=get_var(n->func_call.args[0]->ident.name);if(pv==NULL){LLVMValueRef nf=LLVMBuildGlobalStringPtr(builder,"NULL\\n","nf");LLVMValueRef npf=LLVMGetNamedFunction(module,"printf");LLVMBuildCall2(builder,LLVMFunctionType(LLVMInt32Type(),(LLVMTypeRef[]){LLVMPointerType(LLVMInt8Type(),0)},1,1),npf,(LLVMValueRef[]){nf},1,"");}else if(!pv->is_list){LLVMValueRef nl=LLVMBuildGlobalStringPtr(builder,"NOTLIST\\n","nl");LLVMValueRef npf2=LLVMGetNamedFunction(module,"printf");LLVMBuildCall2(builder,LLVMFunctionType(LLVMInt32Type(),(LLVMTypeRef[]){LLVMPointerType(LLVMInt8Type(),0)},1,1),npf2,(LLVMValueRef[]){nl},1,"");}if(pv&&pv->is_list){'

content = content.replace(old, new)

with open('codegen.c', 'w') as f:
    f.write(content)
print("Done")
