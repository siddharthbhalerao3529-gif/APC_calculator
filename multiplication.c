#include "apc.h"

int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
    if (*head1 == NULL || *head2 == NULL)
    {
        return FAILURE;
    }

    Dlist *temp2 = *tail2;
    int shift = 0; // To handle positional shifts (powers of 10)

    while (temp2 != NULL)
    {
        Dlist *temp1 = *tail1;
        int carry = 0;
        Dlist *partial_head = NULL, *partial_tail = NULL;

        // Multiply head1 with current digit of head2
        while (temp1 != NULL || carry != 0)
        {
            int digit1 = (temp1 != NULL) ? temp1->data : 0;
            int product = digit1 * temp2->data + carry;
            carry = product / 10;
            int digit = product % 10;

            // Store the result digit in partial result
            Dlist *new_node = malloc(sizeof(Dlist));
            if (new_node == NULL)
            {
                free_list(&partial_head);
                return FAILURE;
            }
            new_node->data = digit;
            new_node->prev = NULL;
            new_node->next = partial_head;

            if (partial_head != NULL)
            {
                partial_head->prev = new_node;
            }
            else
            {
                partial_tail = new_node;
            }
            partial_head = new_node;

            if (temp1)
                temp1 = temp1->prev;
        }

        // Add trailing zeros for positional shift
        for (int i = 0; i < shift; i++)
        {
            Dlist *zero_node = malloc(sizeof(Dlist));
            if (zero_node == NULL)
            {
                free_list(&partial_head);
                return FAILURE;
            }
            zero_node->data = 0;
            zero_node->prev = partial_tail;
            zero_node->next = NULL;

            if (partial_tail != NULL)
            {
                partial_tail->next = zero_node;
            }
            else
            {
                partial_head = zero_node;
            }
            partial_tail = zero_node;
        }

        // Add partial result to final result
        if (*headR == NULL)
        {
            *headR = partial_head;
            *tailR = partial_tail;
        }
        else
        {
            Dlist *sum_head = NULL, *sum_tail = NULL;
            addition(&partial_head, &partial_tail, headR, tailR, &sum_head, &sum_tail);
            free_list(headR);
            *headR = sum_head;
            *tailR = sum_tail;
            free_list(&partial_head);
        }

        shift++;
        temp2 = temp2->prev;
    }

    // Remove leading zeros
    while (*headR != NULL && (*headR)->data == 0 && (*headR)->next != NULL)
    {
        Dlist *temp = *headR;
        *headR = (*headR)->next;
        (*headR)->prev = NULL;
        free(temp);
    }

    return SUCCESS;
}