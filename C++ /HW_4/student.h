#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifndef STUDENT_H
#define STUDENT_H
#define LEN	1024

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
		void print () const
		{
			printf ("%s %d\n", name, value);
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
		io_status init (const char * n, int v);
};
class list2_node : public student
{
private:
	list2_node * next = nullptr;
	list2_node * prev = nullptr;
public:
	list2_node() = default;
	~list2_node() = default;
	list2_node(const list2_node& x) = delete;
friend class list2;
};

class list2
{
private:
list2_node * head = nullptr;
public:
	list2() = default;
	~list2(){}
	list2(const list2& x) = delete;
	list2(list2&& x) = delete;
	int read (FILE *fp = stdin, unsigned int max_read = -1);
	void print (unsigned int r = 10, FILE *fp = stdout);
	unsigned int get_length ();
};
#endif
