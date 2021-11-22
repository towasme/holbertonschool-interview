#ifndef SORT_H
#define SORT_H
#include <stdio.h>
#include <stdlib.h>

void heap_sort(int *array, size_t size);
void build_heap_sort(int *array, int limit, int index, size_t size);
int get_index_parent(int index);
int get_index_child(int limit, int parent_index, int side);
void print_array(const int *array, size_t size);
void siftDown(int *array, int index_a, int index_b, size_t size);

#endif /* SORT_H */
