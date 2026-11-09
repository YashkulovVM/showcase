#ifndef RBTREE_H
#define RBTREE_H
#include "student.h"
template <class T> class rb_tree;
template <class T>
class rb_tree_node : public T
{
private:
    enum class colors
    {
        invalid,
        red,
        black,
    };
    rb_tree_node * left = nullptr;
    rb_tree_node * right = nullptr;
    rb_tree_node * parent = nullptr;
    colors color = colors::invalid;
public:
    rb_tree_node () = default;
    ~rb_tree_node(){erase_links(); color = colors::invalid;}
    rb_tree_node(const rb_tree_node& x) = delete;
    rb_tree_node(rb_tree_node&& x) : T ((T&&)x)
    {
        color = x.color;
        erase_links();
        x.erase_links();
        x.color = colors::invalid;
    }
    rb_tree_node& operator=(const rb_tree_node& x) = delete;
    rb_tree_node& operator=(rb_tree_node&& x)
    {
        if (this == &x)
            return *this;
        (T&&) *this = (T&&) x;
        color = x.color;
        erase_links ();
        x.erase_links ();
        x.color = colors::invalid;
        return *this;
    }
    friend class rb_tree<T>;
private:
    void erase_links ()
    {left = nullptr; right = nullptr; parent = nullptr;}
};

template <class T>
class rb_tree
{
private:
    rb_tree_node<T> * root = nullptr;
public:
    rb_tree () = default;
    ~rb_tree() {delete_subtree(root); root = nullptr;}

    int get_elements()
    {
        return get_elements_subtree(root);
    }
    int get_elements_subtree(rb_tree_node<T> * current)
    {
        if(!current)
            return 0;
        int counter = 1;
        counter += get_elements_subtree(current->left);
        counter += get_elements_subtree(current->right);
        return counter;
    }
    io_status read (FILE * fp = stdin)
	{
		delete_subtree(root);
		rb_tree_node<T> x;
		while(x.read(fp) == io_status:: success)
		{
			if(add_node(x) == io_status:: memory)
			{
				delete_subtree(root);
				return io_status:: memory;
			}
		}
		if(!feof(fp))
		{
			delete_subtree(root);
			return io_status:: readnt;
		}
		return io_status:: success;
	}
    void print (int r = 10, FILE *fp = stdout) const
    {  
        print_subtree(root, 0, r, fp);
    }
    static void print_subtree (rb_tree_node<T> * current, int level, int r, FILE *fp = stdout)
	{
		if (current == nullptr || level > r)
			return;
		int spaces = level * 2;
		for (int i = 0; i < spaces; i++) 
			fprintf (fp, " ");
		if (current->color == rb_tree_node<T>::colors::red)
        {
			fprintf(fp, "\033[0;31m");
		    current->print();
            fprintf(fp, "\033[0m");
        }
		else
			current->print();
		print_subtree (current->left, level + 1, r, fp);
		print_subtree (current->right, level + 1, r, fp);
	}
    io_status add_node(rb_tree_node<T>& x)
    {
        if(root == nullptr)
        {
            root = new rb_tree_node((rb_tree_node<T>&&)x);
            if(!root)
                return io_status::memory;
            root->color = rb_tree_node<T>::colors::black;
        }
        else
        {
            rb_tree_node<T> * newnode = new rb_tree_node((rb_tree_node<T>&&)x);
            if(!newnode)
                return io_status::memory;
            add_node_subtree(root, newnode);
        }
        return io_status::success;
    }
private:
    static void delete_subtree (rb_tree_node<T> * current)
	{
		if(current == nullptr)
		    return;
		delete_subtree (current->left);
		delete_subtree (current->right);
		delete current;
	}
    void add_node_subtree(rb_tree_node<T> * current, rb_tree_node<T> * x)
    {
        if(*x < *current) //налево
        {
            if(!current->left)
            {
                x->color = rb_tree_node<T>::colors::red;
                current->left = x;
                current->left->parent = current;
                fix_tree(current->left);
                return;
            }
            else
                add_node_subtree(current->left, x);
        }
        else //идем направо
        {
            if(!current->right)
            {
                x->color = rb_tree_node<T>::colors::red;
                current->right = x;
                current->right->parent = current;
                fix_tree(current->right);
                return;
            }
            else
                add_node_subtree(current->right, x);
        }
        return;
    }

