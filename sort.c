/***************************************************************

Sorting library that implements various generic sorting 
algorithms

***************************************************************/

#include <sort.h>
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

/** Bubble sort
* @param list   -- the list to be sorted
* @param compar -- the comparison function to compare the items in the list
* @param size   -- the size in bytes of the items in the list
* @param n_mem  -- the number of members in the list
*/
void bubble_sort (void *list, int (compar)(void *arg1, void *arg2), size_t size, size_t n_mem)
{
    int i, j;

    n_mem = n_mem * size;

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
    int n1 = ((mid - base) + 1) * size;
    int n2 = (last - mid) * size;
    int i, j, k;

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
    srand (time (NULL));

    while (!sorted (list, compar, size, n_mem)){
        index1 = (rand () % n_mem) * size;
        index2 = (rand () % n_mem) * size;
        swap (list + index1, list + index2, size);
    }
}

// helper function to bogo_sort ()
int sorted (void *list, int (*compar)(void *arg1, void *arg2), size_t size, size_t n_mem)
{
    int i;
    size_t max = size * n_mem;

    for (i = 0; i < max - size; i += size){
        if (!compar (list + i, list + i + size)){
            return 0;
        }
    }

    return 1;
}

/** Count Sort
* @param list  -- the list to be sorted
* @param n_mem -- the number of items in the list
*/
void count_sort (int *list, size_t n_mem)
{
    int length = max_of_list (list, n_mem);
    int tmp[length + 1];
    memset (tmp, 0, sizeof (int) * length);

    int i, j, k;

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
    int i;
    int max = list[0];

    for (i = 1; i < n_mem; i++){
        if (max < list[i])
            max = list[i];
    }

    return max;
}
