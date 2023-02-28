#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "list.h"

#ifdef UNIT_TESTING
/* Redirect printf to a function in the test application so it's possible to
 * test the standard output. You can ignore this; it's not relevant to the
 * assignment. */
#ifdef printf
#undef printf
#endif /* printf */
extern int test_printf(const char *format, ...);
#define printf test_printf
#endif

#define MAX_ITEM_PRINT_LEN 100

// Note: All list_ functions should return a status code
// EXIT_FAILURE or EXIT_SUCCESS to indicate whether the operation was 

#include "reflist.h"












struct node_sort_data {
    node *node;
    int pos;
};


// compare function for qsort (sort on item name)
int node_sort_compare(const void *a, const void *b)
{
    struct node_sort_data *data_a = (struct node_sort_data *)a;
    struct node_sort_data *data_b = (struct node_sort_data *)b;
    return strcmp(data_a->node->item_name, data_b->node->item_name);
}
// de-duplicate the list by combining items with the same name 
//    by adding their quantities
// The order of the returned list is undefined and may be in any order
int list_deduplicate(node **head) 
{
    if (head == NULL) {
        return EXIT_FAILURE;
    }
    struct node_sort_data *data = NULL;
    int len = 0;
    node *curr = *head;
    while (curr != NULL) {
        len++;
        curr = curr->next;
    }
    // Empty or singleton list is already deduplicated
    if (len == 0 || len == 1) {
        return EXIT_SUCCESS;
    }
    // Alloc the temp array for sorting
    data = malloc(sizeof(struct node_sort_data) * len);
    if (data == NULL) {
        return EXIT_FAILURE;
    }
    curr = *head;
    int i = 1;
    while (curr != NULL) {
        data[i-1].node = curr;
        data[i-1].pos = i;
        curr = curr->next;
        i++;
    }
    // Sort the array
    qsort(data, len, sizeof(struct node_sort_data), node_sort_compare);

    // Change the links to their sorted order
    *head = data[0].node;
    for (i = 0; i < len - 1; i++) {
        data[i].node->next = data[i+1].node;
    }
    data[len-1].node->next = NULL;
    free(data);

    // Merge the sorted array
    curr = *head;
    while (curr->next != NULL) {
        if (strcmp(curr->item_name, curr->next->item_name) == 0) {
            node *temp = curr->next;
            curr->quantity += curr->next->quantity;
            curr->next = curr->next->next;
            free(temp->item_name);
            free(temp);
        } else {
            curr = curr->next;
        }
    }
    return EXIT_SUCCESS;
}
