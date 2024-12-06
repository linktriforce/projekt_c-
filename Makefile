# Define the compiler and the linker. The linker must be defined since
# the implicit rule for linking uses CC as the linker. g++ can be
# changed to clang++.
CXX = /usr/bin/g++
CC  = $(CXX)

# Generate dependencies in *.d files
DEPFLAGS = -MT $@ -MMD -MP -MF $*.d

# Define preprocessor, compiler, and linker flags. Uncomment the # lines
# if you use clang++ and wish to use libc++ instead of GNU's libstdc++.
# -g is for debugging.
CPPFLAGS =  -std=c++11 -I.
CXXFLAGS =  -O2 -Wall -Wextra -pedantic-errors -Wold-style-cast #No optimization activated (-O0). -O2 is with optimization
CXXFLAGS += -std=c++11
CXXFLAGS += -g
CXXFLAGS += $(DEPFLAGS)
LDFLAGS =   -g 
# CXXFLAGS += -fsanitize=address
# LDFLAGS += -fsanitize=address
# CXXFLAGS += -fsanitize=address
# LDFLAGS += -fsanitize=address


#CPPFLAGS += -stdlib=libc++
#CXXFLAGS += -stdlib=libc++
#LDFLAGS +=  -stdlib=libc++

# Targets
PROGS = main test_wordle_solver

all: $(PROGS)

test: test_wordle_solver.o

# Targets rely on implicit rules for compiling and linking
main: main.o wordle_solver.o
test_wordle_solver: test_wordle_solver.o wordle_solver.o

preprocessor: preprocessor.o

# Phony targets
.PHONY: all test clean distclean

# Standard clean
clean:
	rm -f *.o $(PROGS)

distclean: clean
	rm *.d


# Include the *.d files
SRC = $(wildcard *.cc)
-include $(SRC:.cc=.d)
