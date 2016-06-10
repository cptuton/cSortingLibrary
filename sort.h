#ifndef _SORT_
#define _SORT_

#ifdef _NO_ASSERT_
#define NDEBUG
#endif

#ifndef _NO_LIBS_
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#endif

/*typedefines*/
typedef unsigned char byte;
typedef int (*comparator_t)(void *arg1, void *arg2);
typedef void *heap_t;
typedef long long int sign;

/*sorting functions*/
void bubble_sort (void *list, comparator_t compar, size_t size, size_t n_mem);
void merge_sort  (void *list, comparator_t compar, size_t size, size_t base, size_t n_mem);
void bogo_sort   (void *list, comparator_t compar, size_t size, size_t n_mem);
void select_sort (void *list, comparator_t compar, size_t size, size_t n_mem);
void count_sort  (int *list, size_t n_mem);
void heap_sort   (void *list, comparator_t compar, size_t size, size_t n_mem);

/*helper functions*/
void swap       (void *x, void *y, size_t size);
void merge      (void *list, comparator_t compar, size_t size, size_t base, size_t mid, size_t last);
int sorted      (void *list, comparator_t compar, size_t size, size_t n_mem);
int max_of_list (int *list, size_t n_mem);
heap_t new_heap (void *list, comparator_t compar, size_t size, size_t n_mem);

/*comparison functions*/
/*NOTE: THESE MAY ALL BE PASSED INTO new_comparator() or passed directly into sorting functions*/
int int_compare_gt  (void *a, void *b);
int int_compare_lt  (void *a, void *b);
int str_compare_gt  (void *a, void *b);
int str_compare_lt  (void *a, void *b);
int char_compare_gt (void *a, void *b);
int char_compare_lt (void *a, void *b);

/*create new comparator*/
comparator_t new_comparator (int (*compar)(void *arg1, void *arg2));

#endif
