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

int exitcode(io_status errorstatus);
int taskNum(const char* argv0);

class student
{
	private:
		char * name = nullptr;
		int value = 0;
	public:
		student () = default;
		student (const student& x) = delete;
		student (student&& x)
		{
			name = x.name; x.name = nullptr;
			value = x.value; x.value = 0;
		}
		~student (){erase();}
		int get_value() const {return value;}
		char* get_name() const {return name;}
		void set_value(int v) {value = v;}
		void set_name(char* n) {name = n;}
		student& operator= (const student& x) = delete;
		student& operator= (student&& x)
		{
			if (this == &x)
				{return *this;}
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
		int operator> (const student& x) const
		{
			return (cmp (x) > 0 ? 1 : 0);
		}
		int operator< (const student& x) const
		{
			return (cmp (x) < 0 ? 1 : 0);
		}
		int operator== (const student& x) const
		{
			return (cmp (x) == 0 ? 1 : 0);
		}
		int operator>= (const student& x) const
		{
			return (cmp (x) >= 0 ? 1 : 0);
		}
		int operator<= (const student& x) const
		{
			return (cmp (x) <= 0 ? 1 : 0);
		}
		void swap(student& x);
		io_status init (const char * n, int v);
	private:
		void erase()
		{
			value = 0;
			if (name != nullptr)
			{
				delete [] name;
				name = nullptr;
			}
		}
		int cmp (const student& x) const;
};
#endif