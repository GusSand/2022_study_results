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
// load the list from file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
// the loaded values are added to the end of the list
int list_load(node **head, char *filename)
{
    if (head == NULL || filename == NULL) {
        return EXIT_FAILURE;
    }
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        return EXIT_FAILURE;
    }

    int start = 1;
    // Get position of end of list
    node *curr = *head;
    while (curr) {
        curr = curr->next;
        start++;
    }
    int i = start;
    float price;
    int quantity;
    char *item_name = NULL;
    char *line = NULL;
    size_t linecap = 0;
    while (getline(&line, &linecap, fp) > 0) {
        item_name = realloc(item_name, linecap);
        int n = sscanf(line, "%[^,],%f,%d", item_name, &price, &quantity);
        if (n != 3 || 
            ref_list_add_item_at_pos(head, item_name, price, quantity, i) == EXIT_FAILURE) {
            goto cleanup_failure;
        }
        i++;
    }

    free(item_name);
    free(line);
    fclose(fp);
    return EXIT_SUCCESS;

cleanup_failure:
    for (int j = i-1; j >= start; j--) {
        ref_list_remove_item_at_pos(head, j);
    }
    free(item_name);
    free(line);
    fclose(fp);
    return EXIT_FAILURE;
}
