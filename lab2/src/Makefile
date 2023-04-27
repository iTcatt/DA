FLAGS = -Wall -Werror -Wextra -g

all: build run

build: main.cpp
	g++ $(FLAGS) main.cpp -o main

run: 
	./main < input.txt > out.txt

valgrind: build
	valgrind ./main < input.txt

clean: 
	rm *.o main