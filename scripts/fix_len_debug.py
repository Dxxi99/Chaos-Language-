with open('codegen.c', 'r') as f:
    content = f.read()

old = 'LLVMValueRef len=LLVMBuildLoad2(builder,LLVMInt64Type(),lenptr,"len");'
new = 'LLVMValueRef len=LLVMBuildLoad2(builder,LLVMInt64Type(),lenptr,"len");{LLVMValueRef lf=LLVMBuildGlobalStringPtr(builder,"%d\\n","lf");LLVMValueRef lpf=LLVMGetNamedFunction(module,"printf");LLVMBuildCall2(builder,LLVMFunctionType(LLVMInt32Type(),(LLVMTypeRef[]){LLVMPointerType(LLVMInt8Type(),0)},1,1),lpf,(LLVMValueRef[]){lf,len},2,"");}'

content = content.replace(old, new)

with open('codegen.c', 'w') as f:
    f.write(content)
print("Done")
