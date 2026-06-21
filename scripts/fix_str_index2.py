with open('codegen.c', 'r') as f:
    content = f.read()

old = 'if(v->is_str){LLVMValueRef idx=codegen_expr(n->index_expr.index);LLVMValueRef gep=LLVMBuildGEP2(builder,LLVMInt8Type(),v->ptr,&idx,1,"stridx");return LLVMBuildZExt(builder,LLVMBuildLoad2(builder,LLVMInt8Type(),gep,"sc"),LLVMInt64Type(),"ext");}'

new = 'if(v->is_str){LLVMValueRef str=LLVMBuildLoad2(builder,LLVMPointerType(LLVMInt8Type(),0),v->ptr,"str");LLVMValueRef idx=codegen_expr(n->index_expr.index);LLVMValueRef gep=LLVMBuildGEP2(builder,LLVMInt8Type(),str,&idx,1,"stridx");return LLVMBuildZExt(builder,LLVMBuildLoad2(builder,LLVMInt8Type(),gep,"sc"),LLVMInt64Type(),"ext");}'

content = content.replace(old, new)

with open('codegen.c', 'w') as f:
    f.write(content)
print("Done")
