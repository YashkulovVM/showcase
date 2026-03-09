// #include <stdio.h>

// #include "student.h"
#include "student_array.h"
#include "time.h"

int solveProblem1(student* array, int size, student& x)
{
    int head = 0, tail = size, mid;
    while(head != tail)
    {   
        mid = (head + tail)/2;
        if(x > array[mid])
            head = mid + 1;
        else
            tail = mid;
    }
    return head;
}

int main(int argc, char** argv)
{
	double time;
	int n, p, s;
	int dif, res, value;
	char* filename, *name;
	io_status errorstatus;
    
	if(((argc == 7 && sscanf(argv[5], "%d", &s) == 1 && !s)
	||  (argc == 6 && sscanf(argv[5], "%d", &s) == 1 && s > 0 && s < 5)) && sscanf(argv[2], "%d", &value) == 1 && sscanf(argv[3], "%d", &n) == 1 && n >= 0
	&& sscanf(argv[4], "%d", &p) == 1 && p >= 0 && sscanf(argv[5], "%d", &s) == 1 && s >= 0)
	{
		name = argv[1];
	}
	else
	{
		printf("Usage: name value n p s filename\n");
		return static_cast<int>(io_status::format);
	}

	student x;
	errorstatus = fillOne(&x, name, value);
	if(errorstatus != io_status::success)
	{
		printf("Cannot allocate memory\n");
		return static_cast<int>(errorstatus);
	}

	student* a = new student [n];

	if(!a)
	{
		printf("Cannot allocate memory\n");
		return static_cast<int>(io_status::memory);
	}
	if(!s)
	{
		filename = argv[6];
		errorstatus = importFromFile(a, n, filename);

		if (errorstatus != io_status::success)
		{
			delete [] a;
			return static_cast<int>(errorstatus);
		}
	}
	else
	{
		errorstatus = formulaeFill(a, n, s);
		if (errorstatus != io_status:: success)
		{
			delete [] a;
			return static_cast<int>(errorstatus);
		}
	}
	printf("Array:\n");
	printArray(a, n, p);

	time = clock_t();
	res = solveProblem1(a, n, x);
	time = (clock_t() - time) / CLOCKS_PER_SEC;


	dif = diff(a, n);
	printf ("%s : Task = %d Diff = %d Res = %d Elapsed = %.2f\n", argv[0], 1, dif, res, time);
	delete [] a;
	return 0;
}