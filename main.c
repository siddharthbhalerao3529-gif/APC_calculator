/*
name        - Siddhart Bhalerao
date        - 4-8-25
description - This program implements an Arbitrary Precision Calculator (APC) that performs
              addition, subtraction, multiplication, and division on integers of any size
              using doubly linked lists. It supports signed numbers, handles leading zeros,
              and avoids overflow by storing each digit as a separate node.
*/

#include "apc.h"


int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Usage: ./a.out <num1> <operator> <num2>\n");
        return -1;
    }

    int sign1 = 1, sign2 = 1;
    char *numStr1 = argv[1], *numStr2 = argv[3];

    if (numStr1[0] == '-')
    {
        sign1 = -1;
        numStr1++;
    }
    if (numStr2[0] == '-')
    {
        sign2 = -1;
        numStr2++;
    }

    Dlist *head1 = NULL, *tail1 = NULL;
    Dlist *head2 = NULL, *tail2 = NULL;
    Dlist *reshead = NULL, *restail = NULL;

    if (creat_list_from_number(numStr1, &head1, &tail1) == FAILURE ||
        creat_list_from_number(numStr2, &head2, &tail2) == FAILURE)
    {
        printf("Error in creating list\n");
        return -1;
    }

    char operator = argv[2][0];
    int status = FAILURE;

    switch (operator)
    {
        case '+':
            if (sign1 == sign2)
            {
                status = addition(&head1, &tail1, &head2, &tail2, &reshead, &restail);
                if (status == SUCCESS && sign1 == -1 && !is_zero_list(reshead))
                    prepend_sign_node(&reshead, &restail, '-');
            }
            else
            {
                int comp = compare_lists(head1, head2);
                if (comp == 0)
                {
                    Dlist *new = malloc(sizeof(Dlist));
                    if (!new) return -1;
                    new->data = 0;
                    new->prev = new->next = NULL;
                    reshead = restail = new;
                    status = SUCCESS;
                }
                else if (comp > 0)
                {
                    status = subtraction(&head1, &tail1, &head2, &tail2, &reshead, &restail);
                    if (status == SUCCESS && sign1 == -1)
                        prepend_sign_node(&reshead, &restail, '-');
                }
                else
                {
                    status = subtraction(&head2, &tail2, &head1, &tail1, &reshead, &restail);
                    if (status == SUCCESS && sign2 == -1)
                        prepend_sign_node(&reshead, &restail, '-');
                }
            }
            break;

        case '-':
            if (sign1 == sign2)
            {
                if (sign1 == -1)
                {
                    int comp = compare_lists(head1, head2);
                    if (comp == 0)
                    {
                        Dlist *new = malloc(sizeof(Dlist));
                        if (!new) return -1;
                        new->data = 0;
                        new->prev = new->next = NULL;
                        reshead = restail = new;
                        status = SUCCESS;
                    }
                    else if (comp < 0)
                    {
                        status = subtraction(&head2, &tail2, &head1, &tail1, &reshead, &restail);
                    }
                    else
                    {
                        status = subtraction(&head1, &tail1, &head2, &tail2, &reshead, &restail);
                        if (status == SUCCESS && !is_zero_list(reshead))
                            prepend_sign_node(&reshead, &restail, '-');
                    }
                }
                else
                {
                    int comp = compare_lists(head1, head2);
                    if (comp == 0)
                    {
                        Dlist *new = malloc(sizeof(Dlist));
                        if (!new) return -1;
                        new->data = 0;
                        new->prev = new->next = NULL;
                        reshead = restail = new;
                        status = SUCCESS;
                    }
                    else if (comp > 0)
                    {
                        status = subtraction(&head1, &tail1, &head2, &tail2, &reshead, &restail);
                    }
                    else
                    {
                        status = subtraction(&head2, &tail2, &head1, &tail1, &reshead, &restail);
                        if (status == SUCCESS && !is_zero_list(reshead))
                            prepend_sign_node(&reshead, &restail, '-');
                    }
                }
            }
            else
            {
                status = addition(&head1, &tail1, &head2, &tail2, &reshead, &restail);
                if (status == SUCCESS && sign1 == -1 && !is_zero_list(reshead))
                    prepend_sign_node(&reshead, &restail, '-');
            }
            break;

        case 'x':
        case 'X':
        // case '*':
            status = multiplication(&head1, &tail1, &head2, &tail2, &reshead, &restail);
            if (status == SUCCESS && sign1 != sign2 && !is_zero_list(reshead))
                prepend_sign_node(&reshead, &restail, '-');
            break;

        case '/':
            if (is_zero_list(head2))
            {
                Dlist *new = malloc(sizeof(Dlist));
                if (!new) return -1;
                new->data = 0;
                new->prev = new->next = NULL;
                reshead = restail = new;
                status = SUCCESS;
            }
            else
            {
                status = division(&head1, &tail1, &head2, &tail2, &reshead, &restail);
                if (status == SUCCESS && sign1 != sign2 && !is_zero_list(reshead))
                    prepend_sign_node(&reshead, &restail, '-');
            }
            break;

        default:
            printf("Invalid operator\n");
            return 1;
    }

    if (status == SUCCESS)
    {
        printf("Result: ");
        if (reshead && reshead->data == '-')
        {
            printf("-");
            reshead = reshead->next;
        }
        print_list(reshead);
    }
    else
    {
        printf("Operation failed.\n");
    }

    free_list(&reshead);
    free_list(&head1);
    free_list(&head2);

    return 0;
}
