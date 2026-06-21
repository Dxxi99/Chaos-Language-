with open('codegen.c', 'r') as f:
    content = f.read()

old_start = content.find('if(strcmp(n->func_call.name,"concat")==0)')
old_end = content.find('}FuncInfo* fi', old_start)
old = content[old_start:old_end+1]

new = 'if(strcmp(n->func_call.name,"concat")==0){return codegen_expr(n->func_call.args[0]);}'

content = content.replace(old, new)

with open('codegen.c', 'w') as f:
    f.write(content)
print("Done")
