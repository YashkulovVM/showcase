#include "list.h"
#include <utility>

list_node::list_node (list_node&& x)
{
    swap(x);
    std::swap(next, x.next);
}

io_status list::read (FILE *fp, unsigned int max_read)
{
    unsigned int counter = 0;
    list_node tmp;
    list_node** p_current = &head;
    io_status errorstatus = io_status::success; 

    if(!fp)
        return io_status::memory;
    
    while((errorstatus = tmp.read(fp)) == io_status::success && counter != max_read)
    {
        (*p_current) = new list_node((list_node&&)tmp);
        if(!(*p_current))
            return io_status::memory;
        p_current = &((*p_current)->next);
        ++counter;
    }
    return errorstatus;
}
void list::print(unsigned int r, FILE *fp)
{
    list_node* current = head;
    unsigned int i = 0;
    for(current = head; current && i < r; i++, current = current->next)
    {
        (*current).print(fp);
    }
}

unsigned int list::get_length()
{
    unsigned int counter = 0;
    list_node* current = head;
    while(current)
    {
        ++counter;
        current = current->next;
    }
    return counter;
}

void list::swap(list& x)
{
    std::swap(head, x.head);
}

list_node* list::get_tail()
{
    list_node* tail = nullptr;
    list_node* current = nullptr;
    if(head == nullptr)
    {
        return tail;
    }
    for(current = head; current; current = current->next)
    {
        if(current->next == nullptr)
            tail = current;
    }
    return tail;
}

void list::popNext(list_node* x)
{
    if(x->next == nullptr)
        return;
    if(x->next->next == nullptr)
    {
        delete x->next->next;
        x->next = nullptr;
        return;
    }
    x->next = x->next->next;
    delete x->next;
    return;
}
void list::addNext(list_node* x, list_node* newnode)
{
    newnode->next = x->next;
    x->next = newnode;
}
void list::popfront()
{
    list_node* buf;
    buf = head;
    head = head->next;
    delete buf;
    return;
}
void list::pushback(list_node* x)
{
    if(!head)
    {
        head = x;
        return;
    }
    list_node* tail = get_tail();
    if(x == nullptr && tail == nullptr)
    {
        return;
    }
    if(x == nullptr)
    {
        tail->next = nullptr;
        return;
    }
    tail->next = x;
    x->next = nullptr;
    return;
}
void list::newHead(list_node* x)
{
    if(head == nullptr)
    {
        head = x;
        head->next = nullptr;
        return;
    }
    list_node* tmp = nullptr;
    tmp = head;
    head = x;
    x->next = tmp;
    return;
}
void list::newTail(list_node* tail, list_node* x)
{
    if(head == nullptr || tail == nullptr)
    {
        head = x;
        head->next = nullptr;
        return;
    }
    tail->next = x;
    x->next = nullptr;
    return;
}

void list::bubbleSort()
{
    list_node* current = nullptr;
    unsigned int len = get_length();
    list_node* tmp = nullptr;
    list newlist;

    for(; len != 0; len--)
    {
        if(head->next == nullptr)
        {
            newlist.newHead(head);
            head = nullptr;
            break;
        }
        if(*(head) > *(head->next))
        {
            tmp = head;//Для головы
            head = head->next;
            tmp->next = head->next;
            head->next = tmp;
        }
        for(current = head; current && current->next && current->next->next; current = current->next)
        {
            if(*(current->next) > *(current->next->next))
            {
                tmp = current->next;//Для всех, кроме головы
                current->next = current->next->next;
                tmp->next = current->next->next;
                current->next->next = tmp;
            }
        }
        newlist.newHead(std::exchange(current->next, nullptr));
    }
    swap(newlist);
    return;
}

list_node* list::findPrevOfMin()
{
    list_node* current = nullptr, *min = head;
    for(current = head; current && current->next; current = current->next)
    {
        if(*(current->next) <= *min->next)
        {
            min = current;
        }
    }
    return min;
}

