# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Default target
default: HashTable.out

# Compile HashTable.cpp into an executable
HashTable.out: HashTable.cpp
	$(CXX) $(CXXFLAGS) -o HashTable.out HashTable.cpp

# Clean up generated files
clean:
	rm -f HashTable.out
