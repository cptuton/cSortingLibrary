#include "sort.h"

int int_compare_gt (void *a, void *b)
{
    return (*(int *)a > *(int *)b ? 1 : 0);
}

int int_compare_lt (void *a, void *b)
{
    return (*(int *)a < *(int *)b ? 1 : 0);
}

int str_compare_gt (void *a, void *b)
{
    return (strncmp ((char *)a, (char *)b, strlen ((char *)a)) >= 0 ? 1 : 0);
}

int str_compare_lt (void *a, void *b)
{
    return (strncmp ((char *)a, (char *)b, strlen ((char *)a)) < 0 ? 1 : 0);
}

int char_compare_gt (void *a, void *b)
{
    return int_compare_gt (a, b);
}

int char_compare_lt (void *a, void *b)
{
    return int_compare_lt (a, b);
}

/*impose abstract type*/
comparator_t new_comparator (int (*compar)(void *arg1, void *arg2))
{
    return compar;
}