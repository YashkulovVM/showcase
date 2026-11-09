compilerflags=-O3 -mfpmath=sse -fstack-protector-all -g -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual -Wno-suggest-attribute=format -msse


all: a.out

a.out: student.o tree.o main.o
	g++ $^ -o $@

tree.o: tree.cpp tree.h student.h
	g++ $(compilerflags) -c $<

student.o: student.cpp student.h
	g++ $(compilerflags) -c $<
	
main.o: main.cpp tree.h student.h
	g++ $(compilerflags) -c $<

.PHONY: clean cleanAll

clean:
	rm -f *.o *.gch

cleanAll:
	rm -f *.o *.gch *.out
