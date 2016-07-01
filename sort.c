/***************************************************************
Sorting library that implements various generic and non-
generic algorithms
Authors: Christian Tuton, Elias Flores
File: sort.c
Date: Summer 2016
***************************************************************/

#include "sort.h"
#include <stdio.h>
#include <time.h>

/** Generic swap function
* @param x    -- the first value to be swapped
* @param y    -- the second value to be swapped
* @param size -- the size in bytes of x and y
*/
void swap (void *x, void *y, size_t size)
{
    byte tmp[size];
    memcpy (tmp, x, size);
    memcpy (x, y,   size);
    memcpy (y, tmp, size);
}

// helper function to bogo sort
void seed_rand ()
{
    #ifndef _RAND_
    srand (time (NULL));
    #endif
}

/** Bubble sort
* @param list   -- the list to be sorted
* @param compar -- the comparison function to compare the items in the list
* @param size   -- the size in bytes of the items in the list
* @param n_mem  -- the number of members in the list
*/
void bubble_sort (void *list, int (compar)(void *arg1, void *arg2), size_t size, size_t n_mem)
{
    size_t i, j;

    n_mem *= size;

    for (i = 0; i < n_mem; i += size){
        for (j = n_mem - size; j > i; j -= size){
            if (compar (list + i, list + j)) {
                swap (list + i, list + j, size);
            }
        }
    }
}

/** Merge Sort
* @param list   -- the list to be sorted
* @param compar -- the comparison function to compare items in the list
* @param size   -- the size in bytes of the items in the list
* @param base   -- the starting index of the list
* @param n_mem  -- the number of items in the list (not the last index!)
*/
void merge_sort (void *list, int (*compar)(void *arg1, void *arg2), size_t size, size_t base, size_t n_mem)
{
    if (base < n_mem){
        size_t q = (base + n_mem) / 2;
        merge_sort (list, compar, size, base, q);
        merge_sort (list, compar, size, q + 1, n_mem);
        merge (list, compar, size, base, q, n_mem);
    }
}

// helper function to merge_sort ()
void merge (void *list, int (*compar)(void *arg1, void *arg2), size_t size, size_t base, size_t mid, size_t last)
{
    size_t n1 = ((mid - base) + 1) * size;
    size_t n2 = (last - mid) * size;
    size_t i, j, k;

    mid *= size;
    base *= size;
    last *= size;

    void *left = malloc (n1);  memset (left, 0, n1);
    void *right = malloc (n2); memset (right, 0, n2);

    for (i = 0; i < n1; i += size)
        memcpy (left + i, list + base + i, size);
    for (i = 0; i < n2; i += size)
        memcpy (right + i, list + mid + i + size, size);

    i = j = 0;

    for (k = base; k <= last; k += size){
        if (i == n1){
            memcpy (list + k, right + j, size);
            j += size;
        }
        else if (j == n2){
            memcpy (list + k, left + i, size);
            i += size;
        }
        else if (compar (left + i, right + j)){
            memcpy (list + k, left + i, size);
            i += size;
        }
        else{
            memcpy (list + k, right + j, size);
            j += size;
        }
}

    free (left);
    free (right);
}

/** Bogo Sort
* @param list   -- the list to be sorted
* @param compar -- the comparison function to compare items in the list
* @param size   -- the size in bytes of the items in the list
* @param n_mem  -- the number of items in the list
*/
void bogo_sort (void *list, int (*compar)(void *arg1, void *arg2), size_t size, size_t n_mem)
{
    seed_rand ();

    #ifndef _RAND_
    #define _RAND_
    #endif

    size_t index1, index2;

    while (!sorted (list, compar, size, n_mem)){
        index1 = (rand () % n_mem) * size;
        index2 = (rand () % n_mem) * size;
        swap (list + index1, list + index2, size);
    }
}

// helper function to bogo_sort ()
int sorted (void *list, int (*compar)(void *arg1, void *arg2), size_t size, size_t n_mem)
{
    size_t i;
    size_t max = size * n_mem;

    for (i = 0; i < max - size; i += size){
        if (!compar (list + i, list + i + size)){
            return 0;
        }
    }

    return 1;
}

/** Counting Sort
* @param list  -- the list to be sorted
* @param n_mem -- the number of items in the list
*/
void count_sort (int *list, size_t n_mem)
{
    size_t length = max_of_list (list, n_mem);
    int tmp[length + 1];
    memset (tmp, 0, sizeof (int) * length);

    size_t i, j, k;

    for (i = 0; i < length; i++){
        tmp[list[i]]++;
    }

    for (i = 0, k = 0; i < length + 1; i++){
        for (j = 0; j < tmp[i]; j++){
            *(list + k) = i;
            if (k < n_mem) k++;
        }
    }
}

//helper function to count_sort ()
int max_of_list (int *list, size_t n_mem)
{
    size_t i;
    int max = list[0];

    for (i = 1; i < n_mem; i++){
        if (max < list[i])
            max = list[i];
    }

    return max;
}

