with open('codegen.c', 'r') as f:
    content = f.read()

old = 'case AST_FUNC_CALL:{if(strcmp(n->func_call.name,"concat")==0){LLVMValueRef a1=codegen_expr(n->func_call.args[0]);LLVMValueRef a2=codegen_expr(n->func_call.args[1]);LLVMValueRef pf=LLVMGetNamedFunction(module,"printf");LLVMValueRef fmt=LLVMBuildGlobalStringPtr(builder,"%s%s\\n","cfmt");LLVMValueRef args[]={fmt,a1,a2};LLVMBuildCall2(builder,LLVMFunctionType(LLVMInt32Type(),(LLVMTypeRef[]){LLVMPointerType(LLVMInt8Type(),0)},1,1),pf,args,3,"");}break;}'

new = 'case AST_FUNC_CALL:{LLVMValueRef pf=LLVMGetNamedFunction(module,"printf");LLVMValueRef fmt=LLVMBuildGlobalStringPtr(builder,"CONCAT\\n","cfmt");LLVMValueRef args[]={fmt};LLVMBuildCall2(builder,LLVMFunctionType(LLVMInt32Type(),(LLVMTypeRef[]){LLVMPointerType(LLVMInt8Type(),0)},1,1),pf,args,1,"");break;}'

content = content.replace(old, new)

with open('codegen.c', 'w') as f:
    f.write(content)
print("Done")
