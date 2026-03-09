#include "student_array.h"
#include <time.h>


int solveProblem3(student* a, int n, int m)
{
	int i =  0;
	int j = n - 1;
	while(i < j)
	{
		while(!(a[i] > a[m]) && i < m)
			i++;
		while(!(a[j] < a[m]) && m < j)
			j--;
		if(a[i] > a[j])
			a[i].swap(a[j]);
		if(i == m)
		{
			m = j;
			i++;
		}
		else if(j == m)
		{
			m = i;
			j--;
		}
		else
		{
			j--; 
			i++;
		}
	}
	return m;
}


int main(int argc, char *argv[])
{
	double time;
	int dif, res, n, m, s, p;
	char* filename;
	io_status errorstatus;
	if((argc != 5 && argc != 6) || sscanf(argv[1], "%d", &m) != 1 || m < 0
		|| sscanf(argv[2], "%d", &n) != 1 || n < 0 || sscanf(argv[3], "%d", &p) != 1 || p < 0 || sscanf(argv[4], "%d", &s) != 1 || s < 0 || s > 4 || (!s && argc != 6))
	{
		printf("Usage: m n p s filename2\n");
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
		filename = argv[5];
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
	res = solveProblem3(a, n, m);
	time = (clock_t() - time) / CLOCKS_PER_SEC;

	printf("New array:\n");
	printArray(a, n, p);

	dif = diff(a, n);

	printf ("%s : Task = %d Diff = %d Res = %d Elapsed = %.2f\n", argv[0], 3, dif, res, time);

	delete [] a;
	return 0;
}