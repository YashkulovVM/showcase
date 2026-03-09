#include "student_array.h"

int createValue(int n, int s, int i)
{

    switch(s)
    {
        case 1: return i;
        case 2: return n - i;
        case 3: return i/2;
        case 4: return n - i/2;
    }
    return -1;
}

io_status importFromFile(student* array, int size, char* filename)
{
    io_status errorflag = io_status::success;
    FILE * fp = fopen(filename, "r");
    if(!fp) return io_status::readnt;
    for(int i = 0; i < size; i++)
    {
        errorflag = array[i].read(fp);
        if(errorflag != io_status::success)
        {
            fclose(fp);
            return errorflag;
        }
    }
    fclose(fp);
    return errorflag;
}

io_status formulaeFill(student* array, int size, int formulae)
{
    io_status errorstatus = io_status::success;
    const char* newname = "Student";
    for(int i = 0; i < size; ++i)
    {
        errorstatus = array[i].init(newname, createValue(size, formulae, i + 1));
        if(errorstatus != io_status::success) return errorstatus;
    }
    return io_status::success;
}

void printArray(student* array, int size, int p)
{
    for(int i = 0; i < (size < p ? size : p); ++i)
    {
        array[i].print();
    }
}

int diff(student* a, int n)
{
	int k = 0;
	if(n < 2)
	{ return 0;}
	for(int i = 1; i < n; i++)
	{
		if(a[i] < a[i - 1])
		{
			k++;
		}
	}
	return k;
}
