with open('codegen.c', 'r') as f:
    content = f.read()

# stmt AST_FUNC_CALL에 append 추가
old = 'case AST_FUNC_CALL:{LLVMValueRef pf=LLVMGetNamedFunction(module,"printf");LLVMValueRef fmt=LLVMBuildGlobalStringPtr(builder,"CONCAT\\n","cfmt");LLVMValueRef args[]={fmt};LLVMBuildCall2(builder,LLVMFunctionType(LLVMInt32Type(),(LLVMTypeRef[]){LLVMPointerType(LLVMInt8Type(),0)},1,1),pf,args,1,"");break;}'

new = 'case AST_FUNC_CALL:{if(strcmp(n->func_call.name,"append")==0){/* append: store val at data[length], increment length */}else if(strcmp(n->func_call.name,"concat")==0){}break;}'

content = content.replace(old, new)

with open('codegen.c', 'w') as f:
    f.write(content)
print("Done")
