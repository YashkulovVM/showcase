#ifndef LIST2_H
#define LIST2_H
#include "student.h"

class list2_node : public student
{//a.get_next() p_a->get_next() <=> (*p_a).get_next()
private:
	list2_node * next = nullptr;
	list2_node * prev = nullptr;
public:
	list2_node() = default;
	~list2_node() = default;
	list2_node(const list2_node& x) = delete;
	list2_node(list2_node&& x);
	list2_node& operator=(const student& x) = delete;
	list2_node& operator=(list2_node&& x);
	int operator> (const list2_node& x) const
	{
		return (cmp (x) > 0 ? 1 : 0);
	}
	int operator< (const list2_node& x) const
	{
		return (cmp (x) < 0 ? 1 : 0);
	}
	int operator== (const list2_node& x) const
	{
		return (cmp (x) == 0 ? 1 : 0);
	}
	int operator>= (const list2_node& x) const
	{
		return (cmp (x) >= 0 ? 1 : 0);
	}
	int operator<= (const list2_node& x) const
	{
		return (cmp (x) <= 0 ? 1 : 0);
	}
	int cmp(const list2_node& x) const
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
	list2_node* get_next(){return next;}
	list2_node* get_prev(){return prev;}
friend class list2;
};

class list2
{
private:
	list2_node * head = nullptr;
public:
	list2() = default;
	~list2()
	{//То же, что старый delete_list
		list2_node *current, *next;
		for(current = head; current; current = next)
		{
			next = current->get_next();
			delete current;
		}
	}
	list2(const list2& x) = delete;
	list2(list2&& x) = delete;
	io_status read (FILE *fp = stdin, unsigned int max_read = -1);
	void print (unsigned int r = 10, FILE *fp = stdout);
	unsigned int get_length ();
	void popOne(list2_node* x);
	void popSqnc(list2_node* start, list2_node* end);
	list2_node* jumpTo(unsigned int k);
	list2_node* shift(int k); //циклический сдвиг на k (k < 0 - влево, k > 0 - вправо)
	void solveProblem2(int k);
	void solveProblem3(int k);
	void solveProblem5(int k);
	void solveProblem6(int k);
	void solveProblem7(int k);
};

#endif