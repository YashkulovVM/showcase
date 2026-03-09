#ifndef LIST_H
#define LIST_H
#include "student.h"
class list_node : public student
{
private:
	list_node * next = nullptr;
public:
	list_node() = default;
	list_node(const char* newname, int newvalue)
	{
		this->init(newname, newvalue);
	} 
	~list_node() = default;
	list_node(const list_node& x) = delete;
	list_node(list_node&& x);
    list_node* get_next(){return next;}
friend class list;
};

class list
{
private:
list_node * head = nullptr;
public:
	list() = default;
	~list()
    {
        list_node *current, *next;
        for(current = head; current; current = next)
        {
            next = current->get_next();
            delete current;
        }
    }
	list(const list& x) = delete;
	list(list&& x) = delete;
	io_status read (FILE *fp = stdin, unsigned int max_read = -1);
	void print (unsigned int r = 10, FILE *fp = stdout);
	unsigned int get_length ();
	list_node* get_tail();
	void swap(list& x);
	void popNext(list_node* x);
	void addNext(list_node* x, list_node* newnode);
	void pushback(list_node* x);
	void popfront();
	void newHead(list_node* x);
	void newTail(list_node* tail, list_node* x);
	void insertX(list_node* x);
	void pushsqnc(list_node* x);
	list_node* cut(list_node* x, unsigned int len);
	void bubbleSort();
	list_node* findPrevOfMin();
	void selectionSort();
	void insertionSort();
	void mergeSort();
	void merge(list& A, list& B);
	int diff();
};
#endif