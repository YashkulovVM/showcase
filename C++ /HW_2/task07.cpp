#include "student_array.h"
#include <time.h>

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

void solveProblem7(student* a, int n)
{
	int i, j, k = 0;
	student temp;
	if(n > 1)
	{
		for(i = 1; i < n; i++)
		{
			j = solveProblem1(a, i, a[i]);
			temp = (student&&)a[i];
			for(k = i; k > j; k--)
			{
				a[k] = (student&&)a[k - 1];
			}
			a[j] = (student&&)temp;
		}
	}
}


int main(int argc, char** argv)
{
	double time;
	int dif, n, s, p;
	char* filename;
	io_status errorstatus;
	if((argc != 4 && argc != 5) || sscanf(argv[1], "%d", &n) != 1 || n < 0 || sscanf(argv[2], "%d", &p) != 1 || p < 0
		|| sscanf(argv[3], "%d", &s) != 1 || s < 0 || s > 4 || (!s && argc != 5))
	{
		printf("Usage: n p s filename\n");
		return static_cast<int>(io_status::format);
	}

	student* a = new student [n];
	if(!a)
	{
		printf("Cannot allocate memory\n");
		return static_cast<int>(io_status::memory);
	}
	if(!s)
	{
		filename = argv[4];
		errorstatus = importFromFile(a, n, filename);
		if(errorstatus != io_status::success)
		{
			delete [] a;
			return static_cast<int>(errorstatus);
		}
	}
	else
	{
		errorstatus = formulaeFill(a, n, s);
		if (errorstatus != io_status::success)
		{
			delete [] a;
			return static_cast<int>(errorstatus);
		}
	}

	printf("Array:\n");
	printArray(a, n, p);

	time = clock_t();
	solveProblem7(a, n);
	time = (clock_t() - time) / CLOCKS_PER_SEC;
	printf("New array:\n");
	printArray(a, n, p);
	dif = diff(a, n);
	printf ("%s : Task = %d Diff = %d Elapsed = %.2f\n", argv[0], 7, dif, time);
	delete [] a;
	return 0;
}