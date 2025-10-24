# C++ compiler & flags
CXX = g++
CXXFLAGS = -std=c++11 -g

# Build this by default
all: testALU

# Object build rules (pattern rules)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Explicit dependencies
testALU.o: alu.h
alu.o: alu.h

# Link the final executable (no suffix)
testALU: testALU.o alu.o
	$(CXX) $(CXXFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm -f testALU *.o

