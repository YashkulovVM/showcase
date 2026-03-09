#include "student.h"

int solveProblem(list_node* head)
{
	int i = 0, flag = 0, max = 0;
	list_node *current, *next;
	for(current = head; (next = current->get_next()); current = next)
	{			
		if(*current < *next)
		{
			if(!flag)
			{
				flag = 1;
				i++;
			}
			i++;
		}
		else
		{
			if(i > max)
				max = i;
			i = 0;
			flag = 0;
		}
	}
	if(i > max)
		return i;
	return max;
}