    void fix_tree(rb_tree_node<T> * current) //В оригинале забыл перекраску
    { //наличие current->parent гарантировано вызовом от current->left или ->right
		rb_tree_node<T> * uncle = nullptr;
		while (current->parent->color == rb_tree_node<T>::colors::red)
        {
			if (current->parent == current->parent->parent->right) //нода справа
            {
				uncle = current->parent->parent->left;
				if (uncle && uncle->color == rb_tree_node<T>::colors::red) 
                {
					// случай 1
					uncle->color = rb_tree_node<T>::colors::black;
					current->parent->color = rb_tree_node<T>::colors::black;
					current->parent->parent->color = rb_tree_node<T>::colors::red;
					current = current->parent->parent;
				}
                else 
                {
					if (current == current->parent->left) 
                    {
						// случай 2
						current = current->parent;
						rotate_right(current);
					}
					// случай 3
					current->parent->color = rb_tree_node<T>::colors::black;
					current->parent->parent->color = rb_tree_node<T>::colors::red;
					rotate_left(current->parent->parent);
				}
			}
            else //нода слева
            {
				uncle = current->parent->parent->right;
				if (uncle && uncle->color == rb_tree_node<T>::colors::red) 
                {
					// случай 1 справа
					uncle->color = rb_tree_node<T>::colors::black;
					current->parent->color = rb_tree_node<T>::colors::black;
					current->parent->parent->color = rb_tree_node<T>::colors::red;
					current = current->parent->parent;	
                }
                else 
                {
					if (current == current->parent->right)
                    {
						// случай 2 справа
						current = current->parent;
						rotate_left(current);
					}
					// случай 3 справа
					current->parent->color = rb_tree_node<T>::colors::black;
					current->parent->parent->color = rb_tree_node<T>::colors::red;
					rotate_right(current->parent->parent);
				}
			}
			if (current == root)
				break;
		}
		root->color = rb_tree_node<T>::colors::black;
	}
    /* void fix_tree(rb_tree_node<T> * current)
    {
        rb_tree_node<T> * up = nullptr, * upup = nullptr;
        while(current->parent
        && current->color == rb_tree_node<T>::colors::red
        && current->parent->color == rb_tree_node<T>::colors::red)
        {
            up = current->parent;
            upup = up->parent;//может быть nullptr
            if(!upup) {up->color = rb_tree_node<T>::colors::black; break;}//выход из цикла
            if(up == upup->left)
            {
                rb_tree_node<T> * uncle = upup->right;
                if(uncle && uncle->color == rb_tree_node<T>::colors::red)
                {
                    uncle->color = rb_tree_node<T>::colors::black;//можно, так как потомки uncle точно черные
                    up->color = rb_tree_node<T>::colors::black;
                    upup->color = rb_tree_node<T>::colors::red;
                    current = upup; продолжение цикла
                }
                else дяди либо нет, либо он черный
                {
                    if(current == up->right)
                    {
                        printf("ДО ЛЕВОГО ПОВОРОТА 1\n\n");
                        printf("КОЛИЧЕСТВО ЭЛЕМЕНТОВ = %d\n\n", get_elements());
                        print(1000);
                        rotate_left(up);
                        printf("ПОСЛЕ ЛЕВОГО ПОВОРОТА 1\n\n");
                        printf("КОЛИЧЕСТВО ЭЛЕМЕНТОВ = %d\n\n", get_elements());
                        print(1000);
                        current = up; //продолжение цикла
                        up = current->parent;
                    }
                    else
                    {
                        printf("ДО ПРАВОГО ПОВОРОТА 1\n\n");
                        printf("КОЛИЧЕСТВО ЭЛЕМЕНТОВ = %d\n\n", get_elements());
                        print(1000);
                        rotate_right(upup);
                        printf("ПОСЛЕ ПРАВОГО ПОВОРОТА 1\n\n");
                        printf("КОЛИЧЕСТВО ЭЛЕМЕНТОВ = %d\n\n", get_elements());
                        print(1000);
                        current = up;
                    }
                }
            }
            else //up == upup->right
            {
                rb_tree_node<T> * uncle = upup->left;
				if(uncle && uncle->color == rb_tree_node<T>::colors::red)
				{
				    uncle->color = rb_tree_node<T>::colors::black;
					up->color = rb_tree_node<T>::colors::black;
					upup->color = rb_tree_node<T>::colors::red;
					current = upup;
				}
				else
				{
					if(current == up->right)
					{
                        printf("ДО ЛЕВОГО ПОВОРОТА 2\n\n");
                        printf("КОЛИЧЕСТВО ЭЛЕМЕНТОВ = %d\n\n", get_elements());
                        print(1000);
						rotate_left(up);
                        printf("ПОСЛЕ ЛЕВОГО ПОВОРОТА 2\n\n");
                        printf("КОЛИЧЕСТВО ЭЛЕМЕНТОВ = %d\n\n", get_elements());
                        print(1000);
						current = up;					
					}
					else
					{
                        printf("ДО ЛЕВОГО ПОВОРОТА 3\n\n");
                        current->print();
                        printf("КОЛИЧЕСТВО ЭЛЕМЕНТОВ = %d\n\n", get_elements());
                        print(1000);
						rotate_left(upup);
                        printf("ПОСЛЕ ЛЕВОГО ПОВОРОТА 3\n\n");
                        current->print();
                        printf("КОЛИЧЕСТВО ЭЛЕМЕНТОВ = %d\n\n", get_elements());
                        print(1000);
						current = up;
					}							
				}
            }
        }
    } */
    void rotate_left(rb_tree_node<T> * current) 
    {
		rb_tree_node<T> * right_child = current->right;
		current->right = right_child->left;
		if (right_child->left != nullptr)
			right_child->left->parent = current;
		right_child->parent = current->parent;
		if (current->parent == nullptr) 
			this->root = right_child;
        else if (current == current->parent->left) 
        {
			current->parent->left = right_child;
		} 
        else 
        {
			current->parent->right = right_child;
		}
		right_child->left = current;
		current->parent = right_child;
	}
    void rotate_right(rb_tree_node<T> * current) //даблчекнуть, правильно ли все работает
    {
		rb_tree_node<T> * left_child = current->left;
		current->left = left_child->right;
		if (left_child->right != nullptr) {
			left_child->right->parent = current;
		}
		left_child->parent = current->parent;
		if (current->parent == nullptr) {
			this->root = left_child;
		} else if (current == current->parent->right) {
			current->parent->right = left_child;
		} else {
			current->parent->left = left_child;
		}
		left_child->right = current;
		current->parent = left_child;
	}
    /*void rotate_right(rb_tree_node<T> * current)
    {
        rb_tree_node<T> * left_child = current->left;
        current->left = left_child->right;
        if(current->left)
            current->left->parent = current;
        left_child->parent = current->parent;
        if(!current->parent)
            {root = left_child; left_child->parent = nullptr;}
        else
        {
            if(current == current->parent->right)
                current->parent->right = left_child;
            else
                current->parent->left = left_child;
            left_child->right = current;
            current->parent = left_child;
        }
    }*/
public:
    int countSmallSTCardinality(int k)
    {
        if(!root)
            return 0;
        int counter = 0, prevElem = 0;
        if(root->left)
            countSmallSTCardinalityUtil(root->left, k, &counter, &prevElem);
        if(root->right)
            countSmallSTCardinalityUtil(root->right, k, &counter, &prevElem);
        return counter;
    }

