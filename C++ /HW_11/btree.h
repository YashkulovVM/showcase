#ifndef BTREE_H
#define BTREE_H
#include "student.h"

template <class T> class b_tree;
template <class T>
class b_tree_node
{
private:
    T *values = nullptr; // 2*m elements array
    int size = 0; // number of children
    b_tree_node ** children = nullptr; // 2*m+1 elements array
public:
    b_tree_node () = default;
    ~b_tree_node ()
    {
        if(values)
            {delete[]values; values = nullptr;}
        if(children)
            {delete[]children; children = nullptr;}
        size = 0;
    }
    void print (int p = 0) const
    {
        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < p; j++)
                printf(" ");
            printf ("values[%2d] ", i + 1);
            values[i].print ();
        }
    }
    friend class b_tree<T>;
private:
    int bin_search(const T& x) const
    {
        int head = 0, tail = size - 1, middle = 0;
        while(head < tail)
        {
            middle = (head + tail) * 0.5;
            if(values[middle] < x)
                head = middle + 1;
            else
                tail = middle;
        }
        if(head == size - 1 && (values[size - 1] < x))
            return size;
        return tail;
    }
    io_status init (int m)
    {
        values = new T[2 * m];
        if(!values)
            return io_status::memory;
        children = new b_tree_node* [2 * m + 1];
        if(!children)
        {
            delete[] values;
            return io_status::memory;
        }
        for(int i = 0; i <= 2 * m; ++i)
            children[i] = nullptr;
        size = 0;
        return io_status::success;
    }
// Insert value ’x’ with children ’down’ at position ’index’
// into the node (assuming enough space)
    void add_value (T& x, b_tree_node<T>* down, int index)
    {
        for (int i = size; i > index; i--)
        {
            values[i] = static_cast<T&&>(values[i - 1]);
            children[i + 1] = children[i];
        }
        values[index] = static_cast<T&&>(x);
        children[index + 1] = down;
        size++;
    }
};

template <class T>
class b_tree
{
private:
    int m; // B-tree base
    b_tree_node<T> * root = nullptr;
public:
    b_tree (int i = 0) { m = i; }
    io_status read (FILE * fp = stdin)
    {
        delete_subtree(root);
        T x;
        while(x.read(fp) == io_status::success)
        {
            if(add_value(x) == io_status::memory)
            {
                delete_subtree(root);
                return io_status::memory;
            }
        }
        if(!feof(fp))
        {
            delete_subtree(root);
            return io_status::readnt;
        }
        return io_status::success;
    }
    void print (int r) const
    {
        print_subtree (root, 0, r);
    }
    int countKNodesCardinality(int k)
    {
        if(!root)
            return 0;
        return countKNodesCardinalityUtil(root, k);
    }
    int countKNodesCardinalityUtil(b_tree_node<T>* current, int k)
    {
        int counter = 0;
        if(!current)
            return 0;
        if(current->size + 1 == k && current->children[0])
            counter += current->size;
        if(k == 0 && !current->children[0])
            counter += current->size;
        for(int i = 0; i <= current->size; ++i)
            counter += countKNodesCardinalityUtil(current->children[i], k);
        return counter;
    }

    int countSmallSTCardinality(int k)
    {
        if(!root)
            return 0;
        int counter = 0, prevElem = 0;
        for(int i = 0; i <= root->size; ++i)
            countSmallSTCardinalityUtil(root->children[i], k, &counter, &prevElem);
        return counter;
    }

    int countSmallSTCardinalityUtil(b_tree_node<T> * current, int k, int* globalC, int * prevElem)
    {
        if(current && !current->children[0])
        {
            if(!(k < 1))
                (*globalC) += current->size;
            *prevElem = current->size;
            return 1;
        }
        int vertCounter = 1, elemCounter = current->size;
        for(int i = 0; i <= current->size; ++i)
        {
            vertCounter += countSmallSTCardinalityUtil(current->children[i], k, globalC, prevElem);
            elemCounter += *prevElem;
        }
        if(!(k < vertCounter))
            *globalC += elemCounter;
        *prevElem = elemCounter;
        return vertCounter;
    }

    int countShortSTCardinality(int k)
    {
        if(!root)
            return 0;
        int counter = 0, prevElem = 0;
        for(int i = 0; i <= root->size; ++i)
            countShortSTCardinalityUtil(root->children[i], k, &counter, &prevElem);
        return counter;
    }

