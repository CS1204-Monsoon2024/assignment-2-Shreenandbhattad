# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Targets
TARGET = main
SRCS = main.cpp HashTable.cpp

# Default target for compiling
default: $(TARGET)

# Compile the source files into an executable
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET).out $(SRCS)

# Clean up generated files
clean:
	rm -f *.out
