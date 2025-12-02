#include "apc.h"

int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
    int borrow = 0;
    Dlist *temp1 = *tail1;
    Dlist *temp2 = *tail2;

    while (temp1 != NULL || temp2 != NULL)
    {
        int digit1 = (temp1 != NULL) ? temp1->data : 0;
        int digit2 = (temp2 != NULL) ? temp2->data : 0;

        digit1 -= borrow; // Apply borrow from previous step

        if (digit1 < digit2)
        {
            digit1 += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        int diff = digit1 - digit2;

        // Insert new node at the HEAD of the result list (to maintain order)
        Dlist *new = malloc(sizeof(Dlist));
        if (new == NULL)
        {
            return FAILURE;
        }
        new->data = diff;
        new->prev = NULL;
        new->next = *headR;

        if (*headR != NULL)
        {
            (*headR)->prev = new;
        }
        else
        {
            *tailR = new; // If result list is empty, set tail
        }
        *headR = new;

        if (temp1)
            temp1 = temp1->prev;
        if (temp2)
            temp2 = temp2->prev;
    }

    // Remove leading zeros (e.g., 009 → 9)
    while (*headR != NULL && (*headR)->data == 0 && (*headR)->next != NULL)
    {
        Dlist *temp = *headR;
        *headR = (*headR)->next;
        (*headR)->prev = NULL;
        free(temp);
    }

    return SUCCESS;
}