    int countShortSTCardinalityUtil(b_tree_node<T>* current, int k, int* counter, int * prevElem)
    {
        if(current && !current->children[0])
            {
                if(!(k < 1))
                    *counter += current->size;
                *prevElem = current->size;
                return 1;
            }
        int level = 0, elemCounter = current->size, maxlevel = 0;
        for(int i = 0; i <= current->size; ++i)
        {
            level = countShortSTCardinalityUtil(current->children[i], k, counter, prevElem);
            elemCounter += *prevElem;
            if(level > maxlevel)
                maxlevel = level;
        }
        if(!(k < maxlevel + 1))
            *counter += elemCounter;
        *prevElem = elemCounter;
        return maxlevel + 1;
    }

    int get_subtree_height(b_tree_node<T> * current)
    {
        if(current && !current->children[0])
            return 1;
        int level = 0, maxlevel = 0;
        for(int i = 0; i <= current->size; ++i)
        {
            level = get_subtree_height(current->children[i]);
            if(level > maxlevel)
                maxlevel = level;
        }
        return maxlevel + 1;
    }

    int countSlimSTCardinality(int k)
    {
        if(!root)
            return 0;
        int len = get_subtree_height(root), counter = 0;
        int* sizes = new int[len]();
        if(!sizes)
            return -1;
        int arr_pos = 0;
        for(int i = 0; i <= root->size; ++i)
            countSlimSTCardinalityUtil(root->children[i], k, sizes, len, arr_pos, &counter);
        delete[]sizes;
        return counter;
    }
    int findMax(int * sizes, int len)
    {
        int max = 0;
        for(int i = 0; i < len; ++i)
        {
            if(sizes[i] > max)
                max = sizes[i];
        }
        return max;
    }
    void flush(int * sizes, int len)
    {
        for(int i = 0; i < len; ++i)
            sizes[i] = 0;
        return;
    }
    void fillSizes(b_tree_node<T>* current, int * sizes, int arr_pos, int * counter)
    {
        if(current && !current->children[0])
        {
            sizes[arr_pos]++;
            *counter += current->size;
            return;
        }
        *counter += current->size;
        sizes[arr_pos]++;
        for(int i = 0; i <= current->size; ++i)
            fillSizes(current->children[i], sizes, arr_pos + 1, counter);
        return;
    }
    void countSlimSTCardinalityUtil(b_tree_node<T> * current, int k, int * sizes, int len, int arr_pos, int * counter)
    {
        if(!current)
            return;
        int elemCounter = 0;
        fillSizes(current, sizes, arr_pos, &elemCounter);
        if(!(k < findMax(sizes, len)))
            *counter += elemCounter;
        flush(sizes, len);
        for(int i = 0; i <= current->size; ++i)
        {
            countSlimSTCardinalityUtil(current->children[i], k, sizes, len, arr_pos + 1, counter);
        }
        return;
    }

    int countElementsOnLvlK(int k)
    {
        if(!root)
            return 0;
        int currLevel = 0;
        return countElementsOnLvlKUtil(root, k, currLevel);
    }
    int countElementsOnLvlKUtil(b_tree_node<T> * current, int k, int currLevel)
    {
        if(!current)
            return 0;
        int counter = 0;
        if(current && currLevel == k)
            counter = current->size;
        for(int i = 0; i <= current->size; ++i)
        {
            counter += countElementsOnLvlKUtil(current->children[i], k, currLevel + 1);
        }
        return counter;
    }

    int countKBranches(int k)
    {
        if(!root || k == 0)
            return 0;
        int currLevel = 1, globalC = 0;
        countKBranchesUtil(root, k, currLevel, &globalC);
        return globalC;
    }
    int countKBranchesUtil(b_tree_node<T> * current, int k, int currLevel, int * globalC)
    {
        if(current && !current->children[0])
        {
            if(currLevel == k)
                {   
                    *globalC += current->size;
                    return 1;
                }
            else 
                return 0;
        }
        int counter = 0;
        for(int i = 0; i <= current->size; ++i)
        {
            counter += countKBranchesUtil(current->children[i], k, currLevel + 1, globalC);
        }
        if(counter != 0)
        {
            *globalC += counter * current->size;
        }
        return counter;
    }

