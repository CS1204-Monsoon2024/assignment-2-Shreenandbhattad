# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Target and source files
TARGET = main
SRCS = main.cpp

# Default target
default: $(TARGET)

# Compile and link the executable
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET).out $(SRCS)

# Clean up
clean:
	rm -f *.out
