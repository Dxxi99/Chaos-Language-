with open('codegen.c', 'r') as f:
    content = f.read()

# AST_INDEX에서 문자열 지원 추가
old = 'case AST_INDEX:{Var* v=get_var(n->index_expr.object->ident.name);if(!v||!v->is_list)return LLVMConstInt(LLVMInt64Type(),0,0);'

new = 'case AST_INDEX:{Var* v=get_var(n->index_expr.object->ident.name);if(!v)return LLVMConstInt(LLVMInt64Type(),0,0);if(v->is_str){LLVMValueRef idx=codegen_expr(n->index_expr.index);LLVMValueRef gep=LLVMBuildGEP2(builder,LLVMInt8Type(),v->ptr,&idx,1,"stridx");return LLVMBuildZExt(builder,LLVMBuildLoad2(builder,LLVMInt8Type(),gep,"sc"),LLVMInt64Type(),"ext");}if(!v->is_list)return LLVMConstInt(LLVMInt64Type(),0,0);'

content = content.replace(old, new)

with open('codegen.c', 'w') as f:
    f.write(content)
print("Done")
