CFLAGS = -O3 -mfpmath=sse -fstack-protector-all -g -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual -Wno-suggest-attribute=format -DM=10
all: a01.out a02.out a03.out a04.out a05.out a06.out a07.out a08.out a10.out clear
a%.out: task%.o array.o
	g++ -g $(CFLAGS) $^ -o $@
task%.o: task%.cpp data.h makros.h array.h
	g++ -c $(CFLAGS) $<
array.o: array.cpp array.h makros.h data.h
	g++ -c $(CFLAGS) $<
clear:
	rm -f array.o task01.o task02.o task03.o task04.o task06.o task05.o task07.o task08.o task09.o task10.o
clearAll:
	rm -f compare.o array.o task01.o task02.o task03.o task04.o task06.o task05.o task07.o task08.o task09.o task10.o a01.out a02.out a03.out a04.out a05.out a06.out a07.out a08.out a09.out a10.out
