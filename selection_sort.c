#include <sort.h>

/** Select Sort
* @param list   -- the list to be sorted
* @param compar -- the comparison function to compare items in the list
* @param size   -- the size in bytes of the items in the list
* @param n_mem  -- the number of items in the list
*/
void select_sort (void *list, int (*compar)(void *arg1, void *arg2), size_t size, size_t n_mem)
{
    int i, j, min;
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
