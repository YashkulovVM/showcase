#ifndef STUDENT_H
#define STUDENT_H
#define LEN 1024
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
enum class io_status
{
	success,
	eof,
	readnt,
	opent,
	format,
	memory,
};
class student
{
private:
    char * name = nullptr;
    int value = 0;
public:
    void swap(student& x);
    student () = default;
    student (const student& x) = delete;
    student (student&& x)
    {
        name = x.name; x.name = nullptr;
        value = x.value; x.value = 0;
    }
    ~student ()
    {
        erase ();
    }
    student& operator= (const student& x) = delete;
    student& operator= (student&& x)
    {
        if (this == &x)
            return *this;
        erase ();
        name = x.name; x.name = nullptr;
        value = x.value; x.value = 0;
        return *this;
    }
    void print (FILE * fp = stdout) const
		{
			fprintf (fp, "%s %d\n", name, value);
		}
    io_status read (FILE * fp);
    int cmp (const student& x) const
    {
        if (name == nullptr)
    {
        if (x.name != nullptr)
        return 1;
        return value - x.value;
    }
    if (x.name == nullptr)
        return -1;
    int res = strcmp (name, x.name);
    if (res)
        return res;
    return value - x.value;
    }
    int operator< (const student& x) const { return cmp (x) < 0; }
    int operator<= (const student& x) const { return cmp (x) <= 0; }
    int operator> (const student& x) const { return cmp (x) > 0; }
    int operator>= (const student& x) const { return cmp (x) >= 0; }
    int operator== (const student& x) const { return cmp (x) == 0; }
    int operator!= (const student& x) const { return cmp (x) != 0; }
private:
    io_status init (const char * n, int v);
    void erase()
		{
			value = 0;
			if (name != nullptr)
			{
				delete [] name;
				name = nullptr;
			}
		}
};
#endif