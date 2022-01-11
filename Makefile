bf.elf: main.o
	g++ main.o -o $@ $(LDFLAGS) 

main.o: main.cpp brainfuck.hpp
	g++ -MMD -MP -fno-rtti -std=c++20 -Wall -c $< -o $@