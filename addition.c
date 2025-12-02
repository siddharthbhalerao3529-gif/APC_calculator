
#include "apc.h"

int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
	int carry = 0;
	Dlist *temp1 = *tail1;
	Dlist *temp2 = *tail2;

	while (temp1 != NULL || temp2 != NULL || carry != 0)
	{
		int digit1 = (temp1 != NULL) ? temp1->data : 0;
		int digit2 = (temp2 != NULL) ? temp2->data : 0;
		int sum = digit1 + digit2 + carry;
		carry = sum / 10;
		int digit = sum % 10;
		Dlist *new = malloc(sizeof(Dlist));
		if (new == NULL)
		{
			return FAILURE;
		}
		new->data = digit;
		new->next = NULL;
		new->prev = NULL;
		if (*headR == NULL && *tailR == NULL)
		{
			*tailR = new;
			*headR = new;
		}
		else
		{
			new->next = *headR;
			(*headR)->prev = new;
			*headR = new;
		}
		if (temp1)
			temp1 = temp1->prev;
		if (temp2)
			temp2 = temp2->prev;
	}
	return SUCCESS;
}
