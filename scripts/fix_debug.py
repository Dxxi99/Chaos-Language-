with open('codegen.c', 'r') as f:
    content = f.read()

# push 케이스 앞에 var_count 출력
old = 'if(strcmp(n->func_call.name,"push")==0||strcmp(n->func_call.name,"append")==0){'
new = 'if(strcmp(n->func_call.name,"push")==0||strcmp(n->func_call.name,"append")==0){LLVMValueRef dbg=LLVMBuildGlobalStringPtr(builder,"PUSH_CALLED\\n","dbg");LLVMValueRef dbg_pf=LLVMGetNamedFunction(module,"printf");LLVMBuildCall2(builder,LLVMFunctionType(LLVMInt32Type(),(LLVMTypeRef[]){LLVMPointerType(LLVMInt8Type(),0)},1,1),dbg_pf,(LLVMValueRef[]){dbg},1,"");'

content = content.replace(old, new)

with open('codegen.c', 'w') as f:
    f.write(content)
print("Done")
