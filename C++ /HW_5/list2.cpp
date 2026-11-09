#include "list2.h"
#include <utility>

list2_node::list2_node(list2_node&& x)
{
    swap(x);
    std::swap(next, x.next);
    std::swap(prev, x.prev);
}
list2_node& list2_node::operator=(list2_node&& x)
{
    if (this == &x)
		{return *this;}
    swap(x);
    std::swap(next, x.next);
    std::swap(prev, x.prev);
    return *this;
}
io_status list2::read(FILE* fp, unsigned int max_read)
{
    list2_node tmp;
    list2_node* prev = nullptr;
    list2_node** p_current = &head;
    io_status errorstatus = io_status::success;
    unsigned int counter = 0;
    if(!fp) return io_status::memory;

    while((errorstatus = tmp.read(fp)) == io_status::success && counter != max_read)
    {
        *p_current = new list2_node((list2_node&&)tmp);
        if(!(*p_current))
            return io_status::memory;
        (*p_current)->prev = prev;
        prev = (*p_current);
        p_current = &((*p_current)->next);
        counter++;
        tmp = list2_node{};
    }

    return errorstatus;

}
void list2::print(unsigned int r, FILE* fp)
{
    list2_node* current;
    unsigned int counter = 0;
    for(current = head ;counter != r && current; current = current->next, ++counter)
    {
        current->print(fp);
    }
}
unsigned int list2::get_length()
{
    list2_node* current;
    int len = 0;
    for(current = head; current; current = current->next)
    {
        len++;
    }
    return len;
}

list2_node* list2::jumpTo(unsigned int k)
{
    list2_node* current = head;
    for(int i = 0; current && i < static_cast<int>(k); i++)
    {
        current = current->next;
    }
        return current;
}

list2_node* list2::shift(int k)
{
    unsigned int len = get_length();
    if(len == 0)
        return head;

    list2_node* rupture1, *rupture2, *tail = jumpTo(len - 1);

    k = k % len;
    if(k == 0)
        return head;
    if(k > 0)
    {
        rupture2 = jumpTo(len - 1 - static_cast<unsigned int>(k));
        rupture1 = jumpTo(len - static_cast<unsigned int>(k) - 2);
    }
    if(k < 0)
    {
        rupture2 = jumpTo(static_cast<unsigned int>(-k));
        rupture1 = jumpTo(static_cast<unsigned int>(-k) - 1);
    }
    head->prev = tail;
    rupture2->prev = nullptr;
    rupture1->next = nullptr;
    tail->next = head;
    head = rupture2;
    return head;
}

void list2::popOne(list2_node* x)
{
    unsigned int len = get_length(); 
    if(len == 1 || len == 0)
    {
        head = nullptr;
        return;
    }
    if(x->prev == nullptr)
    {
        head = x->next;
        (x->next)->prev = nullptr;
        delete x;
        return;    
    }
    if(x->next == nullptr)
    {
        (x->prev)->next = nullptr;
        delete x;
        return;
    }
    (x->prev)->next = x->next;
    (x->next)->prev = x->prev;
    delete x;
    return;
}
void list2::popSqnc(list2_node* start, list2_node* end)
{
   // flag = 0;
    list2_node* current = nullptr;
    for(current = start; current != end && current; current = current->next)
    {
        //flag = 1;
        popOne(current);
    }
    popOne(current);
    return;
}
void list2::solveProblem2(int k)
{
    unsigned int len = get_length();
    list2_node* current = nullptr, *iterator = nullptr;
    for(int i = len; i > 0; i--)
    {
            current = jumpTo(i - 1);
            int j = 0;
            if(current->prev == nullptr)
                break;
            for(iterator = current->prev; iterator && j < k; j++, iterator = iterator->prev)
            {
                if(*current > *iterator)
                {
                    popOne(current);
                    break;
                }
            }
    }
    return;
}
void list2::solveProblem3(int k)
{
    int counter = 0;
    int len = static_cast<int>(get_length());
    list2_node* current = head, *iterator = nullptr;
    for(int i = 0; i < len; i++)
    {
            current = jumpTo(i - counter);
            int j = 0;
            if(current == nullptr || current->next == nullptr)
                break;
            for(iterator = current->next; iterator != nullptr && j < k; j++, iterator = iterator->next)
            {
                if(*current > *iterator)
                {
                    popOne(current);
                    ++counter;
                    break;
                }
            }
    }
    return;
}

