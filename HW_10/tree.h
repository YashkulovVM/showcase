#ifndef TREE_H
#define TREE_H
#include "student.h"
#include <algorithm>

int max(int* array, int len)
{
    int max = 0;
    for(int i = 0; i < len; i++)
    {
        if(array[i] > max)
            max = array[i];
    }
    return max;
}

template <class T> class tree;
template <class T>
class tree_node : public T
{
private:
    tree_node * left = nullptr;
    tree_node * right = nullptr;
public:
    tree_node () = default;
    tree_node (const tree_node& x) = delete;
    tree_node (tree_node&& x) : T ((T&&)x)
    {
        erase_links ();
        x.erase_links ();
    }
    ~tree_node ()
    {
        erase_links ();
    }
    tree_node& operator= (const tree_node& x) = delete;
    tree_node& operator= (tree_node&& x)
    {
        if (this == &x)
            return *this;
        (T&&) *this = (T&&) x;
        erase_links ();
        x.erase_links ();
        return *this;
    }
    friend class tree<T>;
    private:
    void erase_links ()
    { left = nullptr; right = nullptr; }
    friend class tree<T>;
};

template <class T>
class tree
{
private:
    tree_node<T> * root = nullptr;
public:
    tree<T> () = default;
    tree<T> (const tree<T>& x) = delete;
    tree<T> (tree<T>&& x)
    {
        root = x.root; x.root = nullptr;
    }
    ~tree<T> ()
    {
        delete_subtree (root);
        root = nullptr;
    }
    tree<T>& operator= (const tree<T>& x) = delete;
    tree<T>& operator= (tree<T>&& x)
    {
        if (this == &x)
        return *this;
        delete_subtree (root);
        root = x.root; x.root = nullptr;
        return *this;   
    }
    void print (FILE *fp = stdout, unsigned int r = 10) const
    {
        print_subtree (root, 0, r, fp);
    }
    void addNodeSubtree(tree_node<T>* current, tree_node<T>* x)
    {
        tree_node<T>* iterator = current;
        while(true)
        {
            if(*x < *iterator)
            {
                if(iterator->left == nullptr)
                {
                    iterator->left = x;
                    break;
                }
                else
                {
                    iterator = iterator->left;
                    continue;
                }
            }
            else
            {
                if(iterator->right == nullptr)
                {
                    iterator->right = x;
                    break;
                }
                else
                {
                    iterator = iterator->right;
                    continue;
                }
            }
        }
        return;
    }
    io_status read(FILE * fp, unsigned int max_read = -1)
    {
        io_status errorstatus = io_status::success;
        unsigned int counter = 0;
        tree_node<T> tmp;
        if(!fp)
            return io_status::memory;
        while(counter < max_read && (errorstatus = tmp.read(fp)) == io_status::success)
        {
            ++counter;
            tree_node<T>* current = new tree_node<T>((tree_node<T>&&)tmp);
            if(current == nullptr)
                return io_status::memory;
            if(root==nullptr)
                root = current;
            else addNodeSubtree(root, current);
            if(feof(fp))
                break;
        }
        if(errorstatus == io_status::halfway)
        {
            ++counter;
            tree_node<T>* current = new tree_node<T>((tree_node<T>&&)tmp);
            if(current == nullptr)
                return io_status::memory;
            if(root==nullptr)
                root = current;
            else addNodeSubtree(root, current);
        }
        if(counter >= max_read)
            return io_status::success;
        if(!feof(fp))
            return errorstatus;
        return io_status::success;
    }
    static void delete_subtree (tree_node<T> * curr)
    {
        if (curr == nullptr)
        return;
        delete_subtree (curr->left);
        delete_subtree (curr->right);
        delete curr;
    }
    static void print_subtree (tree_node<T> * curr, unsigned int level, unsigned int r, FILE *fp = stdout)
    {
        if (curr == nullptr || level > r)
            return;
        unsigned int spaces = level * 2;
        for (unsigned int i = 0; i < spaces; i++)
            printf (" ");
        curr->print (fp);
            printf ("\n");
        print_subtree (curr->left, level + 1, r, fp);
        print_subtree (curr->right, level + 1, r, fp);
    }
    int countLeavesTotalCardinality()
    {
        if(!root)
            return 0;
        return countLeavesTotalCardinalityUtil(root);
    }
    int countLeavesTotalCardinalityUtil(tree_node<T>* current)
    {
        int counter = 0;
        if(!current->left && !current->right)
            counter += current->get_length();
        if(current->left)
            counter += countLeavesTotalCardinalityUtil(current->left);
        if(current->right)
            counter += countLeavesTotalCardinalityUtil(current->right);
        return counter;
    }

