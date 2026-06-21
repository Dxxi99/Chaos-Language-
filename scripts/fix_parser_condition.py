with open('parser.c', 'r') as f:
    content = f.read()

old = "if ((name[0] >= 'A' && name[0] <= 'Z') || is_struct_type(name))"

new = "if (is_struct_type(name))"

content = content.replace(old, new)

with open('parser.c', 'w') as f:
    f.write(content)
print("Done")
