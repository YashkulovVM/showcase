#include "student_array.h"
#include <time.h>

void solveProblem6(student* a, int n)
{
	int i = 0, j = 0, k = 0;
	student buf;
	for(i = 1; i < n; i++)
	{
		j = 0;
		while(a[j] < a[i])
		{
			j++;
		}
		buf = (student&&)a[i];
		for(k = i; k > j; k--)
		{
			a[k] = (student&&)a[k - 1];
		}
		a[j] = (student&&)buf;
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
	solveProblem6(a, n);
	time = (clock_t() - time) / CLOCKS_PER_SEC;

	printf("New array:\n");
	printArray(a, n, p);
	dif = diff(a, n);
	printf ("%s : Task = %d Diff = %d Elapsed = %.2f\n", argv[0], 6, dif, time);
	delete [] a;
	return 0;
}