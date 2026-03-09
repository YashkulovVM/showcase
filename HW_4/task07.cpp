#include "student.h"

int solveProblem(list_node* head)
{
	int flag = 2, i = 0, max = 0;
	list_node *current, *next;
	for(current = head; (next = current->get_next()); current = next)
	{			
		if(*current == *next)
		{
			if(!flag)
			{
				flag = 1;
				if(i > max)
					max = i;
				i = 0;
			}
			else if(flag == 2)
				flag = 1;
		}
		else if(flag != 2)
		{
			flag = 0;
			i++;
		}
	}
	if(max)
		max--;
	return max;
}