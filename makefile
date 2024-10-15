# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Default target
default: main.out

# Compile HashTable.cpp into an executable
main.out: HashTable.cpp
	$(CXX) $(CXXFLAGS) -o main.out HashTable.cpp

# Clean up generated files
clean:
	rm -f main.out
