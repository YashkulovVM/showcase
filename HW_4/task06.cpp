#include "student.h"

int solveProblem(list_node* head)
{
	int flag = 0, i = 0;
	list_node *current, *next;
	for(current = head; (next = current->get_next()); current = next)
	{			
		if(*current == *next)
		{
			if(!flag)
			{
				flag = 1;
				i++;
			}
		}
		else
			flag = 0;
	}
	return i;
}