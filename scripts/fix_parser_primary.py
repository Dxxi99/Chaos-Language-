with open('parser.c', 'r') as f:
    content = f.read()

# 대문자 체크 부분 찾기
old = "if (name[0] >= 'A' && name[0] <= 'Z')"

new = "if ((name[0] >= 'A' && name[0] <= 'Z') || is_struct_type(name))"

content = content.replace(old, new)

with open('parser.c', 'w') as f:
    f.write(content)
print("Done")
