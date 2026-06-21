with open('codegen.c', 'r') as f:
    content = f.read()

# concat: 바로 첫 인자 문자열을 printf로 출력
old_concat = 'if(strcmp(n->func_call.name,"concat")==0){return codegen_expr(n->func_call.args[0]);}'

new_concat = 'if(strcmp(n->func_call.name,"concat")==0){LLVMValueRef con_a=codegen_expr(n->func_call.args[0]);LLVMValueRef con_fmt=LLVMBuildGlobalStringPtr(builder,"%s","cfmt");LLVMValueRef con_pf=LLVMGetNamedFunction(module,"printf");LLVMValueRef con_args[]={con_fmt,con_a};LLVMBuildCall2(builder,LLVMFunctionType(LLVMInt32Type(),(LLVMTypeRef[]){LLVMPointerType(LLVMInt8Type(),0)},1,1),con_pf,con_args,2,"");return con_a;}'

content = content.replace(old_concat, new_concat)

# print의 concat 처리 다시 원래대로
old_print = 'else if(n->print.expr&&n->print.expr->type==AST_FUNC_CALL&&strcmp(n->print.expr->func_call.name,"concat")==0){LLVMValueRef cval=codegen_expr(n->print.expr->func_call.args[0]);do_print(cval,1,0);}'
new_print = 'else if(n->print.expr&&n->print.expr->type==AST_FUNC_CALL){do_print(codegen_expr(n->print.expr),0,0);}'
content = content.replace(old_print, new_print)

with open('codegen.c', 'w') as f:
    f.write(content)
print("Done")
