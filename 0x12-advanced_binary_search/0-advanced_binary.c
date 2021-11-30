#include "search_algos.h"

/**
 * print_array - Prints an array
 * @array: Address first elem
 * @min: left side
 * @max: right side
 *
 */
void print_array(int *array, int min, int max)
{
        int i;

        for (i = min; i < max; i++)
                printf("%d, ", array[i]);

        printf("%d\n", array[i]);
}

/**
 * search_binary - Binary search
 * @array: Address first elem
 * @min: left side
 * @max: right side
 * @value: Target
 *
 * Return: index otherwise -1
 */
int search_binary(int *array, int min, int max, int value)
{
        int mid;

        if (min > max)
                return (-1);

        printf("Searching in array: ");
        print_array(array, min, max);

        if (min == max && array[max] == value)
                return (max);

        if (min == max && array[max] != value)
                return (-1);

        mid = min + (max - min) / 2;

        if ((mid == min || value != array[mid - 1]) && array[mid] == value)
                return (mid);

        if (array[mid] >= value)
                return (search_binary(array, min, mid, value));
        return (search_binary(array, mid + 1, max, value));
}

/**
 * advanced_binary - Binary search
 * @array: Address first elem
 * @size: Length array
 * @value: Target
 *
 * Return: First occurrence othersie -1
 */
int advanced_binary(int *array, size_t size, int value)
{

        if (!array || size == 0)
                return (-1);

        return (search_binary(array, 0, size - 1, value));
}
