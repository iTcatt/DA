FLAGS = -Wall -Werror -Wextra -g

all: build run

build: main.cpp
	g++ $(FLAGS) main.cpp -o main

run: build
	./main < input.txt > output.txt

valgrind: build
	valgrind ./main < input.txt > output.txt

clean: 
	rm *.o main