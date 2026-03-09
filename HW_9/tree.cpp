#include "tree.h"
#include <algorithm>
io_status tree::read(FILE * fp)
{
    io_status errorstatus = io_status::success;
    unsigned int counter = 0;
    tree_node tmp;
    if(!fp)
        return io_status::memory;
    while((errorstatus = tmp.read(fp)) == io_status::success)
    {
        ++counter;
        tree_node* current = new tree_node((tree_node&&)tmp);
        if(current == nullptr)
            return io_status::memory;
        if(root==nullptr)
            root = current;
        else add_node_subtree(root, current);
    }
    if(!feof(fp))
        return errorstatus;
    return io_status::success;
}

unsigned int tree::countElementsWithKChildrenUtility(unsigned int k, tree_node * current, unsigned int * counter)
{
    unsigned int ret = 0;
    if(current->level)
    {
        (*counter)++;
        ret += countElementsWithKChildrenUtility(k, current->level, counter);
    }
    else if(*counter == k)
        ret++;
    if(current->down)
    {   
        *counter = 1;
        ret += countElementsWithKChildrenUtility(k, current->down, counter);
    }
    else
    {
        if(k == 0)
            ret++;
    }
    return ret;
}

unsigned int tree::countElementsWithKChildren(unsigned int k)
{
    if(!root)
        return 0;
    if(!root->down)
    {
        if(k == 0)
            return 1;
        else
            return 0;
    }
    unsigned int ret = 0, counter = 1;
    ret = countElementsWithKChildrenUtility(k, root->down, &counter);
    return ret;
}

unsigned int tree::countElementsOfSmallSubtrees(unsigned int k)
{
    if(!root)
        return 0;
    unsigned int counter = 0;
    for(tree_node * iter = root->down; iter; iter = iter->level)
        countElementsOfSmallSubtreesUtility(k, iter, &counter);
    return counter;
}

unsigned int tree::countElementsOfSmallSubtreesUtility(unsigned int k, tree_node * current, unsigned int * counter)
{
    unsigned int ret2 = 1;
    for(tree_node * iter = current->down; iter; iter = iter->level)
    {
            if(!iter && !current->level)
        {
            return 1;
        }
        ret2 += countElementsOfSmallSubtreesUtility(k, iter, counter);
    }
    if(ret2 <= k)
        (*counter) += ret2;
    return ret2;
}

unsigned int tree::countElementsOfShortSubtrees(unsigned int k)
{
    if(!root)
            return 0;
        unsigned int counter = 0, elements = 0;
        for(tree_node * iter = root->down; iter; iter = iter->level)
            countElementsOfShortSubtreesUtility(k, iter, &counter, &elements);
        return counter;
}

unsigned int tree::countElementsOfShortSubtreesUtility(unsigned int k, tree_node* current, unsigned int * counter, unsigned int * elements)
{
    if(!current)
        return 0;
    unsigned int maxlevel = 0, level = 1, elementsHere = 1;
    for(tree_node* iter = current->down; iter; iter = iter->level)
    {
        level = countElementsOfShortSubtreesUtility(k, iter, counter, elements);
        if(maxlevel < level)
            maxlevel = level;
        elementsHere += *elements;
    }
    if(maxlevel + 1 <= k)
        (*counter) += elementsHere;
    (*elements) = elementsHere;
    return maxlevel + 1;
}
/*unsigned int tree::countShortSubtreesFromHere(unsigned int k, tree_node* current, unsigned int* counter)
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
}*/

unsigned int tree::countElementsOnLvlK(unsigned int k)
{	
	if(!root)
		return 0;
	if(k == 0)
		return 1;
	return countElementsOnLvlKUtility(k, root, 1);
}

unsigned int tree::countElementsOnLvlKUtility(unsigned int k, tree_node *current, unsigned int level)
{
	unsigned int counter = 0, res = 0;
	if(!current)
		return 0;
	for(tree_node *iter = current->down; iter; iter = iter->level)
	{
		res += countElementsOnLvlKUtility(k, iter, level + 1);	
		counter++;
	}
	if(level == k)
		return res + counter;
	return res;
}

unsigned int tree::countElementsInShortBranches(unsigned int k)
{
    if(!root)
		return 0;
	return countElementsInShortBranchesUtility(k, root, 1);
}

unsigned int tree::countElementsInShortBranchesUtility(unsigned int k, tree_node *current, unsigned int level)
{
	unsigned int res = 0;
	if(!current)
		return 0;
	if(!current->down)
	{	
		if(level >= k)
			return level;		
		return 0;
	}
	for(tree_node *iter = current->down; iter; iter = iter->level)
    {
		res += countElementsInShortBranchesUtility(k, iter, level + 1);	
    }
	return res;
}