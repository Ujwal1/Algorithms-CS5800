# Compiler settings
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

# Source files
SRCS = RedBlackTree.cpp treeTest.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable
EXEC = treeTest

# Default target
all: $(EXEC)

# Link object files to create executable
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compile source files to object files
%.o: %.cpp RedBlackTree.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up object files and executable
clean:
	rm -f $(OBJS) $(EXEC)
