#ifndef _SORT_
#define _SORT_

#include <stdlib.h>
#include <string.h>

typedef unsigned char byte;

void swap (void *x, void *y, size_t size);

void bubble_sort (void *list, int (*compar)(void *arg1, void *arg2), size_t size, size_t n_mem);
void merge_sort  (void *list, int (*compar)(void *arg1, void *arg2), size_t size, size_t base, size_t n_mem);
void merge       (void *list, int (*compar)(void *arg1, void *arg2), size_t size, size_t base, size_t mid, size_t last);
void bogo_sort   (void *list, int (*compar)(void *arg1, void *arg2), size_t size, size_t n_mem);
void select_sort (void *list, int (*compar)(void *arg1, void *arg2), size_t size, size_t n_mem);
int sorted       (void *list, int (*compar)(void *arg1, void *arg2), size_t size, size_t n_mem);
void count_sort  (int *list, size_t n_mem);
int max_of_list  (int *list, size_t n_mem);

#endif
