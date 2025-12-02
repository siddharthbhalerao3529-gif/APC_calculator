#ifndef APC_H
#define APC_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SUCCESS 0
#define FAILURE -1

typedef int data_t;
typedef struct node
{
	struct node *prev;
	data_t data;
	struct node *next;
}Dlist;

/* Include the prototypes here */
int creat_list_from_number(const char *number, Dlist **head, Dlist **tail);
int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR);
int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR);
int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR ,Dlist **tailR);
int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR , Dlist **tailR);
void print_list(Dlist *reshead);
void free_list(Dlist **reshead);
int compare_lists(Dlist *head1, Dlist *head2);
int is_zero_list(Dlist *head);
void prepend_sign_node(Dlist **head, Dlist **tail, char sign);

#endif
