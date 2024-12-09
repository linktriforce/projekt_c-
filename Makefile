# Define the compiler and the linker. The linker must be defined since
# the implicit rule for linking uses CC as the linker. g++ can be
# changed to clang++.
CXX = /usr/bin/g++
CC  = $(CXX)

# Directories for object files and dependency files
OBJ_DIR = build
DEP_DIR = deps

# Ensure the object and dependency directories exist
$(shell mkdir -p $(OBJ_DIR) $(DEP_DIR))

# Generate dependencies in *.d files
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEP_DIR)/$*.d

# Define preprocessor, compiler, and linker flags. Uncomment the # lines
# if you use clang++ and wish to use libc++ instead of GNU's libstdc++.
# -g is for debugging.
CPPFLAGS =  -std=c++11 -I.
CXXFLAGS =  -O0 -Wall -Wextra -pedantic-errors -Wold-style-cast #No optimization activated (-O0). -O2 is with optimization
CXXFLAGS += -std=c++11
CXXFLAGS += -g
CXXFLAGS += $(DEPFLAGS)
LDFLAGS =   -g 
CXXFLAGS += -fsanitize=address
LDFLAGS += -fsanitize=address

# Targets
PROGS = $(OBJ_DIR)/main $(OBJ_DIR)/preprocessor

all: $(PROGS)

test_wordle_solver: test_wordle_solver.o wordle_solver.o

main: main.o wordle_solver.o

preprocessor: $(OBJ_DIR)/preprocessor.o

# Targets rely on implicit rules for compiling and linking

# Phony targets
.PHONY: all test clean distclean

# Standard clean
clean:
	rm -f $(OBJ_DIR)/*.o $(PROGS)

distclean: clean
	rm -f $(DEP_DIR)/*.d

# Include the *.d files
SRC = $(wildcard *.cc)
-include $(SRC:.cc=$(DEP_DIR)/.d)

# Rule for building object files and placing them in OBJ_DIR
$(OBJ_DIR)/%.o: %.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@
