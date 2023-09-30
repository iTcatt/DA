FLAGS = -Wall -Waddress -Wextra -Werror -g

.PHONY: all clean simple build gen

all: build

build:
	g++ $(FLAGS) main.cpp -o main

simple:
	g++ $(FLAGS) simple.cpp -o simple

gen:
	go build -o generator generator.go

test: gen build simple
	./generator 1000 100000
	./main < gen.txt > out.txt
	./simple < gen.txt >> out.txt
	./generator 1000 500000
	./main < gen.txt >> out.txt
	./simple < gen.txt >> out.txt
	./generator 1000 1000000
	./main < gen.txt >> out.txt
	./simple < gen.txt >> out.txt

clean:
	rm main *.exe out.txt gen.txt