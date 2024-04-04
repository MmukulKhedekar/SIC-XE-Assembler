files := main.cpp assembler.cpp optab.cpp reg.cpp symtab.cpp tokenization.cpp utils.cpp
CC := g++
CFlags := -Wall -Wextra -Wpedantic -std=c++20 -I../include

build:
	cd src/;\
	$(CC) $(CFlags) $(files) -o ../bin/main;\
	cd ..

run:
	./bin/main