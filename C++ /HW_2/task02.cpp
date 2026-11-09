#include "student_array.h"
#include <time.h>

void solveProblem2(student* a, int n, student* b, int m, student* c)
{
	int i = 0, j = 0, k = 0;
	while((i < n) && (j < m))
	{
		if(a[i] < b[j])
		{
			c[k] = (student&&)(a[i]);
			i++;
			k++;
		}
		else
		{
			c[k] = (student&&) (b[j]);
			j++;
			k++;
		}
	}
	while(i < n)
	{
		c[k++] = (student&&) a[i++];
	}
	while(j < m)
	{
		c[k++] = (student&&) b[j++];
	}
}

int main(int argc, char** argv)
{
	double time;
	int dif;
	char* filename_a, * filename_b;
	int n, pa, sa, m, pb, sb, filenamePosAdjust = 4;
	io_status errorstatus;
	if((argc != 9 && argc != 8 && argc != 7) || sscanf(argv[1], "%d", &n) != 1 || n < 0|| sscanf(argv[2], "%d", &pa) != 1 || pa < 0
		|| sscanf(argv[3], "%d", &sa) != 1 || sa < 0 || sa > 4 || (!sa && argc != 8))
	{
		printf("Usage: n pa sa filename_a m pb sb filename_b\n");
		return static_cast<int>(io_status::format);
	}
	student* a = new student [n];
	if(!a)
	{
		return static_cast<int>(io_status::memory);
	}
	if(!sa)
	{
		filename_a = argv[4];
		errorstatus = importFromFile(a, n, filename_a);
		if(errorstatus != io_status::success)
		{ 

			delete [] a;
			return static_cast<int>(errorstatus);
		}
		filenamePosAdjust = 5;
	}
	else
	{
		errorstatus = formulaeFill(a, n, sa);
		if (errorstatus != io_status:: success)
		{
			delete[] a;
			return static_cast<int>(errorstatus);
		}
	}
	printf("Array_a:\n");
	printArray(a, n, pa);

	if( sscanf(argv[filenamePosAdjust], "%d", &m) != 1 || m < 0 || sscanf(argv[filenamePosAdjust], "%d", &pb) != 1 || pb < 0 || sscanf(argv[filenamePosAdjust], "%d", &sb) != 1 || sb < 0 || sb > 4
	|| (!sb && argc != 9))
	{
		printf("Usage: n pa sa filename_a m pb sb filename_b\n");
		delete[] a;
		return static_cast<int>(io_status::format);
	}
	student* b = new student [m];
	if(!b)
	{
		printf("Cannot allocate memory\n");
		delete [] a;
		return static_cast<int>(errorstatus);
	}
	if(!sb)
	{
		filename_b = argv[filenamePosAdjust + 3];
		errorstatus = importFromFile(b, m, filename_b);
		if(errorstatus != io_status::success)
		{ 

			delete[] a;
			delete[] b;
			return static_cast<int>(errorstatus);
		}
	}
	else
	{
		errorstatus = formulaeFill(b, m, sb);
		if (errorstatus != io_status::success)
		{

			delete[] a;
			delete[] b;
			return static_cast<int>(errorstatus);
		}
	}
	printf("Array_b:\n");
	printArray(b, m, pb);

	student* c = new student [n + m];
	if(!c)
	{
		printf("Cannot allocate memory\n");
		delete[] a;
		delete[] b;
		return static_cast<int>(errorstatus);
	}
	time = clock_t();
	solveProblem2(a, n, b, m, c);
	time = (clock_t()- time) / CLOCKS_PER_SEC;
	printf("New array:\n");
	printArray(c, n + m, pa + pb);
	dif = diff(c, n + m);
	printf ("%s : Task = %d Diff = %d Elapsed = %.2f\n", argv[0], 2, dif,  time);
	delete [] a;
	delete [] b;
	delete [] c;
	return 0;
}