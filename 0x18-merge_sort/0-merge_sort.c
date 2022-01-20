#include <stdlib.h>
#include <stdio.h>
#include "sort.h"


/**
 * merge_sort - use merge sort in place on an array of integers
 * @array: array to sort
 * @size: size of array
 */
void merge_sort(int *array, size_t size)
{
	int *left, *right, *start = array, top;
	size_t lsize = size / 2, rsize = size / 2 + size % 2;
	static int *buffer, *alloc, idx, i;

	if (array == NULL || size <= 1)
		return;
	top = 0;
	if (buffer == NULL)
	{
		top = 1;
		buffer = malloc(sizeof(int) * size);
	}
	alloc = buffer;
	merge_sort(array, lsize);
	merge_sort(array + lsize, rsize);
	left = array;
	right = array + lsize;
	printf("Merging...\n[left]: ");
	print_array(left, lsize);
	printf("[right]: ");
	print_array(right, rsize);
	for (idx = 0; lsize > 0 && rsize > 0; idx++)
	{
		if (*left < *right)
		{
			buffer[idx] = *left;
			left++;
			lsize--;
		}
		else
		{
			buffer[idx] = *right;
			right++;
			rsize--;
		}
	}
	idx--;
	for (i = idx + 1; lsize; lsize--, left++, i++)
		array[i] = *left;
	for (i = idx + 1; rsize; rsize--, right++, i++)
		array[i] = *right;
	for (; idx >= 0; idx--)
		array[idx] = buffer[idx];
	printf("[Done]: ");
	print_array(start, size);
	if (top)
		free(alloc);
}
