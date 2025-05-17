# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++11 -Wall -Iinclude -O3
MAKE := make
# Source files
SRCS :=  $(wildcard *.cpp)\
$(wildcard src/*.cpp)
OBJS := $(SRCS:.cpp=.o)

# Output executable
TARGET := app

all:
	@$(MAKE) build 2>&1 | tee logging/build.log

# Default target
build: $(TARGET)

# Link object files into executable
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

# Compile each .cpp into .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	clear
	@./$(TARGET) | tee logging/run.log

# Clean
clean:
	rm -f $(OBJS) $(TARGET)
	rm logging/*.log

.PHONY: all clean