void list2::solveProblem5(int k)
{
    int sqncFlag = 0;
    int sqncLen = 0;
    unsigned int len = get_length();
    list2_node* current = nullptr, *start = nullptr, *end = nullptr;
    if(len == 1 && k == 0)
    {
        popOne(head);
        return;
    }
    if(len == 1 && k > 0) return;
    for(current = head; current && current->next; current = current->next)
    {
        if(*current == *(current->next) && sqncFlag == 0)
        {
            start = current;
            sqncFlag = 1;
            sqncLen = 2;
            continue;
        }
        if(*current == *(current->next) && sqncFlag == 1)
        {
            sqncLen++;
            continue;
        }
        if(!(*current == *(current->next)) && sqncFlag == 1)
        {
            end = current;
            if(sqncLen > k)
            {
                popSqnc(start, end);
            }
            sqncFlag = 0;
            sqncLen = 0;
            continue;
        }
    }
    if(sqncFlag == 1 && sqncLen > k && current)
    {
        popSqnc(start, current);
    }
    return;
}
void list2::solveProblem6(int k)
{
    int sqncFlag = 0;
    int sqncLen = 0;
    unsigned int len = get_length();
    list2_node* current = nullptr, *start = nullptr, *end = nullptr;
    if(len == 1 && k == 0)
    {
        popOne(head);
        return;
    }
    if(len == 1 && k > 0) return;
    for(current = head; current && current->next; current = current->next)
    {
        if(!(*current < *(current->next)) && sqncFlag == 0)
        {
            start = current;
            sqncFlag = 1;
            sqncLen = 2;
            continue;
        }
        if(!(*current < *(current->next)) && sqncFlag == 1)
        {
            sqncLen++;
            continue;
        }
        if((*current < *(current->next)) && sqncFlag == 1)
        {
            end = current;
            if(sqncLen > k)
            {
                popSqnc(start, end);
            }
            sqncFlag = 0;
            sqncLen = 0;
            continue;
        }
    }
    if(sqncFlag == 1 && sqncLen > k && current)
    {
        popSqnc(start, current);
    }
    return;
}

void list2::solveProblem7(int k)
{
    int fstSqncFlag = 0, sqncFlag = 0;
    int sqncLen = 0;
    unsigned int len = get_length();
    list2_node* current = nullptr, *start = nullptr, *end = nullptr, *possible = nullptr;

    if(len >= 1 && len <=2)
        return;

    for(current = head; current && current->next; current = current->next)
    {
        if(sqncFlag == 0 && (*current == *(current->next)))
        {
            sqncFlag = 1;
            sqncLen = 2; 
            if(fstSqncFlag == 1)
            {
                possible = current;
            }
            continue;
        }
        if(sqncFlag == 1 && (*current == *(current->next)))
        {
            sqncLen++;
            continue;
        }
        if(sqncFlag == 1 && !(*current == *(current->next)))
        {
            sqncFlag = 0;
            if(sqncLen > k)
            {
                if(fstSqncFlag == 1)
                {
                    end = possible->prev;
                    if(start != end)
                    {
                        popSqnc(start->next, end);
                    }
                    start = current;
                }
                else
                {
                    start = current;
                    fstSqncFlag = 1;
                }
                sqncLen = 0;
            }
        }

    }
    if(sqncFlag == 1 && sqncLen > k && fstSqncFlag == 1 && current)
    {
        if(start != possible->prev)
        {
            popSqnc(start->next, possible->prev);
        }
    }
    return;
}