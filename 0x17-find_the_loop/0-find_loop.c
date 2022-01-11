/* listint_t */
#include "lists.h"


/**
 * find_listint_loop - finds the loop in a linked list using Tortoise and Hare
 *   algorithm
 *
 * @head: head of SLL of integers
 * Return: pointer to node where the loop starts, or NULL if there is no loop
 */
listint_t *find_listint_loop(listint_t *head)
{
	listint_t *tortoise, *hare;

	if (!head || !head->next)
		return (NULL);

	hare = tortoise = head;
	while (hare && hare->next)
	{
		tortoise = tortoise->next;
		hare = hare->next->next;

		if (tortoise == hare)
		{
			tortoise = head;
			while (tortoise != hare)
			{
				tortoise = tortoise->next;
				hare = hare->next;
			}

			return (hare);
		}
	}

	return (NULL);
}
