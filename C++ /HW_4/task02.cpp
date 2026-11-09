#include "student.h"

int solveProblem(list_node* head)
{
	int i = 0;
	list_node *current, *next;
	for(current = head; (next = current->get_next()); current = next)
	{			
		if(*current < *next)
			i++;
	}
	return i;
}