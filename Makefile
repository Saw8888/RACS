# Compiler flags
CFLAGS = $(INCLUDE_PATH) -std=c99 -g

# Specify the target executable
TARGET = build/main.exe

# Specify the object files
OBJECTS = build/main.o build/lexer.o build/parser.o

# Default target
all: $(TARGET)

$(TARGET): $(OBJECTS)
	gcc $(OBJECTS) $(CFLAGS) -o $(TARGET)

# Here we define the individual object files and their dependencies
build/main.o: main.c
	gcc -c main.c $(CFLAGS) -o build/main.o

build/lexer.o: lexer.c lexer.h
	gcc -c lexer.c $(CFLAGS) -o build/lexer.o

build/parser.o: parser.c parser.h
	gcc -c parser.c $(CFLAGS) -o build/parser.o

# Clean target for Windows
clean:
	del /Q build\*.o
	del /Q build\main.exe

.PHONY: all clean
