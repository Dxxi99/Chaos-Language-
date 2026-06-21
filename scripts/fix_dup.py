with open('codegen.c', 'r') as f:
    content = f.read()

# 중복된 OK printf 제거 (두 번째 것만 남기고)
old = 'if(pv&&pv->is_list){LLVMValueRef pok=LLVMGetNamedFunction(module,"printf");LLVMValueRef fok=LLVMBuildGlobalStringPtr(builder,"OK\\n","fok");LLVMBuildCall2(builder,LLVMFunctionType(LLVMInt32Type(),(LLVMTypeRef[]){LLVMPointerType(LLVMInt8Type(),0)},1,1),pok,(LLVMValueRef[]){fok},1,"");LLVMValueRef pok=LLVMGetNamedFunction(module,"printf");LLVMValueRef fok=LLVMBuildGlobalStringPtr(builder,"OK\\n","fok");LLVMBuildCall2(builder,LLVMFunctionType(LLVMInt32Type(),(LLVMTypeRef[]){LLVMPointerType(LLVMInt8Type(),0)},1,1),pok,(LLVMValueRef[]){fok},1,"");LLVMTypeRef lty=get_list_type();'

new = 'if(pv&&pv->is_list){LLVMTypeRef lty=get_list_type();'

content = content.replace(old, new)

with open('codegen.c', 'w') as f:
    f.write(content)
print("Done")
