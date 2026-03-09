compilerflags=-mfpmath=sse -fstack-protector-all -g -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual -Wno-suggest-attribute=format -msse


all: a01.out a02.out a03.out a05.out a06.out a07.out

a%.out: list2.o main.o student.o
	g++ $^ -o $@

list2.o: list2.cpp list2.h student.h
	g++ $(compilerflags) -c $<

main.o: main.cpp list2.h student.h
	g++ $(compilerflags) -c $<

student.o: student.cpp student.h
	g++ $(compilerflags) -c $<

.PHONY: clean cleanAll

clean:
	rm -f *.o *.gch

cleanAll:
	rm -f *.o *.gch *.out
