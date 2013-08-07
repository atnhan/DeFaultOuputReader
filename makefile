# The compiler
CC = g++

# Compiler flags
# -g3 for debugging; -O6 for optimization (release version)
# -Wall to turn on most, but not all, compiler warnings
CFLAGS = -std=c++11 -O6 -Wall

# The build target executable
TARGET = read-default

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).cpp

clean:
	$(RM) $(TARGET)