#include "apc.h"

int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{

    if (*head1 == NULL || (*head1)->data == 0)
    {
        printf("The number should not be zero\n");
        return FAILURE;
    }
    if (*head2 == NULL)
    {
        printf("The number should not be zero\n");
        return FAILURE;
    }
    if ((*head2)->data == 0)
    {
        Dlist *new = malloc(sizeof(Dlist));
        if (new == NULL)
        {
            printf("Memory allocation failed\n");
            return FAILURE;
        }
        new->data = 0;
        new->next = new->prev = NULL;
        *headR = *tailR = new;
        return SUCCESS;
    }

    // Convert linked lists to numbers
    unsigned long long int number1 = 0, number2 = 0;
    Dlist *temp1 = *head1;
    while (temp1 != NULL)
    {
        number1 = number1 * 10 + temp1->data;
        temp1 = temp1->next;
    }
    Dlist *temp2 = *head2;
    while (temp2 != NULL)
    {
        number2 = number2 * 10 + temp2->data;
        temp2 = temp2->next;
    }

    // If number1 < number2, quotient is 0
    if (number1 < number2)
    {
        Dlist *new = malloc(sizeof(Dlist));
        if (!new)
        {
            printf("Memory allocation failed\n");
            return FAILURE;
        }
        new->data = 0;
        new->next = new->prev = NULL;
        *headR = *tailR = new;
        return SUCCESS;
    }

    // Calculate quotient by repeated subtraction
    int count = 0;
    while (number1 >= number2)
    {
        number1 -= number2;
        count++;
    }

    // Handle count == 0 explicitly
    if (count == 0)
    {
        Dlist *new = malloc(sizeof(Dlist));
        if (!new)
        {
            printf("Memory allocation failed\n");
            return FAILURE;
        }
        new->data = 0;
        new->next = new->prev = NULL;
        *headR = *tailR = new;
        return SUCCESS;
    }

    // Build result list from count with digits in correct order
    int digits[20]; // enough for int max digits
    int idx = 0;

    // Extract digits in reverse order
    while (count > 0)
    {
        digits[idx++] = count % 10;
        count /= 10;
    }

    // Insert digits in forward order (MSD to LSD)
    for (int i = idx - 1; i >= 0; i--)
    {
        Dlist *new = malloc(sizeof(Dlist));
        if (!new)
        {
            printf("Memory allocation failed\n");
            return FAILURE;
        }
        new->data = digits[i];
        new->next = NULL;
        new->prev = *tailR;

        if (*tailR)
            (*tailR)->next = new;
        else
            *headR = new;

        *tailR = new;
    }

    return SUCCESS;
}
