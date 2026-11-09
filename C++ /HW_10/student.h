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
    halfway,
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
			fprintf (fp, "%s %d ", name, value);
		}
    io_status read(FILE * fp)
    {
        char n[LEN];
        int v;
        if (fscanf (fp, "%s%d", n, &v) != 2)
        {
            if (!feof (fp))
            {
                return io_status::format;
            }
            return io_status::eof;
        }
        erase();
        return init (n, v);
    }
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
		void swap(student& x)
        {
            char* n;
            int v;
            n = name;
            name = x.name;
            x.name = n;
            v = value;
        value = x.value;
            x.value = v;
        }
        int get_length()const {return (name != nullptr ? 1 : 0);}
		io_status init(const char* n, int v)
        {
            value = v;
            if (n != nullptr)
            {
                size_t len = strlen (n);
                name = new char [len + 1];
                if (name != nullptr)
                {
                    for (size_t i = 0; i <= len; i++)
                        name[i] = n[i];
                }
                else
                {
                    return io_status::memory;
                }
            }
            return io_status::success;
        }

    int cmp(const student& x) const
    {
        if (name == nullptr)
        {
            if (x.name != nullptr)
                {return -1;}
            return value - x.value;
        }
        if (x.name == nullptr)
            {return 1;}
        int res = strcmp (name, x.name);
        if (res)
            {return res;}
        return value - x.value;
    }
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
};
int exitcode(io_status errorstatus)
{
    switch (errorstatus)
    {
    case io_status::format:
        printf("Invalid arguments\n");
        break;
    case io_status::memory:
        printf("Cannot allocate memory\n");
        break;
    case io_status::opent:
        printf("Cannot open file\n");
        break;
    case io_status::eof:
        printf("EOF reached\n");
        break;
	case io_status::readnt:
		printf("Cannot read from file\n");
	case io_status::success:
		break;
    default:
        break;
    }
    return static_cast<int>(errorstatus);
}

int taskNum(const char* argv0)
{
    int res = -1;
    if (sscanf(strrchr(argv0, 'a'), "a%d.out", &res) != 1)
        return -1;
    return res;
}
#endif