    int countSmallSTCardinalityUtil(rb_tree_node<T> * current, int k, int* globalC, int * prevElem)
    {
        if(!current->left && !current->right)
        {
            if(!(k < 1))
                (*globalC)++;
            *prevElem = 1;
            return 1;
        }
        int vertCounter = 1, elemCounter = 1;
        if(current->left)
        {
            vertCounter += countSmallSTCardinalityUtil(current->left, k, globalC, prevElem);
            elemCounter += *prevElem;
        }
        if(current->right)
        {
            vertCounter += countSmallSTCardinalityUtil(current->right, k, globalC, prevElem);
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
        if(root->left)
            countShortSTCardinalityUtil(root->left, k, &counter, &prevElem);
        prevElem = 0;
        if(root->right)
            countShortSTCardinalityUtil(root->right, k, &counter, &prevElem);
        return counter;
    }

    int countShortSTCardinalityUtil(rb_tree_node<T> * current, int k, int* counter, int * prevElem)
    {
        if(!current->left && !current->right)
            {
                if(!(k < 1))
                    (*counter)++;
                *prevElem = 1;
                return 1;
            }
        int level1 = 0, elemCounter = 1, level2 = 0;
        if(current->left)
        {
            level1 = countShortSTCardinalityUtil(current->left, k, counter, prevElem);
            elemCounter += *prevElem;
        }
        if(current->right)
        {
            level2 = countShortSTCardinalityUtil(current->right, k, counter, prevElem);
            elemCounter += *prevElem;
        }
        if(level2 > level1)
            level1 = level2;
        if(!(k < level1 + 1))
            *counter += elemCounter;
        *prevElem = elemCounter;
        return level1 + 1;
    }
    int get_subtree_height(rb_tree_node<T> * current)
    {
        if(!current)
            return 0;
        if(!current->left && !current->right)
            return 1;
        int level1 = 0, level2 = 0;
        if(current->left)
            level1 = get_subtree_height(current->left);
        if(current->right)
            level2 = get_subtree_height(current->right);
        if(level2 > level1)
            level1 = level2;
        return level1 + 1;
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
        if(root->left)
            countSlimSTCardinalityUtil(root->left, k, sizes, len, arr_pos, &counter);
        if(root->right)
            countSlimSTCardinalityUtil(root->right, k, sizes, len, arr_pos, &counter);
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
    void fillSizes(rb_tree_node<T>* current, int * sizes, int arr_pos, int * counter)
    {
        if(!current->left && !current->right)
        {
            sizes[arr_pos]++;
            (*counter)++;
            return;
        }
        *counter += 1;
        sizes[arr_pos]++;
        if(current->left)
            fillSizes(current->left, sizes, arr_pos + 1, counter);
        if(current->right)
            fillSizes(current->right, sizes, arr_pos + 1, counter);
        return;
    }
    void countSlimSTCardinalityUtil(rb_tree_node<T> * current, int k, int * sizes, int len, int arr_pos, int * counter)
    {
        if(!current)
            return;
        int elemCounter = 0;
        fillSizes(current, sizes, arr_pos, &elemCounter);
        if(!(k < findMax(sizes, len)))
            *counter += elemCounter;
        flush(sizes, len);
        if(current->left)
            countSlimSTCardinalityUtil(current->left, k, sizes, len, arr_pos + 1, counter);
        if(current->right)
            countSlimSTCardinalityUtil(current->right, k, sizes, len, arr_pos + 1, counter);
        return;
    }
    int countElementsOnLvlK(int k)
    {
        if(!root)
            return 0;
        int currLevel = 0;
        return countElementsOnLvlKUtil(root, k, currLevel);
    }
    int countElementsOnLvlKUtil(rb_tree_node<T> * current, int k, int currLevel)
    {
        if(!current)
            return 0;
        int counter = 0;
        if(current && currLevel == k)
            counter++;
        counter += countElementsOnLvlKUtil(current->left, k, currLevel + 1);
        counter += countElementsOnLvlKUtil(current->right, k, currLevel + 1);
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
    int countKBranchesUtil(rb_tree_node<T> * current, int k, int currLevel, int * globalC)
    {
        if(!current->left && !current->right)
        {
            if(currLevel == k)
                {   
                    *globalC += 1;
                    return 1;
                }
            else 
                return 0;
        }
        int counter = 0;
        if(current->left)
            counter += countKBranchesUtil(current->left, k, currLevel + 1, globalC);
        if(current->right)
            counter += countKBranchesUtil(current->right, k, currLevel + 1, globalC);
        if(counter != 0)
        {
            *globalC += counter;
        }
        return counter;
    }
};
#endif