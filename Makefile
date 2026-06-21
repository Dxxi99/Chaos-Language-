CC = gcc
CFLAGS = -Wall -g -I/opt/homebrew/Cellar/llvm@18/18.1.8/include -I.
LDFLAGS = -L/opt/homebrew/Cellar/llvm@18/18.1.8/lib
LLVM_LIBS = -lLLVM-18

SRC = main.c lexer.c parser.c symbol_table.c type.c type_checker.c \
      codegen/builder.c codegen/expr.c codegen/cmp.c codegen/stmt.c codegen/type_dispatch.c codegen/core.c

OBJ = main.o lexer.o parser.o symbol_table.o type.o type_checker.o \
      codegen/builder.o codegen/expr.o codegen/cmp.o codegen/stmt.o codegen/type_dispatch.o codegen/core.o

TARGET = chaos

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LLVM_LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET) *.ll
