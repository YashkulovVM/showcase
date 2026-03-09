#include "student.h"

io_status student::read(FILE * fp)
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

io_status student::init(const char* n, int v)
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

int student::cmp(const student& x) const
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

void student::swap(student& x)
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
        printf("Unexpected eof\n");
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