#makefile

compilerflags=-mfpmath=sse -fstack-protector-all -g -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual -Wno-suggest-attribute=format -msse

all: $(patsubst task%.cpp, a%.out,$(wildcard task*.cpp))
a%.out: task%.o student.o list.o main.o
	g++ $(compilerflags) $^ -o $@
main.o: main.cpp list.h
	g++ -c $(compilerflags) $<
student.o: student.cpp student.h
	g++ -c $(compilerflags) $<
list.o: list.cpp list.h
	g++ -c $(compilerflags) $<
task%.o: task%.cpp student.h
	g++ -c $(compilerflags) $<
clean:
	rm -f *.o
cleanAll:
	rm -f *.out *.o *.bak