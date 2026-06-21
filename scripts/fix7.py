with open('codegen.c', 'r') as f:
    content = f.read()

# AST_FUNC_CALL을 statement로 처리
old = 'case AST_BLOCK:case AST_PROGRAM:for'
new = 'case AST_FUNC_CALL:{if(strcmp(n->func_call.name,"concat")==0){LLVMValueRef a1=codegen_expr(n->func_call.args[0]);LLVMValueRef a2=codegen_expr(n->func_call.args[1]);LLVMValueRef pf=LLVMGetNamedFunction(module,"printf");LLVMValueRef fmt=LLVMBuildGlobalStringPtr(builder,"%s%s\\n","cfmt");LLVMValueRef args[]={fmt,a1,a2};LLVMBuildCall2(builder,LLVMFunctionType(LLVMInt32Type(),(LLVMTypeRef[]){LLVMPointerType(LLVMInt8Type(),0)},1,1),pf,args,3,"");}break;}case AST_BLOCK:case AST_PROGRAM:for'

content = content.replace(old, new)

# concat expr은 그냥 첫 인자 반환
old2 = 'if(strcmp(n->func_call.name,"concat")==0){LLVMValueRef a1=codegen_expr(n->func_call.args[0]);LLVMValueRef a2=codegen_expr(n->func_call.args[1]);LLVMValueRef pf=LLVMGetNamedFunction(module,"printf");LLVMValueRef fmt=LLVMBuildGlobalStringPtr(builder,"%s%s\\n","cfmt");LLVMValueRef args[]={fmt,a1,a2};LLVMBuildCall2(builder,LLVMFunctionType(LLVMInt32Type(),(LLVMTypeRef[]){LLVMPointerType(LLVMInt8Type(),0)},1,1),pf,args,3,"");return a1;}'
new2 = 'if(strcmp(n->func_call.name,"concat")==0){return codegen_expr(n->func_call.args[0]);}'

content = content.replace(old2, new2)

with open('codegen.c', 'w') as f:
    f.write(content)
print("Done")
