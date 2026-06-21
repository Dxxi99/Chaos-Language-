with open('codegen.c', 'r') as f:
    content = f.read()

old = 'case AST_FUNC_CALL:{\nif(strcmp(n->func_call.name,"readFile")==0){'

new = 'case AST_FUNC_CALL:{\nif(strcmp(n->func_call.name,"append")==0){\nVar* av=get_var(n->func_call.args[0]->ident.name);\nif(av&&av->is_list){\nLLVMTypeRef lty=get_list_type();\nLLVMValueRef dptr=LLVMBuildStructGEP2(builder,lty,av->ptr,0,"dptr");\nLLVMValueRef data=LLVMBuildLoad2(builder,LLVMPointerType(LLVMInt64Type(),0),dptr,"ldata");\nLLVMValueRef lenptr=LLVMBuildStructGEP2(builder,lty,av->ptr,1,"lenptr");\nLLVMValueRef len=LLVMBuildLoad2(builder,LLVMInt64Type(),lenptr,"len");\nLLVMValueRef val=codegen_expr(n->func_call.args[1]);\nLLVMValueRef gep=LLVMBuildGEP2(builder,LLVMInt64Type(),data,&len,1,"idx");\nLLVMBuildStore(builder,val,gep);\nLLVMValueRef newlen=LLVMBuildAdd(builder,len,LLVMConstInt(LLVMInt64Type(),1,0),"newlen");\nLLVMBuildStore(builder,newlen,lenptr);\n}\n}\nif(strcmp(n->func_call.name,"readFile")==0){'

content = content.replace(old, new)

with open('codegen.c', 'w') as f:
    f.write(content)
print("Done")
