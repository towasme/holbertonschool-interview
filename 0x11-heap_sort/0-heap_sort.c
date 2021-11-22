#include "sort.h"
/**
 * heap_sort - heap sort
 *
 * @array: Array of integers to be printed
 * @size: Number of elements in @array
 */
void heap_sort(int *array, size_t size)
{
	int limit_index, i, first_node_index, last_node_index;

	for (i = 0; i < (int)size; i++)
	{
		limit_index = (int)size - (i + 1);

		build_heap_sort(array, limit_index, 0, size);

		first_node_index = 0;
		last_node_index = limit_index;

		if (((int)size - 1) != i)
			siftDown(array, first_node_index, last_node_index, size);
	}
}

/**
 * build_heap_sort - Build heap sort
 *
 * @array: Array of integers to be printed
 * @limit: Limit index
 * @index: current index
 * @size: Number of elements in @array
 */
void build_heap_sort(int *array, int limit, int index, size_t size)
{
	int left = 1, right = 2, child_left_index,
		child_right_index, higher_child_index;

	child_left_index = get_index_child(limit, index, left);
	child_right_index = get_index_child(limit, index, right);

	if (child_left_index)
		build_heap_sort(array, limit,  child_left_index, size);
	if (child_right_index)
		build_heap_sort(array, limit, child_right_index, size);

	if (child_left_index || child_right_index)
	{
		if (child_left_index && child_right_index)
		{
			if (array[child_left_index] > array[child_right_index])
				higher_child_index = child_left_index;
			else
				higher_child_index = child_right_index;
		} else if (child_left_index && !child_right_index)
		{
			higher_child_index = child_left_index;
		} else
		{
			higher_child_index = child_right_index;
		}

		if (array[higher_child_index] > array[index])
		{
			siftDown(array, index, higher_child_index, size);
			build_heap_sort(array, limit, index, size);
		}
	}
}

/**
 * get_index_parent - get index parent
 *
 * @index: Current index
 * Return: parent index
 */
int get_index_parent(int index)
{
	return ((index - 1) / 2);
}

/**
 * get_index_child - get index child
 *
 * @limit: Array of integers to be printed
 * @parent_index: Number of elements in @array
 * @side: side
 * Return: get index child
 */
int get_index_child(int limit, int parent_index, int side)
{
	int child_index =  2 * parent_index + side;

	if (child_index > limit)
		return (0);
	return (child_index);
}

/**
 * siftDown - sift down
 *
 * @array: Array of integers to be printed
 * @index_a: index a
 * @index_b: index b
 * @size: Number of elements in @array
 */
void siftDown(int *array, int index_a, int index_b, size_t size)
{
	int temp;

	temp = array[index_a];
	array[index_a] = array[index_b];
	array[index_b] = temp;
	print_array(array, size);
}
