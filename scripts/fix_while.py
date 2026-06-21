with open('codegen.c', 'r') as f:
    content = f.read()

old = "LLVMBuildCondBr(builder,LLVMBuildICmp(builder,LLVMIntNE,codegen_expr(n->while_stmt.cond),LLVMConstInt(LLVMInt64Type(),0,0),\"wcond\"),b,e);"

new = "LLVMBuildCondBr(builder,LLVMBuildICmp(builder,LLVMIntNE,LLVMBuildZExt(builder,codegen_expr(n->while_stmt.cond),LLVMInt64Type(),\"ext\"),LLVMConstInt(LLVMInt64Type(),0,0),\"wcond\"),b,e);"

content = content.replace(old, new)

with open('codegen.c', 'w') as f:
    f.write(content)
print("Done")
