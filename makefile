# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Default target
default: main.out

# Compile main.cpp and HashTable.cpp into an executable
main.out: main.cpp HashTable.cpp
	$(CXX) $(CXXFLAGS) -o main.out main.cpp

# Clean up generated files
clean:
	rm -f main.out