    ~b_tree()
    {
        delete_subtree (root);
        erase_links ();
    }
private:
    void erase_links ()
    {
        m = 0;
        root = nullptr;
    }
    static void delete_subtree (b_tree_node<T> * curr)
    {
        if (curr == nullptr)
            return;
        for (int i = 0; i <= curr->size; i++)
            delete_subtree (curr->children[i]);
        delete curr;
    }
    static void print_subtree (b_tree_node<T> * curr,
    int level, int r)
    {
        if (curr == nullptr || level > r)
            return;
        curr->print (level);
        for (int i = 0; i <= curr->size; i++)
        {
            if (curr->children[i] && level + 1 <= r)
            {
                for (int j = 0; j < level; j++)
                printf(" ");
                printf ("children[%2d]\n", i);
                print_subtree (curr->children[i], level + 1, r);
            }
        }
    }
    // Add element x to tree
    io_status add_value (T& x)
    {
        if (root == nullptr)
        {
            root = new b_tree_node<T>();
            if (root == nullptr)
                return io_status::memory;
            if (root->init(m) != io_status::success)
            {
                delete root;
                return io_status::memory;
            }
            root->values[0] = static_cast<T&&>(x);
            root->size = 1;
            return io_status::success;
        }
        b_tree_node<T> *curr = root, *down = nullptr;
        io_status r = add_value_subtree (curr, down, x, m);
        if (r == io_status::memory)
            return io_status::memory;
        if (r == io_status::success)
            return io_status::success;
        // иначе r == io_status::create и был создан новый узел
        // который возвращается в ’down’
        // Создаем новый корень с одним значением ’x’
        // и двумя потомками ’curr’ and ’down’
        b_tree_node<T>* p = new b_tree_node<T>();
        if (p == nullptr)
            return io_status::memory;
        if (p->init (m) != io_status::success)
        {
            delete p;
            return io_status::memory;
        }
        p->values[0] = static_cast<T&&>(x);
        p->children[0] = curr;
        p->children[1] = down;
        p->size = 1;
        root = p;
        return io_status::success;
    }
// Insert value ’x’ with children ’down’ at subtree ’curr’
    static io_status add_value_subtree
    (b_tree_node<T>*& curr, b_tree_node<T>*& down, T& x, int m)
    {
        int index = curr->bin_search (x);
        b_tree_node<T>* p = curr->children[index];
        if (p != nullptr)
        { // Есть потомок
            io_status r = add_value_subtree (p, down, x, m);
            if (r == io_status::memory)
                return io_status::memory;
            if (r == io_status::success)
                return io_status::success;
            // иначе r == io_status::create
            // и был создан новый узел,
            // который возвращается в ’down’
        }
        else
        down = nullptr;
        if (curr->size < 2 * m)
        { // Есть свободное место в текущем узле
            curr->add_value (x, down, index);
            return io_status::success;
        }
        else
        { // Создаем новый узел
            b_tree_node<T>* p = new b_tree_node<T>();
            if (p == nullptr)
                return io_status::memory;
            if (p->init (m) != io_status::success)
            {
            delete p;
            return io_status::memory;
            }
            if (index == m)
            { // ’x’ ровно посередине.
            // Перемещаем вторую половину в новый узел
            for (int i = 1; i <= m; i++)
            {
                p->values[i - 1]
                = static_cast<T&&>(curr->values[i + m - 1]);
                p->children[i] = curr->children[i + m];
                curr->children[i + m] = nullptr;
            }
            p->children[0] = down; // меньше всех
            }
            if (index < m)
            { // ’x’ в первой половине.
                // Перемещаем вторую половину в новый узел
                for (int i = 0; i < m; i++)
                {
                    p->values[i]
                    = static_cast<T&&>(curr->values[i + m]);
                    p->children[i] = curr->children[i + m];
                    curr->children[i + m] = nullptr;
                }
                p->children[m] = curr->children[2 * m];
                curr->children[2 * m] = nullptr;
                // сдвигаем элементы вправо
                // и вставляем ’x’ в позицию ’index’
                for (int i = m; i > index; i--)
                {
                    curr->values[i]
                    = static_cast<T&&> (curr->values[i - 1]);
                    curr->children[i + 1] = curr->children[i];
                }
                curr->children[index + 1] = down;
                curr->values[index] = static_cast<T&&>(x);
                x = static_cast<T&&> (curr->values[m]);
                // новый ’x’ - максимальный
            }
            if (index > m)
            { // ’x’ во второй половине.
                // Перемещаем вторую половину до ’index’
                // в новый узел
                p->children[0] = curr->children[m + 1];
                curr->children[m + 1] = nullptr;
                for (int i = 1 ; i < index - m; i++)
                {
                    p->values[i - 1]
                    = static_cast<T&&> (curr->values[i + m]);
                    p->children[i] = curr->children[i + m + 1];
                    curr->children[i + m + 1] = nullptr;
                }
                // Вставляем ’x’ в нужную позицию
                p->values[index - m - 1] = static_cast<T&&> (x);
                p->children[index - m] = down;
                // Перемещаем остаток второй половины в новый узел
                for (int i = index - m + 1; i <= m; i++)
                {
                    p->values[i - 1]
                    = static_cast<T&&> (curr->values[i + m - 1]);
                    p->children[i] = curr->children[i + m];
                    curr->children[i + m] = nullptr;
                }
                x = static_cast<T&&> (curr->values[m]);
                // новый ’x’ - максимальный
            }
        down = p;
        p->size = m;
        curr->size = m;
        return io_status::create;
        // создан новый узел, он возвращается в ’down’
        }
    return io_status::success;
    }
};
#endif