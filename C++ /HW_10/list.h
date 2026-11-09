#ifndef list_H
#define list_H
#include "student.h"
#include <algorithm>
class list_node : public student
{//a.get_next() p_a->get_next() <=> (*p_a).get_next()
private:
	list_node * next = nullptr;
	list_node * prev = nullptr;
public:
	list_node() = default;
	~list_node() = default;
	list_node(const list_node& x) = delete;
	list_node(list_node&& x)
    {
        swap(x);
        std::swap(next, x.next);
        std::swap(prev, x.prev);
    }
	list_node& operator=(const student& x) = delete;
	list_node& operator=(list_node&& x)
    {
        if (this == &x)
            {return *this;}
        swap(x);
        std::swap(next, x.next);
        std::swap(prev, x.prev);
        return *this;
    }
	int operator> (const list_node& x) const
	{
		return (cmp (x) > 0 ? 1 : 0);
	}
	int operator< (const list_node& x) const
	{
		return (cmp (x) < 0 ? 1 : 0);
	}
	int operator== (const list_node& x) const
	{
		return (cmp (x) == 0 ? 1 : 0);
	}
	int operator>= (const list_node& x) const
	{
		return (cmp (x) >= 0 ? 1 : 0);
	}
	int operator<= (const list_node& x) const
	{
		return (cmp (x) <= 0 ? 1 : 0);
	}
	int cmp(const list_node& x) const
	{
		char* name1 = get_name();
		char* name2 = x.get_name();
		int value1 = get_value();
		int value2 = x.get_value();
		if (name1 == nullptr)
		{
			if (name2 != nullptr)
				{return -1;}
			return value1 - value2;
		}
		if (name2 == nullptr)
			{return 1;}
		int res = strcmp (name1, name2);
		if (res)
			{return res;}
		return value1 - value2;
	}
	list_node* get_next(){return next;}
	list_node* get_prev(){return prev;}
friend class list;
};

class list
{
private:
	list_node * head = nullptr;
    static int m;
    static int r;
public:
	list() = default;
	~list()
	{//То же, что старый delete_list
		list_node *current, *next;
		for(current = head; current; current = next)
		{
			next = current->get_next();
			delete current;
		}
	}
	list(const list& x) = delete;
	list(list&& x)
    {
        head = x.head;
        x.head = nullptr;
    }
    int operator< (const list& b) const
    {
        if(!head && b.head)
            return 1;
        if(!b.head && head)
            return 0;
        return (*head < *b.head);
    }
    static void set_m (int x) {m = x;}
    static void set_r (int x) {r = x;}
    io_status read(FILE* fp)
    {
        list_node tmp;
        list_node* prev = nullptr;
        list_node** p_current = &head;
        io_status errorstatus = io_status::success;
        int counter = 0;
        if(!fp) 
            return io_status::memory;
        while(counter < m && (errorstatus = tmp.read(fp)) == io_status::success)
        {
            *p_current = new list_node((list_node&&)tmp);
            if(!(*p_current))
                return io_status::memory;
            (*p_current)->prev = prev;
            prev = (*p_current);
            p_current = &((*p_current)->next);
            counter++;
            tmp = list_node{};
        }
        if(counter >= m)
            return io_status::success;
        if(head && errorstatus == io_status::eof)
            return io_status::halfway;
        return errorstatus;
    }
	void print(FILE* fp)
    {
        list_node* current;
        int counter = 0;
        for(current = head; counter != r && current; current = current->next, ++counter)
        {
            current->print(fp);
        }
    }
	unsigned int get_length () const
    {
        list_node* current;
        unsigned int len = 0;
        for(current = head; current; current = current->next)
        {
            len++;
        }
        return len;
    }
};
#endif