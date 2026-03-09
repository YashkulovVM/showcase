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
    unsigned int countLeafNodes();
    unsigned int countLeafNodesRecursively(tree_node* current);
    unsigned int countTreeHeight();
    unsigned int countSubtreeHeight(tree_node* current, unsigned int level = 1);
    unsigned int countSubtreeHeightRecursively(tree_node* current);
    unsigned int countMaxLevelSize();
    unsigned int* countMaxLevelSizeSubtree(tree_node* current, unsigned int* sizes, unsigned int len, unsigned int i = 0);
    unsigned int countLRDiffHere(tree_node* current, unsigned int maxsize = 0);
    unsigned int countMaxLRDiffSubtreeRecursively(tree_node* current, unsigned int max = 0);
    unsigned int countMaxLRDiff();
    unsigned int countParentsWithOneChild();
    unsigned int countParentsWithOneChildSubtree(tree_node* current);
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