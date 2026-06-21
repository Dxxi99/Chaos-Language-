with open('codegen.c', 'r') as f:
    content = f.read()

old = 'case TOK_GT:return LLVMBuildICmp(builder,LLVMIntSGT,l,r,"gt");'

new = 'case TOK_GT:return LLVMBuildICmp(builder,LLVMIntSGT,l,r,"gt");case TOK_LT_EQ:return LLVMBuildICmp(builder,LLVMIntSLE,l,r,"le");case TOK_GT_EQ:return LLVMBuildICmp(builder,LLVMIntSGE,l,r,"ge");'

content = content.replace(old, new)

with open('codegen.c', 'w') as f:
    f.write(content)
print("Done")
