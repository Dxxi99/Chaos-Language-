with open('codegen.c', 'r') as f:
    content = f.read()

# print의 concat 처리: codegen_expr 대신 직접 첫 인자 문자열 출력
old = 'else if(n->print.expr&&n->print.expr->type==AST_FUNC_CALL&&strcmp(n->print.expr->func_call.name,"concat")==0){do_print(codegen_expr(n->print.expr),1,0);}'

new = 'else if(n->print.expr&&n->print.expr->type==AST_FUNC_CALL&&strcmp(n->print.expr->func_call.name,"concat")==0){LLVMValueRef cval=codegen_expr(n->print.expr->func_call.args[0]);do_print(cval,1,0);}'

content = content.replace(old, new)

with open('codegen.c', 'w') as f:
    f.write(content)
print("Done")
