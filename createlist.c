#include "apc.h"

int creat_list_from_number(const char *number, Dlist **head, Dlist **tail)
{
    int i = 0;
    if (number[0] == '-' || number[0] == '+')
    {
        i++; // optional: handle negative numbers later
    }
    while (number[i] == '0')
    {
        i++;
    }

    if (number[i] == '\0')
    {
        Dlist *new = malloc(sizeof(Dlist));
        if (new == NULL)
            return FAILURE;
        new->data = 0;
        new->next = new->prev = NULL;
        *head = *tail = new;
        return SUCCESS;
    }

    for (; number[i] != '\0'; i++)
    {
        if (number[i] >= '0' && number[i] <= '9')
        {
            Dlist *new = malloc(sizeof(Dlist));
            if (!new)
                return FAILURE;
            new->data = number[i] - '0';
            new->next = NULL;
            new->prev = *tail;
            if (*tail)
                (*tail)->next = new;
            else
                *head = new;
            *tail = new;
        }
        else
        {
            printf("Invalid character in number.\n");
            return FAILURE;
        }
    }
    return SUCCESS;
}

void print_list(Dlist *head)
{
    if (!head)
    {
        printf("List is empty\n");
        return;
    }
    while (head)
    {
        printf("%d", head->data);
        head = head->next;
    }
    printf("\n");
}

void free_list(Dlist **head)
{
    Dlist *temp = *head;
    while (temp)
    {
        *head = temp->next;
        free(temp);
        temp = *head;
    }
}

// Compare two lists as numbers: returns 1 if head1 > head2, -1 if head1 < head2, 0 if equal
int compare_lists(Dlist *head1, Dlist *head2)
{
    int len1 = 0, len2 = 0;
    Dlist *temp1 = head1, *temp2 = head2;

    while (temp1)
    {
        len1++;
        temp1 = temp1->next;
    }
    while (temp2)
    {
        len2++;
        temp2 = temp2->next;
    }

    if (len1 > len2)
        return 1;
    if (len1 < len2)
        return -1;

    temp1 = head1;
    temp2 = head2;

    while (temp1 && temp2)
    {
        if (temp1->data > temp2->data)
            return 1;
        if (temp1->data < temp2->data)
            return -1;

        temp1 = temp1->next;
        temp2 = temp2->next;
    }

    return 0;
}

// Check if the result list is zero
int is_zero_list(Dlist *head)
{
    while (head)
    {
        if (head->data != 0)
            return 0;
        head = head->next;
    }
    return 1;
}

// Add a '-' sign node at the beginning
void prepend_sign_node(Dlist **head, Dlist **tail, char sign)
{
    Dlist *new = malloc(sizeof(Dlist));
    if (!new)
        return;

    new->data = sign; // storing ASCII code of '-' to differntiate
    new->prev = NULL;
    new->next = *head;

    if (*head)
        (*head)->prev = new;
    else
        *tail = new;

    *head = new;
}
