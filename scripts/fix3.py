with open('codegen.c', 'r') as f:
    content = f.read()

old = 'else if(n->print.expr&&n->print.expr->type==AST_IDENT){Var* v=get_var(n->print.expr->ident.name);do_print(codegen_expr(n->print.expr),v?v->is_str:0,v?v->is_flag:0);}else do_print(codegen_expr(n->print.expr),0,0);'

new = 'else if(n->print.expr&&n->print.expr->type==AST_IDENT){Var* v=get_var(n->print.expr->ident.name);do_print(codegen_expr(n->print.expr),v?v->is_str:0,v?v->is_flag:0);}else if(n->print.expr&&n->print.expr->type==AST_FUNC_CALL&&strcmp(n->print.expr->func_call.name,"concat")==0){do_print(codegen_expr(n->print.expr),1,0);}else do_print(codegen_expr(n->print.expr),0,0);'

content = content.replace(old, new)

with open('codegen.c', 'w') as f:
    f.write(content)
print("Done")
