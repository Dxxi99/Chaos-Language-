CC = gcc
CFLAGS = -Wall -g -I/opt/homebrew/Cellar/llvm@18/18.1.8/include
LDFLAGS = -L/opt/homebrew/Cellar/llvm@18/18.1.8/lib
LLVM_LIBS = -lLLVM-18

SRC = main.c lexer.c parser.c codegen.c
OBJ = $(SRC:.c=.o)
TARGET = chaos

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LLVM_LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJ) $(TARGET) *.ll
