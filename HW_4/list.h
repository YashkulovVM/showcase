#ifndef LIST_H
#define LIST_H
#include "student.h"
void print_list(int p, list_node* head);
io_status read_list(const char *name, list_node **head);
void delete_list(list_node* head);
#endif