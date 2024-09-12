# Compiler flags
CFLAGS = $(INCLUDE_PATH) -std=c99

# Specify the target executable
TARGET = build/main

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

build/lexer.o: parser.c parser.h
	gcc -c parser.c $(CFLAGS) -o build/parser.o

# Add a clean target for convenience
clean:
	rm -f build/*.o $(TARGET)

.PHONY: all clean