/** Selection Sort
* @param list   -- the list to be sorted
* @param compar -- the comparison function to compare items in the list
* @param size   -- the size in bytes of the items in the list
* @param n_mem  -- the number of items in the list
*/
void select_sort (void *list, int (*compar)(void *arg1, void *arg2), size_t size, size_t n_mem)
{
    size_t i, j, min;
    n_mem *= size;

    for (i = 0; i < n_mem; i += size){
        for (j = i + size, min = i; j < n_mem; j += size){
            if (compar (list + min, list + j)){
                min = j;
            }
        }
        swap (list + min, list + i, size);
    }
}

/** Heap Sort
* @param list   -- the list to be sorted
* @param compar -- the comparison function to compare items in the list
* @param size   -- the size in bytes of the items in the list
* @param n_mem  -- the number of items in the list
*/
void heap_sort (void *list, int (*compar)(void *arg1, void *arg2), size_t size, size_t n_mem)
{
    heap_t heap = new_heap (list, compar, size, n_mem);
    size_t i, j;

    for (i = n_mem * size - size, j = 0; i >= 0; i -= size, j += size){
        memcpy (list + j, heap, size); // put first element from heap onto list
        memcpy (heap, heap + i, size); // replace top of heap with bottom

        heap = new_heap (heap, compar, size, n_mem - (j / size));
    }
    
    free (heap);
}

/*creates new heap with order imposed by compar*/
heap_t new_heap (void *list, int (*compar)(void *arg1, void *arg2), size_t size, size_t n_mem)
{
    size_t i, j;

    heap_t heap = malloc (n_mem * size);
    assert (heap);

    for (i = 0; i < n_mem * size; i += size){
        memcpy (heap + i, list + i, size);
        j = i / size;
        while ((j - 1) / 2 >= 0 && j - 1 != -1){
            if (compar (heap + j * size, heap + ((j - 1) / 2) * size))
                swap (heap + j * size, heap + ((j - 1) / 2) * size, size);
            j = (j - 1) / 2;
        }
    }

    return heap;
}

/** Cocktail Shaker Sort
* @param list   -- the list to be sorted
* @param compar -- the comparison function to compare items in the list
* @param size   -- the size in bytes of the items in the list
* @param n_mem  -- the number of items in the list
*/
void cocktail_sort (void *list, int (*compar)(void *arg1, void *arg2), size_t size, size_t n_mem)
{
    size_t i,j,k;
    n_mem *= size;
    size_t mid = n_mem / 2;

    for (i = 0; i < mid; i += size){
        for (j = i; j < n_mem - size - i; j += size){
            if (compar (list + j, list + j + size)){
                swap (list + j, list + j + size, size);
            }
        }
        for (k = j - size; k > i; k -= size){
            if (!compar (list + k, list + k - size)){
                swap (list + k, list + k - size, size);
            }
        }
    }
}

/** Comb Sort
* @param list   -- the list to be sorted
* @param compar -- the comparison function to compare items in the list
* @param size   -- the size in bytes of the items in the list
* @param n_mem  -- the number of items in the list
*/
void comb_sort (void *list, int (*compar)(void *arg1, void *arg2), size_t size, size_t n_mem)
{
    size_t gap = n_mem * size;
    size_t i;
    float shrink = 1.3; //suggested shrink factor

    while (gap != size){
        gap = size * ((size_t)(gap / (size * shrink)));
        if (gap < size)
            gap = size;

        for (i = 0; i + gap < n_mem * size; i += size){
            if (compar (list + i, list + i + gap))
                swap (list + i, list + i + gap, size);
        }
    }
}

/** Quicksort
* @param list   -- the list to be sorted
* @param compar -- the comparison function to compare items in the list
* @param size   -- the size in bytes of the items in the list
* @param base   -- the starting index of the list
* @param n_mem  -- the number of items in the list (not the last index!)
*/
void quicksort (void *list, int (*compar)(void *arg1, void *arg2), size_t size, size_t base, size_t n_mem)
{
    if (base < n_mem) {
        int p = partition(list, compar, size, base, n_mem);
        quicksort(list, compar, size, base, p);
        quicksort(list, compar, size, p + 1, n_mem);
    }
}

// Helper function for quicksort. NOTE will observe worst behavior for already sorted lists
// TODO: Optimize function for worst-case
int partition(void *list, int (*compar)(void *arg1, void *arg2), size_t size, size_t base, size_t n_mem)
{
    int i = base;
    int j = n_mem - 1;

    while(i != j) {
        for (; j > i; j--) {
            if (compar(list + (size * i), list + (size * j))) {
                swap(list + (i * size), list + (j * size), size);
                break;
            }
        }

        for (; i < j; i++) {
            if (compar(list + (size * i), list + (size * j))) {
                swap(list + (i * size), list + (j * size), size);
                break;
            }
        }
    }
    return j;
}
