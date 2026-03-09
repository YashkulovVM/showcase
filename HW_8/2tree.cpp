#include "2tree.h"
#include <algorithm>

void tree::addNodeSubtree(tree_node* current, tree_node* x)
{
    tree_node* iterator = current;
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

io_status tree::read(FILE * fp, unsigned int max_read)
{
    io_status errorstatus = io_status::success;
    unsigned int counter = 0;
    tree_node tmp;
    if(!fp)
        return io_status::memory;
    while(counter < max_read && (errorstatus = tmp.read(fp)) == io_status::success)
    {
        ++counter;
        tree_node* current = new tree_node((tree_node&&)tmp);
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

unsigned int tree::countSubtrees(tree_node* current)
{
    unsigned int ret = 0;
    if(!current)
        return 0;
    if(current->left)
    {
        ret++;
        ret += countSubtrees(current->left);
    }
    if(current->right)
    {
        ret++;
        ret += countSubtrees(current->right);
    }
    return ret;
}

unsigned int tree::countTreeHeight()
{
    return countSubtreeHeight(root);
}

unsigned int tree::countSubtreeHeight(tree_node* current, unsigned int level)
{
    if(!current)
        return 0;
    if(current->left == nullptr && current->right == nullptr)
        return level++;
    level++;
    return level += std::max(countSubtreeHeight(current->left, 0), countSubtreeHeight(current->right, 0));
}

unsigned int tree::countSmallBranchesSubtree(unsigned int k, tree_node* current, unsigned int* counter)
{
    unsigned int ret1 = 0, ret2 = 0;
    if(!current->left && !current->right)
    {
        return 1;
    }
    if(current->left)
    {
        ret1 += countSmallBranchesSubtree(k, current->left, counter);
        if(ret1 <= k)
            (*counter)++;
    }
    if(current->right)
    {
        ret2 += countSmallBranchesSubtree(k, current->right, counter);
        if(ret2 <= k)
            (*counter)++;
    }
    return ret1 + ret2 + 1;
}

unsigned int tree::countSmallBranches(unsigned int k)
{
    if(!root)
        return 0;
    unsigned int counter = 0;
        countSmallBranchesSubtree(k, root, &counter);
    return counter;
}

unsigned int tree::countElementsOfSmallBranchesSubtrees(unsigned int k, tree_node* current, unsigned int* counter)
{
    unsigned int ret1 = 0, ret2 = 0;
    if(!current->left && !current->right)
    {
        return 1;
    }
    if(current->left)
    {
        ret1 += countElementsOfSmallBranchesSubtrees(k, current->left, counter);
        if(ret1 <= k)
            (*counter) += ret1;
    }
    if(current->right)
    {
        ret2 += countElementsOfSmallBranchesSubtrees(k, current->right, counter);
        if(ret2 <= k)
            (*counter) += ret2;
    }
    return ret1 + ret2 + 1;
}

unsigned int tree::countElementsOfSmallBranches(unsigned int k)
{
    if(!root)
        return 0;
    unsigned int counter = 0;
    countElementsOfSmallBranchesSubtrees(k, root, &counter);
    return counter;
}

unsigned int tree::countShortSubtrees(unsigned int k)
{
    if(!root)
        return 0;
    unsigned int counter = 0;
    countShortSubtreesFromHere(k, root, &counter);
    return counter;
}

unsigned int tree::countShortSubtreesFromHere(unsigned int k, tree_node* current, unsigned int* counter)
{
    if(!current->left && !current->right)
    {
        return 1;
    }
    unsigned int ret1 = 0, ret2 = 0;
    if(current->left)
    {
        ret1 += countShortSubtreesFromHere(k, current->left, counter);
        if(ret1 <= k)
            (*counter)++;
    }
    if(current->right)
    {
        ret2 += countShortSubtreesFromHere(k, current->right, counter);
        if(ret2 <= k)
            (*counter)++;
    }
    return std::max(ret1, ret2) + 1;
}

unsigned int max(unsigned int* array, unsigned int len)
{
    unsigned int max = 0;
    for(unsigned int i = 0; i < len; i++)
    {
        if(array[i] > max)
            max = array[i];
    }
    return max;
}

unsigned int tree::countSlimSubtrees(unsigned int k)
{
    if(!root)
        return 0;
    unsigned int len = countTreeHeight(), counter = 0;
    unsigned int* sizes = new unsigned int [len + 1] ();
        if(!sizes)
            return static_cast<unsigned int>(-1);
    countSlimSubtreesFromHere(k, root, sizes, len, &counter, 0);
    delete[]sizes;
    return counter;
}

void tree::countSlimSubtreesFromHere(unsigned int k, tree_node* current, unsigned int* sizes, unsigned int len, unsigned int* counter, unsigned int i)
{
    if(!current->left && !current->right)
        return;
    unsigned int ret = 0;
    if(current->left)
        {
            countMaxLevelSizeSubtree(current->left, sizes, len, i + 1);
            ret = max(sizes, len);
            if(ret <= k)
                (*counter)++;
            std::fill(sizes, sizes + len, 0);
            countSlimSubtreesFromHere(k, current->left, sizes, len, counter, i);
        }
    if(current->right)
        {
            countMaxLevelSizeSubtree(current->right, sizes, len, i + 1);
            ret = max(sizes, len);
            if(ret <= k)
                (*counter)++;
            std::fill(sizes, sizes + len, 0);
            countSlimSubtreesFromHere(k, current->right, sizes, len, counter, i);
        }
    return;
}

unsigned int tree::countNumberOfElementsOnLvl(unsigned int level)
{
    if(!root)
        return 0;
    unsigned int len = countTreeHeight(), ret = 0;
    if(level > len)
        return 0;
    unsigned int* sizes = new unsigned int [len + 1] ();
        if(!sizes)
            return static_cast<unsigned int>(-1);
    countMaxLevelSizeSubtree(root, sizes, len, 0);
    ret = sizes[level];
    delete[]sizes;
    return ret;
}

unsigned int* tree::countMaxLevelSizeSubtree(tree_node* current, unsigned int* sizes, unsigned int len, unsigned int i)
{
    if(!current)
        return sizes;
    else sizes[i]++;
    i++;
    if(current->left)
        countMaxLevelSizeSubtree(current->left, sizes, len, i);
    if(current->right)
        countMaxLevelSizeSubtree(current->right, sizes, len, i);
    return sizes;
}

