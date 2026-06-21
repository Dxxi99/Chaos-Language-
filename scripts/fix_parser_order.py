with open('parser.c', 'r') as f:
    content = f.read()

# struct_names와 is_struct_type을 맨 위로 추출
# 현재 위치 찾기
import re

# 맨 앞에 이동할 코드
move_code = '''static char* struct_names[32];
static int struct_name_count = 0;
static int is_struct_type(const char* name) {
    for (int i = 0; i < struct_name_count; i++)
        if (strcmp(struct_names[i], name) == 0) return 1;
    return 0;
}
'''

# 원래 선언 제거
content = content.replace(''static char* struct_names[32];
static int struct_name_count = 0;
static int is_struct_type(const char* name) {
    for (int i = 0; i < struct_name_count; i++)
        if (strcmp(struct_names[i], name) == 0) return 1;
    return 0;
}
', '')

# includes 다음에 삽입
content = content.replace('#include <string.h>', '#include <string.h>\n\n' + move_code)

with open('parser.c', 'w') as f:
    f.write(content)
print("Done")
