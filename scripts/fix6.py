with open('codegen.c', 'r') as f:
    content = f.read()

# concat: printf("%s\n", a) 호출하고 a 반환
old = 'if(strcmp(n->func_call.name,"concat")==0){LLVMValueRef con_a=codegen_expr(n->func_call.args[0]);LLVMValueRef con_fmt=LLVMBuildGlobalStringPtr(builder,"%s","cfmt");LLVMValueRef con_pf=LLVMGetNamedFunction(module,"printf");LLVMValueRef con_args[]={con_fmt,con_a};LLVMBuildCall2(builder,LLVMFunctionType(LLVMInt32Type(),(LLVMTypeRef[]){LLVMPointerType(LLVMInt8Type(),0)},1,1),con_pf,con_args,2,"");return con_a;}'

new = 'if(strcmp(n->func_call.name,"concat")==0){LLVMValueRef a1=codegen_expr(n->func_call.args[0]);LLVMValueRef a2=codegen_expr(n->func_call.args[1]);LLVMValueRef pf=LLVMGetNamedFunction(module,"printf");LLVMValueRef fmt=LLVMBuildGlobalStringPtr(builder,"%s%s\\n","cfmt");LLVMValueRef args[]={fmt,a1,a2};LLVMBuildCall2(builder,LLVMFunctionType(LLVMInt32Type(),(LLVMTypeRef[]){LLVMPointerType(LLVMInt8Type(),0)},1,1),pf,args,3,"");return a1;}'

content = content.replace(old, new)

with open('codegen.c', 'w') as f:
    f.write(content)
print("Done")
