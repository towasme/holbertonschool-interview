#include "search.h"
skiplist_t *node_index(skiplist_t *list, skiplist_t *current, int value);

/**
* node_index - Finds the index of the node
* @list: A pointer to teh head of the skip list
* @current: Pointer to current node
* @value: Value to search for
*
* Return: Pointer to node where value is and formatted print statement
*/

skiplist_t *node_index(skiplist_t *list, skiplist_t *current, int value)
{

	while (list && list->index <= current->index)
	{
		printf("Value checked at index [%ld] = [%d]\n", list->index, list->n);

		if (list->n == value)
		{
			return (list);
		}
		list = list->next;
	}
	return (NULL);
}

/**
* linear_skip - Searches for a value in a sorted skip list of integers.
* @list: A pointer to the head of the skip list to search in
* @value: Value to search for
*
* Example:
* [0]---------------->[4]------------------>[18]------------->[61]
* [0]->[1]->[2]->[3]->[4]->[7]->[12]->[15]->[18]->[23]->[53]->[61]->[76]->[99]
*
* Return: Pointer on the first node where value is located or NULL
*/

skiplist_t *linear_skip(skiplist_t *list, int value)
{
	skiplist_t *current, *previous;
	size_t current_index, previous_index;

	if (!list)
	{
		return (NULL);
	}

	current = list;
	/* In the express lane... */
	while (current->express)
	{
		previous = current;
		current = current->express;
		current_index = current->index;
		previous_index = previous->index;

		printf("Value checked at index [%ld] = [%d]\n",
						current_index, current->n);

		if (previous->n > value && previous->index == 0)
			return (NULL);
		if (current->n >= value)
			break;
	}

	if (!current->express && current->n < value)
	{
		previous = current;
		previous_index = previous->index;

		while (current->next)
		{
			current = current->next;
		}
		current_index = current->index;
	}
	printf("Value found between indexes [%ld] and [%ld]\n",
							previous_index, current_index);
	return (node_index(previous, current, value));
}
