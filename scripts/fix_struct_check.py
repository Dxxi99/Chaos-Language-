with open('codegen.c', 'r') as f:
    content = f.read()

# codegen이 아니라 parser.c 수정 필요
print("Need to fix parser.c - append is treated as struct")
