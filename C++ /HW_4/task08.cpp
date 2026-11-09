#include "student.h"

int solveProblem(list_node* head)
{
	int flag = 0, i = 0, max = 0;
	list_node *current, *next;
	for(current = head; (next = current->get_next()); current = next)
	{
		if(*current == *next)
		{
			i++;
			continue;
		}
		if(*current > *next)
		{
			if(flag != 2)
			{
				if(flag == 1)
				{
					if(i > max)
						max = i;					
					i = 2; flag = 2;				
				}
				else
				{
					i += 2; flag = 2;
				}
			}
			else
				i++;
			continue;
		}
		if(flag != 1)
		{
			if(flag == 2)
			{
				if(i > max)
					max = i;
				i = 2; flag = 1;
			}
			else
			{
				i += 2; flag = 1;
			}
		}
		else
			i++;
	}
	if(!flag)
		i++;
	if(i > max)
		max = i;
	return max;
}