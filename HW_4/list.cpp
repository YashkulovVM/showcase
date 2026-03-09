#include "list.h"
io_status read_list(const char *name, list_node **head)
{
	io_status ret;
	list_node *first = nullptr, *current = nullptr, *next = nullptr;
	FILE* fp;
	fp = fopen(name, "r");
	if(!fp)
	{
		return io_status:: opent;
	}
	first = new list_node;
	if(!first)
	{
		fclose(fp);
		return io_status:: memory;
	}
	ret = first->read(fp);
	if(ret != io_status:: success)
	{
		delete first;
		fclose(fp);
		return ret;
	}
	first->set_next(nullptr);
	current = first;
	while(!feof(fp))
	{
		if(!(next = new list_node))
		{
			delete_list(first);
			fclose(fp);
			return io_status:: memory;
		}
		ret = next->read(fp);
		if(ret != io_status:: success)
		{
			delete_list(first);
			fclose(fp);
			return ret;
		}
		next->set_next(nullptr);
		current->set_next(next);
		current = next;		
	}
	if(!feof(fp))
	{
		delete_list(first);
		fclose(fp);
		return io_status:: readnt;
	}
	fclose(fp);
	*head = first;
	return io_status:: success;
}
void print_list(int p, list_node* head)
{
	list_node *current = head;
	for(int i = 0; i < p && current; current = current->get_next(), i++)
	{
		printf("%s	%d\n", current->get_name(), current->get_value());
	}
}
void delete_list(list_node* head)
{
	list_node *current, *next;
	for(current = head; current; current = next)
	{
		next = current->get_next();
		delete current;
	}
}