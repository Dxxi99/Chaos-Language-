with open('codegen.c', 'r') as f:
    content = f.read()

# print 처리 부분 수정: AST_FUNC_CALL이고 concat이면 is_str=1
old_print = 'else if(n->print.expr && n->print.expr->type==AST_FUNC_CALL){'
new_print = 'else if(n->print.expr && n->print.expr->type==AST_FUNC_CALL){if(strcmp(n->print.expr->func_call.name,"concat")==0)do_print(codegen_expr(n->print.expr),1,0);else '

content = content.replace(old_print, new_print)

with open('codegen.c', 'w') as f:
    f.write(content)
print("Done")
