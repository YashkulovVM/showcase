#ifndef TREE_H
#define TREE_H
#include "student.h"

class tree;
class tree_node : public student
{
private:
    tree_node * left = nullptr;
    tree_node * right = nullptr;
public:
    tree_node () = default;
    tree_node (const tree_node& x) = delete;
    tree_node (tree_node&& x) : student ((student&&)x)
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
        (student&&) *this = (student&&) x;
        erase_links ();
        x.erase_links ();
        return *this;
    }
    friend class tree;
    private:
    void erase_links ()
    { left = nullptr; right = nullptr; }
};
class tree
{
private:
    tree_node * root = nullptr;
public:
    tree () = default;
    tree (const tree& x) = delete;
    tree (tree&& x)
    {
        root = x.root; x.root = nullptr;
    }
    ~tree ()
    {
        delete_subtree (root);
        root = nullptr;
    }
    tree& operator= (const tree& x) = delete;
    tree& operator= (tree&& x)
    {
        if (this == &x)
        return *this;
        delete_subtree (root);
        root = x.root; x.root = nullptr;
        return *this;   
    }
    void print (unsigned int r = 10, FILE *fp = stdout) const
    {
        print_subtree (root, 0, r, fp);
    }
    static void addNodeSubtree(tree_node* current, tree_node* x);
    io_status read (FILE * fp = stdin, unsigned int max_read = -1);
    unsigned int countTreeHeight();
    unsigned int countSubtreeHeight(tree_node* current, unsigned int level = 0);
    unsigned int countSubtrees(tree_node* current);
    unsigned int countSmallBranchesSubtree(unsigned int k, tree_node* current, unsigned int* counter);
    unsigned int countSmallBranches(unsigned int k);
    unsigned int countElementsOfSmallBranchesSubtrees(unsigned int k, tree_node* current, unsigned int* counter);
    unsigned int countElementsOfSmallBranches(unsigned int k);
    unsigned int countShortSubtrees(unsigned int k);
    unsigned int countShortSubtreesFromHere(unsigned int k, tree_node* current, unsigned int* counter);
    unsigned int countSlimSubtrees(unsigned int k);
    void countSlimSubtreesFromHere(unsigned int k, tree_node* current, unsigned int* sizes, unsigned int len, unsigned int* counter, unsigned int i);
    unsigned int* countMaxLevelSizeSubtree(tree_node* current, unsigned int* sizes, unsigned int len, unsigned int i);
    unsigned int countNumberOfElementsOnLvl(unsigned int level);

private:
    static void delete_subtree (tree_node * curr)
    {
        if (curr == nullptr)
        return;
        delete_subtree (curr->left);
        delete_subtree (curr->right);
        delete curr;
    }
    static void print_subtree (tree_node * curr, int level, int r,
    FILE *fp = stdout)
    {
        if (curr == nullptr || level > r)
            return;
        int spaces = level * 2;
        for (int i = 0; i < spaces; i++)
            printf (" ");
        curr->print (fp);
        print_subtree (curr->left, level + 1, r, fp);
        print_subtree (curr->right, level + 1, r, fp);
    }
    static void add_node_subtree (tree_node * curr, tree_node *x);
};
#endif