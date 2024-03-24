# Makefile

# Compiler
CC = g++

# Compiler flags
CFLAGS = -std=c++11 -Wall

# Source files
SRCS = main.cpp Token.cpp Grammar.cpp

# Header files
HEADERS = Token.hpp Grammar.hpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Target executable
TARGET = beautifier

# Rule to build the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Rule to build object files
%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule to remove generated files
clean:
	rm -f $(OBJS) $(TARGET)
