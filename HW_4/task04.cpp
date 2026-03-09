#include "student.h"

int solveProblem(list_node* head)
{
	int flag = 4;
	list_node *current, *next;
	for(current = head; (next = current->get_next()); current = next)
	{			
		if(*current < *next)
		{
			if(flag == 4 || flag == 3)
				flag = 1;
			else if(flag == 2)
				return 0;
		}		
		else if(*current > *next)
		{
			if(flag == 4 || flag == 3)
				flag = 2;
			else if(flag == 1)
				return 0;
		}
		else
		{
			if(flag == 4)
				flag = 3;
		}
	}
	return flag;
}