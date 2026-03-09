#include "student.h"

int solveProblem(list_node* head)
{
	int i = 0;
	student* max = head;
	list_node *current;
	for(current = head; current; current = current->get_next())
	{
		if(*max < *current)
		{
			max = current;
			i = 1;
		}
		else if(*max == *current)
			i++;
	}
	return i;
}