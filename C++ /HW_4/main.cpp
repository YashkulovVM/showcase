#include "list.h"
#include <time.h>

int solveProblem(list_node*);

int main(int argc, char **argv)
{
	double time = 0;
	char *name = 0;
	int  result, p;
	list_node* head;
	io_status errorstatus = io_status::success;

	if(argc != 3 || sscanf(argv[1], "%d", &p) != 1)
	{
		return exitcode(io_status::format);
	}

	name = argv[2];
	errorstatus = read_list(name, &head);

	if(errorstatus != io_status:: success)
	{
		return exitcode(errorstatus);
	}

	printf("List:\n");
	print_list(p, head);

	time = clock();
	result = solveProblem(head);
	time = (clock()- time) / CLOCKS_PER_SEC;

	printf ("%s : Task = %d Result = %d Elapsed = %.2f\n", argv[0], taskNum(argv[0]), result, time);
	delete_list(head);
	return 0;
}