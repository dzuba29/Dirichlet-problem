COMPILER = g++

FLAGS = -std=c++0x -Wall -Wextra -Wpedantic -fopenmp 


OS := $(shell uname)
ifeq ($(OS),Darwin)
	COMPILER = g++-8
endif

ifdef SYSTEMROOT
    RM = del /Q
else
    RM = rm -f
endif


default: all

all: clean main.o matrix.o functions.o dirichlet.o
	$(COMPILER) $(FLAGS) main.o functions.o matrix.o dirichlet.o -o main

main.o: 
	$(COMPILER) -c $(FLAGS) main.cpp -o main.o

functions.o: 
	$(COMPILER) -c $(FLAGS) functions.cpp -o functions.o

matrix.o:
	$(COMPILER) -c $(FLAGS) ./matrix.cpp -o matrix.o


dirichlet.o:
	$(COMPILER) -c $(FLAGS) ./dirichlet.cpp -o dirichlet.o
clean:
	$(RM) *.o main all