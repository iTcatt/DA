FLAGS = -Wall -Waddress -Wextra -Werror -g

.PHONY: all clean simple build gen

all: build

build:
	g++ $(FLAGS) main.cpp -o main

simple:
	g++ $(FLAGS) simple.cpp -o simple

gen:
	go build -o generator generator.go

clean:
	rm main simple *.exe gen.txt