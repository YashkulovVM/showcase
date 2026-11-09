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

unsigned int tree::countLeafNodes()
{
    return countLeafNodesRecursively(root);
}

unsigned int tree::countLeafNodesRecursively(tree_node* current)
{
    if(current == nullptr)
        return 0;
    if(current->left == nullptr && current->right == nullptr)
        return 1;
    return countLeafNodesRecursively(current->left) + countLeafNodesRecursively(current->right);
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

unsigned int tree::countMaxLevelSize()
{
    if(!root)
        return 0;
    unsigned int len = countTreeHeight(), ret = 0;
    unsigned int* sizes = new unsigned int [len] ();
    if(!sizes)
        return -1;
    unsigned int i = 0;
    countMaxLevelSizeSubtree(root, sizes, len, i);
    ret = max(sizes, len);
    delete[]sizes;
    return ret;
}
unsigned int* tree::countMaxLevelSizeSubtree(tree_node* current, unsigned int* sizes, unsigned int len, unsigned int i)
{
    if(i == len)
        return sizes;
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

unsigned int tree::countParentsWithOneChildSubtree(tree_node* current)
{
    unsigned int ret = 0;
    if(!current)
        return ret;
    if(current->left && !current->right)
    {
        ret++;
    }
    if(!current->left && current->right)
    {
        ret++;
    }
    if(current->left)
        ret += countParentsWithOneChildSubtree(current->left);
    if(current->right)
        ret += countParentsWithOneChildSubtree(current->right);
    return ret;
}
unsigned int tree::countParentsWithOneChild()
{
    return countParentsWithOneChildSubtree(root);
}

unsigned int tree::countLRDiffHere(tree_node* current, unsigned int maxdiff)
{
    unsigned int l = 0, r = 0, diff = 0;
    if(!current)
        return 0;
    l = countSubtreeHeight(current->left, 1);
    r = countSubtreeHeight(current->right, 1);
    auto R = std::minmax(l, r);
    diff = R.second - R.first;
    if(maxdiff < diff)
        return diff;
    else return maxdiff;
}

unsigned int tree::countMaxLRDiffSubtreeRecursively(tree_node* current, unsigned int max)
{
    unsigned int diffHere = 0, diffL = 0, diffR = 0, maxdiff = max;
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

unsigned int tree::countMaxLRDiff()
{
   return countMaxLRDiffSubtreeRecursively(root);
}