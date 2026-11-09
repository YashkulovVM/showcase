#include "student.h"

int solveProblem(list_node* head)
{
	int i = 0;
	list_node *current, *next1, *next2;
	for(current = head; (next1 = current->get_next()) && (next2 = next1->get_next()); current = next1)
	{			
		if(*current <= *next1 && *next1 >= *next2)
			i++;
	}
	return i;
}