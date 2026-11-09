CPPFLAGS = -mfpmath=sse -fstack-protector-all -g -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual -Wno-suggest-attribute=format
all: a01.out a02.out a03.out a04.out a05.out a06.out a07.out clear
a%.out: task%.o student_array.o
	g++ -g $(CPPFLAGS) $^ -o $@
task%.o: task%.cpp student_array.h student.h
	g++ -c $(CPPFLAGS) $<
student_array.o: student_array.cpp student_array.h
	g++ -c $(CPPFLAGS) $<
clear:
	rm -f *.o
clearAll:
	rm -f *.o *.out