void list::selectionSort()
{
    list_node* min = nullptr, *current = nullptr, *tail = nullptr;
    list newlist;
    unsigned int len = get_length();
    if(len == 1)
        return;
    if(len == 2)
    {
        if(*head < *(head->next))
            return;
        else
        {
            min = head;
            head = head->next;
            min->next = nullptr;
            head->next = min;
            return;
        }
    }
    list_node* dummy = new list_node("pudge", 1337);
    dummy->next = head;
    head = dummy;
    for(; len != 1; len--)
    {
        current = findPrevOfMin();
        min = current->next;
        current->next = current->next->next;
        newlist.newTail(tail, min);
        tail = min;
    }
    head = head->next;
    delete dummy;
    swap(newlist);
    return;
}

void list::insertX(list_node* x)
{
    list_node* current = nullptr, *tmp = nullptr;
    if(!head)
    {
        head = x;
        x->next = nullptr;
        return;
    }
    if(*x < *head) //вставка спереди
    {
        tmp = head;
        head = x;
        head->next = tmp;
        return;
    }
    for(current = head; current && current->next;  current = current->next) //вставка между двумя
    {
        if(*x < *(current->next))
        {
            x->next = current->next;
            current->next = x;
            return;
        }
    }
    current->next = x; //вставка в конец
    x->next = nullptr;
    return;
}

void list::insertionSort()
{
    list_node* current = nullptr;
    list newlist;
    if(!head || !(head->next))
        return;
    while(head)
    {
        current = head;
        head = head->next;
        newlist.insertX(current);
    }
    swap(newlist);
    return;
}

list_node* list::cut(list_node* x, unsigned int len)
{
    list_node* current = x, *res = nullptr;
    for(unsigned int i = 0; i < len - 1 && current && current->next; i++)
    {
        current = current->next;
    }
    if(!current)
    {
        return nullptr;
    }
    res = current->next;
    current->next = nullptr;
    return res;
}

void list::pushsqnc(list_node* x)
{
    if(!head)
    {
        head = x;
        return;
    }
        list_node* newtail = get_tail();
        newtail->next = x;
        return;
}

void list::merge(list& A, list& B)
{
    list_node* start = new list_node("pudge", 1337);
    list_node* newhead = start;
    while(A.head && B.head)
    {
        if(*A.head < *B.head)
        {
                newhead->next = A.head;
                A.head = A.head->next;
        }
        else
        {
                newhead->next = B.head;
                B.head = B.head->next;
        }
        newhead = newhead->next;
    }
    if(A.head)
        {
            newhead->next = A.head;
            A.head = nullptr;
        }
    if(B.head)
        {
            newhead->next = B.head;
            B.head = nullptr;
        }
    pushsqnc(start->next);
    delete start;
    return;
}


void list::mergeSort()
{
    if(!head || !(head->next))
        return;
    list_node* currentA = nullptr, * currentB = nullptr;
    list newlist, A, B;
    unsigned int sortedLen = 0, thisLen = get_length();
    for(sortedLen = 1; sortedLen <= thisLen / 2 + 2; sortedLen = sortedLen*2)
    {
        while(head)
        {
            currentA = head;
            A.head = currentA;
            head = cut(currentA, sortedLen);
            currentB = head;
            B.head = currentB;
            head = cut(currentB, sortedLen);
            newlist.merge(A, B);
        }
        swap(newlist);
    }
    while(head)
        {
            currentA = head;
            A.head = currentA;
            head = cut(currentA, sortedLen);
            currentB = head;
            B.head = currentB;
            head = cut(currentB, sortedLen);
            newlist.merge(A, B);
        }
        swap(newlist);
    return;
}

int list::diff()
{
    list_node* current = nullptr;
    int counter = 0;
    for(current = head; current && current->next; current = current->next)
    {
        if(*current > *current->next)
            counter++;
    }
    return counter;
}