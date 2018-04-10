TARGET = main

COMPILER = g++
FLAGS = -std=c++11 -Wall -Wextra -Wpedantic -fopenmp

OS := $(shell uname)
ifeq ($(OS),Darwin)
	COMPILER = g++-7
endif

ifdef SYSTEMROOT
    RM = del /Q
else
    RM = rm -f
endif

default: $(TARGET)

$(TARGET): main.o matrix.o functions.o dirichlet.o
	$(COMPILER) $(FLAGS) main.o matrix.o functions.o dirichlet.o -o $@

main.o: main.cpp
	$(COMPILER) -c $(FLAGS) main.cpp

functions.o: functions.cpp
	$(COMPILER) -c $(FLAGS) functions.cpp

matrix.o: matrix.cpp
	$(COMPILER) -c $(FLAGS) matrix.cpp

dirichlet.o: dirichlet.cpp
	$(COMPILER) -c $(FLAGS) dirichlet.cpp


clean:
	$(RM) *.o

clean_all:
	$(RM) *.o main