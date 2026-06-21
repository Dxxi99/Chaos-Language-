with open('codegen.c', 'r') as f:
    content = f.read()

# append stmt에 printf 디버깅 추가
old = 'if(strcmp(n->func_call.name,"append")==0){'

new = 'if(strcmp(n->func_call.name,"append")==0){LLVMValueRef dpf=LLVMGetNamedFunction(module,"printf");LLVMValueRef dfmt=LLVMBuildGlobalStringPtr(builder,"APPEND\\n","dfmt");LLVMBuildCall2(builder,LLVMFunctionType(LLVMInt32Type(),(LLVMTypeRef[]){LLVMPointerType(LLVMInt8Type(),0)},1,1),dpf,(LLVMValueRef[]){dfmt},1,"");'

content = content.replace(old, new)

with open('codegen.c', 'w') as f:
    f.write(content)
print("Done")