    int countTreeHeight()
    {
        return countSubtreeHeight(root);
    }

    int countSubtreeHeight(tree_node<T>* current)
    {
        int level = 0;
        if(!current)
            return 0;
        level++;
        return level += std::max(countSubtreeHeight(current->left), countSubtreeHeight(current->right));
    }

    int countLongBranchCardinality()
    {
        if(!root)
            return 0;
        return countLongBranchCardinalityUtil(root);
    }
    int countLongBranchCardinalityUtil(tree_node<T>* current)
    {
        int lC = 0, rC = 0;
        if(!current->left && !current->right)
            return current->get_length();
        if(current->left)
            lC += countLongBranchCardinalityUtil(current->left);
        if(current->right)
            rC += countLongBranchCardinalityUtil(current->right);
        return std::max(lC, rC) + current->get_length();
    }
    int countMaxLevelCardinality()
    {
        if(!root)
            return 0;
        int len = countTreeHeight(), ret = 0;
        int* sizes = new int [len] ();
        if(!sizes)
            return -1;
        int i = 0;
        countMaxLevelSizeSubtree(root, sizes, len, i);
        ret = max(sizes, len);
        delete[]sizes;
        return ret;
    }
    int* countMaxLevelSizeSubtree(tree_node<T>* current, int* sizes, int len, int i)
{
    if(i == len)
        return sizes;
    if(!current)
        return sizes;
    else sizes[i] += current->get_length();
    i++;
    if(current->left)
        countMaxLevelSizeSubtree(current->left, sizes, len, i);
    if(current->right)
        countMaxLevelSizeSubtree(current->right, sizes, len, i);
    return sizes;
}
int countSubtree(tree_node<T>* current)
{
    if(!current)
        return 0;
    int counter = 0;
    if(!current->left && !current->right)
        return current->get_length();
    if(current->left)
        counter += countSubtree(current->left);
    if(current->right)
        counter += countSubtree(current->right);
    counter += current->get_length();
    return counter;
}
int countLRDiffHere(tree_node<T>* current, int maxdiff)
{
    int l = 0, r = 0, diff = 0;
    if(!current)
        return 0;
    l = countSubtree(current->left);
    r = countSubtree(current->right);
    auto R = std::minmax(l, r);
    diff = R.second - R.first;
    if(maxdiff < diff)
        return diff;
    else return maxdiff;
}

int countMaxLRDiffSubtreeRecursively(tree_node<T>* current, int max)
{
    int diffHere = 0, diffL = 0, diffR = 0, maxdiff = max;
    if(!current->left && !current->right)
        return 0;
    diffHere = countLRDiffHere(current, maxdiff);
    if(diffHere > maxdiff)
        maxdiff = diffHere;
    if(current->left)
        diffL = countMaxLRDiffSubtreeRecursively(current->left, maxdiff);
    if(current->right)
        diffR = countMaxLRDiffSubtreeRecursively(current->right, maxdiff);
    if(diffL > maxdiff && diffL >= diffR)
        maxdiff = diffL;
    if(diffR > maxdiff && diffR > diffL)
        maxdiff = diffR;
    return maxdiff;
}

int countMaxLRDiff()
{
    if(!root)
        return 0;
   return countMaxLRDiffSubtreeRecursively(root, 0);
}

int countParentsWithOneChildSubtree(tree_node<T>* current)
{
    int ret = 0;
    if(!current)
        return ret;
    if(current->left && !current->right)
    {
        ret += current->get_length();
    }
    if(!current->left && current->right)
    {
        ret += current->get_length();
    }
    if(current->left)
        ret += countParentsWithOneChildSubtree(current->left);
    if(current->right)
        ret += countParentsWithOneChildSubtree(current->right);
    return ret;
}
int countParentsWithOneChild()
{
    return countParentsWithOneChildSubtree(root);
}

};
#endif